#include "raii/lock_read.h"
#include "syscalls/file.h"

using namespace std;
using namespace raii;

lock_read::lock_read(int fd)
  : file_descriptor(fd) {
    syscalls::frdlock(fd);
  }

lock_read::~lock_read() {
  syscalls::funlock(file_descriptor);
}


