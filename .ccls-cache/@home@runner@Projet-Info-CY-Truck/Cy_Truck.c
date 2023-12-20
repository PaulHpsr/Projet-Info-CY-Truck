#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"
#include "header.c"


int main(int argc, char *argv[]) {
    if (argc < 5) {
        fprintf(stderr, "Usage: %s -o <option_choisie> -f <fichier>\n", argv[0]);
        return 1;
    }

    // Récupérer les options
    char *option = argv[2];  // -o option_choisie
    char *fichier = argv[4]; // -f fichier

    printf("Option choisie : %s\n", option);
    printf("Fichier : %s\n", fichier);

    // Traitement des options

  if (strcmp(option, "-d1") == 0) {
      traitement_d1();
  } else if (strcmp(option, "-d2") == 0) {
      traitement_d2();
  } else if (strcmp(option, "-l") == 0) {
      traitement_l();
  } else if (strcmp(option, "-t") == 0) {
      traitement_t();
  } else if (strcmp(option, "-s") == 0) {
      traitement_s();
  } else {
      fprintf(stderr, "Option invalide : %s\n", option);
      return 1;
  }

    return 0;
}