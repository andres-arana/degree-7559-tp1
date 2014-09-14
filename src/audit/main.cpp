#include <cstdlib>
#include "util/sync_log.h"

int main() {
  util::sync_log log;

  log.error("Soy audit");

  return EXIT_SUCCESS;
}
