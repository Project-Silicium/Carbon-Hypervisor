#include <stdint.h>

#include <psci.h>

int
smc_handler (uint64_t *cpu_reg)
{
  // Get SMC Function ID
  uint32_t function_id = (uint32_t)cpu_reg[0];

  // Run Specified SMC Function
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
