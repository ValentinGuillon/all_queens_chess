

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

//reçoit un tableau 2D, et le joueur qui joue
//affiche l'état actuelle du plateau dans le terminal
void afficher_chessboard(int *chessboard, Position chosen, int player);




/*---------------------------------*/
/*---------------------------------*/
/*-------------MAIN----------------*/
/*---------------------------------*/

int main(void) {
                                   //  0  1  2  3  4 <-x   y
    int chessboard[TAILLE][TAILLE] = {{2, 1, 2, 1, 2},   //0
                                      {0, 0, 0, 0, 0},   //1
                                      {2, 0, 0, 0, 1},   //2
                                      {0, 0, 0, 0, 0},   //3
                                      {1, 2, 1, 2, 1}};  //4

    Position origin;
    origin.x = 4;
    origin.y = 2;

    afficher_chessboard(&chessboard[0][0], origin, 1);

    return 0;
}


/*---------------------------------*/
/*----------ÉCRITURE---------------*/
/*----------FONCTIONS--------------*/
/*---------------------------------*/

void afficher_chessboard(int *chessboard, Position chosen, int player) {
    int i, j; //i = abscisse, j = ordonnée
    int queen;

    


    printf("\n\n\n\n\n\n\n\n\n\n\n\n");

    switch (player) {
        case 1:
            printf("                -----         \n");    
            printf("               |  R  |    N   \n");
            printf("                -----         \n");    
            break;
        case 2:
            printf("                        ----- \n");    
            printf("                  R    |  N  |\n");
            printf("                        ----- \n");  
            break;
    }



    printf("        - - - - - - - - - - - - - - -\n");
    printf("       |  A     B     C     D     E  |\n");
    printf("  - - - -----------------------------\n");
    for (j = 0; j < TAILLE; j++) {
        printf(" |  %d  |", j + 1);
        for (i = 0; i < TAILLE; i++) {
            queen = *(chessboard + i + (j * TAILLE));



            if (chosen.x == i && chosen.y == j) {
                printf("< ");
            }
            else {
                printf("  ");
            }


            switch (queen) {
                case 0:
                    printf(" ");
                    break;
                case 1:
                    printf("R");
                    break;
                case 2:
                    printf("N");
                    break;
            }

            if (chosen.x == i && chosen.y == j) {
                printf(" >");
            }
            else {
                printf("  ");
            }

            printf("|");
        }
        printf("\n");
        if (j != 4) {
            printf("       |-----|-----|-----|-----|-----|\n");
        }
        else {
            printf("  - - - -----------------------------\n");
        }
        
    }
    printf("\n");

}