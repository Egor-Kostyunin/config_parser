CC = gcc
SO_FLAGS = -shared -fPIC

config_parser: include/config_parser.h src/*.c
	$(CC) $(SO_FLAGS) -o $@.so src/*.c -I ./include

example: config_parser
	$(CC) -o $@ examples/example1.c config_parser.so -Wl,-rpath,. -I ./include
