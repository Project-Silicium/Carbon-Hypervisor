#ifndef _PLATFORM_H_
#define _PLATFORM_H_

#include <stdint.h>

void
platform_get_mpidr (
  uint64_t **core_mpidr,
  uint8_t   *core_count
  );

void
platform_power_off (void);

void
platform_reboot (void);

void
platform_main (void);

#endif /* _PLATFORM_H_ */
