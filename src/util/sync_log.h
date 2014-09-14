#ifndef __UTIL_SYNC_LOG_H_INCLUDED__
#define __UTIL_SYNC_LOG_H_INCLUDED__

#include <string>
#include "auto_file.h"

namespace util {

  class sync_log {
    private:
      auto_file file;

    public:
      sync_log();

      void info(const std::string &message);

      void warn(const std::string &message);

      void debug(const std::string &message);

      void error(const std::string &message);
  };

};

#endif
