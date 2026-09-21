#ifndef _MEMORY_H_
#define _MEMORY_H_

//
// 32-Bit Memory Actions
//
#define readl(addr)       (*((volatile uint32_t *)(uintptr_t)(addr)))
#define writel(val, addr) (*((volatile uint32_t *)(uintptr_t)(addr))) = (uint32_t)val

#endif /* _MEMORY_H_ */
