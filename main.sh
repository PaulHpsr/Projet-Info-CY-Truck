#!/bin/bash

#---------------------------- Initialisation des variables --------------------

# Répertoire contenant le script en cours d'éxécution
script_dir=$(dirname "$0")

commande=()    #pour utiliser "read" -> permet à l'utilisateur de saisir une commande

nom_csv=""

chemin_csv="$script_dir/data/$nom_csv.csv"  #chemin du fichier csv

option_traitement=()    #Tableau de char -> car plusieurs options  

#-----------------------------------------------------------------------------------------

#---------------------------- Gestion dossier --------------------
dossier="progc"
dossier2="data"
dossier3="images"
dossier4="temp"
executable="CY_Truck"
fichiers=("Cy_Truck.c" "Makefile" "Outils_AVL_S.h" "Outils_AVL_T.h" "Outils_AVL_T.h" "Traitements.c" "Traitements.h" "Outils_AVL_S.c")
fichier2="$nom_csv"

existence_executable()
{
  tentatives_max=3
  tentatives=0

  while [ ! -e "$script_dir/$dossier/$executable" ] && [ "$tentatives" -lt "$tentatives_max" ]; do  #Le programme va tenter de compiler tant que l'exec n'existe pas -> max 3x
    ((tentatives++))
    echo "L'exécutable: $executable n'existe pas. Tentative $tentatives sur $tentatives_max."$'\n'
    echo "Compilation en cours...."$'\n'
    compiler_c
  done

  if [ $? -ne 0 ]; then                                                             #Revérifi si le C est bien compilé
    echo "ERREUR : Impossible de compiler le programme, veuillez vérifier"$'\n'     #Renforcer le code afin de ne pas executer un C mal compilé
    return 1
  fi

  if [ -e "$script_dir/$dossier/$executable" ]; then
    echo "L'exécutable: $executable existe."$'\n'
    return 0                                                                                  #Afin de récupérer la valeur de retour de la fonction plus tard dans le "Main"
  else
    echo "Impossible de compiler l'exécutable après $tentatives_max tentatives."$'\n'        
    return 1
  fi
}

existence_dossier()
{
# Existence fichiers de progc ?
for fichier in "${fichiers[@]}"; do                  #Va vérifier dans le dossier progc si chacuns des fichiers sont présent
    chemin="$script_dir/$dossier/$fichier"
    if [ -e "$chemin" ]; then
        echo "Le fichier $chemin existe."$'\n'
    else    
        echo "Le fichier $chemin n'existe pas."$'\n'
        echo "Veuiller corriger l'erreur puis relancer...."$'\n'
        return 1
    fi
done

# Existence fichier data ?
chemin2="$script_dir/$dossier2/$fichier2"
if [ -e "$chemin2" ]; then
    echo "Le fichier $fichier2 existe."$'\n'
else
    echo "Le fichier $fichier2 n'existe pas."$'\n'
    echo "Veuiller corriger l'erreur puis relancer...."$'\n'
    return 1
fi

# Exitence dossier images ?
if [ -d "$dossier3" ]; then
    echo "Le dossier \ $dossier \ existe"$'\n'
else
    mkdir "$script_dir/$dossier3"                                                                           #Créer le dossier s'il est inexistant
    echo "Le dossier \ $dossier \ n'existait pas mais a été crée"$'\n'
fi

# Exitence dossier temp ?
if [ -d "$dossier4" ]; then
    echo "Le dossier \ $dossier4 existe"$'\n'
    # Vider le contenu du dossier temp
    rm -r "$dossier4"/* #Uniquement les fichier + sous dossier
    echo "Le dossier \ $dossier4 \ a été vidé"$'\n'
else
    mkdir "$script_dir/$dossier4"
    echo "Le dossier \ $dossier4 \ n'existait pas mais a été crée"$'\n'
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
}


compiler_c ()
{
make -C "$script_dir/$dossier" #Indique au make de rechercher le makefile dans progc
}


obtention_utilisation ()
{
#Demander à l'utilisateur de saisir une commande
#Tant qu'il y a - de 4 éléments dans la commande
while [ "${#commande[@]}" -lt 4 ]; do    
  commande=()   #On réinitialise la valeur de commande
  show_help
  read -r -p "Entrer une commande : " -a commande  #On lis l'entrée utilisateur
  echo "Commande après la saisie : ${commande[@]}"
done

while getopts ":f:o:" opt; do
    case $opt in
        f)
            nom_csv="$OPTARG"
            echo "$nom_csv"
            ;;
        o)
            option_traitement+=("$OPTARG")
            echo "$option_traitement"
            ;;
        \?)
            echo "Option invalide: -$OPTARG"$'\n' >&2
            show_help
            ;;
        :)
            echo "L'option -$OPTARG requiert un argument."$'\n' >&2
            show_help
            ;;
    esac
done

#Si les options ne sont pas valides, réitérer le processus d'obtiention de la commande
while [ "$(verif_option_traitement)" -ne 0 ]; do # -ne pour comparer des valeurs numériques (au lieu de != 0)
  echo "Les options ne sont pas valides"$'\n'
  commande=()  # Réinitialiser la commande pour relancer la saisie
  option_traitement=()  # Réinitialiser les options pour une nouvelle saisie
  
while [ "${#commande[@]}" -lt 4 ]; do    
  commande=()   #On réinitialise la valeur de commande
  show_help
  echo "Entrer une commande :"$'\n'
  read -r -p "Entrer une commande : " commande  #On lis l'entrée utilisateur
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
       echo "Option invalide: -$OPTARG"$'\n' >&2
        show_help
        ;;
     :)
       echo "L'option -$OPTARG requiert un argument."$'\n' >&2
        show_help
       ;;
   esac
  done
done
}


verif_option_traitement ()
{

#Vérifier si l'utilisateur a saisi une option valide
for i in "${option_traitement[@]}";           #Parcourir le tableau des options afin de vérifier si les options sont correctes
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
for i in "${option_traitement[@]}";          #On va parcourir les options et effectuer le traitement associé 
do                                           #Si commande -h on ne prend en compte que celle-ci
  if [[ $i == "-h" ]]; then 
    show_help
    return 0
  fi
done

for i in "${option_traitement[@]}";          #On va parcourir une deuxième fois les options et effectuer le traitement associé si pas -h
do
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
          echo "Option non reconnue : $i"$'\n'
          show_help
          ;;
   esac
done
}
#-------------------------------------------------------------------------



#------------------------------ GnuPlot ------------------------------

traitement_gnuplot_d1()
{
#Format du txt : Conducteur nb_trajet
#Trie le fichier decroissant

# Script Gnuplot
sort -k2,2 -r "$script_dir/temp/data_d1.txt" | gnuplot << EOF #Bloc pour envoyer plusieurs comandes à Gnuplot
set terminal pngcairo enhanced font "arial,10" size 800,600 #Def. le terminal de sortie en .png en 800x600p
set output "$script_dir/images/histogramme_d1.png" #Def. le chemin de sortie

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

# Vider le contenu du dossier temp
rm -r "$dossier4"/* #Uniquement les fichier + sous dossier
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

# Vider le contenu du dossier temp
rm -r "$dossier4"/* #Uniquement les fichier + sous dossier
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

# Vider le contenu du dossier temp
rm -r "$dossier4"/* #Uniquement les fichier + sous dossier
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

# Vider le contenu du dossier temp
rm -r "$dossier4"/* #Uniquement les fichier + sous dossier
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

# Vider le contenu du dossier temp
rm -r "$dossier4"/* #Uniquement les fichier + sous dossier
}

#-------------------------------------------------------------------------


#------------------------------ Main ------------------------------

#Ici la partie principale du programme

echo "#-----------------------------------------------#"$'\n'
echo "Bienvenue dans le Cy Truck Data Analyser"$'\n'
echo "#-----------------------------------------------#"$'\n'
show_help                                                          #1) Montrer l'utilisation du programme
obtention_utilisation
echo "$nom_csv"
echo "$option_traitement"
#2) Obtenir la commande de l'utilisateur (connaitre les options + nom du fichier csv)
echo "#-----------------------------------------------#"$'\n'
echo "VERIFICATION DE L'INTEGRITE DE L'OUTIL..."$'\n'
echo "#-----------------------------------------------#"$'\n'
existence_dossier                                                  #3) Vérifier si tous les fichiers existes (maintenant que l'on peut vérifier l'existence du csv)
retour=$?                                                            
if [ $retour -eq 1 ]; then
  echo "ERREUR : L'outil n'est pas complet, veuillez vérifier"$'\n'        #Renvoyer une ERREUR et arrêter le programme si l'on des fichiers important manque -> demander à l'utilisateur de le récupérer
  exit 1
fi
echo "#-----------------------------------------------#"$'\n'
echo "EXECUTION DU PROGRAMME..."$'\n'
echo "#-----------------------------------------------#"$'\n'
existence_executable                                                #4) Vérifier si l'exécutable est déjà existant -> l'exécuter ou le compiler en fonction
retour=$?
if [ $retour -eq 1 ]; then
  echo "ERREUR : Impossible de compiler le programme, veuillez vérifier"$'\n'            #Renvoyer une ERREUR et arrêter le programme si l'on arrive pas à compiler
  exit 1
else
start=$(date +%s)
./progc/CY_Truck "$chemin_csv" "$option_traitement"       #5) Exécuter le programme -> time pour obtenir le temps précis d'éxecution du C        
end=$(date +%s)
temps=$((end - start))
echo "Durée d'exécution: ${temps} secondes"$'\n'
fi

echo "#-----------------------------------------------#"$'\n'
echo "CREATION DE L'HISTOGRAMME...."$'\n'
echo "#-----------------------------------------------#"$'\n'
#Timer interne
start=$(date +%s)
crea_histo                                                                       #Ici un timer moins précis puisque l'on va obtenir le temps d'exécution d'une fonc° du shell  (différence entre la date de début -> start et la date de fin -> end)
end=$(date +%s)
temps=$((end - start))
echo "Durée d'exécution: ${temps} secondes"$'\n'
echo "#-----------------------------------------------#"$'\n'
echo "LE PROGRAMME A ETE EXECUTE"$'\n'                                            #6) Fermer le programme lorsque celui-ci à finis son travail
echo "#-----------------------------------------------#"$'\n'
exit 0
#-------------------------------------------------------------------------
