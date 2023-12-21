#!/bin/bash

make -C progc #Indique au make de rechercher le makefile dans progc

dossier = "progc"
fichiers = ("Cy_Truck.c" "Makefile" "Outils_AVL.h" "Traitements.c" "Traitements.h" "outils_AVL.c")

for fichier in "${fichiers[@]}"; do
    chemin = "$dossier/$fichier"
    if [-e "$chemin"]; then
        echo "Le fichier $chemin existe."
        if gcc -o "${fichiers$.c}" "$chemin"; then
            echo "Compilation réussie pour $fichier"
        else
            echo "Échec de la compilation pour $fichier"
        fi
    else    
        echo "Le fichier $chemin n'existe pas."
    fi
done

# Fonction pour afficher l'aide
show_help() {
    echo "Utilisation: $0 -f <chemin_fichier_csv> -o <option_traitement>"
    echo "  -f : Chemin du fichier CSV à traiter."
    echo "  -o : Option de traitement (-d1, -d2, -l, -t, -s)."
    exit 1
}

# Vérifier les arguments
if [ "$#" -ne 4 ]; then
    show_help
fi

# Initialiser les variables
chemin_csv=""
option_traitement=""

# Traitement des options
while getopts ":f:o:" opt; do
    case $opt in
        f)
            chemin_csv="$OPTARG"
            ;;
        o)
            option_traitement="$OPTARG"
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

# Vérifier si les options requises ont été spécifiées
if [ -z "$chemin_csv" ] || [ -z "$option_traitement" ]; then
    echo "Les options -f et -o doivent être spécifiées avec les valeurs correspondantes."
    show_help
fi

# Mesurer le temps d'exécution avec la commande time
time ./votre_programme_c -c "$chemin_csv" -o "resultats_option_$option_traitement.txt"

# Exécuter le programme C en fonction de l'option de traitement choisie
case $option_traitement in
    -d1)
        ./programme_c -f "$chemin_csv" -o resultats_option_d1.txt
        ;;
    -d2)
        ./programme_c -f "$chemin_csv" -o resultats_option_d2.txt
        ;;
    -l)
        ./programme_c -f "$chemin_csv" -o resultats_option_l.txt
        ;;
    -t)
        ./programme_c -f "$chemin_csv" -o resultats_option_t.txt
        ;;
    -s)
        ./programme_c -f "$chemin_csv" -o resultats_option_s.txt
        ;;
    -h)
        echo "Option de traitement invalide. Les choix valides sont -d1, -d2, -l, -t, -s."
        show_help
        ;;
esac

# Vérifier si l'exécution du programme C a réussi
if [ $? -ne 0 ]; then
    echo "Erreur lors de l'exécution du programme C."
    exit 1
fi

# Lire les résultats traités
resultats=$(cat "resultats_option_$option_traitement.txt")

# Générer le graphique 
echo "$resultats" | gnuplot -p -e "plot '-' with linespoints title 'Résultats Option $option_traitement'"

# Nettoyer les fichiers temporaires
rm "resultats_option_$option_traitement.txt"
