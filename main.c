#include <allegro.h>
#include <string.h>

int main() {
    allegro_init();
    set_color_depth(desktop_color_depth());
    install_keyboard();
    install_mouse();
    if (set_gfx_mode(GFX_AUTODETECT_WINDOWED,800,600,0,0)!=0)// détection et sortie anticipée en cas de problème
    {
        allegro_message("probleme mode graphique");
        allegro_exit();
        exit(EXIT_FAILURE);
    }
    show_mouse(screen);//Affichage de la souris


    while (!key[KEY_ESC]){//Tant que la touche echap n'est pas pressée
        textprintf_ex(screen, font, 10, 10, makecol(255, 255, 255), 0, "X=%d, Y=%d", mouse_x, mouse_y);
        //Affichage des coordonnées de la souris (screen : écran, font : police, x et y : coordonnées, makecol : couleur)
    }
    return 0;
}

END_OF_MAIN();