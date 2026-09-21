/**
  Copyright (c) 2015 Samsung Electronics Co., Ltd.

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License version 2 as
  published by the Free Software Foundation.
**/

#include <stdbool.h>
#include <stdint.h>

#include <pmu.h>
#include <memory.h>
#include <psci_trampoline.h>
#include <psci.h>

//
// External Functions
//
extern void core_trampoline_entry (void);
extern uint64_t call_smc_el3 (uint64_t func_id, uint64_t arg0, uint64_t arg1, uint64_t arg2);

//
// Dynamic Trampoline Code
//
static uint64_t trampoline_code[8][8] = {0};

uint32_t
psci_version (void)
{
  return PSCI_VERSION_1_1;
}

int64_t
psci_cpu_suspend (
  uint32_t power_state,
  uint64_t entry_point_address,
  uint64_t context_id)
{
  // Use EL3 Monitor Implementation
  return (int64_t)call_smc_el3 (PSCI_CPU_SUSPEND_64, power_state, entry_point_address, context_id);
}

int32_t
psci_cpu_off (void)
{
  // Use EL3 Monitor Implementation
  return (int32_t)call_smc_el3 (PSCI_CPU_OFF, 0, 0, 0);
}

static inline
uint8_t
get_core_index (uint64_t mpidr)
{
  // Get Cluster & Core ID
  uint32_t aff1 = (mpidr >> 8) & 0xFF;
  uint32_t aff0 = mpidr & 0xFF;

  // Return Core Number
  if (aff1 == 0x00 && aff0 < 4) {
    return aff0;
  } else if (aff1 == 0x01 && aff0 < 4) {
    return 4 + aff0;
  }

  // Invalid MPIDR
  return -1;
}

int64_t
psci_cpu_on (
  uint64_t target_cpu,
  uint64_t entry_point_address,
  uint64_t context_id)
{
  // Get Core Index
  uint8_t core_index = get_core_index (target_cpu);

  // Verify Core Index
  if (core_index >= 8) {
    return PSCI_INVALID_PARAMETERS;
  }

  // Generate Trampoline
  generate_trampoline (trampoline_code[core_index], entry_point_address, context_id);

  // Call EL3 Monitor
  return (int64_t)call_smc_el3 (PSCI_CPU_ON_64, target_cpu, (uint64_t)trampoline_code[core_index], 0);
}

int64_t
psci_affinity_info (
  uint64_t target_affinity,
  uint32_t lowest_affinity_level)
{
  // TODO!
  return 0;
}

void
psci_system_off (void)
{
  uint32_t ps_hold = 0;

  // Set PS_HOLD Low
  ps_hold  = readl (PMU_BASE + PS_HOLD_CONTROL);
  ps_hold &= ~PS_HOLD_LOW;
  writel (ps_hold, PMU_BASE + PS_HOLD_CONTROL);
}

void
psci_system_reset (void)
{
  // Do S/W Reset
  writel (0x1, PMU_BASE + SWRESET);
}

int32_t
psci_features (uint32_t psci_func_id)
{
  // Check PSCI Function ID
  switch (psci_func_id) {
    case PSCI_VERSION:
    case PSCI_CPU_SUSPEND_32:
    case PSCI_CPU_SUSPEND_64:
    case PSCI_CPU_OFF:
    case PSCI_CPU_ON_32:
    case PSCI_CPU_ON_64:
    case PSCI_AFFINITY_INFO_32:
    case PSCI_AFFINITY_INFO_64:
    case PSCI_SYSTEM_OFF:
    case PSCI_SYSTEM_RESET:
    case PSCI_FEATURES:
      return 0x0;

    default:
      return PSCI_NOT_SUPPORTED;
  }
}

bool
psci_handler (uint64_t *cpu_reg)
{
  // Get SMC Function ID
  uint32_t function_id = (uint32_t)cpu_reg[0];

  // Run Specified PSCI Action
  switch (function_id) {
    case PSCI_VERSION:
      cpu_reg[0] = (uint64_t)psci_version ();
      break;

    case PSCI_CPU_SUSPEND_32:
    case PSCI_CPU_SUSPEND_64:
      cpu_reg[0] = (uint64_t)psci_cpu_suspend ((uint32_t)cpu_reg[1], cpu_reg[2], cpu_reg[3]);
      break;

    case PSCI_CPU_OFF:
      cpu_reg[0] = (uint64_t)psci_cpu_off ();
      break;

    case PSCI_CPU_ON_32:
    case PSCI_CPU_ON_64:
      cpu_reg[0] = (uint64_t)psci_cpu_on (cpu_reg[1], cpu_reg[2], cpu_reg[3]);
      break;

    case PSCI_AFFINITY_INFO_32:
    case PSCI_AFFINITY_INFO_64:
      cpu_reg[0] = (uint64_t)psci_affinity_info (cpu_reg[1], (uint32_t)cpu_reg[2]);
      break;

    case PSCI_SYSTEM_OFF:
      psci_system_off ();
      break;

    case PSCI_SYSTEM_RESET:
      psci_system_reset ();
      break;

    case PSCI_FEATURES:
      cpu_reg[0] = (uint64_t)psci_features ((uint32_t)cpu_reg[1]);
      break;
  }

  // Passthru Unhandled SMC Function IDs
  return cpu_reg[0] == function_id;
}
