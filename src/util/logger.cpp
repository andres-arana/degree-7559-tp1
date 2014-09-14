#include <ctime>
#include <sys/file.h>
#include <unistd.h>
#include <sstream>
#include "logger.h"
#include "file_lock.h"
#include "syscall_error.h"

using namespace std;
using namespace util;

#define PERMS 0666 /* RW for owner, group and others */
#define FILENAME "concucalesita.log"

logger::logger() {
  this->file_descriptor = open(FILENAME, O_WRONLY | O_APPEND);
  if ( this->file_descriptor < 0 ) {
    this->file_descriptor = creat(FILENAME, PERMS);
    if (this->file_descriptor < 0 ) {
      throw syscall_error("creat (abriendo el archivo de " FILENAME ")");
    }
  }
}

void logger::log(const string &method, const string &message) {
  file_lock lock(this->file_descriptor);

  char buff[80];
  auto now = time(0);
  auto tstruct = *localtime(&now);
  strftime(buff, sizeof(buff), "%Y-%m-%d.%X", &tstruct);

  stringstream stream;
  stream << buff << " PID:" << getpid() << " [" << method << "] - " << message << endl;
  auto buffer = stream.str();

  auto res = write(this->file_descriptor, buffer.c_str(), buffer.length());
  if (res < 0) {
    throw syscall_error("write");
  }
}

void logger::info(const string &message) {
  this->log("INFO", message);
}

void logger::warn(const string &message) {
  this->log("WARN", message);
}

void logger::debug(const string &message) {
  this->log("DEBUG", message);
}

void logger::error(const string &message) {
  this->log("ERROR", message);
}

logger::~logger() {
  if (close( this->file_descriptor )) {
    throw syscall_error("close");
  }
}
