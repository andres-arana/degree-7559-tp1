#include "auto_file.h"
#include "syscall_error.h"

#include <sys/file.h>
#include <unistd.h>

using namespace util;

namespace {
  const int FILE_PERMISSIONS = 0666;
};

auto_file::auto_file(const std::string &filename, int flags) {
  this->file_descriptor = open(filename.c_str(), flags, ::FILE_PERMISSIONS);

  if (this->file_descriptor < 0) {
    throw syscall_error("open", filename);
  }
}

int auto_file::fd() const {
  return this->file_descriptor;
}

auto_file::~auto_file() {
  auto result = close(this->file_descriptor);

  if (result < 0) {
    throw syscall_error("close");
  }
}
