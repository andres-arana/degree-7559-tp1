#include "auto_file.h"
#include "syscalls.h"

using namespace util;
using namespace std;

namespace {
  const int FILE_PERMISSIONS = 0666;
};

auto_file::auto_file()
  : file_descriptor(-1) {

  }

auto_file::auto_file(const string &filename, int flags)
  : file_descriptor(
      syscalls::checked_open(filename, flags, ::FILE_PERMISSIONS)) {

  }

auto_file::auto_file(auto_file &&other)
  : file_descriptor(other.file_descriptor) {
    other.file_descriptor = -1;
  }

auto_file &auto_file::operator=(auto_file &&other) {
  syscalls::checked_close(file_descriptor);
  file_descriptor = other.file_descriptor;
  other.file_descriptor = -1;
  return *this;
}

int auto_file::fd() const {
  return file_descriptor;
}

auto_file::~auto_file() {
  syscalls::checked_close(file_descriptor);
}
