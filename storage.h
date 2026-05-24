#ifndef STORAGE_H
#define STORAGE_H

#include "qcm.h"

// Sauvegarde un QCM en mémoire dans un fichier texte .txt
// Le fichier est créé dans le répertoire courant avec l'extension .txt
void sauvegarderQCM(QCM q);

// Charge un QCM depuis un fichier texte .txt
// Retourne une structure QCM avec le nom "INEXISTANT" si le fichier n'existe pas
QCM chargerQCM(char *nomFichier);

// Affiche la liste de tous les QCM disponibles (tous les fichiers .txt du dossier)
// Très utile pour que les étudiants sachent quels QCM ils peuvent passer
void listerQCM();

// Nettoie le buffer stdin pour éviter les problèmes de saisie après scanf
// Nécessaire pour absorber les caractères en trop après une saisie
void viderTampon();

#endif
