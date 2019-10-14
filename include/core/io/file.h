#pragma once

#include <cstdint>
#include <fstream>
#include <string>
#include <vector>

class File {
 public:
  File() = default;
  File(const std::string& path);
  File(const File& other);
  File(File&& other);
  ~File();

  bool IsOpen();

  bool Write(const std::string& dat);
  bool Append(const std::string& dat);

  std::string ReadString();
  std::vector<std::string> ReadLines();

  File& operator=(File other);

  friend void swap(File& first, File& second);

 private:
  std::fstream file_stream;
};
