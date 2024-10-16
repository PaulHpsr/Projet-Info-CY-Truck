# Projet Info CY Truck | Analyse et Visualisation de Données de Trajets Routiers

## Description
Ce projet permet d'analyser, trier et générer des graphiques à partir d'un fichier de données contenant des informations sur des trajets routiers. Développé en C, ce programme offre une interface simple pour l'utilisateur souhaitant visualiser ses données.

## Pré-requis
Assurez-vous d'avoir les fichiers et documents suivants pour faire fonctionner le programme correctement :
- **Données** : un fichier CSV (à créer manuellement si absent)
- **Images** : générées par le programme si non présentes
- **Fichiers sources** : 
  - `Cy_Truck.c` (sans fichier .h)
  - `Makefile`
  - `Outils_AVL_S.c`, `Outils_AVL_T.c`, `Traitements.c` et leurs fichiers .h respectifs
- **Script** : `main.sh`
- **Outil** : `gnuplot`

## Environnement de Développement
Ce projet a été développé à l'aide des outils suivants :
- **Replit**
- **Atom**

## Fonctionnalités Clés
- **Analyse et Tri des Données** : Charge et traite un fichier CSV pour générer des statistiques.
- **Génération de Graphiques** : Visualisation des données traitées via `gnuplot`.
  
## Utilisation
1. **Vérifiez les Droits d'Exécution** :
   Assurez-vous d'avoir les droits d'exécution pour le script `main.sh` :
   ```
   ls -l main.sh
   ```

(Cela doit être fait lorsque l'on se trouve dans le répertoire où se trouve `main.sh` ou en spécifiant le chemin complet vers `main.sh`, 
  exemple : 
  ```ls -l /chemin_vers_le_repertoire/main.sh)```

  2. **Modifiez les Droits si Nécessaire :**
     Si les droits d'exécution ne sont pas accordés, exécutez la commande suivante :
        ```chmod +x main.sh```
    Afin d'obtenir le droit d'éxecution de `main.sh`
  
  3. Préparez vos Données :
     L'utilisateur devra placer le fichier dont les données sont à trier dans le dossier `data` (le fichier doit être un .csv).

  4. **Lancez le Programme :**
      il suffira d'exécuter la commande :
      ```bash main.sh```

  5. **Options de Traitement : **
     Après avoir exécuté main.sh, un message d'aide s'affichera, détaillant les options de traitement disponibles : -d1, -d2, -l, -t, et -s.

      L'utilisateur devra ensuite entrer la commande suivante :
  ```-f nom_du_fichier_à_trier -o options_traitement_1 options_traitement_2```

      L'utilisateur peut utiliser autant d'options qu'il le souhaite.

Pour finir, les graphiques générés par le programme seront stockés dans le dossier `images` du programme.


## Limitations fonctionnelles
Notre programme possède certaines limitations fonctionnelles :

Le fichier CSV doit être structuré selon le format suivant : `Route ID;Step ID;Town A;Town B;Distance;Driver name`
Le traitement avec l'option `-t` peut prendre beaucoup de temps.

## Bibliogrpahie

- Williams, T., & Kelley, C. (2016). Gnuplot 5.0: An Interactive Plotting Program. Gnuplot development team. Disponible en ligne : [Documentation Gnuplot](http://www.gnuplot.info/documentation.html)

- Cooper, M. (2009). Advanced Bash-Scripting Guide: An in-depth exploration of the art of shell scripting. The Linux Documentation Project. Disponible en ligne : [Documentation Shell](http://tldp.org/LDP/abs/html/)
