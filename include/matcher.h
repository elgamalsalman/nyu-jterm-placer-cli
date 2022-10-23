#include "student.h"
#include "course.h"

#include <vector>

#ifndef MATCHER_H 
#define MATCHER_H 

class Matcher {
	struct Edge {
		int dest, cap, cost, rev, flow = 0;
	};

	int mcmf(int, int, int, std::vector<std::vector<Edge>> &);

	public:
		int match(std::vector<Student> &, std::vector<Course> &);
};

#endif
