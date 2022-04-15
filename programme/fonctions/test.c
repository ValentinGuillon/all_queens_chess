/*navigation dans un tableau 2D*/

#include <stdio.h>

#define TAILLE 5

typedef struct position {
    int x;
    int y;
}Position;


//reçoit un tableau 2D, et un position (celle de la reine choisie)
//affiche l'état actuelle du plateau dans le terminal
void afficher_chessboard(int *chessboard, Position chosen);

//reçoit unt tableau à 2D et le numéro du joueur dont c'est le tour
//demander une position au joueur, jusqu'à se qu'elle soit valide (== player)
//retourne cette position
Position choose_queen(int *chessboard, int player);

//reçoit unt tableau à 2D
//demander une position au joueur, jusqu'à se qu'elle soit valide (== 0)
//retourne cette position
Position place_queen(int *chessboard, Position origin);


int main(void) {
                                     //0  1  2  3  4 <-x y
    int chessboard[TAILLE][TAILLE] = {{2, 1, 2, 1, 2}, //0
                                      {0, 0, 0, 0, 0}, //1
                                      {1, 0, 0, 0, 2}, //2
                                      {0, 0, 0, 0, 0}, //3
                                      {1, 2, 1, 2, 1}};//4

    Position origin, dest;
    Position pos_null;
    pos_null.x = -1;
    pos_null.y = -1;

    afficher_chessboard(&chessboard[0][0], pos_null);

    //          y  x
    //chessboard[0][1] = 0;

    origin = choose_queen(&chessboard[0][0], 1);
    dest = place_queen(&chessboard[0][0], origin);

    printf("origin = %d %d\n", origin.x, origin.y);
    printf("destin = %d %d\n", dest.x, dest.y);

    //         y  x
    chessboard[origin.y][origin.x] = 0;
    chessboard[dest.y][dest.x] = 1;



    afficher_chessboard(&chessboard[0][0], pos_null);
    
    return 0;
}


void afficher_chessboard(int *chessboard, Position chosen) {
    int i, j; //i = abscisse, j = ordonnée
    int queen;


    printf("\n\n\n\n");
    printf("        -----------------------------\n");
    printf("       |  A     B     C     D     E  |\n");
    printf("  ----- -----------------------------\n");
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
            printf(" |     |-----|-----|-----|-----|-----|\n");
        }
        else {
            printf("  ----- -----------------------------\n");
        }
        
    }
    printf("\n");

}



Position choose_queen(int *chessboard, int player) {
    int input; //permet de savoir si un input a déjà été donné, afin d'afficher un message d'erreur
    Position chosen;
    Position pos_null;
    pos_null.x = -1;
    pos_null.y = -1;
    char x;
    int y;

    switch (player) {
        case 1:
            printf("Joueur R");
            break;
        case 2:
            printf("Joueur N");
            break;
    }
    printf(", choississez une reine (ex : B3):\n>");

    input = 0;
    //tant que la reine n'est pas au joueur
    do {
        //message d'avertissement dans le cas où la reine selectionnée n'est pas valide
        if (input == 1) {
            switch (*(chessboard + chosen.x + (chosen.y * TAILLE))) {
                case 0:
                    afficher_chessboard(chessboard, pos_null);
                    printf("Vous devez choisir une reine\n>");
                    break;
                case 1:
                    afficher_chessboard(chessboard, pos_null);
                    printf("Cette reine n'est pas à vous\n>");
                    break;
                case 2:
                    afficher_chessboard(chessboard, pos_null);
                    printf("Cette reine n'est pas à vous\n>");
                    break;
            }
        }
        scanf("%c%d", &x, &y);
        //tant que les coordonnées ne sont pas valide
        //x n'est pas A, B, C, D ou E (min ou maj) et y n'est pas entre 1 et 5
        while (((x < 65 || x > 69) && (x < 97 || x > 101)) || (y < 1 || y > 5)) {
            if (input == 2) {
                afficher_chessboard(chessboard, pos_null);
                printf("Coordonnées invalides\n>");
            }
            scanf("%c%d", &x, &y);
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
    } while (*(chessboard + chosen.x + (chosen.y * TAILLE)) != player);
    input = 0;

    return chosen;
}

Position place_queen(int *chessboard, Position origin) {
    int input; //permet de savoir si un input a déjà été donné, afin d'afficher un message d'erreur
    Position chosen;
    char x;
    int y;

    printf("Choississez une position (ex : B3):\n>");

    input = 0;
    //tant que la reine n'est pas au joueur
    do {

        //message d'avertissement dans le cas où la position choisie n'est pas valide
        if (input == 1) {
            afficher_chessboard(chessboard, origin);
            printf("Cette place est déjà prise\n>");
        }

        scanf("%c%d", &x, &y);
        //tant que les coordonnées ne sont pas valide
        //x n'est pas A, B, C, D ou E (min ou maj) et y n'est pas entre 1 et 5
        while (((x < 65 || x > 69) && (x < 97 || x > 101)) || (y < 1 || y > 5)) {
            if (input == 2) {
                afficher_chessboard(chessboard, origin);
                printf("Coordonnées invalides\n>");
            }
            scanf("%c%d", &x, &y);
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