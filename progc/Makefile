all: CY_Truck


SRCS = $(wildcard *.c)
HEADERS = $(wildcard *.h)

CY_Truck: $(SRCS) $(HEADERS)
	gcc -o "$@" $(SRCS) -g -Wno-everything -pthread -lm 

clean:
	rm -f CY_Truck