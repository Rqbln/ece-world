#include "guitar_hero.h"
void playguitar(){
    rest(200); // Pause de 10 ms pour rafraîchir l'écran
    BITMAP *buffer;
    BITMAP *note= load_bitmap("../Games/Guitar_hero/image/bille0.bmp",NULL);;
    BITMAP *arriver= load_bitmap("../Games/Guitar_hero/image/gratte.bmp",NULL);
    BITMAP *fond= load_bitmap("../Games/Guitar_hero/image/fondguitar3.bmp",NULL);
    SAMPLE *musique= load_sample("../Games/Guitar_hero/image/musique0.wav");
    //FONT *police = load_font("arial.pcx", NULL, NULL);
    //set_trans_blender(0, 0, 0, 128);
    if (!musique) {
        allegro_message("Erreur : impossible de charger la musique");
        allegro_exit();
        exit(EXIT_FAILURE);
    }
    int nbnote = 4*bat;
    int xnote[nbnote];
    int ynote[nbnote];
    int nombreAleatoire=20;
    int memo=20;
    char message[50];
    int score=0;
    int vitesse=70;
// Joue la musique en boucle
//play_sample(musique, 255, 128, 100, 1);
    // Initialisation de la fonction rand() avec la fonction srand()
    srand(time(NULL));

    for (int j = 0; j < bat; ++j) {
        for(int i=0;i<nbnote/bat;i++){
            xnote[i+j*(nbnote/bat)]=i*155+WIDTH*0.34;
            ynote[i+j*(nbnote/bat)]=j*(-200*(i+1));
        }
    }
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

    while (!key[KEY_ESC] && memo ==20) {
        clear_bitmap(buffer);
        clear_to_color(buffer, makecol(255, 255, 255)); // Effacer l'écran en blanc
        //play_sample(musique, 255, 128, 100, 1);
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
        //sprintf(message,"Perdu enculé",memo+1);
        textout_centre_ex(buffer, font, message, WIDTH / 2, HEIGHT / 2, makecol(255, 0, 0), -5);
        blit(buffer,screen,0,0,0,0,WIDTH,HEIGHT);
        rest(100); // Pause de 10 ms pour rafraîchir l'écran
        // Libère la mémoire utilisée par la musique
        destroy_sample(musique);
        destroy_bitmap(buffer);
        destroy_bitmap(note);
        destroy_bitmap(arriver);
        destroy_bitmap(fond);
    }
}