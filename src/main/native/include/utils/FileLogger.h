// Copyright (c) 2023-2024 CurtinFRC
// Open Source Software, you can modify it according to the terms
// of the MIT License at the root of this project

#pragma once

#include <wpi/json.h>

#include <fstream>
#include <iostream>
#include <string>

namespace utils {
class LogFile {
 public:
  explicit LogFile(std::string path);
  LogFile();
  void UpdateData(std::string key, std::string value);
  void Write();
  void Close();

  wpi::json _data;

 private:
  std::string _path;
  std::ofstream _file;
};
}  // namespace utils
