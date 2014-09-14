#include <sstream>
#include <errno.h>
#include "syscall_error.h"

using namespace util;
using namespace std;

namespace {
  string build_message(const string &syscall, const string &context) {
    stringstream error;
    error << "La syscall " << syscall << " ";
    if (context != "") {
      error << "(" << context << ") ";
    }
    error << "fallo con errno [" << errno << "]";

    return error.str();
  }
};

syscall_error::syscall_error(const string &syscall, const string &context)
  : runtime_error(::build_message(syscall, context)) {

  }

syscall_error::syscall_error(const string &syscall)
  : runtime_error(::build_message(syscall, "")) {

  }

