#ifndef __UTILS__SYSCALL_ERROR_H_INCLUDED__
#define __UTILS__SYSCALL_ERROR_H_INCLUDED__

#include <stdexcept>
#include <string>

namespace util {

  class syscall_error : public std::runtime_error {
    public:
      explicit syscall_error(
          const std::string &syscall);

      explicit syscall_error(
          const std::string &syscall,
          const std::string &context);
  };

};

#endif
