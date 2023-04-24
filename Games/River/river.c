#include "river.h"
void turtle()
{
    allegro_init();
    install_keyboard();
//Chargement des images
    BITMAP *buffer = create_bitmap(SCREEN_W, SCREEN_H);
    clear_bitmap(buffer);
    BITMAP *background=load_bitmap("../Games/River/image/backgroundv1.bmp",NULL);
    if (!background) {
        allegro_message("Erreur lors du chargement de l'image d'arrière-plan !");
    }

    set_color_depth(desktop_color_depth());
    set_gfx_mode(GFX_AUTODETECT_WINDOWED, SCREEN_W, SCREEN_H, 0, 0);
    set_window_title("-~Turtle River~-");




    while (!key[KEY_ESC]) {
        clear_bitmap(buffer);
        clear_to_color(buffer, makecol(255, 255, 255)); // Effacer l'écran en blanc
        blit(background, buffer, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
        // Codé la toortoo isi
        vsync();
        blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
    }


    destroy_bitmap(buffer);
    destroy_bitmap(background);
    allegro_exit();
}
