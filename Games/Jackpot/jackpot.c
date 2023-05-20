// MACHINE A SOUS LOLA LE GALL


//try 2




#include "jackpot.h"
#include "../../joueur/joueur.h"
#include "../../Sauvegarde/sauvegarde.h"


BITMAP *icons[NUM_ICONS];
char filename[80];

void load_icon() { // sous programme pour charger les icones
    for (int i = 0; i < NUM_ICONS; i++) {
        sprintf(filename, "../Games/Jackpot/IMAGES/icon%d.bmp",i);
        icons[i] = load_bitmap(filename, NULL);
        if (!icons[i]) { //blindage
            allegro_message("Erreur icone");
            exit(EXIT_FAILURE);
        }
    }
}

void load_slotmachine(char *path) {
    // charger la machine a sous en transparence
    BITMAP *slotmachine = NULL;
    slotmachine = load_bitmap(path, NULL);
    if (!slotmachine) { //blindage
        allegro_message("Erreur image slot machine");
        exit(EXIT_FAILURE);
    }
    set_trans_blender(255, 0, 255, 255);
    drawing_mode(DRAW_MODE_TRANS, NULL, 0, 0);
    draw_trans_sprite(screen, slotmachine, (SCREEN_W - slotmachine->w) / 2, (SCREEN_H - slotmachine->h) / 2);
    destroy_bitmap(slotmachine);
}
void anime(){
    int rand_icon;
    for (int j =0; j<10;j++){
        for ( int i = 0;i<3; i++){
            rand_icon= rand() % NUM_ICONS;
            draw_sprite(screen, icons[rand_icon],  807+ i * (77 + 41+i*i), 525);
        }rest( 80);
    }}
int tourner_roues() {
    // tourner les roues de manière aleatoire
    srand(time(NULL));
    int last_rand = -1;
    // valeure d'icone impossible
    int win = 1;
    int rand_icon;
    for (int i = 0; i < 3; i++) { // 3 car 3 roues
        if(key[KEY_R]){
            rand_icon=2;
        }
        else{
            rand_icon= rand() % NUM_ICONS;
            // choix d'une icone aléatoire
        }

        draw_sprite(screen, icons[rand_icon],  807+ i * (77 + 41+i*i), 525);
        // le calcule de la position NE PAS HESITER A CHANGER CAR JE L'AI TROUVER AU HASARD
        if (last_rand != -1 && last_rand != rand_icon) {
            // detecter la victoire
            win = 0;
        }
        last_rand=rand_icon;
    }
    return win;
}
void Jplayer1(int *s1){
    *s1=0;
    int fin = 0;
    // ici on charge toutes les images
    BITMAP *fond;
    fond= load_bitmap("../Games/Jackpot/IMAGES/fond4.bmp",NULL);
    if (!fond) { //blindage
        allegro_message("Erreur image fond");
        exit(EXIT_FAILURE);
    }
    BITMAP *player1;
    player1= load_bitmap("../Games/Jackpot/IMAGES/player1.bmp",NULL);
    if (!player1) { //blindage
        allegro_message("Erreur image player");
        exit(EXIT_FAILURE);
    }
    draw_sprite(screen,fond,0,0);
    draw_sprite(screen, fond, 0, 0);
    set_trans_blender(255, 0, 255, 255);
    drawing_mode(DRAW_MODE_TRANS, NULL, 0, 0);
    draw_trans_sprite(screen, player1, (SCREEN_W - player1->w) / 2, (SCREEN_H - player1->h) / 2);
    char message[80];
    sprintf(message,"%s a toi de jouer, tu as 5 essais !",joueurs[0].nom);
    textout_centre_ex(screen, font, message, SCREEN_W / 2-60, SCREEN_H /2 +100, makecol(255, 255, 255), -1);
    rest(2500);
    clear(screen);
    draw_sprite(screen,fond,0,0);
    load_slotmachine("../Games/Jackpot/IMAGES/SLOTREELS.bmp");
    load_icon();




    // boucle principale
    while (!key[KEY_ESC] && fin<5 ) {
        if (key[KEY_ENTER]) {
            fin++;
            //anime();
            anime();
            int win = tourner_roues();
            if (win==1) {
                *s1+=1;

                rest(2000);
            }
            rest(300);
        }

    }
    // on libère la memoire
    destroy_bitmap(fond);
    destroy_bitmap(player1);
    for (int i = 0; i < NUM_ICONS; i++) {
        destroy_bitmap(icons[i]);
    }
}

void Jplayer2(int *s2){
    *s2=0;
    int fin = 0;
    // ici on charge toutes les images
    BITMAP *fond;
    fond= load_bitmap("../Games/Jackpot/IMAGES/fond4.bmp",NULL);
    if (!fond) {
        //blindage
        allegro_message("Erreur image fond");
        exit(EXIT_FAILURE);
    }
    BITMAP *player2;
    player2= load_bitmap("../Games/Jackpot/IMAGES/player2.bmp",NULL);
    if (!player2) { //blindage
        allegro_message("Erreur image player");
        exit(EXIT_FAILURE);
    }
    draw_sprite(screen,fond,0,0);
    draw_sprite(screen, fond, 0, 0);
    set_trans_blender(255, 0, 255, 255);
    drawing_mode(DRAW_MODE_TRANS, NULL, 0, 0);
    draw_trans_sprite(screen, player2, (SCREEN_W - player2->w) / 2, (SCREEN_H - player2->h) / 2);
    char message[80];
    sprintf(message,"%s a toi de jouer, tu as 5 essais !",joueurs[1].nom);
    textout_centre_ex(screen, font, message, SCREEN_W / 2-60, SCREEN_H /2 +100, makecol(255, 255, 255), -1);
    rest(2500);
    clear(screen);
    draw_sprite(screen,fond,0,0);
    load_slotmachine("../Games/Jackpot/IMAGES/SLOTREELS.bmp");
    load_icon();

    // boucle principale
    while (!key[KEY_ESC] && fin<5 ) {
        if (key[KEY_ENTER]) {
            fin++;
            //anime();
            anime();
            int win = tourner_roues();
            if (win==1) {
                *s2+=1;
                rest(2000);
            }
            rest(300);
        }

    }
    // on libère la memoire
    destroy_bitmap(fond);
    destroy_bitmap(player2);
    for (int i = 0; i < NUM_ICONS; i++) {
        destroy_bitmap(icons[i]);
    }
}


void jackpot(){
    int s1, s2;

   // SAMPLE * son;
    //son= load_wav("../Games/Jackpot/IMAGES/taverne4.wav");
    //play_sample(son,255,128,1000,1);

    BITMAP* buffer = create_bitmap(SCREEN_W, SCREEN_H);

    BITMAP * r;
    r= load_bitmap("../Games/Jackpot/IMAGES/reglesj.bmp",NULL);
    if (!r) {
        //blindage
        allegro_message("Erreur image fond");
        exit(EXIT_FAILURE);
    }
    BITMAP *fond;
    fond= load_bitmap("../Games/Jackpot/IMAGES/fond4.bmp",NULL);
    if (!fond) {
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


    Jplayer1(&s1);
    Jplayer2(&s2);

    draw_sprite(buffer, fond, 0, 0);
    char message[50];
    char messagefin1[100];
    // on detecte la victoire d'un des deux joueurs et on affiche le résultat
    if (s1>s2){
        sprintf(message,"%s a remporte un Bitcoin",joueurs[0].nom);
        textout_centre_ex(buffer, font, message, SCREEN_W / 2, SCREEN_H /2, makecol(255, 255, 255), -1);
        joueurs[0].nbTickets+=1;
        joueurs[1].nbTickets-=1;
        if (highscore[5].score <= s1) {
            saveMiniGame(joueurs,"Jackpot",s1,0);
            sprintf(messagefin1, "%s vient d'établir un nouveau record ! Enregistrement du meilleur score terminé.",joueurs[0].nom);
            textout_centre_ex(buffer,font, messagefin1, SCREEN_W/2, SCREEN_H / 2 + 20, makecol(255, 255, 255), -1);

        }
    } else if (s1<s2){
        sprintf(message,"%s a remporte un Bitcoin",joueurs[1].nom);
        textout_centre_ex(buffer, font, message, SCREEN_W / 2, SCREEN_H /2, makecol(255, 255, 255), -1);
        joueurs[1].nbTickets+=1;
        joueurs[0].nbTickets-=1;
        if (highscore[4].score <= s2) {
            saveMiniGame(joueurs,"Jackpot",s2,1);
            sprintf(messagefin1, "%s vient d'établir un nouveau record ! Enregistrement du meilleur score terminé.",joueurs[1].nom);
            textout_centre_ex(buffer,font, messagefin1, SCREEN_W/2, SCREEN_H / 2 + 20, makecol(255, 255, 255), -1);

        }
    } else {
        textout_centre_ex(buffer, font, "Personne n'a remporte de Bitcoin", SCREEN_W / 2, SCREEN_H/2, makecol(255, 255, 255), -1);

    }

    loadHighScore(highscore);
    blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
    rest(2000);
    //Attendre 2 secondes avant de quitter
    //stop_sample(son);
    destroy_bitmap(fond);
    destroy_bitmap(buffer);
    destroy_bitmap(r);
    //destroy_sample(son);
}
