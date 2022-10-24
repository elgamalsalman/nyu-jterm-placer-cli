#include "../include/student.h"
#include "../include/course.h"
#include "../include/data_reader.h"

#include <sstream>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

void Data_reader::read_students(std::string file_name, std::vector<Student> &students) {
	std::ifstream file(file_name);

	std::string name;
	int year;
	bool is_first_student = true;
	while (file >> name >> year) {
		file.ignore(); // ignore '\n'

		std::string choices_string = "";
		getline(file, choices_string);
		std::stringstream ss(choices_string);

		std::string choice;
		std::vector<std::string> choices;
		while (ss >> choice) {
			choices.push_back(choice);
			if (is_first_student) Student::choice_count++;
		}
		students.emplace_back(name, year, choices);
		is_first_student = false;
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
