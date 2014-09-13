#ifndef __INCLUDE_LOGGER_H__
#define __INCLUDE_LOGGER_H__

#include <cstdio>
#include <ctime>
#include <iostream>
#include <fstream>
#include <string>
#include <sys/file.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>

/*
 * Class that logs any event that wanted to be logged.
 */
class logger {

  private:
    /*
     * File descriptor to storage log information.
     */
    int file_descriptor;

    /*
     * Logs the message in the file description using the menthod;
     */
    void log(std::string method, std::string &message);

  public:
    /*
     * Default constructor.
     */
    logger();

    /*
     * Shows an info message in logger.
     */
    void info(std::string &message);

    /*
     * Shows an warning message in logger.
     */
    void warn(std::string &message);

    /*
     * Shows an error message in logger.
     */
    void debug(std::string &message);

    /*
     * Shows an error message in logger.
     */
    void error(std::string &message);

    /*
     * destructor method.
     */
    ~logger();
};


#endif
