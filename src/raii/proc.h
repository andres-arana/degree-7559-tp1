#ifndef __RAII__PROC_H_INCLUDED__
#define __RAII__PROC_H_INCLUDED__

#include <sys/types.h>
#include <signal.h>
#include <string>
#include <vector>
#include "util/string.h"

namespace raii {
  class proc {
    public:
      proc();

      explicit proc(
          bool interrupt,
          const std::string &command);

      explicit proc(
          bool interrupt,
          const std::string &command,
          const std::vector<std::string> &args);

      template<typename... Ts>
      explicit proc(
          bool interrupt,
          const std::string &command,
          const Ts&... ts)
      : proc(interrupt, command, util::svector(ts...)) { }

      proc(const proc &other) = delete;
      proc &operator=(const proc &other) = delete;

      proc(proc &&other);
      proc &operator=(proc &&other);

      pid_t pid() const;

      void signal(int signal);

      virtual ~proc();

    private:
      pid_t process_id;
      bool interrupt;
      std::string command;
  };
}

#endif
