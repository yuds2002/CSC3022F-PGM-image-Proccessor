CC=g++ # the compiler name
CCFLAGS=-g -fsanitize=address -std=c++11 # flags passed to compiler -fsanitize=address
SOURCES=ConnectedComponent.cpp driver.cpp PGMimageProcessor.cpp
OBJECTS=ConnectedComponent.o driver.o PGMimageProcessor.o

.cpp.o:
	$(CC) $(CCFLAGS) -c $<

myprog: $(OBJECTS)
	$(CC) $(CCFLAGS) $(OBJECTS) -o driver

clean:
	rm -f *.o driver
