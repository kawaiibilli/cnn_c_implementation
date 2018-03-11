run:		main.c model.o layers.o types.o
			gcc main.c -o run

model.o:	model.c types.o layers.o
			gcc -c model.c

layers.o:	layers.c types.o
			gcc -c layers.c

types.o:	types.h
			gcc -c types.h -o types.o

clean:		
			rm types.o layers.o model.o run