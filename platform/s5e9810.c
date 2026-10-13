/**
  Copyright (c) 2015 Samsung Electronics Co., Ltd.

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License version 2 as
  published by the Free Software Foundation.
**/

#include <stdint.h>

#include <memory.h>
#include <pmu.h>

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
