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
//remplis le tableau, en fonction du fichier
int lire_chessboard(FILE *, int *);




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

    printf("%d\n", player);

    FILE *fichier = NULL;
    fichier = fopen("../sauvegarde/chessboard_save.txt", "r");

    if (fichier != NULL) {
        player = lire_chessboard(fichier, &chessboard[0][0]);
    }
    fclose(fichier);

    printf("%d\n", player);

    return 0;
}


/*---------------------------------*/
/*----------ÉCRITURE---------------*/
/*----------FONCTIONS--------------*/
/*---------------------------------*/

int lire_chessboard(FILE *fichier, int *chessboard) {
    int player;
    char actual;
    int i = 0;
    //retour au début du fichier
    fseek(fichier , 0, SEEK_SET);

    actual = '\n';
    
    do {
        if (actual != '\n' && actual != EOF) {
            if (actual == 'r') {
                player = 1;
            }
            else if (actual == 'n') {
                player = 2;
            }
            else {
                *(chessboard + i) = actual - '0';
            }
            i++;
        }
        actual = fgetc(fichier);
    } while (actual != EOF);

    return player;
}
