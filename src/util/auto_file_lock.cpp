#include "auto_file_lock.h"
#include "syscall_error.h"
#include <sys/file.h>

using namespace util;

auto_file_lock::auto_file_lock(int file_descriptor)
  : file_descriptor(file_descriptor) {
    if (flock(this->file_descriptor, LOCK_EX)) {
      throw syscall_error("flock", "lock)");
    }
  }

auto_file_lock::~auto_file_lock() {
  if (flock(this->file_descriptor, LOCK_UN)) {
    throw syscall_error("flock", "unlock");
  }
}

