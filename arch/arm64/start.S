.text
.global _start

//
// Hypervisor Entry Point
//
_start:
  // Setup EL2 Stack Pointer
  adr   x0, __stack_top
  mov   sp, x0

  // Write EL2 Vector Table Address
  adr   x0, el2_vector_table
  msr   vbar_el2, x0

  // Enable SMC Trap
  mrs   x0, hcr_el2
  orr   x0, x0, #(1 << 19)
  msr   hcr_el2, x0

  // Apply Changes
  isb

  // Finish EL2 Setup
  mov   x0, xzr
  msr   vttbr_el2, x0

  // Return to EL1
  ldr   x0, =0xC2000401
  mov   x1, xzr
  smc   #0

  // Infinite Loop
  bl    unhandled_exception

//
// EL2 Vector Table
//
.align 11
el2_vector_table:

.align 7; b unhandled_exception
.align 7; b unhandled_exception
.align 7; b unhandled_exception
.align 7; b unhandled_exception

.align 7; b unhandled_exception
.align 7; b unhandled_exception
.align 7; b unhandled_exception
.align 7; b unhandled_exception

.align 7; b exception_smc_hook
.align 7; b unhandled_exception
.align 7; b unhandled_exception
.align 7; b unhandled_exception

.align 7; b unhandled_exception
.align 7; b unhandled_exception
.align 7; b unhandled_exception
.align 7; b unhandled_exception

//
// Exception Handler
//
unhandled_exception:
  wfe
  b     unhandled_exception

//
// SMC Trap Handler
//
exception_smc_hook:
  // Save Registers
  stp   x30, xzr, [sp, #-16]!
  stp   x28, x29, [sp, #-16]!
  stp   x26, x27, [sp, #-16]!
  stp   x24, x25, [sp, #-16]!
  stp   x22, x23, [sp, #-16]!
  stp   x20, x21, [sp, #-16]!
  stp   x18, x19, [sp, #-16]!
  stp   x16, x17, [sp, #-16]!
  stp   x14, x15, [sp, #-16]!
  stp   x12, x13, [sp, #-16]!
  stp   x10, x11, [sp, #-16]!
  stp   x8,  x9,  [sp, #-16]!
  stp   x6,  x7,  [sp, #-16]!
  stp   x4,  x5,  [sp, #-16]!
  stp   x2,  x3,  [sp, #-16]!
  stp   x0,  x1,  [sp, #-16]!

  // Verify Exception Type
  mrs   x16, esr_el2
  lsr   x16, x16, #26
  cmp   x16, #0x17
  b.ne  unhandled_exception

  // Execute PSCI Handler
  mov   x0, sp
  bl    psci_handler

  // Verify Return Value
  cbnz  x0, smc_passthru

  // Skip SMC Passthru
  b     skip_smc_passthru

smc_passthru:
  // Restore SMC Arguments
  ldp   x0,  x1,  [sp, #0]
  ldp   x2,  x3,  [sp, #16]
  ldp   x4,  x5,  [sp, #32]
  ldp   x6,  x7,  [sp, #48]

  // Call EL3 Monitor
  smc   #0

  // Save Return Values
  stp   x0,  x1,  [sp, #0]
  stp   x2,  x3,  [sp, #16]

skip_smc_passthru:
  // Advance ELR_EL2
  mrs   x16, elr_el2
  add   x16, x16, #4
  msr   elr_el2, x16

  // Restore Registers
  ldp   x0,  x1,  [sp], #16
  ldp   x2,  x3,  [sp], #16
  ldp   x4,  x5,  [sp], #16
  ldp   x6,  x7,  [sp], #16
  ldp   x8,  x9,  [sp], #16
  ldp   x10, x11, [sp], #16
  ldp   x12, x13, [sp], #16
  ldp   x14, x15, [sp], #16
  ldp   x16, x17, [sp], #16
  ldp   x18, x19, [sp], #16
  ldp   x20, x21, [sp], #16
  ldp   x22, x23, [sp], #16
  ldp   x24, x25, [sp], #16
  ldp   x26, x27, [sp], #16
  ldp   x28, x29, [sp], #16
  ldp   x30, xzr, [sp], #16

  // Resume Execution
  eret
