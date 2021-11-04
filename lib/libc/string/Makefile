SRC_LIST := $(wildcard *.cpp)
OBJ_LIST := $(subst .cpp,.o,$(SRC_LIST))

string.o: $(OBJ_LIST)
	$(LD) $(LDFLAGS) -r $^ -o $@
	mv $@ ..
	rm *.o

%.o: %.cpp
	$(GPP) $(CFLAGS) $(CPPFLAGS) $(LIBC_INCLUDE) -I$(INCDIR) -c $^ -o $@

clean:
	rm -f *.o
