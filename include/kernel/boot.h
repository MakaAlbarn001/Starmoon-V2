/****************************************************
 *  boot.h - system boot functions                  *
 *  function list:                                  *
 *      set_basic_gdt()                             *
 ****************************************************/

 void set_basic_gdt();
 extern "C" void gdt_flush();