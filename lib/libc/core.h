#pragma once

#define MEM_USED 1 << 15
#define MEM_EOM 1 << 14

extern unsigned short int *heap_ptr;

extern "C" void initialize_standard_library(void *heap_begin, void *heap_end);