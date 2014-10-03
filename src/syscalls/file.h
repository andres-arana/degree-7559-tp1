#ifndef __SYSCALLS__FILE_H_INCLUDED__
#define __SYSCALLS__FILE_H_INCLUDED__

#include "syscalls/error.h"
#include <fcntl.h>
#include <string>

namespace syscalls {
  void mknod(const std::string &path, int flags);

  void unlink(const std::string &path);

  int open(const std::string &filename, int flags, int permissions);

  void close(int fd);

  void write(int fd, const std::string &what);

  void write(int fd, const void *what, size_t length);

  size_t read(int fd, void* buffer, size_t max);

  void flock(int fd, struct flock fl);

  void funlock(int fd, struct flock fl);
}

#endif
