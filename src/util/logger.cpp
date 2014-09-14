#include <ctime>
#include <sys/file.h>
#include <unistd.h>
#include <errno.h>
#include <stdexcept>
#include <sstream>
#include "logger.h"

using namespace std;
using namespace util;

#define PERMS 0666 /* RW for owner, group and others */
#define FILENAME "concucalesita.log"

logger::logger() {
  this->file_descriptor = open(FILENAME, O_WRONLY | O_APPEND);
  if ( this->file_descriptor < 0 ) {
    this->file_descriptor = creat(FILENAME, PERMS);
    if (this->file_descriptor < 0 ) {
      throw runtime_error("Error abriendo el archivo de " FILENAME);
    }
  }
}

void logger::log(const string &method, const string &message) {
  auto locking = flock( this->file_descriptor, LOCK_EX);
  if (locking == 0) {
    char buff[80];
    auto now = time(0);
    auto tstruct = *localtime(&now);
    strftime(buff, sizeof(buff), "%Y-%m-%d.%X", &tstruct);

    stringstream stream;
    stream << buff << " PID:" << getpid() << " [" << method << "] - " << message << endl;
    auto buffer = stream.str();

    auto res = write(this->file_descriptor, buffer.c_str(), buffer.length());
    if (res < 0) {
      this->raise_errno("write");
    }

    auto unlock = flock( this->file_descriptor, LOCK_UN );

    if (unlock < 0) {
      this->raise_errno("flock");
    }
  }
}

void logger::raise_errno(const std::string &syscall) const {
  stringstream error;
  error << "La syscall " << syscall << " fallo con error = " << errno;
  throw runtime_error(error.str());
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
    throw runtime_error("Cagamos la fruta");
  }
}
