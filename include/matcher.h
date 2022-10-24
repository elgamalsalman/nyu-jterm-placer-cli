#include "student.h"
#include "course.h"

#include <vector>

#ifndef MATCHER_H 
#define MATCHER_H 

class Matcher {
	public:
		struct Edge {
			int dest, cap, cost, rev, flow = 0;
			friend std::ostream& operator<<(std::ostream& os, const Edge &edge);
		};

		int mcmf(int, int, int, std::vector<std::vector<Edge>> &);

		int match(std::vector<Student> &, std::vector<Course> &);
};

#endif
