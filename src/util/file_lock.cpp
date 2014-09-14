#include "file_lock.h"
#include "syscall_error.h"
#include <sys/file.h>

using namespace std;
using namespace util;

#define PERMS 0666 /* RW for owner, group and others */

file_lock::file_lock(int file_descriptor) :
  file_descriptor(file_descriptor) {
    this->lock();
}

file_lock::file_lock(const string &filename) {
  this->file_descriptor = open(filename.c_str(), O_WRONLY | O_APPEND);
  if ( this->file_descriptor < 0 ) {
    this->file_descriptor = creat(filename.c_str(), PERMS);
    if (this->file_descriptor < 0 ) {
      throw syscall_error("creat (abriendo el archivo de " + filename + ")");
    }
  }

  this->lock();
}

file_lock::~file_lock() {
  this->unlock();
}

void file_lock::lock() {
  if (flock(this->file_descriptor, LOCK_EX)) {
    throw syscall_error("flock (lock)");
  }
}

void file_lock::unlock() {
    if (flock(this->file_descriptor, LOCK_UN)) {
      throw syscall_error("flock (unlock)");
    }
}

