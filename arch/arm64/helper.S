.global el3_call_smc

.text
.align 3

//
// EL3 Monitor SMC Call
//
el3_call_smc:
  smc   #0
  ret
