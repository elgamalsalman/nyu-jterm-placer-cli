#include <string>

#ifndef COURSE_H 
#define COURSE_H 

class Course {
	public:
		const std::string id;
		const int cap;
		int enrollment_count;

		Course(std::string _id, int _cap)
			: id{_id}
			, cap{_cap}
		  , enrollment_count{0}	{}
};

#endif
