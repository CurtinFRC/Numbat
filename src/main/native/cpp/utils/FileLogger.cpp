// Copyright (c) 2023-2024 CurtinFRC
// Open Source Software, you can modify it according to the terms
// of the MIT License at the root of this project

#include "utils/FileLogger.h"

utils::LogFile::LogFile(std::string path) : _path(path) {
  _file.open(_path);
}

utils::LogFile::LogFile() : _path("log.txt") {
  _file.open(_path);
}

void utils::LogFile::UpdateData(std::string key, std::string value) {
  _data[key] = value;
}

void utils::LogFile::Write() {
  _file << _data;
}

void utils::LogFile::Close() {
  _file.close();
}
