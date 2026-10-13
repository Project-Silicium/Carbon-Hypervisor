#ifndef _EL3_MON_H_
#define _EL3_MON_H_

uint64_t
el3_call_smc (
  uint64_t func_id,
  uint64_t arg0,
  uint64_t arg1,
  uint64_t arg2
  );

#endif /* _EL3_MON_H_ */
