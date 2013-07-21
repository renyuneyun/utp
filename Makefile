objects = main.o io.o operate.o ui.o
CCOMPILER = gcc
utp : $(objects)
	$(CCOMPILER) -o utp $(objects)
main.o : main.c ui.h
	$(CCOMPILER) -c main.c
io.o : io.c io.h def.h
	$(CCOMPILER) -c io.c
operate.o : operate.c operate.h
	$(CCOMPILER) -c operate.c
ui.o : ui.c ui.h dec.h def.h
	$(CCOMPILER) -c ui.c
.PJONY : clean
clean :
	-rm utp $(objects)
