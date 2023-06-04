#include "allegro.h"


void initialisation_allegro(){
    allegro_init(); // Initialise la bibliothèque Allegro
    install_keyboard(); // Installe les pilotes pour le clavier
    install_mouse(); // Installe les pilotes pour la souris

    install_sound(DIGI_AUTODETECT, MIDI_NONE, NULL); // Installe le système de son
    set_color_depth(desktop_color_depth()); // Règle la profondeur de couleurs sur celle du bureau
    //set_trans_blender(255, 0, 255, 0);
    set_trans_blender(0, 0, 0, 128);
    if (set_gfx_mode(GFX_AUTODETECT_FULLSCREEN,WIDTH,HEIGHT,0,0)!=0){ // Règle le mode graphique sur 800x600 et vérifie s'il fonctionne
        allegro_message("prb gfx mode"); // Affiche un message d'erreur si le mode graphique ne fonctionne pas
        allegro_exit(); // Quitte Allegro
        exit(EXIT_FAILURE); // Quitte le programme avec un code d'erreur
    }
    if (install_sound(DIGI_AUTODETECT, MIDI_AUTODETECT, NULL) != 0) {
        allegro_message("Error initializing sound system: %s\n", allegro_error);
        exit(EXIT_FAILURE);
    }
    if (install_joystick(JOY_TYPE_AUTODETECT) != 0) {
        allegro_message("Échec de l'initialisation de la manette");
        exit(EXIT_FAILURE);
    }
    show_mouse(screen); // Affiche le curseur de la souris à l'écran
}