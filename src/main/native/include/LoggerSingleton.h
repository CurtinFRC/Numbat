#pragma once

#include <string>
#include <vector>

namespace loggers {
  enum class MetaData {
    kProjectName,
    //kBuildDate,
    kGitHash,
    //kGitDate,
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
}
