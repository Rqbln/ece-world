#include "guitar_hero.h"
void playguitar1(){
    rest(200); // Pause de 10 ms pour rafraîchir l'écran
    BITMAP *buffer;
    BITMAP *note= load_bitmap("../Games/Guitar_hero/image/bille0.bmp",NULL);;
    BITMAP *arriver= load_bitmap("../Games/Guitar_hero/image/gratte.bmp",NULL);
    BITMAP *fond= load_bitmap("../Games/Guitar_hero/image/fondguitar3.bmp",NULL);
    SAMPLE *musique= load_sample("../Games/Guitar_hero/image/musique0.wav");
    FONT *police = load_font("arial.pcx", NULL, NULL);
    set_trans_blender(0, 0, 0, 128);
    if (!musique) {
        allegro_message("Erreur : impossible de charger la musique");
        allegro_exit();
        exit(EXIT_FAILURE);
    }
    play_sample(musique, 255, 128, 1000, 1);

    int nbnote = 4*bat;
    int xnote[nbnote];
    int ynote[nbnote];
    int nombreAleatoire=20;
    int memo;
    char message[50];
    int score;
    int vitesse;
    int nbjoueur=2;
    int joueurscore[nbjoueur];
// Joue la musique en boucle
//play_sample(musique, 255, 128, 100, 1);
    // Initialisation de la fonction rand() avec la fonction srand()
    srand(time(NULL));
    if(!arriver){
        allegro_message("../image/arriver.bmp");
        exit(EXIT_FAILURE);
    }
    if(!note){
        allegro_message("../image/note.bmp");
        exit(EXIT_FAILURE);
    }
    if(!fond){
        allegro_message("../image/fondguitar0.bmp ");
        allegro_exit();
        exit(EXIT_FAILURE);
    }
    buffer=create_bitmap(WIDTH,HEIGHT);

    for (int tour = 0; tour < nbjoueur; ++tour) {
        memo=0;
        for (int j = 0; j < bat; ++j) {
            for(int i=0;i<nbnote/bat;i++){
                xnote[i+j*(nbnote/bat)]=i*155+WIDTH*0.34;
                ynote[i+j*(nbnote/bat)]=j*(-200*(i+1));
            }
        }
        vitesse=70;
        score=0;
        rest(150); // Pause de 10 ms pour rafraîchir l'écran
        while (!key[KEY_ESC] && memo ==0) {
            clear_bitmap(buffer);
            clear_to_color(buffer, makecol(255, 255, 255)); // Effacer l'écran en blanc
            // Obtenir les coordonnées de la souris
            stretch_blit(fond,buffer,0,0,fond->w,fond->h,0,0,WIDTH,HEIGHT);
            int x=mouse_x;
            int y=mouse_y;
            draw_sprite(buffer,arriver,(x - ((arriver->w)/2)),(y - ((arriver->h)/2)));
            for (int i=0; i<nbnote; i++){
                // Génération d'un nombre aléatoire compris entre 8 et 20
                //nombreAleatoire = 8+rand() % 20;
                ynote[i]+=nombreAleatoire;
                if (xnote[i] <= (x) && (x) <= (xnote[i] + note->w) && ynote[i] <= (y) && (y) <= (ynote[i] + note->h)){
                    ynote[i]=-200;
                    score+=1;
                    vitesse-=1;
                    // Collision détectée !
                }
                //textprintf_ex(buffer, font, 50, 50, makecol(255, 255, 255), -1, "score: %d", score);

                draw_sprite(buffer,note,xnote[i],ynote[i]);
                if (ynote[i] >= HEIGHT ){
                    memo=1;
                    // Collision détectée !
                }
            }
            textprintf_ex(buffer, font, 10, 10, makecol(255, 255, 255), -1, "score: %d", score);
            blit(buffer,screen,0,0,0,0,WIDTH,HEIGHT);
            rest(vitesse); // Pause de 10 ms pour rafraîchir l'écran
        }
        while (!key[KEY_ESC]) {
            stop_sample(musique);
            sprintf(message,"Perdu enculé");
            joueurscore[tour] = score;
            textout_centre_ex(buffer, font, message, WIDTH / 2, HEIGHT / 2, makecol(255, 0, 0), -1);
            blit(buffer,screen,0,0,0,0,WIDTH,HEIGHT);
            rest(100); // Pause de 10 ms pour rafraîchir l'écran
        }

    }
    rest(150); // Pause de 10 ms pour rafraîchir l'écran
    clear_bitmap(buffer);
    clear_to_color(buffer, makecol(255, 255, 255)); // Effacer l'écran en blanc
    while (!key[KEY_ESC]) {
        if (joueurscore[0]<joueurscore[1]){
            sprintf(message,"joueur 2 a gagné 1 ticket");
        }
        else {
            sprintf(message,"joueur 1 a gagné 1 ticket");
        }
        textout_centre_ex(buffer, font, message, WIDTH / 2, HEIGHT / 2, makecol(255, 0, 0), -1);
        blit(buffer,screen,0,0,0,0,WIDTH,HEIGHT);
        rest(100); // Pause de 10 ms pour rafraîchir l'écran
    }
    rest(150); // Pause de 10 ms pour rafraîchir l'écran
}
void playguitar(){
    rest(200); // Pause de 10 ms pour rafraîchir l'écran
    BITMAP *buffer;
    BITMAP *note= load_bitmap("../Games/Guitar_hero/image/bille0.bmp",NULL);;
    BITMAP *arriver= load_bitmap("../Games/Guitar_hero/image/gratte.bmp",NULL);
    BITMAP *fond= load_bitmap("../Games/Guitar_hero/image/fondguitar3.bmp",NULL);
    SAMPLE *musique= load_sample("../Games/Guitar_hero/image/musique0.wav");
    FONT *police = load_font("arial.pcx", NULL, NULL);
    set_trans_blender(0, 0, 0, 128);
    if (!musique) {
        allegro_message("Erreur : impossible de charger la musique");
        allegro_exit();
        exit(EXIT_FAILURE);
    }
    play_sample(musique, 255, 128, 1000, 1);

    int nbnote = 4*bat;
    int xnote[nbnote];
    int ynote[nbnote];
    int nombreAleatoire=20;
    int memo;
    char message[50];
    int score;
    int vitesse;
    int nbjoueur=2;
    int joueurscore[nbjoueur];
    int note1=0*155+WIDTH*0.34;
    int note2=1*155+WIDTH*0.34;
    int note3=2*155+WIDTH*0.34;
    int note4=3*155+WIDTH*0.34;
    int notey=HEIGHT/1.5;

    int time[4];
    int ok[4];
    ok[0]=0;
    ok[1]=0;
    ok[2]=0;
    ok[3]=0;
    
// Joue la musique en boucle
//play_sample(musique, 255, 128, 100, 1);
    // Initialisation de la fonction rand() avec la fonction srand()
    //srand(time(NULL));
    if(!arriver){
        allegro_message("../image/arriver.bmp");
        exit(EXIT_FAILURE);
    }
    if(!note){
        allegro_message("../image/note.bmp");
        exit(EXIT_FAILURE);
    }
    if(!fond){
        allegro_message("../image/fondguitar0.bmp ");
        allegro_exit();
        exit(EXIT_FAILURE);
    }
    buffer=create_bitmap(WIDTH,HEIGHT);

    for (int tour = 0; tour < nbjoueur; ++tour) {
        memo=0;
        for (int j = 0; j < bat; ++j) {
            for(int i=0;i<nbnote/bat;i++){
                xnote[i+j*(nbnote/bat)]=i*155+WIDTH*0.34;
                ynote[i+j*(nbnote/bat)]=j*(-200*(i+1));
            }
        }
        vitesse=120;
        score=0;
        rest(150); // Pause de 10 ms pour rafraîchir l'écran
        while (!key[KEY_ESC] && memo ==0) {
            clear_bitmap(buffer);
            clear_to_color(buffer, makecol(255, 255, 255)); // Effacer l'écran en blanc
            // Obtenir les coordonnées de la souris
            stretch_blit(fond,buffer,0,0,fond->w,fond->h,0,0,WIDTH,HEIGHT);
            //int x=mouse_x;
            //int y=mouse_y;
            //draw_sprite(buffer,arriver,(x - ((arriver->w)/2)),(y - ((arriver->h)/2)));
            for (int i=0; i<nbnote; i++){
                // Génération d'un nombre aléatoire compris entre 8 et 20
                //nombreAleatoire = 8+rand() % 20;
                ynote[i]+=nombreAleatoire;
                if(keypressed()){
                    if(key[KEY_S]){
                        if (xnote[i] <= (note1 + note->w) && (note1) <= (xnote[i] + note->w) && ynote[i] <= (notey) && (notey) <= (ynote[i] + note->h)){
                            ynote[i]=-200;
                            score+=1;
                            vitesse-=1;
                            // Collision détectée !
                        }
                        else{
                        }
                    }
                    if(key[KEY_D]){
                        if (xnote[i] <= (note2 + note->w) && (note2) <= (xnote[i] + note->w) && ynote[i] <= (notey + note->h) && (notey) <= (ynote[i] + note->h)){
                            ynote[i]=-200;
                            score+=1;
                            vitesse-=1;
                            // Collision détectée !
                        }
                        else{
                        }
                    }

                    if(key[KEY_F]){
                        if (xnote[i] <= (note3 + note->w) && (note3) <= (xnote[i] + note->w) && ynote[i] <= (notey + note->h) && (notey) <= (ynote[i] + note->h)){
                            ynote[i]=-200;
                            score+=1;
                            vitesse-=1;
                            // Collision détectée !
                        }
                        else{
                        }
                    }
                    if(key[KEY_G]){
                        if (xnote[i] <= (note4 + note->w) && (note4) <= (xnote[i] + note->w) && ynote[i] <= (notey + note->h) && (notey) <= (ynote[i] + note->h)){
                            ynote[i]=-200;
                            score+=1;
                            vitesse-=1;
                            // Collision détectée !
                        }
                        else{
                        }
                    }
                }

                //textprintf_ex(buffer, font, 50, 50, makecol(255, 255, 255), -1, "score: %d", score);

                draw_sprite(buffer,note,xnote[i],ynote[i]);
                draw_sprite(buffer,note,note1,notey);
                draw_sprite(buffer,note,note2,notey);
                draw_sprite(buffer,note,note3,notey);
                draw_sprite(buffer,note,note4,notey);

                if (ynote[i] >= HEIGHT ){
                    memo=1;
                    // Collision détectée !
                }
            }
            textprintf_ex(buffer, font, 10, 10, makecol(255, 255, 255), -1, "score: %d", score);
            blit(buffer,screen,0,0,0,0,WIDTH,HEIGHT);
            rest(vitesse); // Pause de 10 ms pour rafraîchir l'écran
        }
        while (!key[KEY_ESC]) {
            stop_sample(musique);
            sprintf(message,"Perdu enculé");
            joueurscore[tour] = score;
            textout_centre_ex(buffer, font, message, WIDTH / 2, HEIGHT / 2, makecol(255, 0, 0), -1);
            blit(buffer,screen,0,0,0,0,WIDTH,HEIGHT);
            rest(100); // Pause de 10 ms pour rafraîchir l'écran
        }
    }
    rest(150); // Pause de 10 ms pour rafraîchir l'écran
    clear_bitmap(buffer);
    clear_to_color(buffer, makecol(255, 255, 255)); // Effacer l'écran en blanc
    while (!key[KEY_ESC]) {
        if (joueurscore[0]<joueurscore[1]){
            sprintf(message,"joueur 2 a gagné 1 ticket");
        }
        else {
            sprintf(message,"joueur 1 a gagné 1 ticket");
        }
        textout_centre_ex(buffer, font, message, WIDTH / 2, HEIGHT / 2, makecol(255, 0, 0), -1);
        blit(buffer,screen,0,0,0,0,WIDTH,HEIGHT);
        rest(100); // Pause de 10 ms pour rafraîchir l'écran
    }
    rest(150); // Pause de 10 ms pour rafraîchir l'écran
}