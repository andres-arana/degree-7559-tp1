#include "raii/fifo.h"
#include "syscalls/file.h"
#include <sys/stat.h>

using namespace std;
using namespace raii;

namespace {
  const int PERMISSIONS = 0666;
}

fifo::fifo(const string &path, int flags)
  : file_descriptor(syscalls::open(path, flags, ::PERMISSIONS)) {

  }

int fifo::fd() {
  return file_descriptor;
}

fifo::~fifo() {
  syscalls::close(file_descriptor);
}
