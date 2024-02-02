#!/bin/bash

clear_console

# Définir la locale pour le format numérique (prendre format US car '.' = ',')
export LC_NUMERIC="en_US.UTF-8"


#---------------------------- Initialisation des variables Globales-------------------------------#

script_dir=$(dirname "$0")   


nom_csv=""


#-----------------------------------------------------------------------------------------#



#-------------------------------------- GESTION DOSSIER ----------------------------------#

#DEF DES DOSSIERS ET FICHIER IMPORTANT
fichiers=("Cy_Truck.c" "Makefile" "Outils_AVL_S.h" "Outils_AVL_T.h" "Outils_AVL_T.h" "Outils_AVL_S.c")


#VERIF SI EXEC EXIST
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






#VERIF EXISTANCES DOSSIERS
existence_dossier()
{
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
  mkdir "$script_dir/images"           #Créer le dossier s'il est inexistant
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


#VERIF SI GNUPLOT ET IMAGEMAGICK INSTALLES 
verif_gnuplot_magick()
{
  if ! command -v gnuplot &> /dev/null; then
    echo "Installation de Gnuplot en cours"$'\n'
    sudo apt-get update
    sudo apt-get install -y gnuplot
  else
    echo "Gnuplot est prêt à être utilisé"$'\n'
  fi

  if ! command -v convert &> /dev/null; then
    echo "Installation de Imagemagick en cours"$'\n'
    sudo apt-get update
    sudo apt-get install -y imagemagick
  else
    echo "Imagemagick est prêt à être utilisé"$'\n'
  fi
}



#-----------------------------------------------------------------------------------------#






#-------------------------------------- FONCTIONS MAIN -----------------------------------#

#AFFICHER LES COMMANDE 'HELP'
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


#COMPILER LE C
compiler_c ()
{
  make -C "$script_dir/progc" #Indique au make de rechercher le makefile dans progc
}


#VERIFIER SI COMMANDE RENTREE EST BONNE
verifier_commande() {
  declare -A commande_vues  
  # Utilisation d'un tableau associatif pour suivre les options vues

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


#VERIFIER SI LES OPTION RENTREE SONT VALIDES
verifier_options() {
  declare -A options_vues 
  # Utilisation d'un tableau associatif pour suivre les options vues

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


#OBTENIR LA COMMANDE RENTREE
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
#-----------------------------------------------------------------------------------------#


#-------------------------------------- TRAITEMENTS D1 D2 ET L -----------------------------------#

shell_d1()
{

start=$(date +%s)

cut -d ';' -f1,6 "$chemin_csv" | sort -t ';' -k1,1 | uniq | cut -d ';' -f 2 | sort | uniq -c | sort -nr | head | awk '{print $2 ,$3 ";" $1}'  > "./temp/data_d1.dat"


end=$(date +%s)
temps=$((end - start))
echo "Durée d'exécution: -d1 ${temps} secondes"$'\n'
}


shell_d2()
{

start=$(date +%s)


sort -n -t';' -k6 "$chemin_csv" | cut -d';' -f6,5 | awk -F';' 'NR>1 {distances[$2]+=$1} END {for (driver in distances) print distances[driver]";", driver}' | sort -n -r -t';' -k1 | head -n10 | awk -F';' '{temp=$1; $1=$2; $2=temp; printf "%s;%s\n", $1, $2}' > "./temp/data_d2.dat"



end=$(date +%s)
temps=$((end - start))
echo "Durée d'exécution: -d2 ${temps} secondes"$'\n'

}


shell_l()
{

start=$(date +%s)

 cut -d';' -f1,5 "$chemin_csv" | awk -F ';' '{noms[$1]++; distances[$1]+=$2} END {for (nom in noms) print nom ";" distances[nom]}' | sort -t ';' -k2,2 -rn | head | sort -t ';' -k1,1 -n > "./temp/data_l.dat"




end=$(date +%s)
temps=$((end - start))
echo "Durée d'exécution: -l ${temps} secondes"$'\n'

}



#-----------------------------------------------------------------------------------------#





#-------------------------------------- CREATION GRAPHIQUE GNUPLOT -----------------------------------#

gnuplot_path=$(which gnuplot)


#D1
traitement_gnuplot_d1()
{

"$gnuplot_path" <<-EOF

set terminal pngcairo enhanced font "arial,12" size 1000,1000
set output "$script_dir/images/graphique_d1.png"

# Paramètres du graphique
set style fill solid noborder
set boxwidth 0.8 relative
set yrange [0:*]
set xlabel "Driver"
set ylabel "Nb Routes"
set title "Option -d1 : Nb routes = f(Driver)"

set ytics right
set xtics rotate by 90
set ytics rotate by 90

set xtics offset 0,-9
set bmargin 10
# Spécifier le délimiteur de colonnes
set datafile separator ";"

# Tracer l'histogramme verticale
plot "$script_dir/temp/data_d1.dat" using 2:xticlabels(1) with boxes title "Nombre de trajets" 

EOF
convert "$script_dir/images/graphique_d1.png" -rotate 90 "$script_dir/images/graphique_d1.png"

}


#D2
traitement_gnuplot_d2()
{
"$gnuplot_path" <<-EOF

set terminal pngcairo enhanced font "arial,12" size 1000,1000
set output "$script_dir/images/graphique_d2.png"

# Paramètres du graphique
set style fill solid noborder
set boxwidth 0.8 relative
set yrange [0:*]
set xlabel "Driver"
set ylabel "Distance (Km)"
set title "Option -d1 : Distance = f(Driver)"

set ytics right
set xtics rotate by 90
set ytics rotate by 90

set xtics offset 0,-9
set bmargin 10

set datafile separator ";"

# Tracer l'histogramme verticale
plot "$script_dir/temp/data_d2.dat" using 2:xticlabels(1) with boxes title "Distance (Km)" 

EOF
convert "$script_dir/images/graphique_d2.png" -rotate 90 "$script_dir/images/graphique_d2.png"

}


#L
traitement_gnuplot_l()
{
"$gnuplot_path" <<-EOF

set terminal pngcairo enhanced font "arial,12" size 1000,1000 
set output "$script_dir/images/graphique_l.png" 

# Paramètres du graphique
set style fill solid
set boxwidth 0.8 relative
set yrange [0:*]
set xlabel "ROUTE ID"
set ylabel "DISTANCE (Km)"
set title "Option -l : Distance = f(Route)"

set datafile separator ";"

# Tracer l'histogramme verticale
plot "$script_dir/temp/data_l.dat" using 2:xticlabels(1) with boxes title "Nombre de trajets" #

EOF
}

#T
traitement_gnuplot_t()
{
sort -nr -t';' -k2,2 "$script_dir/temp/data_t.txt" | head -n10 | sort -n -t';' -k1,1 > "$script_dir/temp/data_t.dat"
rm -r "./temp/data_t.txt"

# Utilisation du fichier trié dans Gnuplot
"$gnuplot_path" <<-EOF

set terminal pngcairo enhanced font "arial,12" size 1000,1000
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

set style fill transparent solid 0.5 noborder


set datafile separator ";"


set xtics rotate by -45

plot  "$script_dir/temp/data_t.dat" using 2:xtic(1) title 'Total trajets' lc rgb '#FF0000', '' using 3 title 'Trajets depuis' lc rgb '#0000FF'
EOF
}



#S
traitement_gnuplot_s()
{


# Tri du fichier
sort -t';' -k5,5 -nr "$script_dir/temp/data_s.txt" | head -n50 | awk '{print NR ";" $0}'  > "$script_dir/temp/data_s.dat"
rm -r "./temp/data_s.txt"

"$gnuplot_path" << EOF
set terminal pngcairo enhanced font 'Arial,12' size 1500,1200
set output './images/graphique_s.png'
set datafile separator ";"

set style data histograms
set style fill solid border -1

set title "option -s : Distance= f(Route)" 
set xlabel "ROUTE ID" 
set ylabel "DISTANCE (Km)" 

set yrange [0:1000]
set xtics rotate by 45 offset 0, -2
set bmargin 4


plot './temp/data_s.dat' using 1:4:xtic(2) with lines lc rgb "blue" lw 2 title 'Distance Average (Km)', \
     './temp/data_s.dat' using 1:5 with lines lc rgb "green" lw 2 title 'Distance Max/Min (Km)', \
     './temp/data_s.dat' using 1:3 with lines lc rgb "green" lw 2 notitle, \
     './temp/data_s.dat' using 1:3:5 with filledcurves lc "red" fs transparent solid 0.5 notitle
EOF
}



#FONCTION CREA GRAPHIQUE
crea_histo()
{
for i in "${option_traitement[@]}";
do
    case "$i" in
        -d1)
        echo "Creation : graphique_d1.png ; Dans dossier : images...."$'\n'
           traitement_gnuplot_d1
            ;;
       -d2)
       echo "Creation : graphique_d2.png ; Dans dossier : images...."$'\n'
            traitement_gnuplot_d2
            ;;
        -l)
        echo "Creation : graphique_l.png ; Dans dossier : images...."$'\n'
        traitement_gnuplot_l
           ;;
       -t)
       echo "Creation : graphique_t.png ; Dans dossier : images...."$'\n'
           traitement_gnuplot_t
           ;;
       -s)
       echo "Creation : graphique_s.png ; Dans dossier : images...."$'\n'
          traitement_gnuplot_s
           ;;
        \?)
          echo "Option non reconnue : $i"$'\n'
          show_help
          ;;
   esac
done
}

#-----------------------------------------------------------------------------------------#



#-------------------------------------- MAIN -----------------------------------#


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
verif_gnuplot_magick
existence_executable
retour=$?
if [ $retour -eq 1 ]; then
  echo "ERREUR : Impossible de compiler le programme, veuillez vérifier"$'\n'
  exit 1
fi


echo "#-----------------------------------------------#"$'\n'
echo "EXECUTION DU PROGRAMME..."$'\n'
echo "#-----------------------------------------------#"$'\n'

traitement_t_effectue=false
traitement_s_effectue=false

for i in "${option_traitement[@]}";
do
  case "$i" in
     -d1)
        shell_d1
        ;;


    -d2)
        shell_d2
        ;;


    -l)
        shell_l
        ;;


    -t)
        if [ "$traitement_t_effectue" = false ]; then
        time ./progc/CY_Truck "${nom_csv}" "${option_traitement[@]}"
        traitement_t_effectue=true
        traitement_s_effectue=true
        fi
        ;;


    -s)
        if [ "$traitement_s_effectue" = false ]; then
        time ./progc/CY_Truck "${nom_csv}" "${option_traitement[@]}"
        traitement_s_effectue=true
        traitement_t_effectue=true
        fi
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


crea_histo


echo "#-----------------------------------------------#"$'\n'
echo "LE PROGRAMME A ETE EXECUTE"$'\n'                                         
echo "#-----------------------------------------------#"$'\n'
exit 0
#-----------------------------------------------------------------------------------------#