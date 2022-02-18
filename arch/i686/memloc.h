#pragma once

#define PIC_MAS 0x20            // port address of the Master Programmable Interrupt Controller(PIC)
#define PIC_SLV 0xA0            // port address of the Slave Programmable Interrupt Controller(PIC)

#if defined(_VGA_)
#define VGA_MEM 0xB8000
#endif