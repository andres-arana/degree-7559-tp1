#include "logger.h"
#include <stdexcept>

using namespace std;

#define PERMS 0666 /* RW for owner, group and others */
#define FILENAME "concucalesita.log"

logger::logger() {
  this->file_descriptor = open( FILENAME, O_WRONLY | O_APPEND);
  if ( this->file_descriptor < 0 ) {
    this->file_descriptor = creat( FILENAME, PERMS);
    if (this->file_descriptor < 0 ) {
      throw runtime_error("Error abriendo el arhcivo de " FILENAME);
    }
  }
}

void logger::log(const string &method, const string &message) {
  /* LOCK_SH: Place a shared lock. More than one process may hold a shared lock
   * for a given file at a given time. */
  int locking = flock( this->file_descriptor, LOCK_SH);
  if (locking == 0) {
    time_t now = time(0);
    struct tm tstruct;
    char buff[80];
    tstruct = *localtime(&now);
    strftime(buff, sizeof(buff), "%Y-%m-%d.%X", &tstruct);
    string buffer = string(string(buff) + " [" + method + "] - " + message + "\n");
    ssize_t res = write( this->file_descriptor, buffer.c_str(), buffer.length());
    if (res<0) {
      //TODO throw a runtime_error()
    }
    /* LOCK_UN: Remove an existing lock held by this process.*/
    int unlock = flock( this->file_descriptor, LOCK_UN );
    if (unlock == 0) {
      //TODO throw a runtime_error()
    }
  }
}

void logger::info(const string &message) {
  this->log(string("INFO"), message);
}

void logger::warn(const string &message) {
  this->log(string("WARN"), message);
}

void logger::debug(const string &message) {
  this->log(string("DEBUG"), message);
}

void logger::error(const string &message) {
  this->log(string("ERROR"), message);
}

logger::~logger() {
  if (close( this->file_descriptor ) != 0) {
    cout << "cagamos la fruta" << endl;
  }
}
