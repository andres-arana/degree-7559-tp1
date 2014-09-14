#include "sync_log.h"
#include "auto_file.h"
#include "auto_file_lock.h"
#include "syscall_error.h"
#include <ctime>
#include <unistd.h>
#include <sstream>

using namespace util;

namespace {
  const std::string FILENAME = "concucalesita.log";

  std::string humanized_current_time() {
    char humanized_time[80];
    auto now = time(0);
    auto local = localtime(&now);
    strftime(humanized_time, sizeof(humanized_time), "%Y-%m-%d.%X", local);

    return std::string(humanized_time);
  }

  void do_log(
      const auto_file &file,
      const std::string &level,
      const std::string what) {

    auto_file_lock lock(file.fd());

    std::stringstream message_stream;
    message_stream <<
      humanized_current_time() <<
      " PID:" << getpid() <<
      " [" << level << "] - " <<
      what << std::endl;

    auto buffer = message_stream.str();
    if (write(file.fd(), buffer.c_str(), buffer.length()) < 0) {
      throw syscall_error("write");
    }
  }
};

sync_log::sync_log()
  : file(::FILENAME, O_WRONLY | O_APPEND | O_CREAT) {

  }

void sync_log::info(const std::string &message) {
  do_log(this->file, "INFO", message);
}

void sync_log::warn(const std::string &message) {
  do_log(this->file, "WARN", message);
}

void sync_log::debug(const std::string &message) {
  do_log(this->file, "DEBUG", message);
}

void sync_log::error(const std::string &message) {
  do_log(this->file, "ERROR", message);
}

