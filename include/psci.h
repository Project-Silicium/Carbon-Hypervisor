#ifndef _PSCI_H_
#define _PSCI_H_

//
// PSCI Versions
//
#define PSCI_VERSION_1_1 0x00010001

//
// PSCI Functions
//
#define PSCI_VERSION            0x84000000
#define PSCI_CPU_SUSPEND_32     0x84000001
#define PSCI_CPU_SUSPEND_64     0xC4000001
#define PSCI_CPU_OFF            0x84000002
#define PSCI_CPU_ON_32          0x84000003
#define PSCI_CPU_ON_64          0xC4000003
#define PSCI_AFFINITY_INFO_32   0x84000004
#define PSCI_AFFINITY_INFO_64   0xC4000004
#define PSCI_SYSTEM_OFF         0x84000008
#define PSCI_SYSTEM_RESET       0x84000009
#define PSCI_FEATURES           0x8400000A

//
// PSCI Return Codes
//
#define PSCI_SUCCESS               0
#define PSCI_NOT_SUPPORTED        -1
#define PSCI_INVALID_PARAMETERS   -2
#define PSCI_DENIED               -3
#define PSCI_ALREADY_ON           -4
#define PSCI_ON_PENDING           -5
#define PSCI_INTERNAL_FAILURE     -6
#define PSCI_NOT_PRESENT          -7
#define PSCI_DISABLED             -8
#define PSCI_INVALID_ADDRESS      -9

#endif /* _PSCI_H_ */
