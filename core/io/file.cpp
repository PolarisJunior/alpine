#include "file.h"

#include <sstream>

File::File(const std::string& path) : file_stream(path) {}

File::~File() {
  file_stream.close();
}

bool File::IsOpen() {
  return file_stream.is_open();
}

std::string File::ReadString() {
  std::stringstream ss;
  char c;

  while (file_stream.get(c)) {
    ss << c;
  }
  return ss.str();
}