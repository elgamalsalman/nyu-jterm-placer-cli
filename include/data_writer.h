#include "student.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#ifndef DATA_WRITER_H 
#define DATA_WRITER_H

class Data_writer {
	void write_matching(std::ostream &, std::vector<Student> &);
	public:
		void write_matching(std::string, std::vector<Student> &);
		void write_matching(std::vector<Student> &);
};

#endif
