export LIBC_INCLUDE :=-I$(INCDIR)/libc

libc.a: core.o string.o stdio.o stdlib.o ctype.o
	$(AR) rcs $@ $^
	mv $@ ..
	
core.o: core.cpp
	$(GPP) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) -I$(INCDIR) $(LIBC_INCLUDE) -c $^ -o $@
	
string.o:
	$(MAKE) --directory=string

stdio.o:
	$(MAKE) --directory=stdio	

stdlib.o:
	$(MAKE) --directory=stdlib

ctype.o:
	$(MAKE) --directory=ctype

clean:
	rm -f *.o