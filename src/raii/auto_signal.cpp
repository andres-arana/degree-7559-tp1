#include "raii/auto_signal.h"
#include "syscalls/syscalls.h"
#include <map>

using namespace raii;
using namespace std;

namespace {
  map<int, function<void()>> handlers;

  void dispatch(int signal) {
    auto handler = handlers.find(signal);

    if (handler != handlers.end()) {
      handler->second();
    }
  }
};

auto_signal::auto_signal(int signal, function<void()> handler)
  : signal(signal) {

    auto installed_handler = handlers.find(signal);

    if (installed_handler != handlers.end()) {
      throw runtime_error("You are already capturing this signal");
    }

    handlers[signal] = handler;

    syscalls::sigaction(signal, ::dispatch);
  }

auto_signal::~auto_signal() {
  auto handler = handlers.find(signal);

  if (handler != handlers.end()) {
    handlers.erase(handler);
  }

  syscalls::sigaction(signal, SIG_DFL);
}

