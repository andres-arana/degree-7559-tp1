#include "syscalls/file.h"
#include <sys/file.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

using namespace std;

void syscalls::mknod(const string &path, int flags) {
  auto result = ::mknod(path.c_str(), flags, 0);

  if (result < 0) {
    throw syscalls::error("mknod", path);
  }
}

void syscalls::unlink(const std::string &path) {
  auto result = ::unlink(path.c_str());

  if (result < 0) {
    throw syscalls::error("unlink", path);
  }
}

int syscalls::open(const string &filename, int flags, int permissions) {
  auto result = ::open(filename.c_str(), flags, permissions);

  if (result < 0) {
    throw syscalls::error("open", filename);
  }

  return result;
}

void syscalls::write(int fd, const string &what) {
  syscalls::write(fd, what.c_str(), what.length());
}

void syscalls::write(int fd, const void *what, size_t length) {
  if (::write(fd, what, length) < 0) {
    throw syscalls::error("write");
  }
}

size_t syscalls::read(int fd, void *buffer, size_t max) {
  auto result = ::read(fd, buffer, max);

  if (result < 0) {
    throw syscalls::error("read");
  }

  return result;
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
