#include "../include/student.h"
#include "../include/course.h"
#include "../include/matcher.h"
#include "../include/data_reader.h"
#include "../include/data_writer.h"

#include <iostream>
#include <vector>

int main(int argc, char *argv[]) {
	if (argc < 3) {
		std::cerr << "Too few arguments! Arguments should be : students_input_file courses_input_file (output_file)" << std::endl;
		exit(-1);
	}

	try {
		// declare student and course vectors
		std::vector<Student> students;
		std::vector<Course> courses;

		// instantiate data reader and read student and course data
		Data_reader dr;
		dr.read_students(argv[1], students);
		dr.read_courses(argv[2], courses);

		// create matchings, throws error for invalid choices
		Matcher matcher;
		int cost = matcher.match(students, courses);

		// instantiate data writer and write matching data
		Data_writer dw;
		if (argc <= 3) {
			dw.write_matching(students);
		} else {
			dw.write_matching(argv[3], students);
		}
		std::cout << "Successful matching with a cost of " << cost << std::endl;
	} catch (const std::exception &e) {
		std::cerr << "There was an error : " << e.what() << std::endl;
		exit(-1);
	}
}
