#include "syscalls/file.h"
#include "raii/auto_file.h"

using namespace raii;
using namespace std;

namespace {
  const int FILE_PERMISSIONS = 0666;
};

auto_file::auto_file()
  : file_descriptor(-1) {

  }

auto_file::auto_file(const string &filename, int flags)
  : file_descriptor(
      syscalls::open(filename, flags, ::FILE_PERMISSIONS)) {

  }

auto_file::auto_file(auto_file &&other)
  : file_descriptor(other.file_descriptor) {
    other.file_descriptor = -1;
  }

auto_file &auto_file::operator=(auto_file &&other) {
  syscalls::close(file_descriptor);
  file_descriptor = other.file_descriptor;
  other.file_descriptor = -1;
  return *this;
}

int auto_file::fd() const {
  return file_descriptor;
}

void auto_file::write(const string &what) {
    syscalls::write(file_descriptor, what);
}

auto_file::~auto_file() {
  syscalls::close(file_descriptor);
}
