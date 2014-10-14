#include "util/app_owned.h"

using namespace std;
using namespace util;

app_owned::app_owned(const std::string &name)
  : app(name),
  halt(0),
  shmemid("m", "memory", "Shared memory id", true, 0, "int", args),
  sigint(SIGINT, [this]() { halt = 1; }) { }

bool app_owned::is_halted() const {
  return halt;
}

void app_owned::do_run() {
  log.debug("Attaching shared memory");
  raii::shmem<util::shared_data> shmem(shmemid.getValue());

  do_run(shmem);
}
