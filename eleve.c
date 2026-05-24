#include "eleve.h"
#include "storage.h"
#include "qcm.h"

// Mode pour les étudiants : passage d'un QCM
// Affiche les QCM disponibles, laisse l'étudiant en choisir un et passer l'examen
void modeetudiant() {
    char nom[50];

    // Affichage de la liste des QCM disponibles sur le système
    // Cela permet à l'étudiant de savoir quels examens il peut passer
    listerQCM();

    printf("\nEntrez le nom du QCM a passer : ");
    scanf("%s", nom);
    viderTampon();

    // Chargement du QCM depuis le disque
    QCM q = chargerQCM(nom);
    // Vérification que le QCM existe bel et bien
    if (strcmp(q.nom, "INEXISTANT") == 0) {
        printf("Ce QCM n'existe pas.\n");
        return;
    }

    // Initialisation du score à 0 avant de commencer l'examen
    float score = 0;
    printf("\n--- DEBUT DU QCM : %s ---\n", q.nom);

    // Parcours de toutes les questions du QCM
    for (int i = 0; i < q.nbQuestions; i++) {
        printf("\nQ%d: %s\n", i + 1, q.listeQuestions[i].texte);
        
        // Affichage des 4 options de réponse (A, B, C, D)
        for (int j = 0; j < 4; j++) {
            printf("  %c) %s\n", 'A' + j, q.listeQuestions[i].options[j]);
        }

        // Tableau pour enregistrer les réponses de l'étudiant
        // 1 si l'étudiant a sélectionné l'option, 0 sinon
        int reponsesEleve[4] = {0};
        int aRepondu = 0;  // Drapeau pour vérifier qu'une réponse a été donnée

        // Boucle de saisie : on demande la réponse jusqu'à ce qu'elle soit valide
        do {
            // Réinitialiser les réponses à chaque tentative
            for (int j = 0; j < 4; j++) reponsesEleve[j] = 0;
            
            // Messages différents selon le mode séquentiel du QCM
            if (q.modeSequentiel == 0)
                printf("Votre reponse (ex: A, AB, 0 pour passer) : ");
            else
                printf("Votre reponse (ex: A ou AB, reponse obligatoire) : ");

            char saisie[10];
            scanf("%s", saisie);
            viderTampon();

            // En mode non-séquentiel, l'étudiant peut passer la question en tapant 0
            if (saisie[0] == '0' && q.modeSequentiel == 0) break;

            // Vérifier qu'il y a au least une réponse valide (A-D)
            int saisieValide = 0;
            
            // Traitement de chaque caractère de la saisie
            for (int k = 0; k < (int)strlen(saisie); k++) {
                char c = saisie[k];
                // Accepter les minuscules et les convertir en majuscules
                if (c >= 'a' && c <= 'd') c = c - 'a' + 'A';

                // Si c'est une lettre de réponse valide (A à D), l'enregistrer
                if (c >= 'A' && c <= 'D') {
                    reponsesEleve[c - 'A'] = 1;
                    aRepondu = 1;  // On a au moins une réponse
                    saisieValide = 1;
                }
            }

            // En mode séquentiel, rejeter les entrées invalides
            if (q.modeSequentiel == 1 && !saisieValide) {
                printf("Saisie invalide ! Entrez une ou plusieurs reponses (A, B, C ou D).\n");
                aRepondu = 0;  // Réinitialiser pour relancer la boucle
            }

        } while (q.modeSequentiel == 1 && !aRepondu);

        // Si l'étudiant a sauté la question (aRepondu == 0), on ne compte rien
        if (!aRepondu) continue;

        // Vérification si la réponse de l'étudiant est correcte
        // On compare avec le tableau des bonnes réponses
        int correct = 1;
        for (int j = 0; j < 4; j++) {
            if (reponsesEleve[j] != q.listeQuestions[i].bonnesReponses[j]) {
                correct = 0;  // La réponse n'est pas parfaitement correcte
            }
        }

        // Incrémentation du score si la réponse est correcte
        if (correct) score += 1.0;
        // Décrémentation en cas de mauvaise réponse si les points négatifs sont activés
        else if (q.pointsNegatifs) score -= 0.5;
    }

    // Conversion du score brut en note sur 20
    // Vérification que la note n'est pas négative
    if (score < 0) score = 0;
    float noteFinale = (score / q.nbQuestions) * 20.0;
    
    // Affichage du résultat final
    printf("\n--- TERMINE ---\nVotre note : %.2f / 20\n", noteFinale);
}
