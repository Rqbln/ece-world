#include "Parc.h"

void parc(){
    BITMAP *buffer;
    BITMAP *pacman[4];
    BITMAP *porte[4];
    BITMAP *fond= load_bitmap("../Parc/image/pacmanmap.bmp",NULL);

    int posx=0;
    int dx=9;
    int dy=9;
    int xPacman=SCREEN_W/2;
    int yPacman=SCREEN_W/2;
    char nomDeFichier[80];

    int order;
    int vx;
    int vy;
    int xporte=SCREEN_W/2;
    int yporte=SCREEN_W/2;
    char tabporte[80];

    for(int j=0;j<4;j++)
    {
        sprintf(tabporte,"../Parc/image/portEnd%d.bmp",j);
        porte[j]= load_bitmap(tabporte,NULL);
        if(!porte[j])
        {
            allegro_message("../image/portEnd%d.bmp",j);
            exit(EXIT_FAILURE);
        }

    }

    for(int i=0;i<3;i++)
    {
        sprintf(nomDeFichier,"../Parc/image/pacman%d.bmp",i);
        pacman[i]= load_bitmap(nomDeFichier,NULL);
        if(!pacman[i])
        {
            allegro_message("../image/pacman%d.bmp",i);
            exit(EXIT_FAILURE);
        }
    }

    if(!fond)
    {
        allegro_message("pas trouver /image/pacmanmap.bmp ");
        allegro_exit();
        exit(EXIT_FAILURE);
    }
    buffer=create_bitmap(SCREEN_W,SCREEN_H);

    while (!key[KEY_ESC]) {
        clear_bitmap(buffer);
        clear_to_color(buffer, makecol(255, 255, 255)); // Effacer l'écran en blanc
        // Obtenir les coordonnées de la souris
        stretch_blit(fond,buffer,0,0,fond->w,fond->h,0,0,SCREEN_W,SCREEN_H);
        int x=mouse_x;
        int y=mouse_y;

        // Afficher les coordonnées de la souris
        textprintf_ex(buffer, font, 10, 10, makecol(0, 0, 0), -1, "Coordonnées de la souris : (%d,%d)", x, y);
        if (xPacman <= (xporte + porte[1]->w) && xporte <= (xPacman + pacman[1]->w) && yPacman <= (yporte + porte[1]->h) && yporte <= (yPacman + pacman[1]->h))
        {
            // Collision détectée !
            textout_centre_ex(buffer, font, "Collision !", SCREEN_W/2, SCREEN_H/2, makecol(255, 0, 0), -1);
        }
        if (key[KEY_ALT]){
            order++;
            if(order>3)
            {
                order=0;
            }
            draw_sprite(buffer,porte[order],xporte,yporte);

        }
        if (key[KEY_RIGHT]){
            posx++;
            xPacman=xPacman+dx;
            if(xPacman<0)
            {
                xPacman=0;
            }
            if(posx>2)
            {
                posx=0;
            }
            draw_sprite(buffer,pacman[posx],xPacman,yPacman);
        }
        else if (key[KEY_LEFT]){
            posx++;
            xPacman=xPacman-dx;
            if(xPacman>SCREEN_W)
            {
                xPacman=0;
            }
            if(posx>2)
            {
                posx=0;
            }
            draw_sprite_h_flip(buffer,pacman[posx],xPacman,yPacman);

        }
        else if (key[KEY_UP]){
            posx++;
            yPacman=yPacman-dy;
            if(xPacman<0)
            {
                xPacman=0;
            }
            if(posx>2)
            {
                posx=0;
            }
            draw_sprite_h_flip(buffer,pacman[posx],xPacman,yPacman);

        }
        else if (key[KEY_DOWN]){
            posx++;
            yPacman=yPacman+dy;
            if(yPacman>SCREEN_H)
            {
                xPacman=0;
            }
            if(posx>2)
            {
                posx=0;
            }
            draw_sprite_h_flip(buffer,pacman[posx],xPacman,yPacman);

        }
        else
        {
            draw_sprite(buffer,pacman[0],xPacman,yPacman);
        }

        // Dessiner un cercle à la position de la souris si la touche espace est appuyée

        blit(buffer,screen,0,0,0,0,SCREEN_W,SCREEN_H);
        if (key[KEY_SPACE]) {
            rest(50);
        }
        else
            rest(100); // Pause de 10 ms pour rafraîchir l'écran
    }
}