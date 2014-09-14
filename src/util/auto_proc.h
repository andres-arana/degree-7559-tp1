#ifndef __UTIL__AUTO_PROC_H_INCLUDED__
#define __UTIL__AUTO_PROC_H_INCLUDED__

#include <sys/types.h>
#include <string>

namespace util {
  class auto_proc {
    private:
      pid_t process_id;

    public:
      explicit auto_proc(
          const std::string &command);
      explicit auto_proc(
          const std::string &command, const std::string &arg1);
      explicit auto_proc(
          const std::string &command, const std::string &arg1,
          const std::string &arg2);
      explicit auto_proc(
          const std::string &command, const std::string &arg1,
          const std::string &arg2, const std::string &arg3);
      explicit auto_proc(
          const std::string &command, const std::string &arg1,
          const std::string &arg2, const std::string &arg3,
          const std::string &arg4);
      explicit auto_proc(
          const std::string &command, const std::string &arg1,
          const std::string &arg2, const std::string &arg3,
          const std::string &arg4, const std::string &arg5);

      pid_t pid() const;

      ~auto_proc();
  };
};

#endif
