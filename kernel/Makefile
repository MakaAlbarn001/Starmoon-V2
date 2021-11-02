CPPSRC := $(wildcard *.cpp)
CPPOBJ := $(subst .cpp,.o,$(CPPSRC))

all: kernel.o

kernel.o: $(CPPOBJ)
	$(LD) $^ -r -o $@

%.o: %.cpp
	$(GPP) -I$(INCDIR) $(CFLAGS) $(CPPFLAGS) -c $^ -o $@