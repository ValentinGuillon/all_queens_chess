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

//reçoit un tableau, à 2 dimension, d'entiers
//vérifie si 4 même reines reine sont alignées
//retourne 1 si les 4 reines sont celles du joueur 1, retourne 2 pour le joueur 2, sinon 0;
int winning(int *chessboard);




/*---------------------------------*/
/*---------------------------------*/
/*-------------MAIN----------------*/
/*---------------------------------*/

int main(void) {
    
    int winner;
                                   //  0  1  2  3  4 <-x   y
    int chessboard[TAILLE][TAILLE] = {{1, 1, 1, 2, 1},   //0
                                      {1, 2, 0, 1, 1},   //1
                                      {2, 0, 1, 1, 0},   //2
                                      {2, 0, 1, 2, 1},   //3
                                      {1, 1, 0, 1, 2}};  //4
    
    winner = winning(&chessboard[0][0]);
    
    switch (winner) {
        case 1:
            printf("J1 gagne\n");
            break;
        case 2:
            printf("J2 gagne\n");
            break;
        case 0:
            printf("Pas de gagnant\n");
            break;
        
        default:
            printf("error\n");
            break;
        }

    return 0;
}


/*---------------------------------*/
/*----------ÉCRITURE---------------*/
/*----------FONCTIONS--------------*/
/*---------------------------------*/

int winning(int *chessboard) {
    int player, count;
    int i, j; //i pour abscisse, j pour ordonnée
    int verif; //nombre de vérif fait en diagonale

    //alignement horizontal
    for (j = 0; j < TAILLE; j++) {
        player = 0;
        count = 0;
        for (i = 0; i < TAILLE; i++) {
            while (player == 0) {
                player = *(chessboard + (j * TAILLE) + i);
                count = 1;
                i++;
            }
            if(*(chessboard + (j * TAILLE) + i) == 0) {
                player = 0;
                count = 0;
            }
            else if (*(chessboard + (j * TAILLE) + i) == player) {
                count++;
            }
            else {
                if (player == 1) {player = 2;}
                else if (player == 2) {player = 1;}
                count = 1;
            }
            
            if (count == 4) {
                return player;
            }
        }
    }

    //alignement vertical
    for (i = 0; i < TAILLE; i++) {
        
        player = 0;
        count = 0;
        for (j = 0; j < TAILLE; j++) {
            while (player == 0) {
                player = *(chessboard + (j * TAILLE) + i);
                count = 1;
                j++;
            }
            if(*(chessboard + (j * TAILLE) + i) == 0) {
                player = 0;
                count = 0;
            }
            else if (*(chessboard + (j * TAILLE) + i) == player) {
                count++;
            }
            else {
                if (player == 1) {player = 2;}
                else if (player == 2) {player = 1;}
                count = 1;
            }
            if (count == 4) {
                return player;
            }
        }
    }

    //alignement diagonale
    //vers bas droite
    player = 0;
    count = 0;
    verif = 1;
    
    while (1) {
        switch (verif) {
            case 1:
                i = 0, j = 0;
                break;
            case 2:
                i = 0, j = 1;
                break;
            case 3:
                i = 1, j = 0;
                break;
            case 4:
                goto end_verif_diag_bas_droite;
                break;
            default:
                break;
        }

        while (1) {
            while (player == 0) {
                player = *(chessboard + (j * TAILLE) + i);
                count = 1;
                i++, j++;
            }

            //si on sort du plateau
            if (i >= TAILLE || j >= TAILLE) {
                verif++;
                break;
                }

            if(*(chessboard + (j * TAILLE) + i) == 0) {
                player = 0;
                count = 0;
                i++, j++;
            }
            else if (*(chessboard + (j * TAILLE) + i) == player) {
                count++;
                i++, j++;
            }
            else {
                if (player == 1) {player = 2;}
                else if (player == 2) {player = 1;}
                count = 1;
                i++, j++;
            }

            if (count == 4) {
                return player;
            }
        }
        printf("\n");
    }
    end_verif_diag_bas_droite:

    //vers haut droite
    player = 0;
    count = 0;
    verif = 1;

    while (1) {
        switch (verif) {
            case 1:
                i = 0, j = 4;
                break;
            case 2:
                i = 1, j = 4;
                break;
            case 3:
                i = 0, j = 3;
                break;
            case 4:
                goto end_verif_diag_haut_droite;
                break;
            default:
                break;
        }

        while (1) {
            while (player == 0) {
                player = *(chessboard + (j * TAILLE) + i);
                count = 1;
                i++, j--;
            }

            //si on sort du plateau
            if (i >= TAILLE || j < 0) {
                verif++;
                break;
                }

            if(*(chessboard + (j * TAILLE) + i) == 0) {
                player = 0;
                count = 0;
                i++, j--;
            }
            else if (*(chessboard + (j * TAILLE) + i) == player) {
                count++;
                i++, j--;
            }
            else {
                if (player == 1) {player = 2;}
                else if (player == 2) {player = 1;}
                count = 1;
                i++, j--;
            }
            
            if (count == 4) {
                return player;
            }
        }
        printf("\n");
    }
    end_verif_diag_haut_droite:


    return 0;
}
