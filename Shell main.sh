#!/bin/bash

#---------------------------- Initialisation des variables --------------------

script_dir=$(dirname "$0")

commande=""    #pour utiliser "read" -> permet à l'utilisateur de saisir une commande

nom_csv=""

chemin_csv="$script_dir/Cy_Truck/data/$nom_csv.cvs"  #chemin du fichier csv

option_traitement=()    #Tableau de char -> car plusieurs options  

#-----------------------------------------------------------------------------------------

#---------------------------- Gestion dossier --------------------
dossier="progc"
dossier2="data"
dossier3="images"
dossier4="temp"
executable="Cy_Truck"
fichiers=("Cy_Truck.c" "Makefile" "Outils_AVL.h" "Traitements.c" "Traitements.h" "outils_AVL.c")
fichier2="data.csv"

existance_executable()
{
  tentatives_max=3
  tentatives=0

  while [ ! -e "$script_dir/$dossier/$executable" ] && [ "$tentatives" -lt "$tentatives_max" ]; do
    ((tentatives++))
    echo "L'éxécutable: $executable n'existe pas. Tentative $tentatives de $tentatives_max."
    echo "Compilation en cours...."
    compiler_c
  done

  if [ -e "$script_dir/$dossier/$executable" ]; then
    echo "L'éxécutable: $executable existe."
    "$script_dir/$dossier/$executable"
  else
    echo "Impossible de compiler l'éxécutable après $tentatives_max tentatives."
  fi
}

existance_dossier()
{
# Existence fichiers de progc ?
for fichier in "${fichiers[@]}"; do
    chemin="$script_dir/$dossier/$fichier"
    if [ -e "$chemin" ]; then
        echo "Le fichier $chemin existe."
    else    
        echo "Le fichier $chemin n'existe pas."
    fi
done

# Existence fichier data ?
chemin2="$dossier2/$fichier2"
if [ -e "$dossier2" ]; then
    echo "Le fichier $fichier2 existe."
else
    echo "Le fichier $fichier2 n'existe pas."
fi

# Exitence dossier images ?
if [ -d "$dossier3" ]; then
    echo "Le dossier \ $dossier \ existe"
else
    mkdir "$dossier"
    echo "Le dossier \ $dossier \ n'existait pas mais a été crée"
fi

# Exitence dossier temp ?
if [ -d "$dossier4" ]; then
    echo "Le dossier \ $dossier4 existe"
else
    mkdir "$dossier4"
    echo "Le dossier \ $dossier4 \ n'existait pas mais a été crée"
fi
}


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


compiler_c ()
{
make -C $script_dir/progc #Indique au make de rechercher le makefile dans progc
}


obtention_utilisation ()
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


verif_option_traitement ()
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


