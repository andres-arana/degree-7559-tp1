#ifndef __RAII__SIGNAL_H_INCLUDED
#define __RAII__SIGNAL_H_INCLUDED

#include <functional>
#include <signal.h>

namespace raii {
  class signal {
    public:
      explicit signal(int signal, std::function<void()> handler);

      signal(const signal& other) = delete;
      signal &operator=(const signal &other) = delete;

      signal(signal &&other) = delete;
      signal &operator=(signal &&other) = delete;

      ~signal();

    private:
      int signal_id;
  };
}

#endif
