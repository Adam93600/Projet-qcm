#include "storage.h"
#include <dirent.h>

// Vide le buffer d'entrée standard après un scanf capricieux
// Cette fonction est essentielle pour éviter que les caractères restants
// dans le buffer n'interfèrent avec les prochaines saisies
void viderTampon() {
    int c;
    // On lit tous les caractères jusqu'au retour à la ligne ou fin de fichier
    while ((c = getchar()) != '\n' && c != EOF);
}

// Sauvegarde un QCM dans un fichier texte lisible au format .txt
// Format du fichier : nom, nombre de questions, puis tous les paramètres et questions
void sauvegarderQCM(QCM q) {
    char nomFichier[100];
    // On crée le nom du fichier en ajoutant l'extension .txt au nom du QCM
    sprintf(nomFichier, "%s.txt", q.nom);

    // On ouvre le fichier en mode écriture ("w" écrase s'il existe)
    FILE *f = fopen(nomFichier, "w");
    if (f == NULL) {
        printf("Erreur : impossible de sauvegarder le fichier.\n");
        return;
    }

    // Écriture de l'en-tête du QCM avec tous les paramètres
    fprintf(f, "%s\n", q.nom);
    fprintf(f, "%d\n", q.nbQuestions);
    fprintf(f, "%d\n", q.pointsNegatifs);
    fprintf(f, "%d\n", q.plusieursVraies);
    fprintf(f, "%d\n", q.modeSequentiel);

    // Boucle sur toutes les questions pour les sauvegarder une par une
    for (int i = 0; i < q.nbQuestions; i++) {
        // Écriture du texte de la question
        fprintf(f, "%s\n", q.listeQuestions[i].texte);
        
        // Pour chaque question, on sauvegarde ses 4 options et les bonnes réponses
        for (int j = 0; j < 4; j++) {
            fprintf(f, "%s\n", q.listeQuestions[i].options[j]);
            // 1 si c'est une bonne réponse, 0 sinon
            fprintf(f, "%d\n", q.listeQuestions[i].bonnesReponses[j]);
        }
    }

    // Fermeture du fichier
    fclose(f);
}

// Charge un QCM depuis un fichier texte .txt
// Retourne une structure QCM avec le nom "INEXISTANT" si le fichier n'existe pas
QCM chargerQCM(char *nom) {
    QCM q;
    char chemin[110];
    // Construction du chemin du fichier avec l'extension .txt
    sprintf(chemin, "%s.txt", nom);

    // Tentative d'ouverture du fichier en mode lecture
    FILE *f = fopen(chemin, "r");
    if (f == NULL) {
        // Le fichier n'existe pas, on retourne une structure vide avec nom "INEXISTANT"
        strcpy(q.nom, "INEXISTANT");
        return q;
    }

    // Lecture de l'en-tête du QCM (les informations de configuration)
    fgets(q.nom, sizeof(q.nom), f);
    // On retire le caractère de retour à la ligne
    q.nom[strcspn(q.nom, "\n")] = 0;

    // Lecture des paramètres du QCM
    fscanf(f, "%d\n", &q.nbQuestions);
    fscanf(f, "%d\n", &q.pointsNegatifs);
    fscanf(f, "%d\n", &q.plusieursVraies);
    fscanf(f, "%d\n", &q.modeSequentiel);

    // Boucle de lecture de toutes les questions du fichier
    for (int i = 0; i < q.nbQuestions; i++) {
        // Lecture du texte de la question
        fgets(q.listeQuestions[i].texte, sizeof(q.listeQuestions[i].texte), f);
        // Suppression du caractère de retour à la ligne
        q.listeQuestions[i].texte[strcspn(q.listeQuestions[i].texte, "\n")] = 0;

        // Lecture des 4 options de la question et leurs statuts (bonne ou mauvaise réponse)
        for (int j = 0; j < 4; j++) {
            fgets(q.listeQuestions[i].options[j], sizeof(q.listeQuestions[i].options[j]), f);
            // Nettoyage du retour à la ligne
            q.listeQuestions[i].options[j][strcspn(q.listeQuestions[i].options[j], "\n")] = 0;
            // Lecture de l'indicateur de bonne réponse (1 ou 0)
            fscanf(f, "%d\n", &q.listeQuestions[i].bonnesReponses[j]);
        }
    }

    // Fermeture du fichier
    fclose(f);
    return q;
}

// Liste tous les fichiers .txt du dossier courant (représentent les QCM disponibles)
// Affiche les noms des QCM sans l'extension .txt pour une meilleure lisibilité
void listerQCM() {
    // Ouverture du répertoire courant
    DIR *dossier = opendir(".");
    struct dirent *entree;
    int count = 0;

    // Vérification que l'ouverture du répertoire a réussi
    if (dossier == NULL) {
        printf("Impossible de lister les QCM.\n");
        return;
    }

    printf("\n  QCM disponibles :\n");
    
    // Parcours de tous les fichiers du répertoire
    while ((entree = readdir(dossier)) != NULL) {
        // Recherche de l'extension du fichier (le dernier point)
        char *ext = strrchr(entree->d_name, '.');
        
        // On ne traite que les fichiers avec l'extension .txt
        if (ext != NULL && strcmp(ext, ".txt") == 0) {
            // Extraction du nom du fichier sans l'extension
            char nomAffiche[100];
            // Copie depuis le début jusqu'au point
            strncpy(nomAffiche, entree->d_name, ext - entree->d_name);
            nomAffiche[ext - entree->d_name] = '\0';
            
            // Affichage du nom du QCM
            printf("  - %s\n", nomAffiche);
            count++;
        }
    }
    
    // Fermeture du répertoire
    closedir(dossier);

    // Message si aucun QCM n'a été trouvé
    if (count == 0) {
        printf("  Aucun QCM disponible pour le moment.\n");
    }
}
