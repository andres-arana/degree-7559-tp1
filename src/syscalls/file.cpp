#include "syscalls/file.h"
#include <sys/file.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

using namespace std;

namespace {
  struct flock make_lock_struct(int type) {
    struct flock result;
    result.l_whence = SEEK_SET;
    result.l_start = 0;
    result.l_len = 0;
    result.l_type = type;

    return result;
  }
}

void syscalls::mknod(const string &path, int flags) {
  if (::mknod(path.c_str(), flags, 0) < 0) {
    throw syscalls::error("mknod", path);
  }
}

void syscalls::unlink(const std::string &path) {
  if(::unlink(path.c_str()) < 0) {
    throw syscalls::error("unlink", path);
  }
}

int syscalls::open(const string &filename, int flags, int permissions) {
  auto result = ::open(filename.c_str(), flags, permissions);

  if (result < 0) {
    syscalls::check_interrupt("open", filename);
  }

  return result;
}

void syscalls::write(int fd, const string &what) {
  syscalls::write(fd, what.c_str(), what.length());
}

void syscalls::write(int fd, const void *what, size_t length) {
  if (::write(fd, what, length) < 0) {
    syscalls::check_interrupt("write");
  }
}

size_t syscalls::read(int fd, void *buffer, size_t max) {
  auto result = ::read(fd, buffer, max);

  if (result < 0) {
    syscalls::check_interrupt("read");
  } else if ((unsigned int)result < max) {
    throw syscalls::interrupt("read", "partial read");
  }

  return result;
}

void syscalls::close(int fd) {
  if (fd > 0) {
    auto result = ::close(fd);

    if (result < 0) {
      syscalls::check_interrupt("close");
    }
  }
}

void syscalls::frdlock(int fd) {
  auto fl = make_lock_struct(F_RDLCK);

  if (::fcntl(fd, F_SETLKW, &fl)) {
    syscalls::check_interrupt("fcntl, FSETLKW F_RDLCK");
  }
}

void syscalls::fwrlock(int fd) {
  auto fl = make_lock_struct(F_WRLCK);

  if (::fcntl(fd, F_SETLKW, &fl)) {
    syscalls::check_interrupt("fcntl", "F_SETLK F_WRLCK");
  }
}

void syscalls::funlock(int fd) {
  auto fl = make_lock_struct(F_UNLCK);

  if (::fcntl(fd, F_SETLKW, &fl)) {
    syscalls::check_interrupt("fcntl", "F_SETLK F_UNLCK");
  }
}
