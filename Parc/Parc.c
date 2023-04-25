#include "Parc.h"

void parc(){
    BITMAP *buffer;
    BITMAP *pacman[4];
    BITMAP *porte[4];
    BITMAP *fond= load_bitmap("../Parc/image/pacmanmap.bmp",NULL);
    BITMAP *hippodrome= load_bitmap("../Parc/image/hippodrome.bmp",NULL);
    BITMAP *casino= load_bitmap("../Parc/image/hippodrome.bmp",NULL);

    int xcasino= WIDTH/6;
    int ycasino= HEIGHT/6;
    int xhippodrome= WIDTH/4;
    int yhippodrome= HEIGHT/4;

    int posx=0;
    int dx=9;
    int dy=9;
    int xPacman=WIDTH/2;
    int yPacman=HEIGHT/2;
    char nomDeFichier[80];

    int order=0;
    int vx;
    int vy;
    int xporte=WIDTH/2;
    int yporte=HEIGHT*0.9;
    char tabporte[80];
    int end=0;

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
    buffer=create_bitmap(WIDTH,HEIGHT);

    while (!key[KEY_ESC] && end==0) {
        clear_bitmap(buffer);
        clear_to_color(buffer, makecol(255, 255, 255)); // Effacer l'écran en blanc
        // Obtenir les coordonnées de la souris
        stretch_blit(fond,buffer,0,0,fond->w,fond->h,0,0,WIDTH,HEIGHT);

        //collision porte end
        if (xPacman <= (xporte + porte[1]->w) && xporte <= (xPacman + pacman[1]->w) && yPacman <= (yporte + porte[1]->h) && yporte <= (yPacman + pacman[1]->h))
        {
            order++;
            if(order>3)
            {
                end=1;
            }
            // Collision détectée !
            textout_centre_ex(buffer, font, "Collision !", WIDTH/2, HEIGHT/2, makecol(255, 0, 0), -1);
        }

            draw_sprite(buffer,porte[order],xporte,yporte);
        //collision activité hippodrome
        if (xPacman <= (xhippodrome + hippodrome->w) && xhippodrome <= (xPacman + pacman[1]->w) && yPacman <= (yhippodrome + hippodrome->h) && yhippodrome <= (yPacman + pacman[1]->h))
        {
            pari();
            anim_horse();
            // Collision détectée !
            textout_centre_ex(buffer, font, "Collision !", WIDTH/2, HEIGHT/2, makecol(255, 0, 0), -1);
        }

        draw_sprite(buffer,hippodrome,xhippodrome,yhippodrome);

        if (xPacman <= (xcasino + casino->w) && xcasino <= (xPacman + pacman[1]->w) && yPacman <= (ycasino + casino->h) && ycasino <= (yPacman + pacman[1]->h))
        {
            jackpot();
            // Collision détectée !
            textout_centre_ex(buffer, font, "Collision !", WIDTH/2, HEIGHT/2, makecol(255, 0, 0), -1);
        }

        draw_sprite(buffer,casino,xcasino,ycasino);


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
            if(xPacman>WIDTH)
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
            if(yPacman>HEIGHT)
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
        blit(buffer,screen,0,0,0,0,WIDTH,HEIGHT);
        if (key[KEY_SPACE]) {
            rest(50);
        }
        else
            rest(100); // Pause de 10 ms pour rafraîchir l'écran
    }
}