AS = $(ARCH)-elf-as
CC = $(ARCH)-elf-gcc
GPP = $(ARCH)-elf-g++
LD = $(ARCH)-elf-ld
AR = $(ARCH)-elf-ar
OBJDUMP = $(ARCH)-elf-objdump
OBJCOPY = $(ARCH)-elf-objcopy
INCDIR := $(CURDIR)/include
CFLAGS := -g -ffreestanding -O2 -Wall -Wextra -fno-omit-frame-pointer
CPPFLAGS := -mno-red-zone -fno-exceptions -fno-rtti
LDFLAGS := -nostdlib
LIBDIR := $(CURDIR)/lib

CRTBEGIN_OBJ=$(shell $(CC) $(CFLAGS) -print-file-name=crtbegin.o)
CRTEND_OBJ=$(shell $(CC) $(CFLAGS) -print-file-name=crtend.o)

.DEFAULT_GOAL := i686

## i686 - build for the x86 architecture.
i686: ARCH = i686
i686: .EXPORT_ALL_VARIABLES
i686:
	$(MAKE) -C arch
	$(MAKE) -C kernel
	$(GPP) -T scripts/$(ARCH).ld -Wl,-Map=$@.map -o $@ $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) arch/crt0.o arch/crti.o $(CRTBEGIN_OBJ) \
	kernel/kernel.o arch/arch.o $(CRTEND_OBJ) arch/crtn.o -lgcc
	$(OBJCOPY) --only-keep-debug $@ $@.dbg

.phony: clean
clean:
	rm -rf *.o
	$(MAKE) clean -C arch
	rm -rf i686
	rm -rf *.map
	rm -rf *.dbg

.phony: .EXPORT_ALL_VARIABLES
.EXPORT_ALL_VARIABLES: