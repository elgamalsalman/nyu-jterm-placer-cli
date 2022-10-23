#include "../include/student.h"
#include "../include/data_writer.h"

#include <fstream>
#include <string>
#include <vector>
#include <iomanip>

void Data_writer::write_matching(std::vector<Student> &students) {
	std::ofstream file(file_name);

	for (Student &student : students) {
		file << std::setw(15) << std::left << student.name << ' ' << std::setw(15) << std::left << student.placement << std::endl;
	}

	file.close();
}
