#include "Vector2D.h"
#include <iostream>
#include <fstream>

std::ostream& operator<<(std::ostream& stream_os, const Vector2D& rhs){
  stream_os << " " << rhs.x << " " << rhs.y;

  return stream_os;
}
  
std::ifstream& operator>>(std::ifstream& stream_ifs, Vector2D& lhs){
  stream_ifs >> lhs.x >> lhs.y;

  return stream_ifs;
}