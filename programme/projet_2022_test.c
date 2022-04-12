/*
Projet 2022, Programmation Impérative
Écrit par :
    Groupe : L1-Y
    Membres :
        Lylian DENISET (21001107)
        Valentin GUILLON (20002588)

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

//reçoit un tableau 2D, et un position (celle de la reine choisie)
//affiche l'état actuelle du plateau dans le terminal
void afficher_chessboard(int *chessboard, Position chosen, int player);


//reçoit un fichier, et un tableau 2D
//remplis le tableau, en fonction du fichier
int lire_chessboard(FILE *fichier, int *chessboard);

//reçoit un fichier, et un tableau 2D
//écris dans le fichier, l'état actuel du tableau
void ecrire_chessboard(FILE *fichier, int *chessboard, int player);


//reçoit unt tableau à 2D et le numéro du joueur dont c'est le tour
//demander une position au joueur, jusqu'à se qu'elle soit valide (== player)
//retourne cette position
Position choose_queen(int *chessboard, int player);

//reçoit unt tableau à 2D
//demander une position au joueur, jusqu'à se qu'elle soit valide (== 0)
//retourne cette position
Position place_queen(int *chessboard, Position origin, int player);


//reçoit une position de départ et d'arrivée, et un tableau, à 2 dimension, d'entiers
//détermine si la position est autorisé
//retourne 0 si le déplacement est possible, sinon 1
int sans_conflit(Position origin, Position dest, int *chessboard);

//reçoit un tableau, à 2 dimension, d'entiers
//vérifie si 4 même reines reine sont alignées
//retourne 1 si les 4 reines sont celles du joueur 1, retourne 2 pour le joueur 2, sinon 0;
int winning(int *chessboard);


/*---------------------------------*/
/*---------------------------------*/
/*-------------MAIN----------------*/
/*---------------------------------*/

int main(void) {
    char reload; //permet de savoir si la partie précédente doit être chargée
    int player = 1; //joueur dont c'est le tour
    int winner; //joueur gagnant (0 s'il n'y en a pas encore)
    Position pos_origin, pos_dest; //coordonnées de la reine selectionnée, et de sa destination
    Position pos_null; pos_null.x = -1; pos_null.y = -1;//position pour l'affichage, quand on ne veux pas mettre de pièce en surbrillance
    
    
                                   //  0  1  2  3  4 <-x   y
    int chessboard[TAILLE][TAILLE] = {{2, 1, 2, 1, 2},   //0
                                      {0, 0, 0, 0, 0},   //1
                                      {1, 0, 0, 0, 2},   //2
                                      {0, 0, 0, 0, 0},   //3
                                      {1, 2, 1, 2, 1}};  //4

    FILE *fichier = NULL;


    
    printf("\nSouhaitez-vous charger la partie sauvegardée ? (y/n)\n>");
    do {
        scanf("%1s", &reload);
    } while (reload != 'y' && reload != 'n' && reload != '7');

    switch (reload) {
        //chargement de la partie sauvegarder
        case 'y':
            printf("Chargement de la partie...\n");
            fichier = fopen("sauvegarde/chessboard_save.txt", "r");
            if (fichier != NULL) {
                player = lire_chessboard(fichier, &chessboard[0][0]);
                printf("Partie chargée !\n");
                fclose(fichier);
            }
            else {
                printf("file error : Sauvegarde inexistante ou corrompue\n");
            }
            
            break;

        //chargement de la partie
        case 'n':
            printf("Alors commençons !\n");
            break;
        
        //chargement d'une partie test
        case '7':
            printf("Chargement de la partie...\n");
            fichier = fopen("sauvegarde/chessboard_test.txt", "r");
            if (fichier != NULL) {
                player = lire_chessboard(fichier, &chessboard[0][0]);
                printf("Partie test chargée !\n");
                fclose(fichier);
            }
            else {
                printf("file error : Sauvegarde inexistante ou corrompue\n");
            }
            
            break;

        default:
            printf("input error : Partie non chargée");
            break;
    }



    //jeu
    winner = 0;
    while (winner == 0) {
        rechoose_queen:
        //choix de la reine
        afficher_chessboard(&chessboard[0][0], pos_null, player);
        pos_origin = choose_queen(&chessboard[0][0], player);

        //en cas d'abandon ou de sauvegarde
        if (pos_origin.x == -1) {
            goto has_ff_or_save;
        }

        rechoose_position:
        //choix de sa destination
        afficher_chessboard(&chessboard[0][0], pos_origin, player);
        pos_dest = place_queen(&chessboard[0][0], pos_origin, player);

        //en cas d'abandon ou de sauvegarde
        if (pos_origin.x == -1) {
            goto has_ff_or_save;
        }


        //verification de la possibilité du déplacement
        //si non
        if (sans_conflit(pos_origin, pos_dest, &chessboard[0][0]) == 0) {
            int replace;
            afficher_chessboard(&chessboard[0][0], pos_origin, player);
            //changer de reine, ou changer sa destination
            printf("Mouvement impossible. Replacer(1) ou changer(2) de reine?\n>");
            do {
                scanf("%d", &replace);
            } while (replace != 1 && replace != 2);

            switch (replace) {
                case 1:
                    //choisir une nouvelle destination
                    goto rechoose_position;
                    break;

                case 2:
                    //choisir une nouvelle reine
                    goto rechoose_queen;
                    break;
            }
        }
        //si oui
        else if (sans_conflit(pos_origin, pos_dest, &chessboard[0][0]) == 1) {
            chessboard[pos_origin.y][pos_origin.x] = 0;
            chessboard[pos_dest.y][pos_dest.x] = player;
        }

        afficher_chessboard(&chessboard[0][0], pos_null, player);
        //verifie si 4 reines sont alignées
        winner = winning(&chessboard[0][0]);
        
        //change le joueur
        if (winner == 0) {
            switch (player) {
                case 1:
                    player = 2;
                    break;
                case 2:
                    player = 1;
                    break;
            }
        }
    }


    //et cas d'abandon ou de sauvegarde
    //condition permettant que le programme ne puisse pas rentrer dans ce while sans goto
    while (0) {
        has_ff_or_save:
        switch (pos_origin.y) {
            //abandon
            case 0:
                switch (player) {
                    case 1:
                        printf("Le Joueur R a abandonné la partie\n");
                        player = 2;
                        winner = player;
                        break;
                    case 2:
                        printf("Le Joueur N a abandonné la partie\n");
                        player = 1;
                        winner = player;
                        break;
                }
                break;

            //sauvegarde
            case 1:
                winner = -1;
                break;
        }
    }





    //affiche le gagnant
    switch (winner) {
        //sauvegarde de la partie
        case -1:
            //sauvegarde de la partie
            fichier = fopen("sauvegarde/chessboard_save.txt", "w");
            if (fichier != NULL) {
                ecrire_chessboard(fichier, &chessboard[0][0], player);
                printf("La partie a été sauvardée !\n");
                fclose(fichier);
            }
            else {
                printf("error: fichier de sauvegarde introuvable\nEchec de la sauvegarde\n");
            }

            break;

        //J1 gagne
        case 1:
            printf("Le joueur R remporte la partie !\n");
            break;

        //J2 gagne
        case 2:
            printf("Le joueur N remporte la partie !\n");
            break;
    }


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
    
    printf(", choisissez une reine (ex : B3)\n (Z0 = abandonner, Z1 = sauvegarder)\n>");

    input = 0;
    //tant que la reine n'est pas au joueur
    do {
        //message d'avertissement dans le cas où la reine selectionnée n'est pas valide
        if (input == 1) {
            switch (*(chessboard + chosen.x + (chosen.y * TAILLE))) {
                case 0:
                    afficher_chessboard(chessboard, pos_null, player);
                    printf("Vous devez choisir une reine\n\n>");
                    break;
                case 1:
                    afficher_chessboard(chessboard, pos_null, player);
                    printf("Cette reine n'est pas à vous\n\n>");
                    break;
                case 2:
                    afficher_chessboard(chessboard, pos_null, player);
                    printf("Cette reine n'est pas à vous\n\n>");
                    break;
            }
        }
        scanf("%c%d", &x, &y);
        //permet d'abandonner ou de sauvegarder la partie
        if ((x == 'Z' || x == 'z') && (y == 0 || y == 1)) {
            chosen.x = -1;
            chosen.y = y;
            return chosen;
        }

        //tant que les coordonnées ne sont pas valide
        //x n'est pas A, B, C, D ou E (min ou maj) et y n'est pas entre 1 et 5
        while (((x < 65 || x > 69) && (x < 97 || x > 101)) || (y < 1 || y > 5)) {
            if (input == 2) {
                afficher_chessboard(chessboard, pos_null, player);
                printf("Coordonnées invalides\n\n>");
            }
            scanf("%c%d", &x, &y);
            //permet d'abandonner ou de sauvegarder la partie
            if ((x == 'Z' || x == 'z') && (y == 0 || y == 1)) {
                chosen.x = -1;
                chosen.y = y;
                return chosen;
            }
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



int sans_conflit(Position origin, Position dest, int *chessboard) {
    char dir;
    Position distance;
    int adjust_x, adjust_y;
    int distance_x_adj, distance_y_adj;
    int i;

    //verif direction
        //horizontal
    if (origin.y == dest.y) {
        dir = 'h';
        distance.x = dest.x - origin.x;
        distance.y = dest.y - origin.y;
    }
        //vertical
    else if (origin.x == dest.x) {
        dir = 'v';
        distance.x = dest.x - origin.x;
        distance.y = dest.y - origin.y;
    }
        //diagonal
    else if ((dest.x - origin.x) == (dest.y - origin.y) || (dest.x - origin.x) == -(dest.y - origin.y)) {
        dir = 'd';
        distance.x = dest.x - origin.x;
        distance.y = dest.y - origin.y;
    }
        //non alignés
    else {
        return 0;
    }



    //pour savoir si la coordonnées est positive ou négative
    //adjust permet de pouvoir se déplacer dans le tableau dans n'importe qu'elle direction (sans ça, dans le switch suivant, il faudra écrire pour chaque direction en x et en y (soit 4 possibilité))
        //for x
    if (distance.x < 0) {
        adjust_x = -1;
        distance_x_adj = -distance.x;
    }
    else {
        adjust_x = 1;
        distance_x_adj = distance.x;
    }
        //for y
    if (distance.y < 0) {
        adjust_y = -1;
        distance_y_adj = -distance.y;
    }
    else {
        adjust_y = 1;
        distance_y_adj = distance.y;
    }



    //verif qu'il n'y a pas de reines sur le trajet
    //étant donnée qu'une case libre est représenté par un 0 (zéro), dès qu'un 0 est rencontré, on retourne 0 (signifiant déplacement non autorisé)
    switch (dir) {
        case 'h': //horizontal
            for (i = 1; i <= distance_x_adj; i++) {
                if (*(chessboard + origin.x + (origin.y * TAILLE) + (i * adjust_x)) != 0) {
                    return 0;
                }
            }
            break;
        case 'v': //vertical
            for (i = 1; i <= distance_y_adj; i++) {
                if (*(chessboard + origin.x + (origin.y * TAILLE) + ((i * TAILLE) * adjust_y)) != 0) {
                    return 0;
                }
            }
            break;
        case 'd': //diagonal
            for (i = 1; i <= distance_y_adj; i++) {
                if (*(chessboard + origin.x + (origin.y * TAILLE) + (i * adjust_x) + ((i * TAILLE) * adjust_y)) != 0) {
                    return 0;
                }
            }
            break;
        
        default:
            return 0;
            break;
    }
    
    //aucune reine rencontrée
    return 1;
}



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