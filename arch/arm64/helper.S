.global call_smc_el3

.text
.align 3

//
// EL3 Monitor SMC Call
//
call_smc_el3:
  smc   #0
  ret