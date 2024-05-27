/******************************************************************************
*  ASR => 4R2.04                                                              *
*******************************************************************************
*                                                                             *
*  N° de Sujet : 1                                                            *
*                                                                             *
*******************************************************************************
*                                                                             *
*  Intitulé : Analyse de Trames GPS                                           *
*                                                                             *
*******************************************************************************
*                                                                             *
*  Nom-prénom1 : MELOUANE Lotfi                                               *
*                                                                             *
*  Nom-prénom2 : COSTA Ayko                                                   *
*                                                                             *
*******************************************************************************
*                                                                             *
*  Nom du fichier :  main.c                                                   *
*                                                                             *
******************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *veriftrame(char *ch, char extraction[][100]) {
    // Chaine commence par $GPGGA
    if ((ch[0] == '$') && (ch[1] == 'G') && (ch[2] == 'P') && (ch[3] == 'G') && (ch[4] == 'G') && (ch[5] == 'A')) {
        printf("Type de trame correct\n");
    } else {
        printf("Trame incorrecte\n");
        exit(0);
    }

    // Chaîne ayant plus de 15 champs et extraction de ces champs
    char delimitateur[] = ",";
    char *p = strtok(ch, delimitateur);
    int i = 0;
    while (p != NULL) {
        strcpy(extraction[i], p);
        p = strtok(NULL, delimitateur);
        i++;
    }

    if (i >= 5) {
        printf("Trame correcte\n");
        printf("La trame est bien de type %s\n", extraction[0]); // corrected to use extracted type
    } else {
        printf("Trame incorrecte\n");
        exit(0);
    }
    return extraction[0]; // Added return statement
}

// fonction qui convertit les coordonnées GPS
char *convertpos(char extraction[][100], char *flatitude, char *flongitude) {
    double latitude = atof(extraction[2]);
    double longitude = atof(extraction[4]);

    int degl, minl, degll, minll;
    double secl, secll;

    // latitude
    degl = (int)(latitude / 100.0);
    minl = (int)(latitude - (degl * 100.0));
    secl = 60.0 * (latitude - (degl * 100.0) - minl);

    sprintf(flatitude, "%3d°%2d'%5.3f\"", degl, minl, secl);

    // longitude
    degll = (int)(longitude / 100.0);
    minll = (int)(longitude - (degll * 100.0));
    secll = 60.0 * (longitude - (degll * 100.0) - minll);

    sprintf(flongitude, "%3d°%2d'%5.3f\"", degll, minll, secll);

    // renvoi des coordonnées
    return flatitude; // corrected to return appropriate values
    // return flongitude; // removed as unreachable code
}

// fonction qui convertit le temps en h/m/s
char *convertmin(char extraction[][100], char *ftemps) {
    char temps[25];
    int heures;
    int minutes;
    double secondes;
    strcpy(temps, extraction[1]);
    double temps2 = atof(temps);
    heures = (int)temps2 / 10000;
    minutes = (int)(temps2 - (heures * 10000)) / 100;
    secondes = (temps2 - (heures * 10000) - (minutes * 100));
    sprintf(ftemps, "%dh%02dmin%06.3fsec \n", heures, minutes, secondes);
    return ftemps;
}

// fonction main
int main() {
    char *ch = malloc(99 * sizeof(char));
    char *flongitude = malloc(99 * sizeof(char));
    char *flatitude = malloc(99 * sizeof(char));
    char *ftemps = malloc(99 * sizeof(char));
    char extraction[20][100] = {0};
    printf("Veuillez entrer la trame : ");
    scanf("%s", ch);
    veriftrame(ch, extraction);
    convertpos(extraction, flatitude, flongitude);
    convertmin(extraction, ftemps);
    printf("L'heure à laquelle la trame a été envoyée est : %s", ftemps);
    printf("La latitude est : %s %s\n", flatitude, extraction[3]);
    printf("La longitude est : %s %s\n", flongitude, extraction[5]);
    // ecriture du fichier "resultat"
    FILE *fichier = NULL;
    fichier = fopen("resultat.txt", "w");
    if (fichier == NULL) {
        printf("Erreur à l'ouverture du fichier texte\n");
    } else {
        fprintf(fichier, "L'heure à laquelle la trame a été envoyée est : %s", ftemps);
        fprintf(fichier, "La latitude est : %s %s\n", flatitude, extraction[3]);
        fprintf(fichier, "La longitude est : %s %s\n", flongitude, extraction[5]);
        fclose(fichier);
    }
    // Free allocated memory
    free(ch);
    free(flongitude);
    free(flatitude);
    free(ftemps);
    return 0;
}
