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

//reçoit unt tableau à 2D et le numéro du joueur dont c'est le tour
//demander une position au joueur, jusqu'à se qu'elle soit valide
//retourne cette position
Position place_queen(int *chessboard, Position origin, int player);



/*---------------------------------*/
/*---------------------------------*/
/*-------------MAIN----------------*/
/*---------------------------------*/

int main(void) {

                                   //  0  1  2  3  4 <-x   y
    int chessboard[TAILLE][TAILLE] = {{1, 1, 1, 2, 1},   //0
                                      {1, 2, 0, 1, 1},   //1
                                      {2, 0, 1, 1, 0},   //2
                                      {2, 0, 1, 2, 1},   //3
                                      {1, 1, 0, 1, 2}};  //4

/*
    //input pour le joueur
                                   //  A  B  C  D  E <-x   y
    int chessboard[TAILLE][TAILLE] = {{1, 1, 1, 2, 1},   //1
                                      {1, 2, 0, 1, 1},   //2
                                      {2, 0, 1, 1, 0},   //3
                                      {2, 0, 1, 2, 1},   //4
                                      {1, 1, 0, 1, 2}};  //5
*/
    Position origin;
    Position chosen;



    while (1) {
        printf("\n\n\n");

        printf("origin = ");
        scanf("%d %d", origin.x, origin.y);

        chosen = place_queen(&chessboard[0][0], origin, 1);
        printf("------main -> x = %d, y = %d\n", chosen.x, chosen.y);
    }


    return 0;
}


/*---------------------------------*/
/*----------ÉCRITURE---------------*/
/*----------FONCTIONS--------------*/
/*---------------------------------*/

Position place_queen(int *chessboard, Position origin, int player) {
    int input; //permet de savoir si un input a déjà été donné, afin d'afficher un message d'erreur
    Position chosen;
    char x;
    int y;

    //printf("Choisissez une position (ex : B3):\n (Z0 = abandonner, Z1 = sauvegarder)\n>");
    printf("Choisissez une position (ex : B3):\n\n>");

    input = 0;
    //tant que la reine n'est pas au joueur
    do {

        //message d'avertissement dans le cas où la position choisie n'est pas valide
        if (input == 1) {
            afficher_chessboard(chessboard, origin, player);
            printf("Cette place est déjà prise\n\n>");
        }

        scanf("%c%d", &x, &y);
        /*
        //permet d'abandonner ou de sauvegarder la partie
        if ((x == 'Z' || x == 'z') && (y == 0 || y == 1)) {
            chosen.x = -1;
            chosen.y = y;
            return chosen;
        }*/

        //tant que les coordonnées ne sont pas valide
        //x n'est pas A, B, C, D ou E (min ou maj) et y n'est pas entre 1 et 5
        while (((x < 65 || x > 69) && (x < 97 || x > 101)) || (y < 1 || y > 5)) {
            if (input == 2) {
                afficher_chessboard(chessboard, origin, player);
                printf("Coordonnées invalides\n\n>");
            }
            scanf("%c%d", &x, &y);
            /*
            //permet d'abandonner ou de sauvegarder la partie
            if ((x == 'Z' || x == 'z') && (y == 0 || y == 1)) {
                chosen.x = -1;
                chosen.y = y;
                return chosen;
            }*/

            input = 2;
        }
        input = 0;

        //conversion des inputs en position lisible dans le tableau
        //pour x
        //si c'est une majuscule
        if (x >= 65 && x <= 69) {
            chosen.x = x - 65;
        }
        //si c'est une minuscule
        else if ((x >= 97 && x <= 101)) {
            chosen.x = x - 97;
        }
        //pour y
        chosen.y = y - 1;

        input = 1;
    } while (*(chessboard + chosen.x + (chosen.y * TAILLE)) != 0);
    input = 0;

    return chosen;
}
