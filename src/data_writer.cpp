#include "../include/student.h"
#include "../include/data_writer.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>

void Data_writer::write_matching(std::ostream &s, std::vector<Student> &students) {
	for (Student &student : students) {
		s << std::setw(15) << std::left << student.name << ' ' << std::setw(15) << std::left << student.placement << std::endl;
	}
}

void Data_writer::write_matching(std::string file_name, std::vector<Student> &students) {
	std::ofstream file(file_name);
	write_matching(file, students);
	file.close();
}

void Data_writer::write_matching(std::vector<Student> &students) {
	write_matching(std::cout, students);
}
