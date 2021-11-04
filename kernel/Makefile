CPPSRC := $(wildcard *.cpp)
CPPOBJ := $(subst .cpp,.o,$(CPPSRC))

all: kernel.o

kernel.o: $(CPPOBJ)
	$(LD) $^ -r -o $@
	rm $(CPPOBJ)

%.o: %.cpp
	$(GPP) -I$(INCDIR) $(CFLAGS) $(CPPFLAGS) -c $^ -o $@

.phony: clean
clean:
	rm -rf *.o