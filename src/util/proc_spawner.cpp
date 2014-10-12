#include "util/proc_spawner.h"

using namespace util;

proc_spawner::proc_spawner(sync_log &log)
  : proc(true, "build/exec/spawner", "-l", log.get_level()) {

    log.debug("Started SPAWNER process with id $", pid());
  }
