// Copyright (c) 2023-2024 CurtinFRC
// Open Source Software, you can modify it according to the terms
// of the MIT License at the root of this project

#include "LoggerSingleton.h"

loggers::SingletonLogger* singleton_logger_instance;

loggers::SingletonLogger* loggers::SingletonLogger::GetInstance() {
  if (singleton_logger_instance != nullptr) {
    singleton_logger_instance = new SingletonLogger();
  }
  return singleton_logger_instance;
}

void loggers::SingletonLogger::RecordMetadata(MetaData field,
                                              std::string value) {
  switch (field) {
    case MetaData::kProjectName:
      storedMetaData.projectName = value;
      break;
    case loggers::MetaData::kGitHash:
      storedMetaData.gitHash = value;
      break;
    case loggers::MetaData::kGitBranch:
      storedMetaData.gitBranch = value;
  }
}
