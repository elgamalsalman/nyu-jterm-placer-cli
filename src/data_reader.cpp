#include "../include/student.h"
#include "../include/course.h"
#include "../include/data_reader.h"

#include <fstream>
#include <string>
#include <vector>

void Data_reader::read_students(std::string file_name, std::vector<Student> &students) {
	std::ifstream file(file_name);

	std::string name;
	int year;
	while (file >> name >> year) {
		std::vector<std::string> choices;
		for (int i = 0; i < Student::choice_count; i++) {
			std::string choice;
			file >> choice;
			choices.push_back(choice);
		}
		students.emplace_back(name, year, choices);
	}

	file.close();
}

void Data_reader::read_courses(std::string file_name, std::vector<Course> &courses) {
	std::ifstream file(file_name);

	std::string id;
	int cap;
	while (file >> id >> cap) {
		courses.emplace_back(id, cap);
	}

	file.close();
}
