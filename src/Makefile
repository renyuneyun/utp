objects = main.o io.o operate.o ui.o
utp : $(objects)
	gcc -o utp $(objects)
main.o : main.c ui.h
	gcc -c main.c
io.o : io.c io.h def.h
	gcc -c io.c
operate.o : operate.c operate.h
	gcc -c operate.c
ui.o : ui.c ui.h dec.h def.h
	gcc -c ui.c
.PJONY : clean
clean :
	-rm utp $(objects)
