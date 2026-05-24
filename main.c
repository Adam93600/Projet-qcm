#include "qcm.h"
#include "prof.h"
#include "eleve.h"

// Point d'entrée du programme QCM-CY-TECH
// Menu principal qui permet de choisir entre mode étudiant, professeur ou quitter
int main() {
    int choix;  // Variable pour stocker le choix de l'utilisateur
    
    // Boucle infinie jusqu'à ce que l'utilisateur choisisse de quitter
    while(1) {
        // Affichage du menu principal
        printf("\n╔════════════════════╗\n");
        printf("║  QCM-CY-TECH       ║\n");
        printf("╠════════════════════╣\n");
        printf("║ 1. Etudiant        ║\n");
        printf("║ 2. Professeur      ║\n");
        printf("║ 3. Quitter         ║\n");
        printf("╚════════════════════╝\n");
        printf("Choix: ");

        // Vérification que scanf a bien lu un nombre entier
        if (scanf("%d", &choix) != 1) {
            viderTampon();  // On nettoie le tampon des caractères mal saisis
            printf("Veuillez entrer un chiffre valide.\n");
            continue;       // On relance la boucle pour redemander le choix
        }
        
        // Aiguillage selon le choix de l'utilisateur
        if(choix == 1) {
            modeetudiant();  // Passage en mode étudiant
        }
        else if(choix == 2) {
            modeprof();      // Passage en mode professeur
        }
        else if(choix == 3) {
            printf("Au revoir!\n");
            break;           // Sortie de la boucle et fermeture du programme
        }
        else {
            printf("Option invalide\n");
        }
    }
    
    return 0;
}