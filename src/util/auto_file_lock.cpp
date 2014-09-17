#include "auto_file_lock.h"
#include "syscall_error.h"
#include <sys/file.h>

using namespace util;

namespace {
  void do_lock(int file_descriptor) {
    if (file_descriptor > 0) {
      if (flock(file_descriptor, LOCK_EX)) {
        throw syscall_error("flock", "lock)");
      }
    }
  }

  void do_unlock(int file_descriptor) {
    if (file_descriptor > 0) {
      if (flock(file_descriptor, LOCK_UN)) {
        throw syscall_error("flock", "unlock");
      }
    }
  }
};

auto_file_lock::auto_file_lock() 
  : file_descriptor(-1) {

  }

auto_file_lock::auto_file_lock(int file_descriptor)
  : file_descriptor(file_descriptor) {
    ::do_lock(this->file_descriptor);
  }

auto_file_lock::auto_file_lock(auto_file_lock &&other)
  : file_descriptor(other.file_descriptor) {
    other.file_descriptor = -1;
  }

auto_file_lock &auto_file_lock::operator=(auto_file_lock &&other) {
  ::do_unlock(this->file_descriptor);
  this->file_descriptor = other.file_descriptor;
  other.file_descriptor = -1;
  return *this;
}

auto_file_lock::~auto_file_lock() {
  ::do_unlock(this->file_descriptor);
}

