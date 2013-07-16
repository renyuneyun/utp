VPATH = src
objects = main.o io.o operate.o
ute : $(objects)
	gcc -o ute $(objects)
main.o : main.c dec.h
	gcc -c main.c
io.o : io.c io.h
	gcc -c io.c
operate.o : operate.c operate.h
	gcc -c operate.c
.PJONY : clean
clean :
	-rm uts $(objects)
