#ifndef __SYSCALLS__INTERRUPT_H_INCLUDED__
#define __SYSCALLS__INTERRUPT_H_INCLUDED__

#include <stdexcept>
#include <string>

namespace syscalls {
  class interrupt : public std::runtime_error {
    public:
      explicit interrupt(
          const std::string &syscall);

      explicit interrupt(
          const std::string &syscall,
          const std::string &context);
  };

  void check_interrupt(const std::string &syscall);

  void check_interrupt(
      const std::string &syscall,
      const std::string &context);
}

#endif
