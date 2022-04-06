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


//reçoit une position de départ et d'arrivée, et un tableau, à 2 dimension, d'entiers
//détermine si la position est autorisé
//retourne 0 si le déplacement est possible, sinon 1
int sans_conflit(Position, Position, int *);



/*---------------------------------*/
/*---------------------------------*/
/*-------------MAIN----------------*/
/*---------------------------------*/

int main(void) {
    /*
                                   //  0  1  2  3  4 <-x   y
    int chessboard[TAILLE][TAILLE] = {{1, 2, 3, 4, 5},   //0
                                      {8, 2, 5, 9, 6},   //1
                                      {2, 7, 4, 2, 3},   //2
                                      {6, 9, 3, 2, 4},   //3
                                      {4, 3, 1, 2, 7}};  //4
    */
    
                                   //  0  1  2  3  4 <-x   y
    int chessboard[TAILLE][TAILLE] = {{2, 0, 0, 1, 1},   //0
                                      {1, 0, 0, 1, 0},   //1
                                      {2, 0, 1, 0, 1},   //2
                                      {0, 2, 0, 2, 0},   //3
                                      {0, 2, 1, 2, 0}};  //4
    

    Position depart;
    Position arrivee;

    while(1) {
        printf("position départ :\n>");
        scanf("%d %d", &depart.x, &depart.y);

        printf("position arrivée :\n>");
        scanf("%d %d", &arrivee.x, &arrivee.y);

        if (sans_conflit(depart, arrivee, &chessboard[0][0])) {
            printf("\nAutorisé !\n");
        }
        else {
            printf("\nNon Autorisé !\n");
        }
        printf("\n");
    }
    


    return 0;
}


/*---------------------------------*/
/*----------ÉCRITURE---------------*/
/*----------FONCTIONS--------------*/
/*---------------------------------*/


int sans_conflit(Position origin, Position dest, int *chessboard) {
    char dir;
    Position distance;
    int adjust_x, adjust_y;
    int distance_x_adj, distance_y_adj;
    int i;

    //verif direction
        //horizontal
    if (origin.y == dest.y) {
        //printf("------------c'est horizontal\n");
        dir = 'h';
        distance.x = dest.x - origin.x;
        distance.y = dest.y - origin.y;
        /*
        printf("------------origin = %d %d\n", origin.x, origin.y);
        printf("------------dest = %d %d\n", dest.x, dest.y);
        printf("------------distance = %d %d\n\n", distance.x, distance.y);
        */
    }
        //vertical
    else if (origin.x == dest.x) {
        //printf("------------c'est verticale\n");
        dir = 'v';
        distance.x = dest.x - origin.x;
        distance.y = dest.y - origin.y;
        /*
        printf("------------origin = %d %d\n", origin.x, origin.y);
        printf("------------dest = %d %d\n", dest.x, dest.y);
        printf("------------distance = %d %d\n\n", distance.x, distance.y);
        */
    }
        //diagonal
    else if ((dest.x - origin.x) == (dest.y - origin.y) || (dest.x - origin.x) == -(dest.y - origin.y)) {
        //printf("------------c'est diagonal\n");
        dir = 'd';
        distance.x = dest.x - origin.x;
        distance.y = dest.y - origin.y;
        /*
        printf("------------origin = %d %d\n", origin.x, origin.y);
        printf("------------dest = %d %d\n", dest.x, dest.y);
        printf("------------distance = %d %d\n\n", distance.x, distance.y);
        */
    }
    else {
        //printf("------------non-alignés\n");
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
                //printf("------------position observée : [%d; %d]\n", origin.x + (i * adjust_x), origin.y);
                //printf("------------pion observé : %d\n", *(chessboard + origin.x + (origin.y * TAILLE) + (i * adjust_x)));
                if (*(chessboard + origin.x + (origin.y * TAILLE) + (i * adjust_x)) != 0) {
                        //printf("------------reine trouvé en horizontall en [%d; %d]\n", origin.x + (i * adjust_x), origin.y);
                    return 0;
                }
            }
            break;
        case 'v': //vertical
            for (i = 1; i <= distance_y_adj; i++) {
                //printf("------------position observée : [%d; %d]\n", origin.x, origin.y + (i * adjust_y));
                //printf("------------pion observé : %d\n", *(chessboard + origin.x + (origin.y * TAILLE) + ((i * TAILLE) * adjust_y)));
                if (*(chessboard + origin.x + (origin.y * TAILLE) + ((i * TAILLE) * adjust_y)) != 0) {
                        //printf("------------reine trouvé en verticall en [%d; %d]\n", origin.x, origin.y + (i * adjust_y));
                    return 0;
                }
            }
            break;
        case 'd': //diagonal
            for (i = 1; i <= distance_y_adj; i++) {
                //printf("------------position observée : [%d; %d]\n", origin.x + (i * adjust_x), origin.y + (i * adjust_y));
                //printf("------------pion observé : %d\n", *(chessboard + origin.x + (origin.y * TAILLE) + (i * adjust_x) + ((i * TAILLE) * adjust_y)));
                if (*(chessboard + origin.x + (origin.y * TAILLE) + (i * adjust_x) + ((i * TAILLE) * adjust_y)) != 0) {
                        //printf("------------reine trouvé en diagonal en [%d; %d]\n", origin.x + (i * adjust_x), origin.y + (i * adjust_y));
                    return 0;
                }
            }
            break;
        
        default:
            //printf("------------default\n");
            return 0;
            break;
    }
    
    //aucune reine rencontrée
    /*
    switch (dir) {
        case 'h':
            printf("------------déplacement horizontal autorisé\n");
            break;
        case 'v':
            printf("------------déplacement vertical autorisé\n");
            break;
        case 'd':
            printf("------------déplacement diagonal autorisé\n");
            break;
        
        default:
            printf("------------erro\n");
            break;
    }
    */

    return 1;
}