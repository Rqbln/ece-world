#include "Parc.h"
void attraction(){

}

void parc(){
    BITMAP *buffer;
    BITMAP *pacman[4];
    BITMAP *porte[4];
    BITMAP *fond= load_bitmap("../Parc/image/pacmanmap.bmp",NULL);
    BITMAP *hippodrome= load_bitmap("../Parc/image/hippodrome1.bmp",NULL);
    BITMAP *casino= load_bitmap("../Parc/image/casino0.bmp",NULL);
    BITMAP *river= load_bitmap("../Parc/image/river0.bmp",NULL);
    BITMAP *serpent= load_bitmap("../Parc/image/river0.bmp",NULL);
    BITMAP *fondmap= load_bitmap("../Parc/image/fondmap0.bmp",NULL);
    int xserpent= 0;
    int yserpent= HEIGHT*0.8;
    int xriver= WIDTH*0.8;
    int yriver= 0;
    int xcasino= WIDTH*0.8;
    int ycasino= HEIGHT*0.8;
    int xhippodrome= 0;
    int yhippodrome= 0;

    int posx=0;
    int dx=15;
    int dy=15;
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
            xPacman=WIDTH/2;
            yPacman=HEIGHT/2;
            // Collision détectée !
            textout_centre_ex(buffer, font, "Collision !", WIDTH/2, HEIGHT/2, makecol(255, 0, 0), -1);
        }

        draw_sprite(buffer,hippodrome,xhippodrome,yhippodrome);

        if (xPacman <= (xcasino + casino->w) && xcasino <= (xPacman + pacman[1]->w) && yPacman <= (ycasino + casino->h) && ycasino <= (yPacman + pacman[1]->h))
        {
            jackpot();
            xPacman=WIDTH/2;
            yPacman=HEIGHT/2;
            // Collision détectée !
            textout_centre_ex(buffer, font, "Collision !", WIDTH/2, HEIGHT/2, makecol(255, 0, 0), -1);
        }

        draw_sprite(buffer,casino,xcasino,ycasino);

        if (xPacman <= (xriver + river->w) && xriver <= (xPacman + pacman[1]->w) && yPacman <= (yriver + river->h) && yriver <= (yPacman + pacman[1]->h))
        {
            playguitar();
            xPacman=WIDTH/2;
            yPacman=HEIGHT/2;
            // Collision détectée !
            textout_centre_ex(buffer, font, "Collision !", WIDTH/2, HEIGHT/2, makecol(255, 0, 0), -1);
        }

        draw_sprite(buffer,river,xriver,yriver);

        if (xPacman <= (xserpent + serpent->w) && xserpent <= (xPacman + pacman[1]->w) && yPacman <= (yserpent + serpent->h) && yserpent <= (yPacman + pacman[1]->h))
        {
            snake();
            xPacman=WIDTH/2;
            yPacman=HEIGHT/2;
            // Collision détectée !
            textout_centre_ex(buffer, font, "Collision !", WIDTH/2, HEIGHT/2, makecol(255, 0, 0), -1);
        }

        draw_sprite(buffer,serpent,xserpent,yserpent);


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

void parc2(){
    BITMAP *buffer;
    BITMAP *pacman[4];
    BITMAP *porte[4];
    BITMAP *fond= load_bitmap("../Parc/image/fondplage1.bmp",NULL);
    BITMAP *fondmap= load_bitmap("../Parc/image/mapfond2.bmp",NULL);

    BITMAP *hippodrome= load_bitmap("../Parc/image/hippodrome1.bmp",NULL);  //image des attractions/mini-jeux
    BITMAP *guitar= load_bitmap("../Parc/image/concert2.bmp",NULL);
    BITMAP *casino= load_bitmap("../Parc/image/casino0.bmp",NULL);
    BITMAP *river= load_bitmap("../Parc/image/lac0.bmp",NULL);
    BITMAP *serpent= load_bitmap("../Parc/image/river0.bmp",NULL);
    BITMAP *tirballon= load_bitmap("../Parc/image/futuroscope0.bmp",NULL);
    BITMAP *labyrinthe= load_bitmap("../Parc/image/labyrinthe0.bmp",NULL);
    BITMAP *taupe= load_bitmap("../Parc/image/cirque0.bmp",NULL);
    BITMAP *canard= load_bitmap("../Parc/image/parc0.bmp",NULL);

    int ximgfond = -4200+WIDTH;  //coordonnée de l image de fond
    int yimgfond= -2700 +HEIGHT;

    int xserpent= ximgfond+1700; //coordonnée des mini-jeux (ximgfond + coordonnée paint)
    int yserpent= yimgfond+950;
    int xguitar= ximgfond+2260;
    int yguitar= yimgfond+510;
    int xriver= ximgfond+2310;
    int yriver= yimgfond+2020;
    int xcasino= ximgfond+1960;
    int ycasino= yimgfond+1420;
    int xhippodrome= ximgfond+2500;
    int yhippodrome= yimgfond+1300;
    int xtir= ximgfond+2000;
    int ytir= yimgfond+1510;
    int xlabyrinthe= ximgfond+1400;
    int ylabyrinthe= yimgfond+1010;
    int xtaupe= ximgfond+1000;
    int ytaupe= yimgfond+1510;
    int xcanard= ximgfond+1940;
    int ycanard= yimgfond+2100;

    int xporte=ximgfond+1700;
    int yporte=yimgfond+950;
    int xPacman=WIDTH/2;
    int yPacman=HEIGHT/2;

    int posx=0; //position des sprite du personnage
    int dx=15;//vitesse
    int dy=8;
    int xcenter;//centre du personnage
    int ycenter;
    int order=0;//position des sprite de la porte
    int r = 0, v = 0, b = 255; //couleur RGB
    int end=0;//condition de fin
    char tabporte[80];//tableau nom d image
    char nomDeFichier[80];
    //Verifie si les image sont bien la
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
    buffer=create_bitmap(WIDTH,HEIGHT);

    while (!key[KEY_ESC] && end==0) {  //boucle principale
        xcenter = pacman[1]->w / 2;
        ycenter = pacman[1]->w / 2;
        draw_sprite(buffer,fond,ximgfond,yimgfond);
        int pixel_color = getpixel(screen, xcenter, ycenter);
        int pixel_r = getr(pixel_color);
        int pixel_v = getg(pixel_color);
        int pixel_b = getb(pixel_color);
        //if (pixel_r >= r - 50 && pixel_r <= r + 50 && pixel_v >= v - 50 && pixel_v <= v + 50 && pixel_b >= b - 50 && pixel_b <= b + 50) {
        /*if (getpixel(buffer, xcenter, ycenter) == makecol(0, 0, 255)) {
            dx=5;
            dy=2;
        }
        else{
            dx=15;
            dy=8;
        }*/

        clear_bitmap(buffer);
        clear_to_color(buffer, makecol(255, 255, 255)); // Effacer l'écran en blanc
        // Obtenir les coordonnées de la souris
        //draw_sprite(buffer,fond,ximgfond,yimgfond);
        //stretch_blit(fond,buffer,0,0,fond->w,fond->h,0,0,WIDTH,HEIGHT);
        //image de fond qui bouge
        draw_sprite(buffer,fondmap,ximgfond,yimgfond);
        textprintf_ex(buffer, font, 10, 10, makecol(255, 255, 255), -1, "score: %d", pixel_r);
        draw_sprite(buffer,porte[order],xporte,yporte);
        draw_sprite(buffer,hippodrome,xhippodrome,yhippodrome);
        draw_sprite(buffer,tirballon,xtir,ytir);
        draw_sprite(buffer,labyrinthe,xlabyrinthe,ylabyrinthe);
        draw_sprite(buffer,canard,xcanard,ycanard);
        draw_sprite(buffer,taupe,xtaupe,ytaupe);
        draw_sprite(buffer,guitar,xguitar,yguitar);
        draw_sprite(buffer,casino,xcasino,ycasino);
        draw_sprite(buffer,river,xriver,yriver);
        draw_sprite(buffer,serpent,xserpent,yserpent);

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

       // draw_sprite(buffer,porte[order],xporte,yporte);
        //collision activité hippodrome
        if (xPacman <= (xhippodrome + hippodrome->w) && xhippodrome <= (xPacman + pacman[1]->w) && yPacman <= (yhippodrome + hippodrome->h) && (yhippodrome +hippodrome->h) <= (yPacman + pacman[1]->h))
        {
            pari();
            anim_horse();
            yguitar-= pacman[1]->h;
            yserpent-= pacman[1]->h;
            yriver-= pacman[1]->h;
            ycasino-= pacman[1]->h;
            yhippodrome-= pacman[1]->h;
            yporte-= pacman[1]->h;
            yimgfond-= pacman[1]->h;
            ytir-= pacman[1]->h;
            ylabyrinthe-= pacman[1]->h;
            ytaupe-= pacman[1]->h;
            ycanard-= pacman[1]->h;
            // Collision détectée !
            textout_centre_ex(buffer, font, "Collision !", WIDTH/2, HEIGHT/2, makecol(255, 0, 0), -1);
        }

        //draw_sprite(buffer,hippodrome,xhippodrome,yhippodrome);
        if (xPacman <= (xtir + tirballon->w) && xtir <= (xPacman + pacman[1]->w) && yPacman <= (ytir + tirballon->h) && (ytir +tirballon->h) <= (yPacman + pacman[1]->h))
        {
            pari();
            anim_horse();
            yguitar-= pacman[1]->h;
            yserpent-= pacman[1]->h;
            yriver-= pacman[1]->h;
            ycasino-= pacman[1]->h;
            yhippodrome-= pacman[1]->h;
            yporte-= pacman[1]->h;
            yimgfond-= pacman[1]->h;
            ytir-= pacman[1]->h;
            ylabyrinthe-= pacman[1]->h;
            ytaupe-= pacman[1]->h;
            ycanard-= pacman[1]->h;
            // Collision détectée !
            textout_centre_ex(buffer, font, "Collision !", WIDTH/2, HEIGHT/2, makecol(255, 0, 0), -1);
        }

        //draw_sprite(buffer,tirballon,xtir,ytir);
        if (xPacman <= (xlabyrinthe + labyrinthe->w) && xlabyrinthe <= (xPacman + pacman[1]->w) && yPacman <= (ylabyrinthe + labyrinthe->h) && (ylabyrinthe +labyrinthe->h) <= (yPacman + pacman[1]->h))
        {
            pari();
            anim_horse();
            yguitar-= pacman[1]->h;
            yserpent-= pacman[1]->h;
            yriver-= pacman[1]->h;
            ycasino-= pacman[1]->h;
            yhippodrome-= pacman[1]->h;
            yporte-= pacman[1]->h;
            yimgfond-= pacman[1]->h;
            ytir-= pacman[1]->h;
            ylabyrinthe-= pacman[1]->h;
            ytaupe-= pacman[1]->h;
            ycanard-= pacman[1]->h;
            // Collision détectée !
            textout_centre_ex(buffer, font, "Collision !", WIDTH/2, HEIGHT/2, makecol(255, 0, 0), -1);
        }

        //draw_sprite(buffer,labyrinthe,xlabyrinthe,ylabyrinthe);
        if (xPacman <= (xcanard + canard->w) && xcanard <= (xPacman + pacman[1]->w) && yPacman <= (ycanard + canard->h) && (ycanard +canard->h) <= (yPacman + pacman[1]->h))
        {
            pari();
            anim_horse();
            yguitar-= pacman[1]->h;
            yserpent-= pacman[1]->h;
            yriver-= pacman[1]->h;
            ycasino-= pacman[1]->h;
            yhippodrome-= pacman[1]->h;
            yporte-= pacman[1]->h;
            yimgfond-= pacman[1]->h;
            ytir-= pacman[1]->h;
            ylabyrinthe-= pacman[1]->h;
            ytaupe-= pacman[1]->h;
            ycanard-= pacman[1]->h;
            // Collision détectée !
            textout_centre_ex(buffer, font, "Collision !", WIDTH/2, HEIGHT/2, makecol(255, 0, 0), -1);
        }

        //draw_sprite(buffer,canard,xcanard,ycanard);
        if (xPacman <= (xtaupe + taupe->w) && xtaupe <= (xPacman + pacman[1]->w) && yPacman <= (ytaupe + taupe->h) && (ytaupe +taupe->h) <= (yPacman + pacman[1]->h))
        {
            pari();
            anim_horse();
            yguitar-= pacman[1]->h;
            yserpent-= pacman[1]->h;
            yriver-= pacman[1]->h;
            ycasino-= pacman[1]->h;
            yhippodrome-= pacman[1]->h;
            yporte-= pacman[1]->h;
            yimgfond-= pacman[1]->h;
            ytir-= pacman[1]->h;
            ylabyrinthe-= pacman[1]->h;
            ytaupe-= pacman[1]->h;
            ycanard-= pacman[1]->h;
            // Collision détectée !
            textout_centre_ex(buffer, font, "Collision !", WIDTH/2, HEIGHT/2, makecol(255, 0, 0), -1);
        }

        //draw_sprite(buffer,taupe,xtaupe,ytaupe);
        if (xPacman <= (xguitar + guitar->w) && xguitar <= (xPacman + pacman[1]->w) && yPacman <= (yguitar + guitar->h) && (yguitar +guitar->h) <= (yPacman + pacman[1]->h))
        {
            playguitar();
            yserpent-= pacman[1]->h;
            yriver-= pacman[1]->h;
            ycasino-= pacman[1]->h;
            yguitar-= pacman[1]->h;
            yhippodrome-= pacman[1]->h;
            yporte-= pacman[1]->h;
            yimgfond-= pacman[1]->h;
            ytir-= pacman[1]->h;
            ylabyrinthe-= pacman[1]->h;
            ytaupe-= pacman[1]->h;
            ycanard-= pacman[1]->h;
            // Collision détectée !
            textout_centre_ex(buffer, font, "Collision !", WIDTH/2, HEIGHT/2, makecol(255, 0, 0), -1);
        }

        //draw_sprite(buffer,guitar,xguitar,yguitar);
        if (xPacman <= (xcasino + casino->w) && xcasino <= (xPacman + pacman[1]->w) && yPacman <= (ycasino + casino->h) && (ycasino + casino->h) <= (yPacman + pacman[1]->h))
        {
            jackpot();
            yguitar-= pacman[1]->h;
            yserpent-= pacman[1]->h;
            yriver-= pacman[1]->h;
            ycasino-= pacman[1]->h;
            yhippodrome-= pacman[1]->h;
            yporte-= pacman[1]->h;
            yimgfond-= pacman[1]->h;
            ytir-= pacman[1]->h;
            ylabyrinthe-= pacman[1]->h;
            ytaupe-= pacman[1]->h;
            ycanard-= pacman[1]->h;
            // Collision détectée !
            textout_centre_ex(buffer, font, "Collision !", WIDTH/2, HEIGHT/2, makecol(255, 0, 0), -1);
        }

        //draw_sprite(buffer,casino,xcasino,ycasino);

        if (xPacman <= (xriver + river->w) && xriver <= (xPacman + pacman[1]->w) && yPacman <= (yriver + river->h) && (yriver + river->h) <= (yPacman + pacman[1]->h))
        {
            //playguitar();
            yguitar-= pacman[1]->h;
            yserpent-= pacman[1]->h;
            yriver-= pacman[1]->h;
            ycasino-= pacman[1]->h;
            yhippodrome-= pacman[1]->h;
            yporte-= pacman[1]->h;
            yimgfond-= pacman[1]->h;
            ytir-= pacman[1]->h;
            ylabyrinthe-= pacman[1]->h;
            ytaupe-= pacman[1]->h;
            ycanard-= pacman[1]->h;
            // Collision détectée !
            textout_centre_ex(buffer, font, "Collision !", WIDTH/2, HEIGHT/2, makecol(255, 0, 0), -1);
        }

        //draw_sprite(buffer,river,xriver,yriver);

        if (xPacman <= (xserpent + serpent->w) && xserpent <= (xPacman + pacman[1]->w) && yPacman <= (yserpent + serpent->h) && (yserpent + serpent->h) <= (yPacman + pacman[1]->h))
        {
            snake();
            yguitar-= pacman[1]->h;
            yserpent-= pacman[1]->h;
            yriver-= pacman[1]->h;
            ycasino-= pacman[1]->h;
            yhippodrome-= pacman[1]->h;
            yporte-= pacman[1]->h;
            yimgfond-= pacman[1]->h;
            ytir-= pacman[1]->h;
            ylabyrinthe-= pacman[1]->h;
            ytaupe-= pacman[1]->h;
            ycanard-= pacman[1]->h;
            // Collision détectée !
            textout_centre_ex(buffer, font, "Collision !", WIDTH/2, HEIGHT/2, makecol(255, 0, 0), -1);
        }

        //draw_sprite(buffer,serpent,xserpent,yserpent);


        if (key[KEY_RIGHT]&& ((WIDTH+1)<(fondmap->w +ximgfond))){
            if (key[KEY_UP] && yimgfond<0){
                yguitar+= dy;
                yserpent+= dy;
                yriver+= dy;
                ycasino+= dy;
                yhippodrome+= dy;
                yporte+= dy;
                yimgfond+= dy;
                ytir+= dy;
                ylabyrinthe+= dy;
                ytaupe+= dy;
                ycanard+= dy;
            }
            if(key[KEY_DOWN]&& ((HEIGHT+1)<(fondmap->h +yimgfond))){
                yguitar-= dy;
                yserpent-= dy;
                yriver-= dy;
                ycasino-= dy;
                yhippodrome-= dy;
                yporte-= dy;
                yimgfond-= dy;
                ytir-= dy;
                ylabyrinthe-= dy;
                ytaupe-= dy;
                ycanard-= dy;
            }
            posx++;
            xguitar-= dx;
            xserpent-= dx;
            xriver-= dx;
            xcasino-= dx;
            xhippodrome-= dx;
            xporte-= dx;
            ximgfond -= dx;
            xtir-= dx;
            xlabyrinthe-= dx;
            xtaupe-= dx;
            xcanard-= dx;

            /*if(xPacman<0)
            {
                xPacman=0;
            }*/
            if(posx>2)
            {
                posx=0;
            }

            draw_sprite(buffer,pacman[posx],xPacman,yPacman);
        }
        else if (key[KEY_LEFT]&& ximgfond<0){
            if (key[KEY_UP]&& yimgfond<0){
                yguitar+= dy;
                yserpent+= dy;
                yriver+= dy;
                ycasino+= dy;
                yhippodrome+= dy;
                yporte+= dy;
                yimgfond+= dy;
                ytir+= dy;
                ylabyrinthe+= dy;
                ytaupe+= dy;
                ycanard+= dy;
            }
            if(key[KEY_DOWN] && ((HEIGHT+1)<(fondmap->h +yimgfond))){
                yguitar-= dy;
                yserpent-= dy;
                yriver-= dy;
                ycasino-= dy;
                yhippodrome-= dy;
                yporte-= dy;
                yimgfond-= dy;
                ytir-= dy;
                ylabyrinthe-= dy;
                ytaupe-= dy;
                ycanard-= dy;
            }
            posx++;
            xguitar+= dx;
            xserpent+= dx;
            xriver+= dx;
            xcasino+= dx;
            xhippodrome+= dx;
            xporte+= dx;
            ximgfond += dx;
            xtir+= dx;
            xlabyrinthe+= dx;
            xtaupe+= dx;
            xcanard+= dx;

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
        else if (key[KEY_UP]&& yimgfond<0){
            posx++;
            yguitar+= dy;
            yserpent+= dy;
            yriver+= dy;
            ycasino+= dy;
            yhippodrome+= dy;
            yporte+= dy;
            yimgfond+= dy;
            ytir+= dy;
            ylabyrinthe+= dy;
            ytaupe+= dy;
            ycanard+= dy;
             /*if(xPacman<0)
            {
                xPacman=0;
            }*/
            if(posx>2)
            {
                posx=0;
            }
            draw_sprite_h_flip(buffer,pacman[posx],xPacman,yPacman);

        }
        else if (key[KEY_DOWN]&& ((HEIGHT+1)<(fondmap->h +yimgfond))){
            posx++;
            yguitar-= dy;
            yserpent-= dy;
            yriver-= dy;
            ycasino-= dy;
            yhippodrome-= dy;
            yporte-= dy;
            yimgfond-= dy;
            ytir-= dy;
            ylabyrinthe-= dy;
            ytaupe-= dy;
            ycanard-= dy;
            /*if(yPacman>HEIGHT)
            {
                xPacman=0;
            }*/
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
            rest(10);
        }
        else
            rest(60); // Pause de 10 ms pour rafraîchir l'écran
    }
}
