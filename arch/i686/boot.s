.section .multiboot
/* Define the static values of the Multiboot header. */
.set MAGIC, 0xe85250D6                           # Sets the multiboot Magic value
.set ARCH, 0                                    # Sets the architecture and flags for GRUB
.set LENG, header_end - header_start            # Defines the Length of the header
.align 8
# Define the Multiboot header.
header_start:
.long MAGIC
.long ARCH
.long LENG
.long -(MAGIC + ARCH + LENG)           # Creates a verifying checksum
info_req_tag:                           # Information Request tag for GRUB
.short 1                                # Defines the Type of tag: Multiboot Info Request
.short 0                                # Flags: 0 - Must be provided if present
.long (header_tag_end - info_req_tag)       # Length of the tag
.long 4                                 # Tag requests: 4 - Basic Memory Info
.long 6                                 # 6 - Full Memory Map
.long 5                                 # 5 - BIOS Boot Device
.long 3                                 # 3 - Loaded Modules
.long 9                                 # 9 - ELF Symbols
.long 0                                 # padding
header_tag_end:
.short 0
.short 0
.long 8
header_end:

.section .text
.global _start                          # Define the entry point.
_start:
    xor %ebp, %ebp                      # Clear the base pointer to normalize the stack frames
    mov $stack_top, %esp                # set the stack pointer to the newly created stack
    push %ebp                           # Set the stack frame terminator.

    call _init                          # Call the global constructors

    push $page_tables                   # push the address of the starter page tables
    call setup_paging                   # build the init page tables
    add %esp, 4                         # clear the stack

    /* push the heap beginning and end onto the stack. */
    push $heap_end
    push $heap_begin
    call initialize_standard_library        # call the standard library initializer
    add %esp, 8                         # clear the stack

    call main

loop:                                   # Create a loop point for idle.
    hlt                                 # Halt the system until an interrupt
    jmp loop                            # Jump to the loop point.

    call _fini                          # Call the global destructors

.global init_paging
# initialize the paging system on the processor
init_paging:
    mov $page_tables, %eax              // move the location of the page tables into eax
    mov %eax, %cr3                      // copy the contents of eax into cr3
    mov %cr0, %eax                      // copy the contents of cr0 into eax
    or %eax, 0x80000001                 // ensure the PG and PE bits are set in cr0
    mov %eax, %cr0                      // copy the contents of eax into cr0
    ret                                 // return

.global gdt_flush
.extern gp
#   flushes the gdt with new segments.
gdt_flush:
    push %ebp               # maintain the stack frame by pushing the previous function's ebp
    mov %esp, %ebp          # set the current function's ebp
    lgdt (gp)               # load the GDT location into the GDTR
    mov $0x10, %ax          # set %eax to the ring-0 data segment pointer
    mov %ax, %fs            # set the ds,es,fs,gs, and ss segment selectors to the data segment
    mov %ax, %ds            # 
    mov %ax, %es            # 
    mov %ax, %gs            # 
    mov %ax, %ss            # 
    jmp $0x8,$flush_seg     # jump into the code segment with a far jump to the ring-0 code seg pointer
flush_seg:
    mov %ebp, %esp          # clear any local variables and data on the stack
    pop %ebp                # restore the calling functions ebp
    ret                     # return

.section .bss                             # Align the stack on a 4KB page boundary
stack_bottom:
.skip 16384                              # Sets the size of the stack
stack_top:
.align 4096                             # Align the heap on a 4KB page boundary
page_tables:
.skip 16384                             # Create space for the paging tables.
.section .heap
.align 4096
heap_begin:
.zero 16384                              # Set the size of the heap
heap_end: