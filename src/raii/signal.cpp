#include "syscalls/signal.h"
#include "raii/signal.h"
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

signal::signal(int signal, function<void()> handler)
  : signal_id(signal) {

    auto installed_handler = handlers.find(signal_id);

    if (installed_handler != handlers.end()) {
      throw runtime_error("You are already capturing this signal");
    }

    handlers[signal_id] = handler;

    syscalls::sigaction(signal_id, ::dispatch);
  }

signal::~signal() {
  auto handler = handlers.find(signal_id);

  if (handler != handlers.end()) {
    handlers.erase(handler);
  }

  syscalls::sigaction(signal_id, SIG_DFL);
}

