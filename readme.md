README PROJET QCM 

Équipe :
- Membre 1 (Architecte Data) : Amnache youva
- Membre 2 (Mode Professeur) : Farhat Adam
- Membre 3 (Mode Étudiant) : Megherbi Badis

Description :
Catastrophe ! Moodle est à l'arrêt à l'approche des partiels. 
Ce projet est un gestionnaire de QCM interactif en langage C qui permet :
- Aux professeurs de créer des QCM sécurisés par mot de passe.
- De paramétrer les QCM (points négatifs, choix multiples, mode séquentiel).
- Aux étudiants de passer les tests avec un calcul automatique de la note sur 20.
- La persistance des données grâce à une sauvegarde en format texte `.txt`.

Compilation et Exécution :
On utilise un `Makefile` pour simplifier la compilation.

1. Ouvrez un terminal dans le dossier du projet.
2. Compilez le projet en tapant : `make`
3. Exécutez le programme avec : `./qcm_cytech`

(Pour nettoyer les fichiers de compilation : `make clean`)

Informations :
- Mot de passe professeur : `miguelmiguel`
- Format de sauvegarde : fichiers `.txt`
