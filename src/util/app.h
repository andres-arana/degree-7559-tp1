#ifndef __UTIL_APP_H_INCLUDED__
#define __UTIL_APP_H_INCLUDED__

#include "util/sync_log.h"
#include "tclap/CmdLine.h"
#include <string>

namespace util {

#define DEFINE_MAIN(clazz) int main(int argc, char** argv) { clazz app; return app.run(argc, argv); }

  class app {
    public:
      explicit app(const std::string &name);

      explicit app(const app& other) = delete;
      app &operator=(const app &other) = delete;

      explicit app(app&& other) = delete;
      app & operator=(app &&other) = delete;

      int run(int argc, char **argv);

      virtual ~app() {};

    protected:
      sync_log log;

      TCLAP::CmdLine args;

      virtual void do_run() = 0;
  };

};

#endif
