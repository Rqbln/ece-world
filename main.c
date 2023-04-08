#include <allegro.h>
#include "stdio.h"

typedef struct strpacman
{
    int x,y;
    int tx,ty;
    int dx,dy;

}strpacman;

int main()
{
    allegro_init();
    install_keyboard();
    install_mouse();
    set_color_depth(desktop_color_depth());
    if( set_gfx_mode(GFX_AUTODETECT_WINDOWED, 640, 480, 0, 0)!=0)
    {
        allegro_message("prblm gfx");
        allegro_exit();
        exit(EXIT_FAILURE);
    }
    BITMAP *buffer;
    BITMAP *pacman[4];
    BITMAP *nude[6];
    BITMAP *fond= load_bitmap("../image/pacmanmap.bmp",NULL);

    int posx=0;
    int dx=9;
    int dy=9;
    int xPacman=SCREEN_W/2;
    int yPacman=SCREEN_W/2;
    char nomDeFichier[80];

    int order;
    int vx;
    int vy;
    int xNude=SCREEN_W/2;
    int yNude=SCREEN_W/2;
    char tabNude[80];

    for(int j=0;j<5;j++)
    {
        sprintf(tabNude,"../image/nude%d.bmp",j);
        nude[j]= load_bitmap(tabNude,NULL);
        if(!nude[j])
        {
            allegro_message("../image/nude%d.bmp",j);
            exit(EXIT_FAILURE);
        }

    }

    for(int i=0;i<3;i++)
    {
        sprintf(nomDeFichier,"../image/pacman%d.bmp",i);
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
        if (xPacman <= (xNude + nude[1]->w) && xNude <= (xPacman + pacman[1]->w) && yPacman <= (yNude + nude[1]->h) && yNude <= (yPacman + pacman[1]->h))
        {
            // Collision détectée !
            textout_centre_ex(buffer, font, "Collision !", SCREEN_W/2, SCREEN_H/2, makecol(255, 0, 0), -1);
        }
        if (key[KEY_ALT]){
            order++;
            if(order>4)
            {
                order=0;
            }
            draw_sprite(buffer,nude[order],xNude,yNude);

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

    allegro_exit();
    return 0;
}
END_OF_MAIN()