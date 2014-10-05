#include "syscalls/file.h"
#include <unistd.h>
#include <sys/file.h>

using namespace std;

int syscalls::open(const string &filename, int flags, int permissions) {
  auto result = ::open(filename.c_str(), flags, permissions);

  if (result < 0) {
    throw syscalls::error("open", filename);
  }

  return result;
}

void syscalls::write(int fd, const string &what) {
  if (::write(fd, what.c_str(), what.length()) < 0) {
    throw syscalls::error("write");
  }
}

void syscalls::close(int fd) {
  if (fd > 0) {
    auto result = ::close(fd);

    if (result < 0) {
      throw syscalls::error("close");
    }
  }

}

void syscalls::flock(int fd) {
  if (fd > 0 && ::flock(fd, LOCK_EX)) {
    throw syscalls::error("flock", "LOCK_EX");
  }
}

void syscalls::funlock(int fd) {
  if (fd > 0 && ::flock(fd, LOCK_UN)) {
    throw syscalls::error("flock", "LOCK_UN");
  }
}
