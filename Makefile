all: Cy_Truck

Cy_Truck: Cy_Truck.c
		gcc -o Cy_Truck Cy_Truck.c

run: Cy_Truck
		./Cy_Truck -o option_choisie -f fichier.txt
