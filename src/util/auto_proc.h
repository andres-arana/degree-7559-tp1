#ifndef __UTIL__AUTO_PROC_H_INCLUDED__
#define __UTIL__AUTO_PROC_H_INCLUDED__

#include <sys/types.h>
#include <string>
#include <vector>

namespace util {
  class auto_proc {
    private:
      pid_t process_id;

    public:
      auto_proc();
      explicit auto_proc(
          const std::string &command,
          const std::vector<std::string> &args);

      auto_proc(const auto_proc &other) = delete;
      auto_proc &operator=(const auto_proc &other) = delete;

      auto_proc(auto_proc &&other);
      auto_proc &operator=(auto_proc &&other);

      pid_t pid() const;

      ~auto_proc();
  };
};

#endif
