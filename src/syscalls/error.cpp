#include "syscalls/error.h"
#include "util/string.h"
#include <errno.h>

using namespace std;
using namespace syscalls;

error::error(const string &syscall, const string &context)
  : runtime_error(util::sformat("La syscall $ ($) falló con errno [$]",
        syscall, context, errno)) {

  }

error::error(const string &syscall)
  : error(syscall, "") {

  }
