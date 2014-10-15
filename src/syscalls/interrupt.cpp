#include "syscalls/error.h"
#include "syscalls/interrupt.h"
#include "util/string.h"
#include <errno.h>

using namespace std;
using namespace syscalls;

interrupt::interrupt(const string &syscall, const string &context)
  : runtime_error(util::sformat("$ ($)",
        syscall, context)) {

  }

interrupt::interrupt(const string &syscall)
  : interrupt(syscall, "") {

  }

void syscalls::check_interrupt(const string &syscall) {
  syscalls::check_interrupt(syscall, "");
}

void syscalls::check_interrupt(const string &syscall, const string& context) {
  if (errno == EINTR) {
    throw syscalls::interrupt(syscall, context);
  } else {
    throw syscalls::error(syscall, context);
  }
}
