#include "allegro.h"

void initialisation_allegro(){
    allegro_init(); // Initialise la bibliothèque Allegro
    install_keyboard(); // Installe les pilotes pour le clavier
    install_mouse(); // Installe les pilotes pour la souris
    set_color_depth(desktop_color_depth()); // Règle la profondeur de couleurs sur celle du bureau
    if (set_gfx_mode(GFX_AUTODETECT_FULLSCREEN,WIDTH,HEIGHT,0,0)!=0){ // Règle le mode graphique sur 800x600 et vérifie s'il fonctionne
        allegro_message("prb gfx mode"); // Affiche un message d'erreur si le mode graphique ne fonctionne pas
        allegro_exit(); // Quitte Allegro
        exit(EXIT_FAILURE); // Quitte le programme avec un code d'erreur
    }
    show_mouse(screen); // Affiche le curseur de la souris à l'écran
}