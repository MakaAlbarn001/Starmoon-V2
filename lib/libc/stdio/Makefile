SRC_LST :=$(wildcard *.cpp)
OBJ_LST :=$(subst .cpp,.o,$(SRC_LST))

stdio.o: $(OBJ_LST)
	$(LD) $(LDFLAGS) -r $^ -o $@
	mv $@ ..
	rm *.o

%.o: %.cpp
	$(GPP) $(CFLAGS) $(CPPFLAGS) $(LIBC_INCLUDE) -I$(INCDIR) -c $^ -o $@

clean:
	rm -f *.o