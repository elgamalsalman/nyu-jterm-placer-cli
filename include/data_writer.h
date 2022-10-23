#include "student.h"

#include <string>
#include <vector>

#ifndef DATA_WRITER_H 
#define DATA_WRITER_H

class Data_writer {
	public:
		void write_matching(std::string, std::vector<Student> &);
};

#endif
