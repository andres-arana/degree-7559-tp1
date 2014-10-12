#include "syscalls/file.h"
#include "raii/file_lock.h"

using namespace raii;

file_lock::file_lock()
  : file_descriptor(-1) {

  }

file_lock::file_lock(int file_descriptor)
  : file_descriptor(file_descriptor) {
	fl.l_whence = SEEK_SET;
	fl.l_start = 0;
	fl.l_len = 0;
    syscalls::flock(file_descriptor, fl);
  }

file_lock::file_lock(file_lock &&other)
  : file_lock(other.file_descriptor) {
    other.file_descriptor = -1;
  }

file_lock &file_lock::operator=(file_lock &&other) {
  syscalls::funlock(file_descriptor, fl);
  file_descriptor = other.file_descriptor;
  other.file_descriptor = -1;
  return *this;
}

file_lock::~file_lock() {
  syscalls::funlock(file_descriptor, fl);
}

