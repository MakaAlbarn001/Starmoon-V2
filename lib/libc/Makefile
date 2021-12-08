export LIBC_INCLUDE :=-I$(INCDIR)/libc

libc.a: core.o string.o stdio.o stdlib.o ctype.o
	$(AR) rcs $@ $^
	mv $@ ..
	rm *.o
	
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
	$(MAKE) clean --directory=stdlib
	$(MAKE) clean --directory=string
	$(MAKE) clean --directory=stdio
	$(MAKE) clean --directory=ctype
	rm -f *.o