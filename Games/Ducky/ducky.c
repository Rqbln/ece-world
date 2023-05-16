// PECHE AUX CANARDS LOLA LE GALL







#include "ducky.h"
#include "../../joueur/joueur.h"

#define NCANARD 40
// Nombre de canards
#define TX 60
// Largeur canards
#define TY 70
// Hauteur canards




void aleaDepCanard(t_canard* canard){
    // generer les deplacements aléatoire des canards
    int newDepX;
    int newDepY;
    do{
        newDepX = rand()%5-2;
        newDepY = rand()%5-2;
    } while (newDepX == 0 && newDepY == 0);
    canard->depX = newDepX;
    canard->depY = newDepY;
}


t_canard* creerCanard(){
    //on alloue un canard
    t_canard* canard;
    canard = malloc(sizeof(t_canard));
    if(canard==NULL){
        allegro_message("Pb allocation t_canard");
        allegro_exit();
        exit(EXIT_FAILURE);
    }
    canard->posX = rand()%(SCREEN_W-TX);
    canard->posY = rand()%(SCREEN_H-200-TY);

    aleaDepCanard(canard);
    return canard;
}


void actualiserCanard(t_canard* canard){
    int posX = canard->posX;
    int posY = canard->posY;
    int depX = canard->depX;
    int depY = canard->depY;

    if(posX+depX+TX > SCREEN_W || posX+depX<0){
        canard->depX *= -1;
    }

    if(posY+depY+TY > SCREEN_H-200 || posY+depY<0){
        canard->depY *= -1;
    }

    canard->posX += canard->depX;
    canard->posY += canard->depY;
}



void dessinerCanard(BITMAP* buffer, t_canard* canard){
    // dessiner un seul canard
    int posX = canard->posX;
    int posY = canard->posY;

    BITMAP *canardimage = NULL;
    canardimage = load_bitmap("../Games/Ducky/IMAGES/canard.bmp", NULL);
    if (!canardimage) { //blindage
        allegro_message("Erreur image canard");
        exit(EXIT_FAILURE);
    }
    set_trans_blender(255, 0, 255, 255);
    drawing_mode(DRAW_MODE_TRANS, NULL, 0, 0);
    draw_trans_sprite(buffer, canardimage, posX, posY);
    destroy_bitmap(canardimage);
}

void remplirTab(t_canard* colonies[NCANARD]){
    // on remplit un tableau de N canards
    for (int fourmis=0; fourmis<NCANARD; fourmis++){
        colonies[fourmis] = creerCanard();
    }
}


int collision(t_canard *c1, t_canard *c2){
    // on dectecte les collisions
    if(c1 == c2) return 0;

    if(c1->posX < c2->posX && c1->posX+TX > c2->posX && c1->posY < c2->posY && c1->posY+TY > c2->posY) return 1;

    if(c2->posX < c1->posX && c2->posX+TX > c1->posX && c2->posY < c1->posY && c2->posY+TY > c1->posY) return 1;

    return 0;
}
void actualiserTab(t_canard* colonies[NCANARD]){
    int boum;
    for(int canard1=0; canard1<NCANARD; canard1++){
        for(int canard2 = 0; canard2<NCANARD; canard2++){
            boum = collision(colonies[canard1],colonies[canard2]);
            if(boum==1){
                aleaDepCanard(colonies[canard1]);
                aleaDepCanard(colonies[canard2]);
            }
        }
    }
    for(int canards=0; canards<NCANARD; canards++){
        actualiserCanard(colonies[canards]);
    }
}


void dessinerTab(BITMAP* buffer, t_canard* colonies[NCANARD]){
    // on dessine touts les canards
    for(int canards = 0; canards<NCANARD; canards++){
        dessinerCanard(buffer,colonies[canards]);
    }
}

int canardClicked(t_canard* canard, int mouseX, int mouseY) {
    // detection d'un canard attrapé
    return mouseX >= canard->posX && mouseX <= canard->posX + TX &&
           mouseY >= canard->posY && mouseY <= canard->posY + TY;
}

void player1(int *score1){
    // game du P1
    t_canard* colonies[NCANARD];
    *score1=0;
    remplirTab(colonies);
    // init des images
    BITMAP* buffer = create_bitmap(SCREEN_W, SCREEN_H);
    BITMAP *fond;
    fond= load_bitmap("../Games/Ducky/IMAGES/fond.bmp",NULL);
    if (!fond) { //blindage
        allegro_message("Erreur image fond");
        exit(EXIT_FAILURE);
    }
    BITMAP *player1;
    player1= load_bitmap("../Games/Ducky/IMAGES/player1.bmp",NULL);
    if (!player1) { //blindage
        allegro_message("Erreur image player");
        exit(EXIT_FAILURE);
    }
    SAMPLE * duck;
    duck= load_wav("../Games/Ducky/IMAGES/Vidéo-sans-titre.wav");
    ///////////////////////////////////////////////////////////////////////////////
    int mouseX, mouseY;
    show_mouse(screen);
    draw_sprite(buffer, fond, 0, 0);
    set_trans_blender(255, 0, 255, 255);
    drawing_mode(DRAW_MODE_TRANS, NULL, 0, 0);
    draw_trans_sprite(buffer, player1, (SCREEN_W - player1->w) / 2, (SCREEN_H - player1->h) / 2);
    char message[80];
    sprintf(message,"%s a toi de jouer, ramasse le plus de canards !",joueurs[0].nom);
    textout_centre_ex(buffer, font, message, SCREEN_W / 2-60, SCREEN_H /2 +100, makecol(255, 255, 255), -1);
    blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
    rest (2500);

    // Pour le compteur de 20 secondes
    clock_t depart_temps = clock();
    double temps_actuel = 0.0;
    double compteur = 20.0;
    int nb2=1;
    int nb3=1;
    // boucle de jeux
    while (!key[KEY_ESC] && temps_actuel < compteur){
        clear_bitmap(buffer);
        draw_sprite(buffer, fond, 0, 0);
        mouseX = mouse_x;
        mouseY = mouse_y;
        if (mouse_b & 1) {
            for (int i = 0; i < NCANARD; i++) {
                if (canardClicked(colonies[i], mouseX, mouseY) && mouseY<(SCREEN_H-200)) {
                    play_sample(duck,255,128,1000,0);
                    *score1 += 1;
                    int nb= *score1;
                    if (nb>8 && nb<=16){
                        colonies[i]->posX = TX + 110+nb2*TX;
                        colonies[i]->posY = SCREEN_H - TY - 105+TX;
                        nb2+=1;
                    }else if(nb>=17){
                        colonies[i]->posX = TX + 110+nb3*TX;
                        colonies[i]->posY = SCREEN_H - TY - 105+2*TX;
                        nb3+=1;
                    }else {
                            colonies[i]->posX = TX + 110+nb*TX;
                            colonies[i]->posY = SCREEN_H - TY - 105;
                        }
                    colonies[i]->depX = 0;
                    colonies[i]->depY = 0;
                }
            }
        }

        actualiserTab(colonies);
        dessinerTab(buffer,colonies);
        char score_text[50];
        sprintf(score_text, "Score: %d", *score1);
        textout_ex(buffer, font, score_text, 10, 10, makecol(255, 255, 255), -1);
        char timer[50];
        float car=20-temps_actuel;
        sprintf(timer, "Temps: %.0f", car);
        textout_ex(buffer, font, timer, SCREEN_W-75, 10, makecol(255, 255, 255), -1);
        temps_actuel = (double)(clock() - depart_temps) / CLOCKS_PER_SEC;
        blit(buffer,screen,0,0,0,0,SCREEN_W,SCREEN_H);

        rest(10);
    }

    for(int canard = 0; canard<NCANARD; canard++){
        free(colonies[canard]);
    }
    destroy_bitmap(fond);
    destroy_bitmap(player1);

}

void player2(int *score2){
    // game du P2
    t_canard* colonies[NCANARD];
    *score2=0;
    remplirTab(colonies);
    // init des images
    BITMAP* buffer = create_bitmap(SCREEN_W, SCREEN_H);
    BITMAP *fond;
    fond= load_bitmap("../Games/Ducky/IMAGES/fond.bmp",NULL);
    if (!fond) { //blindage
        allegro_message("Erreur image fond");
        exit(EXIT_FAILURE);
    }
    BITMAP *player2;
    player2= load_bitmap("../Games/Ducky/IMAGES/player2.bmp",NULL);
    if (!player2) { //blindage
        allegro_message("Erreur image player");
        exit(EXIT_FAILURE);
    }
    SAMPLE * duck;
    duck= load_wav("../Games/Ducky/IMAGES/Vidéo-sans-titre.wav");
    ///////////////////////////////////////////////////////////////////////////////
    int mouseX, mouseY;
    show_mouse(screen);
    draw_sprite(buffer, fond, 0, 0);
    set_trans_blender(255, 0, 255, 255);
    drawing_mode(DRAW_MODE_TRANS, NULL, 0, 0);
    draw_trans_sprite(buffer, player2, (SCREEN_W - player2->w) / 2, (SCREEN_H - player2->h) / 2);
    char message[80];
    sprintf(message,"%s a toi de jouer, ramasse le plus de canards !",joueurs[1].nom);
    textout_centre_ex(buffer, font, message, SCREEN_W / 2-60, SCREEN_H /2 +100, makecol(255, 255, 255), -1);
    blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
    rest (2500);

    // Pour le compteur de 20 secondes
    clock_t depart_temps = clock();
    double temps_actuel = 0.0;
    double compteur = 20.0;
    int nb2=1;
    int nb3=1;
    // boucle de jeux
    while (!key[KEY_ESC] && temps_actuel < compteur){
        clear_bitmap(buffer);
        draw_sprite(buffer, fond, 0, 0);
        mouseX = mouse_x;
        mouseY = mouse_y;
        if (mouse_b & 1) {
            for (int i = 0; i < NCANARD; i++) {
                if (canardClicked(colonies[i], mouseX, mouseY) && mouseY<(SCREEN_H-200)) {
                    play_sample(duck,255,128,1000,0);
                    *score2 += 1;
                    int nb= *score2;
                    if (nb>8 && nb<=16){
                        colonies[i]->posX = 830+TX + 110+nb2*TX;
                        colonies[i]->posY = SCREEN_H - TY - 105+TX;
                        nb2+=1;
                    }else if(nb>=17){
                        colonies[i]->posX = 830+TX + 110+nb3*TX;
                        colonies[i]->posY = SCREEN_H - TY - 105+2*TX;
                        nb3+=1;
                    }else {
                        colonies[i]->posX = 830+TX + 110+nb*TX;
                        colonies[i]->posY = SCREEN_H - TY - 105;
                    }
                    colonies[i]->depX = 0;
                    colonies[i]->depY = 0;
                }
            }
        }

        actualiserTab(colonies);
        dessinerTab(buffer,colonies);
        char score_text[50];
        sprintf(score_text, "Score: %d", *score2);
        textout_ex(buffer, font, score_text, 10, 10, makecol(255, 255, 255), -1);
        char timer[50];
        float car=20-temps_actuel;
        sprintf(timer, "Temps: %.0f", car);
        textout_ex(buffer, font, timer, SCREEN_W-75, 10, makecol(255, 255, 255), -1);
        temps_actuel = (double)(clock() - depart_temps) / CLOCKS_PER_SEC;
        blit(buffer,screen,0,0,0,0,SCREEN_W,SCREEN_H);

        rest(10);
    }

    for(int canard = 0; canard<NCANARD; canard++){
        free(colonies[canard]);
    }
    destroy_bitmap(fond);
    destroy_bitmap(player2);

}
void ducky(){ // remplace le main
    srand(time(NULL));
    int s1, s2;
    BITMAP *fond;
    fond= load_bitmap("../Games/Ducky/IMAGES/fond.bmp",NULL);
    if (!fond) { //blindage
        allegro_message("Erreur image fond");
        exit(EXIT_FAILURE);
    }

    BITMAP* buffer = create_bitmap(SCREEN_W, SCREEN_H);
    BITMAP * r;
    r= load_bitmap("../Games/Ducky/IMAGES/reglesd.bmp",NULL);
    if (!r) {
        //blindage
        allegro_message("Erreur image fond");
        exit(EXIT_FAILURE);
    }

    while (!key[KEY_ENTER]){
        draw_sprite(buffer, fond, 0, 0);
        draw_sprite(buffer, r, (SCREEN_W - r->w) / 2, (SCREEN_H - r->h) / 2);
        blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);

    }
    // enft drawtranssprite ca enleve tous le rouge
    // noot noot
    //merci
    //



    player1(&s1);
    player2(&s2);
    draw_sprite(buffer, fond, 0, 0);
    char message[50];
    // on detecte la victoire d'un des deux joueurs et on affiche le résultat
    if (s1>s2){
        sprintf(message,"%s a remporter un ticket",joueurs[0].nom);
        textout_centre_ex(buffer, font, message, SCREEN_W / 2, SCREEN_H /2, makecol(255, 255, 255), -1);
        joueurs[0].nbTickets+=1;
        joueurs[1].nbTickets-=1;
    } else if (s1<s2){
        sprintf(message,"%s a remporter un ticket",joueurs[1].nom);
        textout_centre_ex(buffer, font, message, SCREEN_W / 2, SCREEN_H /2, makecol(255, 255, 255), -1);
        joueurs[1].nbTickets+=1;
        joueurs[0].nbTickets-=1;
    } else {
        textout_centre_ex(buffer, font, "Les deux joueurs ont remporter un ticket", SCREEN_W / 2, SCREEN_H/2, makecol(255, 255, 255), -1);
        joueurs[1].nbTickets+=1;
        joueurs[0].nbTickets+=1;
    }

    blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
    rest(2000);
    //Attendre 2 secondes avant de quitter

    destroy_bitmap(fond);
    destroy_bitmap(buffer);
    destroy_bitmap(r);
}