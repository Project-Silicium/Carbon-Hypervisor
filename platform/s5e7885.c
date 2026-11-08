/**
  Copyright (c) 2015 Samsung Electronics Co., Ltd.

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License version 2 as
  published by the Free Software Foundation.
**/

#include <stdint.h>

#include <memory.h>
#include <pmu.h>

//
// Core MPIDRs
//
static uint64_t platform_core_mpidr[] = {
  0x100, 0x101, 0x102, 0x103, 0x200, 0x201, // Cluster 0
  0x000, 0x001                              // Cluster 1
};

void
platform_get_mpidr (
  uint64_t **core_mpidr,
  uint8_t   *core_count)
{
  // Pass Core MPIDR Array
  *core_mpidr = platform_core_mpidr;
  *core_count = sizeof (platform_core_mpidr) / sizeof ((platform_core_mpidr)[0]);
}

void
platform_power_off (void)
{
  uint32_t ps_hold = 0;

  // Set PS_HOLD Low
  ps_hold  = readl (PMU_BASE + PS_HOLD_CONTROL);
  ps_hold &= ~PS_HOLD_LOW;
  writel (ps_hold, PMU_BASE + PS_HOLD_CONTROL);
}

void
platform_reboot (void)
{
  // Do S/W Reset
  writel (0x1, PMU_BASE + SWRESET);
}

void
platform_main (void)
{
  // Nothing to do here.
}
