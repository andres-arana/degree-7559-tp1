#include "util/proc_carrousel.h"

using namespace util;

proc_carrousel::proc_carrousel(sync_log &log)
  : proc(true, "build/exec/carrousel", "-l", log.get_level()) {

    log.debug("Started CARROUSEL process with id $", pid());
  }
