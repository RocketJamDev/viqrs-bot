# Compiler
CC = g++

# Flags
CFLAGS = -fsanitize=undefined -g -Wall

#Librearies
LIBS = -L lib/QR-Code-generator -lqrcodegen

# Create
viqrs-bot: viqrs clean

viqrs: main.o vipscode.o
	rm -f bin/viqrs
	$(CC) $(CFLAGS) -o bin/viqrs main.o vipscode.o $(LIBS)

main.o: src/main.cpp src/vipscode.hpp
	$(CC) $(CFLAGS) -c src/main.cpp

vipscode.o: src/vipscode.hpp
	$(CC) $(CFLAGS) -c src/vipscode.cpp

clean:
	$(RM) count *.o *~
