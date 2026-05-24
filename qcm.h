#ifndef QCM_H
#define QCM_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mot de passe pour accéder au mode professeur
// Modifiez cette valeur pour sécuriser votre système
#define mdp "miguelmiguel"

// Structure représentant une question d'un QCM
// Chaque question a un texte, 4 options de réponse et un tableau indiquant les bonnes réponses
typedef struct {
    char texte[256];              // Le texte de la question
    char options[4][100];         // Les 4 options de réponse (A, B, C, D)
    int bonnesReponses[4];        // Tableau indiquant les bonnes réponses : 1 si vrai, 0 si faux
} Question;

// Structure principale représentant un QCM complet
// Contient le nom, le nombre de questions, les paramètres de configuration et toutes les questions
typedef struct {
    char nom[50];                 // Nom unique du QCM
    int nbQuestions;              // Nombre de questions dans ce QCM
    int pointsNegatifs;           // 1 = points négatifs activés, 0 = désactivés
    int plusieursVraies;          // 1 = plusieurs bonnes réponses possibles, 0 = une seule
    int modeSequentiel;           // 1 = réponses obligatoires, 0 = on peut passer les questions
    Question listeQuestions[50];  // Tableau de toutes les questions (max 50)
} QCM;

// Fonction utilitaire pour nettoyer le buffer d'entrée après un scanf problématique
// À appeler après chaque scanf pour éviter les problèmes de saisie suivante
void viderTampon();

#endif