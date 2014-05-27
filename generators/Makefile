all: 	bin/opalrivetpythia8
	
obj/opalrivetpythia8.o: src/opalrivetpythia8.cc
	gcc -c src/opalrivetpythia8.cc -o obj/opalrivetpythia8.o -I./  -I../top/usr/include
	
	
	
bin/opalrivetpythia8: obj/opalrivetpythia8.o
	gcc -lpythia8tohepmc  obj/opalrivetpythia8.o -o bin/opalrivetpythia8  -L../top/usr/lib64
