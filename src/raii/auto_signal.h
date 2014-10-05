#ifndef __RAII__AUTO_SIGNAL_H_INCLUDED
#define __RAII__AUTO_SIGNAL_H_INCLUDED

#include <functional>
#include <signal.h>

namespace raii {
  class auto_signal {
    public:
      explicit auto_signal(int signal, std::function<void()> handler);

      auto_signal(const auto_signal& other) = delete;
      auto_signal &operator=(const auto_signal &other) = delete;

      auto_signal(auto_signal &&other) = delete;
      auto_signal &operator=(auto_signal &&other) = delete;

      ~auto_signal();

    private:
      int signal;
  };
}

#endif
