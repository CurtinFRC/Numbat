// Copyright (c) 2023-2024 CurtinFRC
// Open Source Software, you can modify it according to the terms
// of the MIT License at the root of this project

#pragma once

#include <string>
#include <vector>

namespace loggers {
enum class MetaData {
  kProjectName,
  // kBuildDate,
  kGitHash,
  // kGitDate,
  kGitBranch,
};

struct StoredMetaData {
  std::string projectName;
  std::string gitHash;
  std::string gitBranch;
};

class SingletonLogger {
 public:
  static SingletonLogger* GetInstance();
  void RecordMetadata(MetaData field, std::string value);

 private:
  std::vector<MetaData> loggedMetaData;
  StoredMetaData storedMetaData;
};
}  // namespace loggers
