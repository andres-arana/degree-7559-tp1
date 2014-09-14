#ifndef __UTIL_LOGGER_H_INCLUDED__
#define __UTIL_LOGGER_H_INCLUDED__

#include <string>

namespace util {

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
      void log(const std::string &method, const std::string &message);

    public:
      /*
       * Default constructor.
       */
      logger();

      /*
       * Shows an info message in logger.
       */
      void info(const std::string &message);

      /*
       * Shows an warning message in logger.
       */
      void warn(const std::string &message);

      /*
       * Shows an error message in logger.
       */
      void debug(const std::string &message);

      /*
       * Shows an error message in logger.
       */
      void error(const std::string &message);

      /*
       * destructor method.
       */
      ~logger();
  };

};

#endif
