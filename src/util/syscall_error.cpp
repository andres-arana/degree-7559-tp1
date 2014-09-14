#include <sstream>
#include <errno.h>
#include "syscall_error.h"

using namespace util;
using namespace std;

namespace {
  string build_message(const string &syscall) {
    stringstream error;
    error << "La syscall " << syscall << " fallo con error = " << errno;
    return error.str();
  }
};

syscall_error::syscall_error(const string &syscall) : 
  runtime_error(::build_message(syscall)){
  
}

