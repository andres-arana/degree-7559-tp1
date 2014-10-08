#include "syscalls/file.h"
#include "raii/auto_file_lock.h"

using namespace raii;

auto_file_lock::auto_file_lock() 
  : file_descriptor(-1) {

  }

auto_file_lock::auto_file_lock(int file_descriptor)
  : file_descriptor(file_descriptor) {
    syscalls::flock(file_descriptor);
  }

auto_file_lock::auto_file_lock(auto_file_lock &&other)
  : file_descriptor(other.file_descriptor) {
    other.file_descriptor = -1;
  }

auto_file_lock &auto_file_lock::operator=(auto_file_lock &&other) {
  syscalls::funlock(file_descriptor);
  file_descriptor = other.file_descriptor;
  other.file_descriptor = -1;
  return *this;
}

auto_file_lock::~auto_file_lock() {
  syscalls::funlock(file_descriptor);
}

