default: myprogram

myprogram: libmyprogram.a myprogram.c
	clang myprogram.c libmyprogram.a -o myprogram
	
libmyprogram.a: file1.o
	ar -rcv $@ $^
	
