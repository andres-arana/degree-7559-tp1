#ifndef __UTIL__SHARED_DATA__H_INCLUDED__
#define __UTIL__SHARED_DATA__H_INCLUDED__

namespace util {
  struct shared_data {
    unsigned long cashier_child_id;
    unsigned int cashier_child_money;
    unsigned int cashier_child_change;

    unsigned long balance;

    unsigned int config_price;
    unsigned int config_capacity;
    unsigned int config_duration;

    int sem_cashier;
    int sem_carrousel_entrance;
    int sem_carrousel_places;
  };
}

#endif
