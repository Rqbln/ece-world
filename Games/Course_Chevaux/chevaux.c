//by Baptiste Chesnot
#include "chevaux.h"
#include "../../joueur/joueur.h"

void anim_horse(){
    rest(200); // Pause de 10 ms pour rafraîchir l'écran
    BITMAP *buffer;
    BITMAP *cheval[13];
    BITMAP *arriver= load_bitmap("../Games/Course_Chevaux/image/arriver.bmp",NULL);
    BITMAP *enterkey= load_bitmap("../Games/Course_Chevaux/image/enterkey.bmp",NULL);
    BITMAP *fond= load_bitmap("../Games/Course_Chevaux/image/map0.bmp",NULL);
    BITMAP *menu[2];
    menu[0] = load_bitmap("../Games/Course_Chevaux/image/parchem1.bmp",NULL);
    menu[1] = load_bitmap("../Games/Course_Chevaux/image/parchem2.bmp",NULL);
    BITMAP *select[10][2];

    int position[nbCheval];
    int xcheval[nbCheval];
    int ycheval[nbCheval];
    char nomDeFichier[80];
    int nombreAleatoire;
    int memo;
    int xArriver=WIDTH*0.95;
    int yArriver=HEIGHT*0.35;
    char message[50];
    int yselect[nbCheval];
    char nomDuFichier[60];
    int tour=0;
    int option=0;
    int joueur[NB_JOUEURS];
    int xselect=WIDTH/1.5;
    int j;
    int fin=0;
    int xenter=WIDTH-400;
    int yenter=HEIGHT-100;
    // Initialisation de la fonction rand() avec la fonction srand()
    srand(time(NULL));
    for(int i=0;i<nbCheval;i++){
        xcheval[i]=0;
        position[i]=0;
        ycheval[i]=i*55+HEIGHT*0.31;
        yselect[i]=i*55+HEIGHT*0.31;
        for(int y=0 ; y<2 ; y++){
            sprintf(nomDuFichier,"../Games/Course_Chevaux/image/selectPari%d%d.bmp",i,y);
            select[i][y]= load_bitmap(nomDuFichier,NULL);
            if(!select[i][y]){
                allegro_message("../Games/Course_Chevaux/image/selectPari%d%d.bmp",i,y);
                exit(EXIT_FAILURE);
            }
        }
    }
    if(!arriver){
        allegro_message("../Games/Course_Chevaux/image/arriver.bmp");
        exit(EXIT_FAILURE);
    }
    for(int i=0;i<12;i++){
        sprintf(nomDeFichier,"../Games/Course_Chevaux/image/cheval%d.bmp",i);
        cheval[i]= load_bitmap(nomDeFichier,NULL);
        if(!cheval[i]){
            allegro_message("../Games/Course_Chevaux/image/cheval%d.bmp",i);
            exit(EXIT_FAILURE);
        }
    }
    if(!fond){
        allegro_message("../Games/Course_Chevaux/image/map0.bmp ");
        allegro_exit();
        exit(EXIT_FAILURE);
    }
    buffer=create_bitmap(WIDTH,HEIGHT);
    while (tour < 2) {
        clear_bitmap(buffer);
        clear_to_color(buffer, makecol(255, 255, 255)); // Effacer l'écran en blanc
        stretch_blit(fond,buffer,0,0,fond->w,fond->h,0,0,WIDTH,HEIGHT);
        draw_sprite(buffer,arriver,xArriver,yArriver);
        draw_sprite(buffer,menu[tour],WIDTH-850,0);
        //for (int tour = 0; tour < nbJoueur; ++tour) {
        for (int i=0; i<nbCheval; i++){
            draw_sprite(buffer,cheval[0],xcheval[0],ycheval[i]);
            if (option==i){
                j=1;
            }
            else{
                j=0;
            }
            draw_sprite(buffer,select[i][j],xselect,yselect[i]);
            textprintf_ex(buffer, font, 200, 100, makecol(255, 255, 255), -1, "joueur %d fais ton choix enculé!",tour);
        }
        draw_sprite(buffer,enterkey, xenter, yenter);
        if (key[KEY_UP]) { // Flèche du haut
            option--;
            if (option<0){
                option=nbCheval-1;
            }
            rest(250); // Pause pour éviter les mouvements trop rapides
        }
        if (key[KEY_DOWN]) { // Flèche du bas
            option++;
            if (option>=nbCheval){
                option=0;
            }
            rest(250); // Pause pour éviter les mouvements trop rapides
        }
        if (key[KEY_ENTER]) { // Touche Entrée
            rest(50); // Pause pour éviter les mouvements trop rapides
            joueur[tour] = option;
            //sprintf("valider, le joueur %d a voté le cheval %d !",tour,option);
            tour+=1;
            textprintf_ex(buffer, font, WIDTH/2, HEIGHT/2, makecol(255, 255, 255), -1, "valider, le joueur %d a voté le cheval %d !",tour,option);

            //textout_centre_ex(buffer, font, "valider, le joueur %d a voté le cheval %d !", WIDTH/2, HEIGHT/2, makecol(255, 0, 0), -1);
            rest(250); // Pause pour éviter les mouvements trop rapides
        }
        blit(buffer,screen,0,0,0,0,WIDTH,HEIGHT);
        rest(20); // Pause de 10 ms pour rafraîchir l'écran
    }

    while (fin==0 && !key[KEY_ESC]){
        for(int i=0;i<nbCheval;i++) {
            xcheval[i] = 0;
            position[i] = 0;
            ycheval[i] = i * 55 + HEIGHT * 0.31;
        }
        memo=20;
        while (!key[KEY_ENTER] && memo ==20) {
            clear_bitmap(buffer);
            clear_to_color(buffer, makecol(255, 255, 255)); // Effacer l'écran en blanc
            // Obtenir les coordonnées de la souris
            stretch_blit(fond,buffer,0,0,fond->w,fond->h,0,0,WIDTH,HEIGHT);
            draw_sprite(buffer,arriver,xArriver,yArriver);
            for (int i=0; i<nbCheval; i++){
                // Génération d'un nombre aléatoire compris entre 8 et 20
                nombreAleatoire = 8+rand() % 20;
                position[i]++;
                xcheval[i]+=nombreAleatoire;

                if(position[i]>11){
                    position[i]=1;
                }
                draw_sprite(buffer,cheval[position[i]],xcheval[i],ycheval[i]);
                if (xcheval[i] <= (xArriver + arriver->w) && xArriver*1.01 <= (xcheval[i] + cheval[0]->w) && ycheval[i] <= (yArriver + arriver->h) && yArriver <= (ycheval[i] + cheval[0]->h)){
                    memo=i;
                    // Collision détectée !
                }
            }
            blit(buffer,screen,0,0,0,0,WIDTH,HEIGHT);
            if (key[KEY_SPACE]) {
                rest(15);
            }
            else
                rest(55); // Pause de 10 ms pour rafraîchir l'écran
        }
        while (!key[KEY_ENTER] && !key[KEY_ESC]) {
            sprintf(message,"LE CAVALIER %d A WIN LA GAME",memo+1);
            textout_centre_ex(buffer, font, message, WIDTH / 2, HEIGHT / 2, makecol(255, 0, 0), -1);
            draw_sprite(buffer,enterkey, xenter, yenter);
            if(memo==joueur[0] && memo==joueur[1]){
                fin=1;
                textout_centre_ex(buffer, font, "Les deux joueurs ont remporter un ticket", WIDTH / 2, HEIGHT /3, makecol(255, 0, 0), -1);
                joueurs[1].nbTickets+=1;
                joueurs[0].nbTickets+=1;
            }else if(memo==joueur[0]){
                fin=1;
                sprintf(message,"%s a remporter un ticket",joueurs[0].nom);
                textout_centre_ex(buffer, font, message, WIDTH / 2, HEIGHT /3, makecol(255, 0, 0), -1);
                joueurs[0].nbTickets+=1;
            }else if(memo==joueur[1]){
                fin=1;
                sprintf(message,"%s a remporter un ticket",joueurs[1].nom);
                textout_centre_ex(buffer, font, message, WIDTH / 2, HEIGHT /3, makecol(255, 0, 0), -1);
                joueurs[1].nbTickets+=1;
            }else{fin=0;}
            //textout_centre_ex(buffer, font, message, WIDTH / 2, HEIGHT / 2, makecol(255, 0, 0), -1);
            blit(buffer,screen,0,0,0,0,WIDTH,HEIGHT);
            rest(100); // Pause de 10 ms pour rafraîchir l'écran
        }
    }
}