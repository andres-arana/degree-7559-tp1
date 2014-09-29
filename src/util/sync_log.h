#ifndef __UTIL_SYNC_LOG_H_INCLUDED__
#define __UTIL_SYNC_LOG_H_INCLUDED__

#include <string>
#include "util/auto_file.h"
#include "util/string.h"

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

      void separator();

      void info(const std::string &message);

      template<typename... Ts>
      void info(const std::string &format, const Ts&... ts) {
        info(sformat(format, ts...));
      }

      void warn(const std::string &message);

      template<typename... Ts>
      void warn(const std::string &format, const Ts&... ts) {
        warn(sformat(format, ts...));
      }

      void debug(const std::string &message);

      template<typename... Ts>
      void debug(const std::string &format, const Ts&... ts) {
        debug(sformat(format, ts...));
      }

      void error(const std::string &message);

      template<typename... Ts>
      void error(const std::string &format, const Ts&... ts) {
        error(sformat(format, ts...));
      }
  };

};

#endif
