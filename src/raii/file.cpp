#include "syscalls/file.h"
#include "raii/file.h"

using namespace raii;
using namespace std;

namespace {
  const int FILE_PERMISSIONS = 0666;
};

file::file()
  : file_descriptor(-1) {

  }

file::file(const string &filename, int flags)
  : file_descriptor(
      syscalls::open(filename, flags, ::FILE_PERMISSIONS)) {

  }

file::file(file &&other)
  : file_descriptor(other.file_descriptor) {
    other.file_descriptor = -1;
  }

file &file::operator=(file &&other) {
  syscalls::close(file_descriptor);
  file_descriptor = other.file_descriptor;
  other.file_descriptor = -1;
  return *this;
}

int file::fd() const {
  return file_descriptor;
}

void file::write(const string &what) {
    syscalls::write(file_descriptor, what);
}

file::~file() {
  syscalls::close(file_descriptor);
}
