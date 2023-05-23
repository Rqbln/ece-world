//by Baptiste Chesnot
#include "chevaux.h"

void anim_horse(){
    rest(200); // Pause de 10 ms pour rafraîchir l'écran
    //initialisation des BITMAP
    BITMAP *buffer;
    BITMAP *cheval[13];
    BITMAP *arriver= load_bitmap("../Games/Course_Chevaux/image/arriver.bmp",NULL);
    BITMAP *enterkey= load_bitmap("../Games/Course_Chevaux/image/enterkey.bmp",NULL);
    BITMAP *spacekey= load_bitmap("../Games/Course_Chevaux/image/spacekey1.bmp",NULL);
    BITMAP *fond= load_bitmap("../Games/Course_Chevaux/image/map0.bmp",NULL);
    BITMAP *menu[2];
    BITMAP *lettre[37];//+10 pour les chiffre
    menu[0] = load_bitmap("../Games/Course_Chevaux/image/parchem1.bmp",NULL);
    menu[1] = load_bitmap("../Games/Course_Chevaux/image/parchem2.bmp",NULL);
    BITMAP *select[10][2];
    //initialisation des SAMPLE
    SAMPLE *musicparis= load_sample("../Games/Course_Chevaux/musique/pascheval.wav");
    SAMPLE *musiccourse= load_sample("../Games/Course_Chevaux/musique/coursecommente.wav");
    SAMPLE *musicarrive= load_sample("../Games/Course_Chevaux/musique/coursearriver.wav");
    SAMPLE *course= load_sample("../Games/Course_Chevaux/musique/course.wav");
    SAMPLE *fete= load_sample("../Games/Course_Chevaux/musique/fete.wav");
    //initialisation des variable
    int numlettre=0;
    int nblettre=30;
    int xlettre=0;
    int ylettre=0;
    char message[nblettre];
    int position[nbCheval];
    int xcheval[nbCheval];
    int ycheval[nbCheval];
    char nomDeFichier[80];
    int nombreAleatoire;
    int memo;
    int xArriver=WIDTH*0.95;
    int yArriver=HEIGHT*0.35;
    int yselect[nbCheval];
    char nomDuFichier[60];
    int tour=0;
    int option=0;
    int joueur[NB_JOUEURS];
    int xselect=WIDTH/1.5;
    int j;
    int fin=0;
    int xenter=WIDTH-400;
    int yenter=HEIGHT-80;
    int ticket=0;
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
    if (!musicparis && !musiccourse && !musicarrive) {
        allegro_message("Erreur : impossible de charger la musique");
        allegro_exit();
        exit(EXIT_FAILURE);
    }
    if(!arriver && !fond){
        allegro_message("image/arriver et fond");
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
    for(int i=0;i<37;i++){ //+10
        if (i<27){
            sprintf(nomDeFichier,"../police/lettre/%c.bmp",i+97);
        } else{
            sprintf(nomDeFichier,"../police/lettre/%d.bmp",i-27);
        }
        lettre[i]= load_bitmap(nomDeFichier,NULL);
        if(!lettre[i]){
            allegro_message("../police/lettre/%c.bmp",i+97);
            exit(EXIT_FAILURE);
        }
    }
    buffer=create_bitmap(WIDTH,HEIGHT);
    play_sample(musicparis, 255, 128, 1000, 1);
    play_sample(fete, 150, 128, 1000, 1);

    while (tour < 2) { //menu pour les paris avant la course
        clear_bitmap(buffer);
        clear_to_color(buffer, makecol(255, 255, 255)); // Effacer l'écran en blanc
        stretch_blit(fond,buffer,0,0,fond->w,fond->h,0,0,WIDTH,HEIGHT);
        draw_sprite(buffer,arriver,xArriver,yArriver);
        draw_sprite(buffer,menu[tour],WIDTH-850,0);
        for (int i=0; i<nbCheval; i++){
            draw_sprite(buffer,cheval[0],xcheval[0],ycheval[i]);
            if (option==i){
                j=1;
            }
            else{
                j=0;
            }
            draw_sprite(buffer,select[i][j],xselect,yselect[i]);
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
            joueurs[tour].nbTickets-=1; //retire un ticket a chaque joueur
            //sprintf("valider, le joueur %d a voté le cheval %d !",tour,option);
            joueurs[tour].nb_essaie_chevaux+=1;
            tour+=1;
            textprintf_ex(buffer, font, WIDTH/2, HEIGHT/2, makecol(255, 255, 255), -1, "valider, le joueur %d a voté le cheval %d !",tour,option);
            rest(250); // Pause pour éviter les mouvements trop rapides
        }
        blit(buffer,screen,0,0,0,0,WIDTH,HEIGHT);
        rest(20); // Pause de 10 ms pour rafraîchir l'écran
    }


    while (fin==0 && !key[KEY_ESC]){//initialise la course(position et music)
        stop_sample(musicarrive);
        stop_sample(musicparis);
        stop_sample(fete);
        play_sample(musiccourse, 255, 128, 1000, 1);
        play_sample(course, 150, 128, 1000, 1);
        for(int i=0;i<nbCheval;i++) {
            xcheval[i] = 0;
            position[i] = 0;
            ycheval[i] = i * 55 + HEIGHT * 0.31;
        }
        memo=20;
        while (memo ==20) {//boucle qui depend de memo. memo prendra par la suite la valeur du cavalier vainqueur en attendant il a le nombre quelconque 20
            clear_bitmap(buffer);
            clear_to_color(buffer, makecol(255, 255, 255)); // Effacer l'écran en blanc
            // Obtenir les coordonnées de la souris
            stretch_blit(fond,buffer,0,0,fond->w,fond->h,0,0,WIDTH,HEIGHT);
            draw_sprite(buffer,arriver,xArriver,yArriver);//affiche la ligne d arrivée
            for (int i=0; i<nbCheval; i++){
                // Génération d'un nombre aléatoire compris entre 8 et 20
                nombreAleatoire = 8+rand() % 20;
                position[i]++;
                xcheval[i]+=nombreAleatoire;//deplacement chevaux
                if(position[i]>11){
                    position[i]=1;
                }
                draw_sprite(buffer,cheval[position[i]],xcheval[i],ycheval[i]);
                if (xcheval[i] <= (xArriver + arriver->w) && xArriver*1.01 <= (xcheval[i] + cheval[0]->w) && ycheval[i] <= (yArriver + arriver->h) && yArriver <= (ycheval[i] + cheval[0]->h)){
                    memo=i;
                }
            }
            draw_sprite(buffer,spacekey, xenter/2, yenter);
            blit(buffer,screen,0,0,0,0,WIDTH,HEIGHT);//applique le buffer sur l ecran
            //permet d accelerer la partie
            if (key[KEY_SPACE]) {
                rest(15);
            }
            else
                rest(55); // Pause de 10 ms pour rafraîchir l'écran
        }
        //gestion music
        stop_sample(musiccourse);
        stop_sample(course);
        play_sample(musicarrive, 150, 128, 1000, 1);
        play_sample(fete, 255, 128, 1000, 1);
        while (!key[KEY_ENTER] && !key[KEY_ESC]) {
            //affiche le cavalier vainqueur
            sprintf(message,"  LE CAVALIER %d A WIN  ",memo+1);
            textout_centre_ex(buffer, font, message, WIDTH / 2, HEIGHT / 2, makecol(255, 0, 0), -1);
            draw_sprite(buffer,enterkey, xenter, yenter);
            nblettre = strlen(message);
            for (int i = 0; i < nblettre; ++i) {

                numlettre = (message[i] - '0')-49;
                if (numlettre<0 || numlettre>25){
                    if (numlettre>-33 && numlettre<-6){
                        numlettre+=32;
                    }
                    else if(numlettre>-50 && numlettre<-39) {
                        numlettre+=49+26;//26+49 pour les chiffre on remplace 49 par ca
                    }
                    else{
                        numlettre=26;
                    }
                }
                //printf("Caractere : %c, Entier : %d\n", message[i], (message[i] - '0'));
                ylettre=j*(lettre[0]->h);
                xlettre=i*(lettre[0]->w);
                draw_sprite(buffer,lettre[numlettre],xlettre,ylettre);
            }


            //condition de fin de partie et attribution des points
            if(memo==joueur[0] && memo==joueur[1]){
                fin=1;
                textout_centre_ex(buffer, font, "Les deux joueurs ont remporter un ticket", WIDTH / 2, HEIGHT /3, makecol(255, 0, 0), -1);
                if(ticket==0){
                    joueurs[1].nbTickets+=1;
                    joueurs[0].nbTickets+=1;
                    joueurs[0].score_chevaux[joueurs[0].nb_essaie_chevaux-1]=0;
                    joueurs[1].score_chevaux[joueurs[1].nb_essaie_chevaux-1]=0;
                    ticket=1;
                }

            }else if(memo==joueur[0]){
                fin=1;
                sprintf(message,"%s a remporter un ticket",joueurs[0].nom);
                textout_centre_ex(buffer, font, message, WIDTH / 2, HEIGHT /3, makecol(255, 0, 0), -1);
                joueurs[0].score_chevaux[joueurs[0].nb_essaie_chevaux-1]=1;
                joueurs[1].score_chevaux[joueurs[1].nb_essaie_chevaux-1]=0;
                if(ticket==0){
                    joueurs[0].nbTickets+=2;
                    ticket=1;
                }
            }else if(memo==joueur[1]){
                joueurs[0].score_chevaux[joueurs[0].nb_essaie_chevaux-1]=0;
                joueurs[1].score_chevaux[joueurs[1].nb_essaie_chevaux-1]=1;
                fin=1;
                sprintf(message,"%s a remporter un ticket",joueurs[1].nom);
                textout_centre_ex(buffer, font, message, WIDTH / 2, HEIGHT /3, makecol(255, 0, 0), -1);
                if(ticket==0){
                    joueurs[1].nbTickets+=2;
                    ticket=1;
                }
            }else{fin=0;} //permet de securiser la boucle
            blit(buffer,screen,0,0,0,0,WIDTH,HEIGHT);//applique le buffer sur l ecran
            rest(100); // Pause de 10 ms pour rafraîchir l'écran
        }
    }
    rest(200); // Pause pour eviter de capter plusieur fois la touche echap
    stop_sample(musicarrive);
    stop_sample(fete);
}
void animation_chevauxEnd(){
    BITMAP *bitcoin[8];
    BITMAP *buffer = create_bitmap(WIDTH, HEIGHT);
    BITMAP *witcher = load_bitmap("../Games/Guitar_hero/image/witcher_face.bmp",NULL);;
    BITMAP *blonde = load_bitmap("../Games/Guitar_hero/image/daenerys.bmp",NULL);
    BITMAP *fond = load_bitmap("../Games/Guitar_hero/image/image_dragon.bmp",NULL);
    SAMPLE *victoire = load_wav("../Games/Guitar_hero/musique/victoire.wav");
    SAMPLE *bonus = load_wav("../Games/Guitar_hero/musique/bonus.wav");
    char message[50];
    int xbitcoin = WIDTH/2;
    int ybitcoin = (HEIGHT/2)+70;
    int posbitcoin = 0;
    int cmpt=0;
    int time=50;
    for (int j = 0; j < 8; j++) {
        sprintf(message, "../Games/bitcoin/bitcoin%d.bmp", j);
        bitcoin[j] = load_bitmap(message, NULL);
        if (!bitcoin[j]) {
            allegro_message("../image/bitcoin/bitcoin%d.bmp", j);
            exit(EXIT_FAILURE);
        }
    }
    if(!victoire){
        allegro_message("../../image/victoire.bmp");
        exit(EXIT_FAILURE);
    }


    play_sample(victoire, 255, 128, 1000, 1);
    while (!key[KEY_ENTER]) {
        clear_bitmap(buffer);
        clear_to_color(buffer, makecol(255, 255, 255)); // Effacer l'écran en blanc
        draw_sprite(buffer,witcher,0,0);
        textout_centre_ex(buffer, font, message, 1400, 200, makecol(0, 0, 0), -1);
        blit(buffer, screen, 0, 0, 0, 0, WIDTH, HEIGHT);
    }
    rest(250); // Pause pour éviter les mouvements trop rapides
    play_sample(bonus, 255, 128, 1000, 0);
    while (!key[KEY_ENTER] && (joueurs[0].score_guitare[joueurs[0].nb_essaie_guitare-1] != joueurs[1].score_guitare[joueurs[1].nb_essaie_guitare-1])) {
        cmpt+=1;
        posbitcoin += 1;
        if (posbitcoin >= 8) {
            posbitcoin = 0;
        }
        if(cmpt>30 && cmpt<50){
            ybitcoin-=6;
        }
        if(cmpt>=50){
            time =15;
            xbitcoin-=WIDTH/80;
            ybitcoin-=HEIGHT/80;
        }
        clear_bitmap(buffer);
        clear_to_color(buffer, makecol(255, 255, 255)); // Effacer l'écran en blanc
        draw_sprite(buffer,blonde,0,0);
        draw_sprite(buffer, bitcoin[posbitcoin], xbitcoin, ybitcoin);
        blit(buffer, screen, 0, 0, 0, 0, WIDTH, HEIGHT);
        rest(time); // Pause pour éviter les mouvements trop rapides
    }
    stop_sample(victoire);
    rest(250); // Pause pour éviter les mouvements trop rapides
}