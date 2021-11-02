ASMSRC:=$(wildcard *.s)
CPPSRC:=$(wildcard *.cpp)
CRTSRC:=$(filter crt%.s, $(ASMSRC))
ARCHSRC:=$(filter-out crt%.s, $(ASMSRC))
CRTOBJ:=$(subst .s,.o,$(CRTSRC))
ARCHOBJ:=$(subst .s,.o,$(ARCHSRC))
CPPOBJ:=$(subst .cpp,.o,$(CPPSRC))

.DEFAULT_GOAL := arch.o

arch.o: $(CRTOBJ) $(ARCHOBJ) $(CPPOBJ)
	mv $(CRTOBJ) ..
	$(LD) $(filter-out boot.o,$(ARCHOBJ)) $(CPPOBJ) -r -o $@
	mv boot.o ../crt0.o
	mv $@ ..
	rm *.o

%.o: %.s
	$(AS) $< -o $@

%.o: %.cpp
	$(GPP) -I$(INCDIR) $(CFLAGS) $(CPPFLAGS) -c $^ -o $@
