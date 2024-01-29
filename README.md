# Projet-Info-CY-Truck | Projet d'informatique PreIng2 CY_Truck MI2

## Programme codé en language C, qui permet l'analyse, le trie et la génération de graphiques à partir d'un fichier de donnée qui contient l’ensemble des données de trajets routiers.

## Pré-requis 

Il est nécessaire d'avoir les fichiers et documents suivants afin que le programme fonctionne correctement :
- images
- data
- progc; dont : Cy_Truck.c (ne possède pas de .h), Makefile, Outils_AVL_S.c, Outils_AVL_T.c, Traitements.c et leurs .h respectifs
- main.sh
- gnuplot

## Codé avec 

- Replit 
- Atom

## Description

Ce projet permet à l'utilisateur d'analyser et trier les données contenues dans un fichier csv, afin de générer un ou plusieurs graphiques résumant le contenu de ce fichier en fonction du traitement voulu par l'utilisateur.

## Utilisation

- En premier lieu, l'utilisateur doit vérifier s'il possède le droit d'exécution pour le script shell "main.sh" grâce à la commande unix : ls -l main.sh    (cela doit être fait lorsque l'on se trouve dans le répertoire ou se trouve "main.sh" ou en spécifiant le chemin complet vers "main.sh" (exemple : ls -l /chemin_vers_le_repertoire/main.sh)
- Par suite, si l'utilisateur ne possède pas le droit d'exécution il faudra que celui-ci exécute la commande : "chmod +x main.sh" ; afin d'obtenir le droit d'éxécution de "main.sh".
- Enfin, afin de lancer le programme, l'utilisateur devra exécuter la commande : "bash main.sh"

L'utilisateur devra placer le fichier dont les données sont à trier dans le document data (le fichier doit être un .csv)

Le programme affichera ensuite un message d'aide afin de renseigner l'utilisateur quant aux différentes options de traitements (-d1, -d2, -l, -t et -s).
Celui-ci devra ensuite rentrer la commande suivante : "-f nom_du_fichier_à_trier -o options_traitement_1 options_traitement_2"   (l'utilisateur peut utiliser autant d'options qu'il souhaite).

Pour finir, les graphiques générés par le programme seront stockés dans le dossier "images" du programme.

## Limitations fonctionnelles

Notre programme possèdes certaines limitations fonctionnelles :
- Le programme ne vérifie pas si gnuplot est installé ou non
- Si gnuplot n'est pas présent le programme ne lance pas d'installation automatique de celui-ci
- Le fichier CSV doit être structuré selon le format suivant : Route ID;Step ID;Town A;Town B;Distance;Driver name
- Gnuplot ne permettant pas de créer un histogramme horizontal en barre, nous avons opté pour un histogramme horizontal avec courbe

## Auteurs
CY-Tech | MI2
- Omar AFDALI
- Paul HOPSORE
- Corentin PELLERIN
  
