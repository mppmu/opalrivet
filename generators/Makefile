all: 	bin/opalrivetpythia8 bin/opalrivetevtgen
	
obj/opalrivetpythia8.o: src/opalrivetpythia8.cc
	gcc -c src/opalrivetpythia8.cc -o obj/opalrivetpythia8.o -I./  -I../top/usr/include
	
	
	
bin/opalrivetpythia8: obj/opalrivetpythia8.o
	gcc -lpythia8tohepmc  obj/opalrivetpythia8.o -o bin/opalrivetpythia8  -L../top/usr/lib64




obj/opalrivetevtgen.o: src/opalrivetevtgen.cc
	gcc $(shell root-config --cflags) -c src/opalrivetevtgen.cc -o obj/opalrivetevtgen.o -I./  -I../top/usr/include
	
	
	
bin/opalrivetevtgen: obj/opalrivetevtgen.o
	gcc  -lEvtGenExternal $(shell  root-config --libs)  obj/opalrivetevtgen.o -o bin/opalrivetevtgen  -L../top/usr/lib64
