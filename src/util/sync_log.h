#ifndef __UTIL_SYNC_LOG_H_INCLUDED__
#define __UTIL_SYNC_LOG_H_INCLUDED__

#include <string>
#include "auto_file.h"

namespace util {

  class sync_log {
    private:
      auto_file file;
      std::string name;

    public:
      sync_log(const std::string &name);

      sync_log(const sync_log &other) = delete;
      sync_log &operator=(const sync_log &other) = delete;

      sync_log(sync_log &&other);
      sync_log &operator=(sync_log &&other);

      void info(const std::string &message);

      void warn(const std::string &message);

      void debug(const std::string &message);

      void error(const std::string &message);
  };

};

#endif
