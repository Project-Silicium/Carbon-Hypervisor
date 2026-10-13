#include <stdint.h>

#include <el3_mon.h>
#include <platform.h>
#include <psci_trampoline.h>
#include <psci.h>

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
  return (int64_t)el3_call_smc (PSCI_CPU_SUSPEND_64, power_state, entry_point_address, context_id);
}

int32_t
psci_cpu_off (void)
{
  // Use EL3 Monitor Implementation
  return (int32_t)el3_call_smc (PSCI_CPU_OFF, 0, 0, 0);
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
  return (int64_t)el3_call_smc (PSCI_CPU_ON_64, target_cpu, (uint64_t)trampoline_code[core_index], 0);
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
  // Power Off Platform
  platform_power_off ();
}

void
psci_system_reset (void)
{
  // Reboot Platform
  platform_reboot ();
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
