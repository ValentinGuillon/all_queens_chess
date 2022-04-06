/*
Projet 2022, Programmation Impérative
Par Lylian DENISET & Valentin GUILLON, Groupe L1-Y
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

//reçoit un tableau 2D
//affiche l'état actuelle du plateau dans le terminal
void afficher_chessboard(int *); //NON FAIT----------------------------------

//reçoit un fichier, et un tableau 2D
//remplis le tableau, en fonction du fichier
void lire_chessboard(FILE *, int *); //NON FAIT------------------------------

//reçoit un fichier, et un tableau 2D
//écris dans le fichier, l'état actuel du tableau
void ecrire_chessboard(FILE *, int *); //NON FAIT----------------------------
//reçoit unt tableau à 2D et le numéro du joueur dont c'est le tour
//demander une position au joueur, jusqu'à se qu'elle soit valide
//retourne cette position
Position choose_queen(int *, int); //NON FAIT--------------------------------

//reçoit unt tableau à 2D
//demander une position au joueur, jusqu'à se qu'elle soit valide
//retourne cette position
Position take_queen(int *); //NON FAIT---------------------------------------


//reçoit une position de départ et d'arrivée, et un tableau, à 2 dimension, d'entiers
//détermine si la position est autorisé
//retourne 0 si le déplacement est possible, sinon 1
int sans_conflit(Position, Position, int *);

//reçoit un tableau, à 2 dimension, d'entiers
//vérifie si 4 même reines reine sont alignées
//retourne 1 si les 4 reines sont celles du joueur 1, retourne 2 pour le joueur 2, sinon 0;
int winning(int *); //NON FAIT----------------------------------------------


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


