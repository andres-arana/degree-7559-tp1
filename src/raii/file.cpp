#include "syscalls/file.h"
#include "raii/file.h"

using namespace raii;
using namespace std;

namespace {
  const int FILE_PERMISSIONS = 0666;
};

file::file(const string &filename, int flags)
  : file_descriptor(syscalls::open(filename, flags, ::FILE_PERMISSIONS)) {

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
