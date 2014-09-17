#include "sync_log.h"
#include "auto_file.h"
#include "auto_file_lock.h"
#include "syscall_error.h"
#include <ctime>
#include <unistd.h>
#include <sstream>

using namespace util;
using namespace std;

namespace {
  const string FILENAME = "concucalesita.log";

  string humanized_current_time() {
    char humanized_time[80];
    auto now = time(0);
    auto local = localtime(&now);
    strftime(humanized_time, sizeof(humanized_time), "%Y-%m-%d.%X", local);

    return string(humanized_time);
  }

  void do_log(
      const auto_file &file,
      const string &level,
      const string what) {

    auto_file_lock lock(file.fd());

    stringstream message_stream;
    message_stream <<
      humanized_current_time() <<
      " PID:" << getpid() <<
      " [" << level << "] - " <<
      what << endl;

    auto buffer = message_stream.str();
    if (write(file.fd(), buffer.c_str(), buffer.length()) < 0) {
      throw syscall_error("write");
    }
  }
};

sync_log::sync_log()
  : file(::FILENAME, O_WRONLY | O_APPEND | O_CREAT) {

  }

sync_log::sync_log(sync_log &&other)
  : file(move(other.file)) {

  }

sync_log &sync_log::operator =(sync_log &&other) {
  this->file = move(other.file);

  return *this;
}

void sync_log::info(const string &message) {
  do_log(this->file, "INFO", message);
}

void sync_log::warn(const string &message) {
  do_log(this->file, "WARN", message);
}

void sync_log::debug(const string &message) {
  do_log(this->file, "DEBUG", message);
}

void sync_log::error(const string &message) {
  do_log(this->file, "ERROR", message);
}

