.PHONY: test clean

CC = gcc
CC_OPTIONS = -Wall -Wextra
EXECUTABLES = shmem_writer shmem_reader

test: shmem_writer shmem_reader
	./shmem_writer 
	./shmem_reader
	
shmem_writer: shmem_writer.c ipc.key
	$(CC) $(CC_OPTIONS) -o shmem_writer shmem_writer.c

shmem_reader: shmem_reader.c ipc.key
	$(CC) $(CC_OPTIONS) -o shmem_reader shmem_reader.c

clean: 
	rm $(EXECUTABLES)
