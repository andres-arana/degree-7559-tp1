#include "util/sync_log.h"
#include "syscalls/syscalls.h"
#include <ctime>

using namespace util;
using namespace std;

namespace {
  const string FILENAME = "concucalesita.log";

  string human_current_time() {
    char humanized_time[80];
    auto now = time(0);
    auto local = localtime(&now);
    strftime(humanized_time, sizeof(humanized_time), "%Y-%m-%d %X", local);

    return string(humanized_time);
  }

  void do_log(
      const raii::auto_file &file,
      const string &name,
      const string &level,
      const string what) {

    raii::auto_file_lock lock(file.fd());

    auto message = sformat(
        "$ PID: $ ($) [$]: $\n",
        human_current_time(), syscalls::getpid(), name, level, what);

    syscalls::write(file.fd(), message);
  }
};

sync_log::sync_log(const string &name)
  : file(::FILENAME, O_WRONLY | O_APPEND | O_CREAT),
  name(name),
  log_level(sync_log::level::DEBUG) {

  }

void sync_log::set_level(sync_log::level value) {
  log_level = value;
}

void sync_log::set_level(unsigned int value) {
  log_level = static_cast<sync_log::level>(value);
}

void sync_log::info(const string &message) {
  if (log_level <= sync_log::level::INFO) {
    do_log(file, name, "INFO", message);
  }
}

void sync_log::warn(const string &message) {
  if (log_level <= sync_log::level::WARN) {
    do_log(file, name, "WARN", message);
  }
}

void sync_log::debug(const string &message) {
  if (log_level <= sync_log::level::DEBUG) {
    do_log(file, name, "DEBUG", message);
  }
}

void sync_log::error(const string &message) {
  if (log_level <= sync_log::level::ERROR) {
    do_log(file, name, "ERROR", message);
  }
}

