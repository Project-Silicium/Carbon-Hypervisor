ifndef TARGET
$(error TARGET is not Set! Please Specifiy a SoC.)
endif

ARCH  = arm64
CROSS = aarch64-linux-gnu

CC      = clang --target=$(CROSS)
OBJCOPY = llvm-objcopy

CFLAGS      = -ffreestanding -Oz -flto -g -fno-pic -fno-pie -Iinclude
PLAT_CFLAGS = -Iinclude/$(TARGET)

LDFLAGS = -nostdlib -nostartfiles -static -fuse-ld=lld -Wl,--build-id=none

OBJS      = arch/$(ARCH)/start.o arch/$(ARCH)/helper.o psci/psci.o psci/psci_trampoline.o smc/smc_handler.o main.o
PLAT_OBJS = platform/$(TARGET).o

all: hyp.elf hyp.bin

%.o: %.S
	$(CC) $(CFLAGS) $(PLAT_CFLAGS) -c $< -o $@

%.o: %.c
	$(CC) $(CFLAGS) $(PLAT_CFLAGS) -c $< -o $@

hyp.elf: $(OBJS) $(PLAT_OBJS)
	$(CC) $(CFLAGS) $(PLAT_CFLAGS) $(LDFLAGS) -T arch/$(ARCH)/linker.ld $(OBJS) $(PLAT_OBJS) -o $@

hyp.bin: hyp.elf
	$(OBJCOPY) -O binary $< $@

clean:
	rm -f $(OBJS) $(PLAT_OBJS) hyp.elf hyp.bin
