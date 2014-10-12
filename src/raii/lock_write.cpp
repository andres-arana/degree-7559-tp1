#include "raii/lock_write.h"
#include "syscalls/file.h"

using namespace std;
using namespace raii;

lock_write::lock_write(int fd)
  : file_descriptor(fd) {
    syscalls::fwrlock(fd);
  }

lock_write::~lock_write() {
  syscalls::funlock(file_descriptor);
}


