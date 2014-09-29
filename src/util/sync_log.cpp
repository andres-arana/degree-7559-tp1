#include "sync_log.h"
#include "auto_file.h"
#include "auto_file_lock.h"
#include "syscalls.h"
#include <ctime>

using namespace util;
using namespace std;

namespace {
  const string FILENAME = "concucalesita.log";

  string human_current_time() {
    char humanized_time[80];
    auto now = time(0);
    auto local = localtime(&now);
    strftime(humanized_time, sizeof(humanized_time), "%Y-%m-%d.%X", local);

    return string(humanized_time);
  }

  void do_log(
      const auto_file &file,
      const string &name,
      const string &level,
      const string what) {

    auto_file_lock lock(file.fd());

    auto message = sformat(
        "$ PID: $ ($) [$]: $\n",
        human_current_time(), syscalls::checked_getpid(), name, level, what);

    syscalls::checked_write(file.fd(), message);
  }
};

sync_log::sync_log(const string &name)
  : file(::FILENAME, O_WRONLY | O_APPEND | O_CREAT), name(name){

  }

sync_log::sync_log(sync_log &&other)
  : file(move(other.file)) {

  }

sync_log &sync_log::operator =(sync_log &&other) {
  this->file = move(other.file);

  return *this;
}

void sync_log::separator() {
  do_log(this->file, this->name, "INFO", "**********************************");
};

void sync_log::info(const string &message) {
  do_log(this->file, this->name, "INFO", message);
}

void sync_log::warn(const string &message) {
  do_log(this->file, this->name, "WARN", message);
}

void sync_log::debug(const string &message) {
  do_log(this->file, this->name, "DEBUG", message);
}

void sync_log::error(const string &message) {
  do_log(this->file, this->name, "ERROR", message);
}

