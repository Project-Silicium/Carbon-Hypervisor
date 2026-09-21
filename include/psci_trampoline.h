#ifndef _PSCI_TRAMPOLINE_H_
#define _PSCI_TRAMPOLINE_H_

//
// AARCH64 Instruction Bases
//
#define MOVZ_BASE 0xD2800000
#define MOVK_BASE 0xF2800000
#define BR_BASE   0xD61F0000

//
// AARCH64 Instruction Macros
//
#define MOVZ(rd, imm16, hw) (MOVZ_BASE | ((uint32_t)(hw) << 21) | ((uint32_t)(imm16) << 5) | (uint32_t)(rd))
#define MOVK(rd, imm16, hw) (MOVK_BASE | ((uint32_t)(hw) << 21) | ((uint32_t)(imm16) << 5) | (uint32_t)(rd))
#define BR(rn)              (BR_BASE   | ((uint32_t)(rn) << 5))

//
// Functions
//
void
generate_trampoline (
  uint64_t *location,
  uint64_t  entry_point,
  uint64_t  context_id
  );

#endif /* _PSCI_TRAMPOLINE_H_ */
