#!/bin/bash

#---------------------------- Initialisation des variables --------------------

script_dir=$(dirname "$0")

commande=""    #pour utiliser "read" -> permet à l'utilisateur de saisir une commande

nom_csv=""

chemin_csv="$script_dir/Cy_Truck/data/$nom_csv.cvs"  #chemin du fichier csv

option_traitement=()    #Tableau de char -> car plusieurs options  

#-----------------------------------------------------------------------------------------



#------------------------------ Fonctions ------------------------------

# Fonction pour afficher l'aide
show_help() 
{
    echo "------------------------------"$'\n'
    echo "Commandes :"$'\n'
    echo "  -h : Affiche l'aide"$'\n'
    echo "Utilisation: $0 -f <nom_fichier_csv> -o <option_traitement>"$'\n'
    echo "------------------------------"
    echo "Options : "$'\n' # $'\n' -> saut de ligne
    echo "1) Conducteurs avec le plus de trajets : option -d1"$'\n'
    echo "2) Conducteurs et la plus grande distance: option -d2"$'\n'
    echo "3) Les 10 trajets les plus longs : option -l"$'\n'
    echo "4) Les 10 villes les plus traversées : option -t"$'\n'
    echo "5) Statistiques sur les étapes : option -s"$'\n'
    echo "------------------------------"$'\n'
    exit 1
}


compiler_c
{
make -C $script_dir/Cy_Truck/progc #Indique au make de rechercher le makefile dans progc
}


obtention_utilisation
{
#Demander à l'utilisateur de saisir une commande
while[ "$commande" -ne 4 ]; do         
  echo show_help
  echo "Entrer une commande :"$'\n'
  read -r commande
done

while getopts ":f:o:" opt; do
    case $opt in
        f)
            nom_csv="$OPTARG"
            ;;
        o)
            option_traitement+=("$OPTARG")
            ;;
        \?)
            echo "Option invalide: -$OPTARG" >&2
            show_help
            ;;
        :)
            echo "L'option -$OPTARG requiert un argument." >&2
            show_help
            ;;
    esac
done
while [ "$(verif_option_traitement)" != "0" ]; do
  echo "Les options ne sont pas valides"
  commande=""  # Réinitialiser la commande pour relancer la saisie
  option_traitement=()  # Réinitialiser les options pour une nouvelle saisie
  while [ "$commande" -ne 4 ]; do
   show_help
    echo "Entrer une commande :"
    read -r commande
  done

  while getopts ":f:o:" opt; do
    case $opt in
     f)
        nom_csv="$OPTARG"
        ;;
     o)
       option_traitement+=("$OPTARG")
       ;;
      \?)
       echo "Option invalide: -$OPTARG" >&2
        show_help
        ;;
     :)
       echo "L'option -$OPTARG requiert un argument." >&2
        show_help
       ;;
   esac
  done
done
}


verif_option_traitement
{

#Vérifier si l'utilisateur a saisi une option valide
for i in "${option_traitement[@]}"; 
do
    if [[ $i == "-h"]]; then 
      show_help
    fi
    if [[ $i != "-d1" && $i != "-d2" && $i != "-l" && $i != "-t" && $i != "-s" ]]; then
      echo "Option invalide : $i"$'\n'
      show_help
      exit 1
    else
      echo "Option valide : $i"$'\n'
      exit 0
    fi
}

#-------------------------------------------------------------------------

