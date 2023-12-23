#!/bin/bash

#---------------------------- Initialisation des variables --------------------

# Répertoire contenant le script en cours d'éxécution
script_dir=$(dirname "$0")

commande=""    #pour utiliser "read" -> permet à l'utilisateur de saisir une commande

nom_csv=""

chemin_csv="$script_dir/Cy_Truck/data/$nom_csv.csv"  #chemin du fichier csv

option_traitement=()    #Tableau de char -> car plusieurs options  

#-----------------------------------------------------------------------------------------

#---------------------------- Gestion dossier --------------------
dossier="progc"
dossier2="data"
dossier3="images"
dossier4="temp"
executable="Cy_Truck"
fichiers=("Cy_Truck.c" "Makefile" "Outils_AVL.h" "Traitements.c" "Traitements.h" "outils_AVL.c")
fichier2="$nom_csv.csv"

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
    return 0
  else
    echo "Impossible de compiler l'éxécutable après $tentatives_max tentatives."
    return 1
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
        echo "Veuiller corriger l'erreur puis relancer...."
        return 1
    fi
done

# Existence fichier data ?
chemin2="$script_dir/$dossier2/$fichier2"
if [ -e "$chemin2" ]; then
    echo "Le fichier $fichier2 existe."
else
    echo "Le fichier $fichier2 n'existe pas."
    echo "Veuiller corriger l'erreur puis relancer...."
    return 1
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
    # Vider le contenu du dossier temp
    rm -r "$dossier4"/* #Uniquement les fichier + sous dossier
    echo "Le dossier \ $dossier4 \ a été vidé"
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
while [ "$(verif_option_traitement)" -ne 0 ]; do # -ne pour comparer des valeurs numériques (au lieu de != 0)
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
    if [[ $i == "-h" ]]; then 
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
done
}

crea_histo()
{
for i in "${option_traitement[@]}"; 
do
  if [[ $i == "-h" ]]; then 
    show_help
  else
    case "$i" in
        -d1)
           traitement_gnuplot_d1
            ;;
       -d2)
            traitement_gnuplot_d2
            ;;
        -l)
           traitement_gnuplot_l
           ;;
       -t)
           traitement_gnuplot_t
           ;;
       -s)
          traitement_gnuplot_s
           ;;
        \?)
          echo "Option non reconnue : $i"
          show_help
          ;;
   esac
  fi
done
}
#-------------------------------------------------------------------------



#------------------------------ GnuPlot ------------------------------

traitement_gnuplot_d1()
{
#Format du txt : Conducteur valeur_trajet
#Trie le fichier decroissant

# Script Gnuplot
sort -k2,2 -r "$script_dir/temp/data_d1.txt" | gnuplot << EOF #Bloc pour envoyer plusieurs comandes à Gnuplot
set terminal pngcairo enhanced font "arial,10" size 800,600 #Def. le terminal de sortie en .png en 800x600p
set output "$script_dir/images/histogramme_d1.png" #Def. le fichier de sortie

# Paramètres du graphique
set style fill solid
set boxwidth 0.8 relative
set yrange [0:*]
set xlabel "Nombre de trajets"
set ylabel "DRIVER NAMES"
set title "Option -d1 : NB routes = f(Driver)"

# Tracer l'histogramme horizontal
plot 'data_d1.txt' using 2:yticlabels(1) with boxes title "Nombre de trajets" #Utilise les données du txt pour histo horizontal
EOF

}

traitement_gnuplot_d2()
{
#Format du txt : Conducteur valeur_distance
#Trie le fichier decroissant

# Script Gnuplot
sort -k2,2 -r "$script_dir/temp/data_d2.txt" | gnuplot << EOF #Bloc pour envoyer plusieurs comandes à Gnuplot
set terminal pngcairo enhanced font "arial,10" size 800,600 #Def. le terminal de sortie en .png en 800x600p
set output "$script_dir/images/histogramme_d2.png" #Def. le fichier de sortie

# Paramètres du graphique
set style fill solid
set boxwidth 0.8 relative
set yrange [0:*]
set xlabel "DISTANCE (Km)"
set ylabel "DRIVER NAMES"
set title "Option -d2 : Distance = f(Driver)"

# Tracer l'histogramme horizontal
plot 'data_d2.txt' using 2:yticlabels(1) with boxes title "Nombre de trajets" #Utilise les données du txt pour histo horizontal
EOF

}

traitement_gnuplot_l()
{
#Format du txt : ID valeur_distance
#Trie le fichier decroissant

# Script Gnuplot
sort -k1,1 -r "$script_dir/temp/data_l.txt" | gnuplot << EOF #Bloc pour envoyer plusieurs comandes à Gnuplot
set terminal pngcairo enhanced font "arial,10" size 800,600 #Def. le terminal de sortie en .png en 800x600p
set output "$script_dir/images/histogramme_l.png" #Def. le fichier de sortie

# Paramètres du graphique
set style fill solid
set boxwidth 0.8 relative
set yrange [0:*]
set xlabel "ROUTE ID"
set ylabel "DISTANCE (Km)"
set title "Option -l : Distance = f(Driver)"

# Tracer l'histogramme verticale
plot 'data_l.txt' using 2:xticlabels(1) with boxes title "Nombre de trajets" #Utilise les données du txt pour histo verticale
EOF

}

traitement_gnuplot_t()
{
#Format du txt : Ville nb_trajets_tot nb_départs

#Script Gnuplot

sort -k2,2 -r "$script_dir/temp/data_t.txt" | gnuplot << EOF
set terminal pngcairo enhanced font "arial,10" size 800,600
set output "$script_dir/images/histogramme_t.png"

# Paramètres du graphique
set style fill solid
set boxwidth 0.4
set yrange [0:*]
set xlabel "TOWN NAMES"
set ylabel "NB TRAJETS"
set title "Option -t : Nb routes = f(Towns)"

# Tracer l'histogramme regroupé
plot 'data_t.txt' using 2:xticlabels(1) title "Nombre total de trajets", '' using 3 title "Nombre de départs de trajets" lc rgb "orange"
EOF
}


traitement_gnuplot_s()
{
#Format du txt : ID dist_min dist_max dist_moy

#Script Gnuplot
sort -k4,4 -r "$script_dir/temp/data_s.txt" | gnuplot << EOF
set terminal pngcairo enhanced font "arial,10" size 800,600
set output "$script_dir/images/histogramme_s.png"

# Paramètres du graphique
set style fill transparent solid 0.3
set boxwidth 0.5
set yrange [0:*]
set xlabel "ID"
set ylabel "DISTANCE (Km)"
set title "Option -s : Distance = f(Route)"

# Charger les données
plot 'data_s.txt' using 1:2:3:4 with filledcurves notitle lc rgb "skyblue", \
     '' using 1:5:6:7 with filledcurves notitle lc rgb "pink", \
     '' using 1:8:9:10 with filledcurves notitle lc rgb "lightgreen", \
     '' using 1:4 with lines title "Moyenne" lc rgb "blue", \
     '' using 1:2 with lines title "Minimum" lc rgb "red", \
     '' using 1:3 with lines title "Maximum" lc rgb "green"
EOF
}

#-------------------------------------------------------------------------


#------------------------------ Main ------------------------------

echo "#-----------------------------------------------#"
echo "Bienvenue dans le Cy Truck Data Analyser"
echo "#-----------------------------------------------#"
show_help
obtention_utilisation
echo "#-----------------------------------------------#"
echo "VERIFICATION DE L'INTEGRITE DE L'OUTIL..."
echo "#-----------------------------------------------#"
existance_dossier
retour=$?
if [ $retour -eq 1 ]; then
  echo "ERREUR : L'outil n'est pas complet, veuillez vérifier"
  exit 1
fi
echo "#-----------------------------------------------#"
echo "EXECUTION DU PROGRAMME..."
echo "#-----------------------------------------------#"
existance_executable
retour=$?
if [ $retour -eq 1 ]; then
  echo "ERREUR : Impossible de compiler le programme, veuillez vérifier"
  exit 1
else
time "$script_dir/$dossier/$executable" "$chemin_csv" "$option_traitement"
fi

echo "#-----------------------------------------------#"
echo "CREATION DE L'HISTOGRAMME...."
echo "#-----------------------------------------------#"
#Timer interne
start=$(date +%s)
crea_histo
end=$(date +%s)
temps=$(end - start)
echo "Durée d'exécution: ${temps} secondes"
echo "#-----------------------------------------------#"
echo "LE PROGRAMME A ETE EXECUTE"
echo "#-----------------------------------------------#"
exit 0
#-------------------------------------------------------------------------