#include "../include/student.h"
#include "../include/course.h"
#include "../include/matcher.h"

#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <set>
#include <cassert>

int Matcher::match(std::vector<Student> &students, std::vector<Course> &courses) {
	// curate a list of all possible courses
	std::set<std::string> course_ids;
	for (Course course : courses) {
		course_ids.insert(course.id);
	}

	// validate all students' choices
	for (Student student : students) {
		for (std::string choice : student.choices) {
			bool is_valid_course = (course_ids.count(choice) == 1);

			if (!is_valid_course) {
				throw "Invalid choice exception";
				exit(-1);
			}
		}
	}

	// construct the graph
	const int student_count = (int)students.size();
	const int course_count = (int)courses.size();
	const int node_count = student_count + course_count + 2;
	std::vector<std::vector<Edge>> adj;
	adj.assign(node_count, std::vector<Edge>());

	// add edges between student and course nodes
	for (int student_ind = 0; student_ind < student_count; student_ind++) {
		Student &student = students[student_ind];
		for (int i = 0; i < Student::choice_count; i++) {
			std::string course_id = student.choices[i];
			int course_ind = 0;
			for (; course_ind < course_count; course_ind++) {
				if (courses[course_ind].id == course_id) break;
			}

			assert(course_ind < course_count);

			course_ind += student_count;
			int ind = (int)adj[student_ind].size();
			int rev_ind = (int)adj[course_ind].size();
			int cost = i * i * student.year;
			adj[student_ind].push_back({course_ind, 1, cost, rev_ind});
			adj[course_ind].push_back({student_ind, 0, -cost, ind});
		}
	}

	// add edges from source to all student nodes
	const int source = student_count + course_count;
	for (int student_ind = 0; student_ind < student_count; student_ind++) {
		int ind = (int)adj[source].size();
		int rev_ind = (int)adj[student_ind].size();
		int cost = 0;
		adj[source].push_back({student_ind, 1, cost, rev_ind});
		adj[student_ind].push_back({source, 0, -cost, ind});
	}

	// add edges from all course nodes to the sink
	const int sink = student_count + course_count + 1;
	for (int course_ind = 0; course_ind < course_count; course_ind++) {
		int course_node = course_ind + student_count;
		int ind = (int)adj[course_node].size();
		int rev_ind = (int)adj[sink].size();
		int cap = courses[course_ind].cap;
		int cost = 0;
		adj[course_node].push_back({sink, cap, cost, rev_ind});
		adj[sink].push_back({course_node, 0, -cost, ind});
	}

	std::cerr << "// adj:-\n";
	for (int i = 0; i < node_count; i++) {
		std::cerr << "// " << i << ":";
		for (Edge e : adj[i]) {
			std::cerr << " " << e.dest;
		}
		std::cerr << std::endl;
	}

	// Minimum Cost Maximum Flow
	int total_cost = mcmf(node_count, source, sink, adj);

	// set placements and place unplaced students in empty course slots
	for (int student_ind = 0; student_ind < student_count; student_ind++) {
		Student &student = students[student_ind];
		bool is_placed = false;
		for (int edge_ind = 0; edge_ind < Student::choice_count; edge_ind++) {
			Edge &edge = adj[student_ind][edge_ind];

			if (!edge.flow) {
				is_placed = true;
				int placed_course_ind = edge.dest - student_count;
				Course &placed_course = courses[placed_course_ind];
				student.placement = placed_course.id;
				placed_course.enrollment_count++;
				break;
			}
		}

		// place unplaced students in empty course slots
		if (!is_placed) {
			for (int course_ind = 0; course_ind < course_count; course_ind++) {
				Course &course = courses[course_ind];
				if (course.enrollment_count < course.cap) {
					is_placed = true;
					student.placement = course.id;
					course.enrollment_count++;
					break;
				}
			}
		}

		assert(is_placed);
	}

	return total_cost;
}

int Matcher::mcmf(int n, int source, int sink, std::vector<std::vector<Edge>> &adj) {
	const int infinity = 1e9;
	std::vector<int> parent, dis, backedge_ind;

	// Single Source Shortest Paths (SSSP) algorithm using bellman-ford-moore to allow for negative edges
	auto sssp = [n, source, sink, &adj, &dis, &parent, &backedge_ind, infinity]() -> bool {
		dis.assign(n, infinity);
		parent.assign(n, -1);
		backedge_ind.assign(n, -1);
		std::vector<bool> in_q(n, false);
		std::queue<int> q;

		q.push(source);
		dis[source] = 0;

		while (!q.empty()) {
			int u = q.front(); q.pop();
			in_q[u] = false;
			int ind = 0;
			for (auto &[v, cap, cost, rev, _] : adj[u]) {
				if (cap > 0 && dis[v] > dis[u] + cost) {
					dis[v] = dis[u] + cost;
					parent[v] = u;
					backedge_ind[v] = rev;
					if (!in_q[v]) {
						in_q[v] = true;
						q.push(v);
					}
				}

				ind++;
			}
		}

		return (dis[sink] != infinity);
	};

	// Search for augmenting paths, the ford-fulkerson's method
	int total_flow = 0;
	int total_cost = 0;
	while (sssp()) {
		// calculate flow on the found shortest path
		int curr_flow = infinity;
		int curr = sink;
		while (curr != source) {
			int p = parent[curr];
			int rev_ind = backedge_ind[curr];
			int ind = adj[curr][rev_ind].rev;
			curr_flow = std::min(curr_flow, adj[p][ind].cap);
			curr = p;
		}

		// update flow along the found shortest path
		curr = sink;
		total_flow += curr_flow;
		total_cost += curr_flow * dis[sink];
		while (curr != source) {
			int p = parent[curr];
			int rev_ind = backedge_ind[curr];
			int ind = adj[curr][rev_ind].rev;
			adj[p][ind].cap -= curr_flow;
			adj[p][ind].flow += curr_flow;
			adj[curr][rev_ind].cap += curr_flow;
			adj[curr][rev_ind].flow -= curr_flow;
			curr = p;
		}
	}

	return total_cost;
}
