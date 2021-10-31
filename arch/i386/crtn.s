.section .init
.global _init
.type _init, @function
_init:
    popl %ebp
    ret

.section .fini
.global _fini
.type _fini, @function
_fini:
    popl %ebp
    ret
   