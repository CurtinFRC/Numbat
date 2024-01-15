// Copyright (c) 2023-2024 CurtinFRC
// Open Source Software, you can modify it according to the terms
// of the MIT License at the root of this project

#include "utils/FileLogger.h"

numbat::utils::LogFile::LogFile(std::string path) : _path(path) {
  _file.open(_path);
}

numbat::utils::LogFile::LogFile() : _path("log.txt") {
  _file.open(_path);
}

void numbat::utils::LogFile::UpdateData(std::string key, std::string value) {
  _data[key] = value;
}

void numbat::utils::LogFile::Write() {
  _file << _data;
}

void numbat::utils::LogFile::Close() {
  _file.close();
}
