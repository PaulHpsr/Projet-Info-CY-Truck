all: CY_Truck

CC = gcc
override CFLAGS += -g -Wno-everything -pthread -lm 

##ajout pour compiler les fichier de src directement
SRCS = $(wildcard *.c)
HEADERS = $(wildcard *.h)

CY_Truck: $(SRCS) $(HEADERS)
	$(CC) -o "$@" $(SRCS) $(CFLAGS)

clean:
	rm -f Cy_Truck