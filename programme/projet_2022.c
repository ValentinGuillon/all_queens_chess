/*
Projet 2022, Programmation Impérative
Par Lylian DENISET & Valentin GUILLON, Groupe L1-Y
Programme : All Queens Chess
*/

#include <stdio.h>

#define TAILLE 5

typedef struct Position {
    int x;
    int y;
}position;


/*---------------------------------*/
/*---------DÉCLARATION-------------*/
/*----------FONCTIONS--------------*/
/*---------------------------------*/

//reçoit un tableau, à 2 dimension, d'entiers
//affiche l'état actuelle du plateau
void afficher_chessboard(int *);

//reçoit un fichier, et un tableau, à 2 dimension, d'entiers
//remplis le tableau, en fonction du fichier
void lire_chessboard(FILE *, int *);

//reçoit un fichier, et un tableau, à 2 dimension, d'entiers
//écris dans le fichier, l'état actuel du tableau
void ecrire_chessboard(FILE *, int *);

//reçoit une position de départ et d'arrivée, et un tableau, à 2 dimension, d'entiers
//détermine si la position est autorisé
//retourne 0 si le déplacement est possible, sinon 1
int sans_conflit(position, position, int *);

//reçoit un tableau, à 2 dimension, d'entiers
//vérifie si 4 même reines reine sont alignées
//retourne 1 si les 4 reines sont celles du joueur 1, retourne 2 pour le joueur 2, sinon 0;
int winning(int *);


/*---------------------------------*/
/*---------------------------------*/
/*-------------MAIN----------------*/
/*---------------------------------*/

int main(void) {

    return 0;
}


/*---------------------------------*/
/*----------ÉCRITURE---------------*/
/*----------FONCTIONS--------------*/
/*---------------------------------*/


