//by Baptiste Chesnot
#include "chevaux.h"
void pari(){
    BITMAP *buffer;
    BITMAP *cheval= load_bitmap("../Games/Course_Chevaux/image/cheval0.bmp",NULL);;
    BITMAP *arriver= load_bitmap("../Games/Course_Chevaux/image/arriver.bmp",NULL);
    BITMAP *fond= load_bitmap("../Games/Course_Chevaux/image/map0.bmp",NULL);
    BITMAP *menu = load_bitmap("../Games/Course_Chevaux/image/menu.bmp",NULL);
    BITMAP *select[10][2];

    int position[nbCheval];
    int xcheval = 0;
    int ycheval[nbCheval];
    int memo=20;
    int xArriver=WIDTH*0.95;
    int yArriver=HEIGHT*0.35;
    char nomDuFichier[80];
    int xselect=WIDTH/1.5;
    int yselect[nbCheval];


    for(int i=0;i<nbCheval;i++)
    {
        ycheval[i]=i*55+HEIGHT*0.31;
        yselect[i]=i*55+HEIGHT*0.31;
        position[i]=0;
        sprintf(nomDuFichier,"../Games/Course_Chevaux/image/selectPari%d.bmp",i);
        select[i][0]= load_bitmap(nomDuFichier,NULL);
        if(!select[i][0])
        {
            allegro_message("../Games/Course_Chevaux/image/cheval%d.bmp",i);
            exit(EXIT_FAILURE);
        }

    }

    if(!arriver){
        allegro_message("../Games/Course_Chevaux/image/arriver.bmp");
        exit(EXIT_FAILURE);
    }

    if(!cheval){
        allegro_message("../Games/Course_Chevaux/image/cheval0.bmp");
        exit(EXIT_FAILURE);
    }

    if(!fond)
    {
        allegro_message("../Games/Course_Chevaux/image/map0.bmp ");
        allegro_exit();
        exit(EXIT_FAILURE);
    }
    buffer=create_bitmap(WIDTH,HEIGHT);

    while (!key[KEY_ESC] && memo ==20) {
        clear_bitmap(buffer);
        clear_to_color(buffer, makecol(255, 255, 255)); // Effacer l'écran en blanc
        // Obtenir les coordonnées de la souris
        stretch_blit(fond,buffer,0,0,fond->w,fond->h,0,0,WIDTH,HEIGHT);
        draw_sprite(buffer,arriver,xArriver,yArriver);
        draw_sprite(buffer,menu,WIDTH/2,0);
        for (int i=0; i<nbCheval; i++){
            draw_sprite(buffer,select[i][0],xselect,yselect[i]);
            draw_sprite(buffer,cheval,xcheval,ycheval[i]);
        }
        //blit(buffer,screen,0,0,0,0,WIDTH,HEIGHT);
        //rest(20); // Pause de 10 ms pour rafraîchir l'écran
        //stretch_blit(menu,fond,0,0,menu->w,menu->h,0,0,WIDTH,HEIGHT); //permet d afficher un nouveau fond
        //draw_sprite(buffer,menu,WIDTH/2,0);
        blit(buffer,screen,0,0,0,0,WIDTH,HEIGHT);
        rest(20); // Pause de 10 ms pour rafraîchir l'écran
    }
}
void anim_horse(){
    rest(200); // Pause de 10 ms pour rafraîchir l'écran
    BITMAP *buffer;
    BITMAP *cheval[13];
    BITMAP *arriver= load_bitmap("../Games/Course_Chevaux/image/arriver.bmp",NULL);
    BITMAP *fond= load_bitmap("../Games/Course_Chevaux/image/map0.bmp",NULL);

    int posx=0;
    int position[nbCheval];
    int dx=9;
    int dy=9;
    int xCheval=WIDTH/2;
    int yCheval=HEIGHT/2;
    int xcheval[nbCheval];
    int ycheval[nbCheval];
    char nomDeFichier[80];
    int nombreAleatoire;
    int memo=20;
    int xArriver=WIDTH*0.95;
    int yArriver=HEIGHT*0.35;
    char message[50];

    // Initialisation de la fonction rand() avec la fonction srand()
    srand(time(NULL));

    for(int i=0;i<nbCheval;i++)
    {
        xcheval[i]=0;
        ycheval[i]=i*55+HEIGHT*0.31;
        position[i]=0;
    }

    if(!arriver){
        allegro_message("../Games/Course_Chevaux/image/arriver.bmp");
        exit(EXIT_FAILURE);
    }

    for(int i=0;i<12;i++)
    {
        sprintf(nomDeFichier,"../Games/Course_Chevaux/image/cheval%d.bmp",i);
        cheval[i]= load_bitmap(nomDeFichier,NULL);
        if(!cheval[i])
        {
            allegro_message("../Games/Course_Chevaux/image/cheval%d.bmp",i);
            exit(EXIT_FAILURE);
        }
    }

    if(!fond)
    {
        allegro_message("../Games/Course_Chevaux/image/map0.bmp ");
        allegro_exit();
        exit(EXIT_FAILURE);
    }
    buffer=create_bitmap(WIDTH,HEIGHT);

    while (!key[KEY_ESC] && memo ==20) {
        clear_bitmap(buffer);
        clear_to_color(buffer, makecol(255, 255, 255)); // Effacer l'écran en blanc
        // Obtenir les coordonnées de la souris
        stretch_blit(fond,buffer,0,0,fond->w,fond->h,0,0,WIDTH,HEIGHT);
        /*if (xCheval <= (xArriver + arriver->w) && xArriver <= (xCheval + cheval[0]->w) && yCheval <= (yArriver + arriver->h) && yArriver <= (yCheval + cheval[0]->h))
        {
            // Collision détectée !
            textout_centre_ex(buffer, font, "Collision !", WIDTH/2, HEIGHT/2, makecol(255, 0, 0), -1);
        }*/
        draw_sprite(buffer,arriver,xArriver,yArriver);
        for (int i=0; i<nbCheval; i++){
            // Génération d'un nombre aléatoire compris entre 8 et 20
            nombreAleatoire = 8+rand() % 20;
            position[i]++;
            xcheval[i]+=nombreAleatoire;

            if(position[i]>11)
            {
                position[i]=1;
            }
            draw_sprite(buffer,cheval[position[i]],xcheval[i],ycheval[i]);
            if (xcheval[i] <= (xArriver + arriver->w) && xArriver*1.01 <= (xcheval[i] + cheval[0]->w) && ycheval[i] <= (yArriver + arriver->h) && yArriver <= (ycheval[i] + cheval[0]->h))
            {
                memo=i;
                // Collision détectée !
            }

        }
        /*if (key[KEY_RIGHT]){
            posx++;
            xCheval=xCheval+dx;
            if(xCheval<0)
            {
                xCheval=0;
            }
            if(posx>11)
            {
                posx=1;
            }
            draw_sprite(buffer,cheval[posx],xCheval,yCheval);
        }
        else if (key[KEY_LEFT]){
            posx++;
            xCheval=xCheval-dx;
            if(xCheval>WIDTH)
            {
                xCheval=0;
            }
            if(posx>11)
            {
                posx=1;
            }
            draw_sprite_h_flip(buffer,cheval[posx],xCheval,yCheval);

        }
        else if (key[KEY_UP]){
            posx++;
            yCheval=yCheval-dy;
            if(xCheval<0)
            {
                xCheval=0;
            }
            if(posx>11)
            {
                posx=1;
            }
            draw_sprite_h_flip(buffer,cheval[posx],xCheval,yCheval);

        }
        else if (key[KEY_DOWN]){
            posx++;
            yCheval=yCheval+dy;
            if(yCheval>HEIGHT)
            {
                xCheval=0;
            }
            if(posx>11)
            {
                posx=1;
            }
            draw_sprite_h_flip(buffer,cheval[posx],xCheval,yCheval);

        }
        else
        {
            draw_sprite(buffer,cheval[0],xCheval,yCheval);
        }*/


        blit(buffer,screen,0,0,0,0,WIDTH,HEIGHT);
        if (key[KEY_SPACE]) {
            rest(15);
        }
        else
            rest(55); // Pause de 10 ms pour rafraîchir l'écran
    }
    while (!key[KEY_ESC]) {
        sprintf(message,"LE CAVALIER %d A WIN LA GAME",memo+1);
        textout_centre_ex(buffer, font, message, WIDTH / 2, HEIGHT / 2, makecol(255, 0, 0), -1);
        blit(buffer,screen,0,0,0,0,WIDTH,HEIGHT);
        rest(100); // Pause de 10 ms pour rafraîchir l'écran
    }

}