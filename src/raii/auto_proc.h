#ifndef __RAII__AUTO_PROC_H_INCLUDED__
#define __RAII__AUTO_PROC_H_INCLUDED__

#include <sys/types.h>
#include <signal.h>
#include <string>
#include <vector>
#include "util/string.h"

namespace raii {
  class auto_proc {
    public:
      auto_proc();

      explicit auto_proc(
          bool interrupt,
          const std::string &command);

      explicit auto_proc(
          bool interrupt,
          const std::string &command,
          const std::vector<std::string> &args);

      template<typename... Ts>
      explicit auto_proc(
          bool interrupt,
          const std::string &command,
          const Ts&... ts)
      : auto_proc(interrupt, command, util::svector(ts...)) { }

      auto_proc(const auto_proc &other) = delete;
      auto_proc &operator=(const auto_proc &other) = delete;

      auto_proc(auto_proc &&other);
      auto_proc &operator=(auto_proc &&other);

      pid_t pid() const;

      void signal(int signal);

      ~auto_proc();

    private:
      pid_t process_id;
      bool interrupt;
  };
}

#endif
