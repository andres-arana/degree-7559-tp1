#ifndef __UTIL__SYNC_LOG_H_INCLUDED__
#define __UTIL__SYNC_LOG_H_INCLUDED__

#include <string>
#include "raii/file.h"
#include "util/string.h"

namespace util {
  class sync_log {
    public:
      enum class level : unsigned int {
        DEBUG = 0, WARN = 1, INFO = 2, ERROR= 3
      };

      sync_log(const std::string &name);

      sync_log(const sync_log &other) = delete;
      sync_log &operator=(const sync_log &other) = delete;

      sync_log(sync_log &&other) = delete;
      sync_log &operator=(sync_log &&other) = delete;

      void set_level(level value);

      void set_level(unsigned int value);

      unsigned int get_level() const;

      void info(const std::string &message);

      template<typename... Ts>
        void info(const std::string &format, const Ts&... ts) {
          if (log_level <= level::INFO) {
            info(sformat(format, ts...));
          }
        }

      void warn(const std::string &message);

      template<typename... Ts>
        void warn(const std::string &format, const Ts&... ts) {
          if (log_level <= level::WARN) {
            warn(sformat(format, ts...));
          }
        }

      void debug(const std::string &message);

      template<typename... Ts>
        void debug(const std::string &format, const Ts&... ts) {
          if (log_level <= level::DEBUG) {
            debug(sformat(format, ts...));
          }
        }

      void error(const std::string &message);

      template<typename... Ts>
        void error(const std::string &format, const Ts&... ts) {
          if (log_level <= level::ERROR) {
            error(sformat(format, ts...));
          }
        }

    private:
      raii::file file;
      std::string name;
      level log_level;
  };
}

#endif
