ARCH = arm64
CROSS = aarch64-linux-gnu

CC      = clang --target=$(CROSS)
OBJCOPY = llvm-objcopy

CFLAGS  = -ffreestanding -Oz -flto -g -fno-pic -fno-pie -Iinclude
LDFLAGS = -nostdlib -nostartfiles -static -fuse-ld=lld -Wl,--build-id=none

OBJS = arch/$(ARCH)/start.o arch/$(ARCH)/helper.o psci.o psci_trampoline.o

all: hyp.elf hyp.bin

%.o: %.S
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

hyp.elf: $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) -T arch/$(ARCH)/linker.ld $(OBJS) -o $@

hyp.bin: hyp.elf
	$(OBJCOPY) -O binary $< $@

clean:
	rm -f $(OBJS) hyp.elf hyp.bin
