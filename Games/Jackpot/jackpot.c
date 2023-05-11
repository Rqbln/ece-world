// MACHINE A SOUS LOLA LE GALL

#include "jackpot.h"


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

void load_slotmachine(char *path) { // charger la machine a sous en transparence
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
    for (int j;j<4;j++){
    for ( int i = 0;i<3; i++){
    draw_sprite(screen, icons[i],  807+ i * (77 + 41+i*i), 525);
    rest( 100);}}
}
int tourner_roues() {// tourner les roues de manière aleatoire
    srand(time(NULL));
    int last_rand = -1; // valeure d'icone impossible
    int win = 1;
    int rand_icon;
    for (int i = 0; i < 3; i++) { // 3 car 3 roues
        if(key[KEY_R]){
            rand_icon=2;
        }
        else{
            rand_icon= rand() % NUM_ICONS; // choix d'une icone aléatoire
        }

        draw_sprite(screen, icons[rand_icon],  807+ i * (77 + 41+i*i), 525);// le calcule de la position NE PAS HESITER A CHANGER CAR JE L'AI TROUVER AU HASARD
        if (last_rand != -1 && last_rand != rand_icon) { // detecter la victoire
            win = 0;
        }
        last_rand=rand_icon;
    }
    return win;
}

void jackpot(){

    BITMAP* buffer = create_bitmap(SCREEN_W, SCREEN_H);
    int fin = 0;
    // ici on charge toutes les images
    BITMAP *fond;
    fond= load_bitmap("../Games/Jackpot/IMAGES/fond3.bmp",NULL);
    if (!fond) { //blindage
        allegro_message("Erreur image fond");
        exit(EXIT_FAILURE);
    }
    draw_sprite(screen,fond,0,0);
    load_slotmachine("../Games/Jackpot/IMAGES/SLOTREELS.bmp");
    load_icon();

    // boucle principale
    while (!key[KEY_ESC] && fin==0 ) {
        if (key[KEY_ENTER]) {
            anime();
            int win = tourner_roues();
            if (win==1) {
                BITMAP *plus1 = NULL;
                plus1 = load_bitmap("../Games/Jackpot/IMAGES/plus1.bmp", NULL);
                if (!plus1) { //blindage
                    allegro_message("Erreur image slot machine");
                    exit(EXIT_FAILURE);
                }
                set_trans_blender(255, 0, 255, 255);
                drawing_mode(DRAW_MODE_TRANS, NULL, 0, 0);
                int target_y = 200;
                int speed = 5;
                int deb_y = SCREEN_H-180;

                while(deb_y  < target_y) {
                    clear_bitmap(buffer);
                    draw_trans_sprite(buffer, plus1, SCREEN_W-180, deb_y );
                    deb_y  -= speed;
                }
                destroy_bitmap(plus1);
                rest(2000);
                fin=1;
            }
            rest(100);
        }

        rest(10);
    }
    // on libère la memoire
    destroy_bitmap(fond);
    for (int i = 0; i < NUM_ICONS; i++) {
        destroy_bitmap(icons[i]);
    }

}
