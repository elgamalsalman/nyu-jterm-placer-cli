#include "../include/student.h"

#include <iostream>
#include <string>

std::ostream& operator<<(std::ostream& os, const Student &student) {
  os << student.name << ", ";
  os << std::to_string(student.year) << ", ";
  os << "[";
  for (int i = 0; i < (int)student.choices.size(); i++) {
    if (i) os << ", ";
    os << student.choices[i];
  }
  os << "]";
  os << ", " << student.placement;
  os << "}";

  return os;
}
