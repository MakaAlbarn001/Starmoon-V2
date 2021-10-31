.section .multiboot
/* Define the static values of the Multiboot header. */
.set MAGIC, 0x85250D6                           # Sets the multiboot Magic value
.set ARCH, 0                                    # Sets the architecture and flags for GRUB
.set LENG, header_end - header_start            # Defines the Length of the header
.set CHECKSUM, -(MAGIC + ARCH + LENG)           # Creates a verifying checksum
.align 8
# Define the Multiboot header.
header_start:
.long MAGIC
.long ARCH
.long LENG
.long CHECKSUM
info_req_tag:                           # Information Request tag for GRUB
.short 1                                # Defines the Type of tag: Multiboot Info Request
.short 0                                # Flags: 0 - Must be provided if present
.long (header_end - info_req_tag)       # Length of the tag
.long 4                                 # Tag requests: 4 - Basic Memory Info
.long 6                                 # 6 - Full Memory Map
.long 5                                 # 5 - BIOS Boot Device
.long 3                                 # 3 - Loaded Modules
.long 9                                 # 9 - ELF Symbols
.long 0                                 # padding
header_end:

.section .text
.global _start                          # Define the entry point.
_start:
    xor %ebp, %ebp                      # Clear the base pointer to normalize the stack frames
    mov $stack_top, %esp                # set the stack pointer to the newly created stack
    push %ebp                           # Set the stack frame terminator.

    call _init                          # Call the global constructors
    /* push the heap beginning and end onto the stack. */
    push $heap_begin
    push $heap_end

loop:                                   # Create a loop point for idle.
    hlt                                 # Halt the system until an interrupt
    jmp loop                            # Jump to the loop point.

    call _fini                          # Call the global destructors

.section .bss
.align 4096                             # Align the stack on a 4KB page boundary
stack_bottom:
.skip 4096                              # Sets the size of the stack
stack_top:
.section .heap
.align 4096                             # Align the heap on a 4KB page boundary
heap_begin:
.skip 4096                              # Set the size of the heap
heap_end:
