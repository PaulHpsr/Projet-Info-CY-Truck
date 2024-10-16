## Projet CY_Truck | Application d'analyse, de tri et générateur de graphiques
Programme codé en langage C, qui permet l'analyse, le tri et la génération de graphiques à partir d'un fichier de données contenant l’ensemble des données de trajets routiers.

## Pré-requis 
Il est nécessaire d'avoir les fichiers et documents suivants afin que le programme fonctionne correctement :
- images (si non présent -> créé par le programme)
- data (il faut le créer manuellement si non présent)
- progc ; dont : Cy_Truck.c (ne possède pas de .h), Makefile, Outils_AVL_S.c, Outils_AVL_T.c, Traitements.c et leurs .h respectifs
- main.sh
- gnuplot

## Codé avec 
- Replit 
- Atom

## Description
Ce projet permet à l'utilisateur d'analyser et trier les données contenues dans un fichier CSV, afin de générer un ou plusieurs graphiques résumant le contenu de ce fichier en fonction du traitement voulu par l'utilisateur.

## Utilisation

- En premier lieu, l'utilisateur doit vérifier s'il possède le droit d'exécution pour le script shell `main.sh` grâce à la commande Unix :

```bash
ls -l main.sh
```
(Cela doit être fait lorsque l'on se trouve dans le répertoire où se trouve `main.sh` ou en spécifiant le chemin complet vers `main.sh`, 
  exemple : 
  ```ls -l /chemin_vers_le_repertoire/main.sh)```

  - Par suite, si l'utilisateur ne possède pas le droit d'exécution, il faudra que celui-ci exécute la commande :
        ```chmod +x main.sh```
    Afin d'obtenir le droit d'éxecution de `main.sh`
  - Enfin, pour lancer le programme, il suffira d'exécuter la commande :
      ```bash main.sh```

L'utilisateur devra placer le fichier dont les données sont à trier dans le dossier `data` (le fichier doit être un .csv).

Le programme affichera ensuite un message d'aide afin de renseigner l'utilisateur quant aux différentes options de traitements `(-d1, -d2, -l, -t et -s)`. Celui-ci devra ensuite rentrer la commande suivante :
  ```-f nom_du_fichier_à_trier -o options_traitement_1 options_traitement_2```

L'utilisateur peut utiliser autant d'options qu'il le souhaite.

Pour finir, les graphiques générés par le programme seront stockés dans le dossier `images` du programme.

Limitations fonctionnelles
Notre programme possède certaines limitations fonctionnelles :

Le fichier CSV doit être structuré selon le format suivant : `Route ID;Step ID;Town A;Town B;Distance;Driver name`
Le traitement avec l'option `-t` peut prendre beaucoup de temps.
