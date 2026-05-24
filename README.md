# QCM-PROJET

Un gestionnaire de QCM en terminal développé en C.  

## Description

QCM-CY-TECH est une solution d'urgence pour pallier l'arrêt de Moodle à l'approche des partiels. Le projet propose un système complet de gestion de QCM fonctionnant dans un terminal, permettant aux professeurs de créer des évaluations sécurisées et aux étudiants de les passer, avec un calcul automatique de la note sur 20.

## Fonctionnalités

- Création de QCM sécurisée par mot de passe (mode professeur)
- Paramétrage des QCM (points négatifs, choix multiples, mode séquentiel)
- Passage des QCM avec calcul automatique de la note sur 20
- Sauvegarde persistante des QCM en fichiers `.txt`
- Listage automatique des QCM disponibles

## Prérequis

- Compilateur C (GCC recommandé)
- Environnement POSIX (Linux, macOS, ou Windows avec WSL)

## Compilation

```bash
make
```

## Utilisation

```bash
./qcm_cytech
```

Au lancement, le programme vous demandera :
1. Si vous êtes étudiant ou professeur
2. Le nom du QCM à passer ou à créer

*(Pour nettoyer les fichiers de compilation : `make clean`)*

## Contrôles

- Mode étudiant : tapez une ou plusieurs lettres pour répondre (ex: A, AB, BCD)
- Tapez `0` pour passer une question (si le mode séquentiel est désactivé)

## Structure des fichiers

- `main.c` : Point d'entrée du programme, menu principal
- `prof.c/h` : Création et configuration des QCM (mode professeur)
- `eleve.c/h` : Passage des QCM et calcul de la note (mode étudiant)
- `storage.c/h` : Sauvegarde et chargement des QCM en fichiers `.txt`
- `qcm.h` : Définition des structures de données principales

## Informations

- **Mot de passe professeur :** `miguelmiguel`
- **Format de sauvegarde :** fichiers `.txt`

## Auteurs

- **Amnache Youva** - *Architecte Data*
- **Farhat Adam** - *Mode Professeur*
- **Megherbi Badis** - *Mode Étudiant*

