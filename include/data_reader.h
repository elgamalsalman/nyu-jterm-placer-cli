#include "student.h"
#include "course.h"

#include <string>
#include <vector>

#ifndef DATA_READER_H 
#define DATA_READER_H 

class Data_reader {
	public:
		void read_students(std::string, std::vector<Student> &);
		void read_courses(std::string, std::vector<Course> &);
};

#endif
