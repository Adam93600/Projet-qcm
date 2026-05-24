#include "prof.h"
#include "storage.h"  // Pour sauvegarder les QCM créés par le professeur
#include "qcm.h"

// Mode pour les professeurs : création et gestion de QCM
// Protégé par un mot de passe pour des raisons de sécurité
void modeprof() {
    char tentative[50];
    printf("Mot de passe : ");
    scanf("%s", tentative);
    viderTampon();

    // Vérification du mot de passe stocké dans la macro mdp de qcm.h
    if (strcmp(tentative, mdp) != 0) {
        printf("Accès refusé !\n");
        return;  // Sortie anticipée si le mot de passe est incorrect
    }

    // Initialisation d'une nouvelle structure QCM
    QCM nouveau;
    printf("\n--- CRÉATION QCM ---\n");
    
    // Demande du nom du QCM (sans espaces pour simplifier)
    printf("Nom du QCM (sans espaces) : ");
    scanf("%s", nouveau.nom);
    viderTampon();
    
    // Boucle pour s'assurer que le nombre de questions est valide
    // On force le professeur à entrer un nombre entre 1 et 50
    do {
        printf("Nombre de questions (max 50) : ");
        if (scanf("%d", &nouveau.nbQuestions) == 1 && nouveau.nbQuestions > 0 && nouveau.nbQuestions <= 50) {
            viderTampon();
            break;  // Entrée valide, on sort de la boucle
        }
        viderTampon();
        printf("Erreur : veuillez entrer un nombre entre 1 et 50.\n");
    } while (1);
    
    // Configuration : activation des points négatifs ?
    printf("Points négatifs ? (1:Oui, 0:Non) : ");
    while(scanf("%d", &nouveau.pointsNegatifs) != 1) { 
        viderTampon(); 
        printf("Saisissez 1 ou 0 : "); 
    }
    
    // Configuration : possibilité de plusieurs bonnes réponses ?
    printf("Plusieurs réponses possibles ? (1:Oui, 0:Non) : ");
    while(scanf("%d", &nouveau.plusieursVraies) != 1) { 
        viderTampon(); 
        printf("Saisissez 1 ou 0 : "); 
    }

    // Configuration : mode séquentiel (réponse obligatoire) ?
    printf("Mode séquentiel (réponse obligatoire) ? (1:Oui, 0:Non) : ");
    while(scanf("%d", &nouveau.modeSequentiel) != 1) { 
        viderTampon(); 
        printf("Saisissez 1 ou 0 : "); 
    }
    viderTampon();

    // Boucle de création de toutes les questions
    for (int i = 0; i < nouveau.nbQuestions; i++) {
        int bonneReponseExiste = 0;  // Vérification qu'il y a au moins une bonne réponse
        
        // Boucle pour s'assurer qu'au moins une réponse est correcte
        while (!bonneReponseExiste) {
            bonneReponseExiste = 0;
            printf("\nQuestion %d : ", i + 1);
            // Utilisation de fgets pour lire une ligne complète avec espaces
            fgets(nouveau.listeQuestions[i].texte, 256, stdin);
            // Suppression du caractère newline à la fin
            nouveau.listeQuestions[i].texte[strcspn(nouveau.listeQuestions[i].texte, "\n")] = 0;

            // Saisie des 4 options de réponse pour cette question
            for (int j = 0; j < 4; j++) {
                printf("  Option %c : ", 'A' + j);
                fgets(nouveau.listeQuestions[i].options[j], 100, stdin);
                // Nettoyage du newline
                nouveau.listeQuestions[i].options[j][strcspn(nouveau.listeQuestions[i].options[j], "\n")] = 0;
                
                // Le professeur spécifie si cette option est une bonne réponse (1) ou non (0)
                printf("  Est-ce correct ? (1:Oui, 0:Non) : ");
                // Boucle jusqu'à ce qu'une entrée valide soit faite
                while(scanf("%d", &nouveau.listeQuestions[i].bonnesReponses[j]) != 1) {
                    viderTampon();
                    printf("  Erreur, tapez 1 ou 0 : ");
                }
                viderTampon();
                
                // Vérification si au moins une bonne réponse a été trouvée
                if (nouveau.listeQuestions[i].bonnesReponses[j] == 1) {
                    bonneReponseExiste = 1;
                }
            }
            
            // Sécurité : vérifier qu'au moins une réponse est correcte
            if (!bonneReponseExiste) {
                printf("ERREUR : Vous devez sélectionner au moins une bonne réponse !\n");
                printf("Veuillez recommencer cette question.\n");
            }
        }
    }

    // Sauvegarde du QCM terminé sur le disque
    sauvegarderQCM(nouveau);
    printf("\nQCM '%s' enregistré avec succès !\n", nouveau.nom);
}