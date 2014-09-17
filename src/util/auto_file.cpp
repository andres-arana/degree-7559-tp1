#include "auto_file.h"
#include "syscall_error.h"
#include <unistd.h>

using namespace util;
using namespace std;

namespace {
  const int FILE_PERMISSIONS = 0666;

  void close_file_descriptor(int file_descriptor) {
    if (file_descriptor > 0) {
      auto result = close(file_descriptor);

      if (result < 0) {
        throw syscall_error("close");
      }
    }
  }
};

auto_file::auto_file()
  : file_descriptor(-1) {
  
  }

auto_file::auto_file(const string &filename, int flags) 
  : file_descriptor(open(filename.c_str(), flags, ::FILE_PERMISSIONS)) {
    if (this->file_descriptor < 0) {
      throw syscall_error("open", filename);
    }
  }

auto_file::auto_file(auto_file &&other) 
  : file_descriptor(other.file_descriptor) {
    other.file_descriptor = -1;
  }

auto_file &auto_file::operator=(auto_file &&other) {
  ::close_file_descriptor(this->file_descriptor);
  this->file_descriptor = other.file_descriptor;
  other.file_descriptor = -1;
  return *this;
}

int auto_file::fd() const {
  return this->file_descriptor;
}

auto_file::~auto_file() {
  ::close_file_descriptor(this->file_descriptor);
}
