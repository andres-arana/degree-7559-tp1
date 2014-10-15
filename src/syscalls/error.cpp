#include "syscalls/error.h"
#include "util/string.h"
#include <errno.h>

using namespace std;
using namespace syscalls;

error::error(const string &syscall, const string &context)
  : runtime_error(util::sformat("Syscall $ ($) failed with errno [$]",
        syscall, context, errno)) {

  }

error::error(const string &syscall)
  : error(syscall, "") {

  }
