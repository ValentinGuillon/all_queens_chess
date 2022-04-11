/*
Projet 2022, Programmation Impérative
Par Lylian DENISET (21001107) & Valentin GUILLON (20002588), Groupe L1-Y
Programme : All Queens Chess
*/

#include <stdio.h>
#include <stdlib.h> //type FILE, and files fonctions

#define TAILLE 5

typedef struct position {
    int x;
    int y;
}Position;


/*---------------------------------*/
/*---------DÉCLARATION-------------*/
/*----------FONCTIONS--------------*/
/*---------------------------------*/

//reçoit un fichier, et un tableau 2D
//écris dans le fichier, l'état actuel du tableau
void ecrire_chessboard(FILE *, int *, int player);




/*---------------------------------*/
/*---------------------------------*/
/*-------------MAIN----------------*/
/*---------------------------------*/

int main(void) {
                                       //  0  1  2  3  4 <-x   y
    int chessboard[TAILLE][TAILLE] = {{2, 0, 0, 1, 1},   //0
                                      {1, 0, 0, 1, 0},   //1
                                      {2, 0, 1, 0, 1},   //2
                                      {0, 2, 0, 2, 0},   //3
                                      {0, 2, 1, 2, 0}};  //4
    
    int player = 0;

    printf("\n>");
    scanf("%d", &player);

    FILE *fichier = NULL;
    fichier = fopen("../sauvegarde/chessboard_save.txt", "w");

    if (fichier != NULL) {
        ecrire_chessboard(fichier, &chessboard[0][0], player);
    }


    return 0;
}


/*---------------------------------*/
/*----------ÉCRITURE---------------*/
/*----------FONCTIONS--------------*/
/*---------------------------------*/

void ecrire_chessboard(FILE *fichier, int *chessboard, int player) {
    int i, j; //i = y, j = x

    //retour au début du fichier
    fseek(fichier , 0, SEEK_SET);

    for (i = 0; i < TAILLE; i++) {
        for (j = 0; j < TAILLE; j++) {
            //printf("%d", *(chessboard + j + (i * 5)));
            fprintf(fichier, "%d", *(chessboard + j + (i * 5)));
        }
        //printf("\n");
        fprintf(fichier, "\n");
    }

    switch (player) {
        case 1:
            fprintf(fichier, "r");
            break;
        case 2:
            fprintf(fichier, "n");
            break;
    }
    
}
