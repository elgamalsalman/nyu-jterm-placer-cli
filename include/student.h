#include <string>
#include <vector>

#ifndef STUDENT_H 
#define STUDENT_H 

class Student {
	public:
		const inline static int choice_count = 2;

		const std::string name;
		const int year;
		std::vector<std::string> choices;
		std::string placement;

		Student(std::string nm, int yr, std::vector<std::string> &ch) : name{nm}, year{yr}, choices{ch}, placement{""} {}

		friend std::ostream& operator<<(std::ostream& os, const Student &student);
};

#endif
