#!/bin/bash

#---------------------------- Initialisation des variables --------------------

# Répertoire contenant le script en cours d'éxécution
script_dir=$(dirname "$0")


nom_csv=""




#-----------------------------------------------------------------------------------------



#---------------------------- Gestion dossier --------------------

fichiers=("Cy_Truck.c" "Makefile" "Outils_AVL_S.h" "Outils_AVL_T.h" "Outils_AVL_T.h" "Outils_AVL_S.c")

existence_executable()
{

  if [ ! -e "$script_dir/progc/CY_Truck" ] ; then  #Le programme va tenter de compiler
    ((tentatives++))
    echo "L'exécutable: Cy_Truck n'existe pas."$'\n'
    echo "Compilation en cours...."$'\n'
    compiler_c
  fi

  if [ -e "$script_dir/progc/CY_Truck" ]; then
    echo "L'exécutable: Cy_Truck existe."$'\n'    
  else
    echo "Impossible de compiler l'exécutable après $tentatives_max tentatives."$'\n'        
    return 1
  fi
}

existence_dossier()
{
# Existence fichiers de progc ?
for fichier in "${fichiers[@]}"; do                  #Va vérifier dans le dossier progc si chacuns des fichiers sont présent
    chemin="$script_dir/progc/$fichier"
    if [ -e "$chemin" ]; then
        echo "Le fichier $chemin existe."$'\n'
    else    
        echo "Le fichier $chemin n'existe pas."$'\n'
        echo "Veuiller corriger l'erreur puis relancer...."$'\n'
        exit 1
    fi
done


# Existence fichier data ?
if [ -e "$chemin_csv" ]; then
    echo "Le fichier $nom_csv existe."$'\n'
else
    echo "Le fichier $nom_csv n'existe pas."$'\n'
    echo "Veuiller corriger l'erreur puis relancer...."$'\n'
    exit 1
fi

# Exitence dossier images ?
if [ -d "images" ]; then
    echo "Le dossier \ images \ existe"$'\n'
else
    mkdir "$script_dir/images"                                                                           #Créer le dossier s'il est inexistant
    echo "Le dossier \ images \ n'existait pas mais a été crée"$'\n'
fi

# Exitence dossier temp ?
if [ -d "temp" ]; then
    echo "Le dossier \ temp existe"$'\n'
    # Vider le contenu du dossier temp
    rm -r "./temp" #Uniquement les fichier + sous dossier
    mkdir "$script_dir/temp"
    echo "Le dossier \ temp \ a été vidé"$'\n'
else
    mkdir "$script_dir/temp"
    echo "Le dossier \ temp \ n'existait pas mais a été crée"$'\n'
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
make -C "$script_dir/progc" #Indique au make de rechercher le makefile dans progc
}

verifier_commande() {
  declare -A commande_vues  # Utilisation d'un tableau associatif pour suivre les options vues

  for argument in "${commande[@]}"; do
    case "$argument" in
      -f | -o)
        # Vérifier si l'option a déjà été vue
        if [ -n "${commande_vues[$argument]}" ]; then
          echo "Erreur : Option $argument déjà spécifiée."$'\n'
          return 1 #Valeur d'erreur
        else
          commande_vues["$argument"]=1
        fi
        ;;
    esac
  done
}

verifier_options() {
  declare -A options_vues  # Utilisation d'un tableau associatif pour suivre les options vues

  for option in "${option_traitement[@]}"; do
    case "$option" in
      -d1 | -d2 | -s | -t | -l | -h)
        # Vérifier si l'option a déjà été vue
        if [ -n "${options_vues[$option]}" ]; then
          echo "Erreur : Option $option déjà spécifiée."$'\n'
          return 1 #Valeur d'erreur
        else
          options_vues["$option"]=1
        fi
        ;;
      *)
        echo "Erreur : Option $option non autorisée."$'\n'
        return 1 #Valeur d'erreur
        ;;
    esac
  done
}


obtention_utilisation ()
{
declare -g commande=() #-> varr globale
declare -g option_traitement=()     

ajout_options=false


# Demander à l'utilisateur de saisir une commande
# Tant qu'il y a - de 4 éléments dans la commande
while [ "${#commande[@]}" -lt 4 ]; do
  commande=()   # On réinitialise la valeur de commande
  read -r -p "Entrer une commande : " -a commande  # On lit l'entrée utilisateur
  echo "Commande après la saisie : ${commande[@]}"$'\n'
done

presence_com=0

for i in "${commande[@]}"; do 
  if [ "$i" = "-f" ] || [ "$i" = "-o" ]; then
    presence_com=$((presence_com + 1))
  fi
done

if [ "$presence_com" != 2 ]; then
  echo "Il manque une option de commande (soit -o soit -f), veuillez réessayer"$'\n'
  obtention_utilisation
fi

verifier_commande
local verification_result=$?
  # Si la vérif n'est pas valide redemande la commande
  if [ "$verification_result" -ne 0 ]; then
    obtention_utilisation
  fi

for ((index=0; index<"${#commande[@]}"; index++)); do
  arg="${commande[index]}"
  case "$arg" in
    -f)
      ajout_options=false
      nom_csv="${commande[index+1]}"
      ((index++))  # Incrémentation de l'index pour passer au prochain argument après le nom du fichier CSV
      ;;
    -o)
      ajout_options=true
      ;;
    *)
      if [ "$ajout_options" = true ]; then
        option_traitement+=("$arg")
      fi
      ;;
  esac
done

verifier_options

local verification_result=$?
  # Si la vérif n'est pas valide redemande la commande
  if [ "$verification_result" -ne 0 ]; then
    obtention_utilisation
  fi

for i in "${option_traitement[@]}"; do
  echo " ${i} "
done

echo " ${nom_csv} "
declare -g chemin_csv="$script_dir/data/$nom_csv.csv"  #chemin du fichier csv
echo " ${chemin_csv} "

}

#------------------------------ GnuPlot ------------------------------#
gnuplot_path=$(which gnuplot)

traitement_gnuplot_s()
{
#Format du txt : ID;dist_min;dist_max;dist_moy

# Tri du fichier
sort -t';' -k4,4 -nr "$script_dir/temp/data_s.txt" > "$script_dir/temp/data_s_sorted.txt"


"$gnuplot_path" << EOF
set terminal pngcairo enhanced font "arial,10" size 800,600
set output "$script_dir/images/graphique_s.png"

# Paramètres du graphique
set boxwidth 0.5
set yrange [0:*]
set xlabel "ROUTE ID"
set ylabel "DISTANCE (Km)"
set title "Option -s : Distance = f(Route)"

# Spécifier le délimiteur de colonnes
set datafile separator ";"

# Charger les données
plot '$script_dir/temp/data_s_sorted.txt' using 1:2 with lines title "Minimum" lc rgb "red", \
     '' using 1:3 with lines title "Maximum" lc rgb "blue", \
     '' using 1:4 with lines title "Moyenne" lc rgb "green"
EOF
}

traitement_gnuplot_d1()
{
#Format du txt : Conducteur;nb_trajet
# Tri du fichier

# Utilisation du fichier trié dans Gnuplot
"$gnuplot_path" <<-EOF

set terminal pngcairo enhanced font "arial,10" size 800,600
set output "$script_dir/images/graphique_d1.png"

# Spécifier le délimiteur de colonnes
set datafile separator ";"

# Paramètres du graphique
set style data histograms
set style fill solid border -1

set ytics right
set xtics rotate by 90
set ytics rotate by 90

set xtics offset 0,-9
set bmargin 10

set boxwidth 0.8 relative
set yrange [0:250]
set style line 1 lc rgb 'green' lt 1 lw 2
set style fill solid noborder

set xlabel "DRIVER NAMES"
set ylabel "Nombre de trajets"
set title "Option -d1 : NB routes = f(Driver)"



# Tracer l'histogramme horizontal avec filledcurves
plot "$script_dir/temp/data_d1.txt" sing 1:xtic(2)  with boxes linestyle 1 title "Nombre de trajets" lc rgb "blue"

EOF

convert "$script_dir/images/graphique_d1.png" -rotate 90 "$script_dir/images/graphique_d1.png"
}

traitement_gnuplot_d2()
{
#Format du txt : Conducteur valeur_distance
#Trie le fichier decroissant

# Script Gnuplot

# Utilisation du fichier trié dans Gnuplot
"$gnuplot_path" <<-EOF

set terminal pngcairo enhanced font "arial,10" size 800,600
set output "$script_dir/images/graphique_d2.png"

# Spécifier le délimiteur de colonnes
set datafile separator ";"

# Paramètres du graphique
set style data histograms
set style fill solid border -1
set boxwidth 0.5
set yrange [0:*]
set ylabel "DRIVER NAMES"
set xlabel "Distance (Km)"
set title "Option -d2 : Distance = f(Driver)"
set xtics rotate by 90
set ytics rotate by 90
set xtics offset 0,-9
set bmargin 10
set style line 1 lc rgb '#2ecc71' lt 1 lw 2
set style fill solid noborder

# Tracer l'histogramme horizontal avec filledcurves
plot "$script_dir/temp/data_d2_sorted.txt" using 2:xtic(1) with boxes linestyle 1 title "Nombre de trajets" lc rgb "blue"

EOF

convert "$script_dir/images/graphique_d2.png" -rotate 90 "$script_dir/images/graphique_d2.png"

}

traitement_gnuplot_l()
{
#Format du txt : RouteID;nb_trajet
# Utilisation du fichier trié dans Gnuplot
"$gnuplot_path" <<-EOF

set terminal pngcairo enhanced font "arial,10" size 800,600 #Def. le terminal de sortie en .png en 800x600p
set output "$script_dir/images/graphique_l.png" #Def. le fichier de sortie

# Paramètres du graphique
set style fill solid
set boxwidth 0.8 relative
set yrange [0:*]
set xlabel "ROUTE ID"
set ylabel "DISTANCE (Km)"
set title "Option -l : Distance = f(Route)"

# Spécifier le délimiteur de colonnes
set datafile separator ";"

# Tracer l'histogramme verticale
plot "$script_dir/temp/data_l.txt" using 2:xticlabels(1) with boxes title "Nombre de trajets" #Utilise les données du txt pour histo verticale

EOF
}

traitement_gnuplot_t()
{
#Format du txt : Conducteur;nb_trajet
# Tri du fichier
sort -t';' -k1,1n "$script_dir/temp/data_t.txt" > "$script_dir/temp/data_t_sorted.txt"

# Utilisation du fichier trié dans Gnuplot
"$gnuplot_path" <<-EOF

set terminal pngcairo enhanced font "arial,10" size 800,600
set output "$script_dir/images/graphique_t.png"
set title 'Option -t : Nb routes = f(Towns)'
set style data histogram
set style histogram clustered gap 1
set style fill solid border -1
set auto x
set yrange [0:*]
set xlabel 'Villes'
set ylabel 'Nombre de trajets'
set key top left

# Utilisation du format "#AARRGGBB" pour définir l'opacité des barres
set style fill transparent solid 0.5 noborder

# Spécifier le délimiteur de colonnes
set datafile separator ";"

# Faire pivoter les étiquettes de l'axe des x de 45 degrés
set xtics rotate by -45

plot  "$script_dir/temp/data_t_sorted.txt" using 2:xtic(1) title 'Total trajets' lc rgb '#FF0000', '' using 3 title 'Trajets depuis' lc rgb '#0000FF'
EOF
}
#---------------------

crea_histo()
{
for i in "${option_traitement[@]}";
do
    case "$i" in
        -d1)
        echo "d1"
           traitement_gnuplot_d1
            ;;
       -d2)
       echo "d2"
            traitement_gnuplot_d2
            ;;
        -l)
        traitement_gnuplot_l
           ;;
       -t)
       echo "t"
           traitement_gnuplot_t
           ;;
       -s)
       echo "s"
          traitement_gnuplot_s
           ;;
        \?)
          echo "Option non reconnue : $i"$'\n'
          show_help
          ;;
   esac
done
}



#------------------------------ Main ------------------------------#
echo "#-----------------------------------------------#"$'\n'
echo "Bienvenue dans le Cy Truck Data Analyser"$'\n'
echo "#-----------------------------------------------#"$'\n'

show_help
obtention_utilisation
for i in "${option_traitement[@]}";
do               
  if [ "$i" = "-h" ]; then 
    show_help
    obtention_utilisation
  fi
done


echo "#-----------------------------------------------#"$'\n'
echo "VERIFICATION DE L'INTEGRITE DE L'OUTIL..."$'\n'
echo "#-----------------------------------------------#"$'\n'
existence_dossier   
existence_executable
if [ $retour -eq 1 ]; then
  echo "ERREUR : Impossible de compiler le programme, veuillez vérifier"$'\n'            #Renvoyer une ERREUR et arrêter le programme si l'on arrive pas à compiler
  exit 1
fi


echo "#-----------------------------------------------#"$'\n'
echo "EXECUTION DU PROGRAMME..."$'\n'
echo "#-----------------------------------------------#"$'\n'


for i in "${option_traitement[@]}";
do
    case "$i" in
        -d1)
        sort -n -t';' -k1 "$chemin_csv" | cut -d';' -f1,6 > "./temp/tmpD1.csv"
awk -F';' '{count[$3";"$2]++} END {for (i in count) print count[i], i}' "./temp/tmpD1.csv" | sort -nr | head -n10 > "./temp/data_d1.txt"
            ;;
       -d2)
       echo "d2"
      for i in "${option_traitement[@]}";
do
    case "$i" in
        -d1)
        sort -n -t';' -k1 "$chemin_csv" | cut -d';' -f1,6 > "./temp/tmpD1.csv"
        awk -F';' '{count[$3";"$2]++} END {for (i in count) print count[i], i}' "./temp/tmpD1.csv" | sort -nr | head -n10 > "./temp/data_d1.txt"
            ;;
       -d2)
       echo "d2"
      sort -n -t';' -k6 "$chemin_csv" | cut -d';' -f6,5 > "./temp/tmpD2.csv"
awk -F';' 'NR>1 {distances[$2]+=$1} END {for (driver in distances) print distances[driver]";", driver}' "./temp/tmpD2.csv" | sort -n -r -t';' -k1 | head -n10 > "./temp/data_d2.txt"
      ;;
        -l)
        echo "l"
           sort -n -t';' -k1 "$chemin_csv" | cut -d';' -f1,5,6 > "./temp/tmpL.csv"
           awk -F';' 'NR>1 {distances[$1]+=$2} END {for (id in distances) print id,";",distances[id]}' "./temp/tmpL.csv" | sort -n -r -t' ' -k2 | head -n10 > "./temp/data_l.txt"
           ;;
       -t)
       echo "t"
           time ./progc/CY_Truck "${nom_csv}" "${option_traitement[@]}"
           ;;
       -s)
       echo "s"
          time ./progc/CY_Truck "${nom_csv}" "${option_traitement[@]}"
           ;;
        \?)
          echo "Option non reconnue : $i"$'\n'
          show_help
          ;;
   esac
done
            ;;
        -l)
        echo "l"
           sort -n -t';' -k1 "$chemin_csv" | cut -d';' -f1,5,6 > "./temp/tmpL.csv"
           awk -F';' 'NR>1 {distances[$1]+=$2} END {for (id in distances) print id,";",distances[id]}' "./temp/tmpL.csv" | sort -n -r -t' ' -k2 | head -n10 > "./temp/data_l.txt"
           ;;
       -t)
       echo "t"
           time ./progc/CY_Truck "${nom_csv}" "${option_traitement[@]}"
           ;;
       -s)
       echo "s"
          time ./progc/CY_Truck "${nom_csv}" "${option_traitement[@]}"
           ;;
        \?)
          echo "Option non reconnue : $i"$'\n'
          show_help
          ;;
   esac
done



echo "#-----------------------------------------------#"$'\n'
echo "CREATION DE L'HISTOGRAMME...."$'\n'
echo "#-----------------------------------------------#"$'\n'
#Timer interne
start=$(date +%s)
crea_histo
end=$(date +%s)
temps=$((end - start))
echo "Durée d'exécution: ${temps} secondes"$'\n'


echo "#-----------------------------------------------#"$'\n'
echo "LE PROGRAMME A ETE EXECUTE"$'\n'                                         
echo "#-----------------------------------------------#"$'\n'
exit 0