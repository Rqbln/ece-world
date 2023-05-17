//by Baptiste Chesnot
#include "guitar_hero.h"
#include "../../joueur/joueur.h"
#include "../../Sauvegarde/sauvegarde.h"
void animation_guitare(){
    BITMAP *buffer = create_bitmap(WIDTH, HEIGHT);
    BITMAP *dragon = load_bitmap("../Games/Guitar_hero/image/tete_dragon.bmp",NULL);;
    BITMAP *witcher = load_bitmap("../Games/Guitar_hero/image/witcher_dos.bmp",NULL);
    BITMAP *fond = load_bitmap("../Games/Guitar_hero/image/image_dragon.bmp",NULL);
    SAMPLE *vol = load_wav("../Games/Guitar_hero/musique/vole.wav");
    SAMPLE *grondement1 = load_wav("../Games/Guitar_hero/musique/grondement1.wav");
    SAMPLE *grondement2 = load_wav("../Games/Guitar_hero/musique/grondement2.wav");

    if(!grondement2){
        allegro_message("../../image/gdment2.bmp");
        exit(EXIT_FAILURE);
    }
    if(!vol){
        allegro_message("../../image/vol.bmp");
        exit(EXIT_FAILURE);
    }
    play_sample(grondement1, 255, 128, 1000, 1);
    while (!key[KEY_ENTER]) {
        clear_bitmap(buffer);
        clear_to_color(buffer, makecol(255, 255, 255)); // Effacer l'écran en blanc
        draw_sprite(buffer,dragon,0,0);
        blit(buffer, screen, 0, 0, 0, 0, WIDTH, HEIGHT);
    }
    stop_sample(grondement1);
    rest(250); // Pause pour éviter les mouvements trop rapides
    play_sample(vol, 255, 128, 1000, 1);
    while (!key[KEY_ENTER]) {
        clear_bitmap(buffer);
        clear_to_color(buffer, makecol(255, 255, 255)); // Effacer l'écran en blanc
        draw_sprite(buffer,witcher,0,0);
        blit(buffer, screen, 0, 0, 0, 0, WIDTH, HEIGHT);
    }
    stop_sample(vol);
    rest(250); // Pause pour éviter les mouvements trop rapides
    play_sample(grondement2, 255, 128, 1000, 1);
    while (!key[KEY_ENTER]) {
        clear_bitmap(buffer);
        clear_to_color(buffer, makecol(255, 255, 255)); // Effacer l'écran en blanc
        draw_sprite(buffer,fond,0,0);
        blit(buffer, screen, 0, 0, 0, 0, WIDTH, HEIGHT);
    }
    stop_sample(grondement2);
}
void animation_guitarEnd(){
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

    if (joueurs[0].score_guitare[joueurs[0].nb_essaie_guitare-1]<joueurs[1].score_guitare[joueurs[1].nb_essaie_guitare-1]){
        sprintf(message,"%s",joueurs[1].nom);
        joueurs[1].nbTickets+=2;
        if (highscore[2].score < (joueurs[1].score_guitare[joueurs[1].nb_essaie_guitare-1])) {
            saveMiniGame(joueurs,"Guitar",(joueurs[1].score_guitare[joueurs[1].nb_essaie_guitare-1]),1);
            loadHighScore(highscore);
        }
    }
    else if(joueurs[0].score_guitare[joueurs[0].nb_essaie_guitare-1]>joueurs[1].score_guitare[joueurs[1].nb_essaie_guitare-1]){
        sprintf(message,"%s",joueurs[0].nom);
        joueurs[0].nbTickets+=2;
        if (highscore[2].score < (joueurs[0].score_guitare[joueurs[0].nb_essaie_guitare-1])) {
            saveMiniGame(joueurs,"Guitar",(joueurs[0].score_guitare[joueurs[0].nb_essaie_guitare-1]),0);
            loadHighScore(highscore);
        }
    }
    else {
        sprintf(message,"egalite");
        joueurs[0].nbTickets+=1;
        joueurs[1].nbTickets+=1;
        if (highscore[2].score < (joueurs[0].score_guitare[joueurs[0].nb_essaie_guitare-1])) {
            saveMiniGame(joueurs,"Guitar",(joueurs[0].score_guitare[joueurs[0].nb_essaie_guitare-1]),0);
            loadHighScore(highscore);
        }
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
void menuguitar(){
    //innitialisation des BITMAP
    BITMAP *buffer = create_bitmap(WIDTH, HEIGHT);
    BITMAP *fond = load_bitmap("../Games/Guitar_hero/image/fondguitar3.bmp",NULL);
    BITMAP *fond2 = load_bitmap("../Games/Guitar_hero/image/tetedragon1.bmp",NULL);
    BITMAP *selectstart[2];
    BITMAP *selectstart1[2];
    BITMAP *selectrules[2];
    BITMAP *selectexit[2];
    BITMAP *regle = load_bitmap("../Games/Guitar_hero/image/parcheminGH.bmp",NULL);
    BITMAP *enterkey= load_bitmap("../Games/Course_Chevaux/image/enterkey.bmp",NULL);
    SAMPLE *sound = load_wav("../Games/Guitar_hero/musique/westworld.wav");
    if (!sound) {
        allegro_message("Erreur lors du chargement du fichier WAV\n");
        exit(EXIT_FAILURE);
    }
    play_sample(sound, 255, 128, 1000, 1);

    //declaration variable
    char nomDeFichier[50];
    int ecart=200;
    int xselect=WIDTH/2-200;
    int yselectstart=HEIGHT/2-2*ecart;
    int yselectstart1=HEIGHT/2-ecart;
    int yselectrules=HEIGHT/2;
    int yselectexit=HEIGHT/2+ecart;
    int option=0;
    int xenter=WIDTH-400;
    int yenter=HEIGHT-80;

    //creation des touche de selection
    for(int i=0;i<2;i++){
        sprintf(nomDeFichier,"../Games/Guitar_hero/image/selectmode1%d.bmp",i);
        selectstart[i]= load_bitmap(nomDeFichier,NULL);
        if(!selectstart[i]){
            allegro_message("../../Menu/image/selectstart1%d (Personnalisé).bmp",i);
            exit(EXIT_FAILURE);
        }
        sprintf(nomDeFichier,"../Games/Guitar_hero/image/selectmode2%d.bmp",i);
        selectstart1[i]= load_bitmap(nomDeFichier,NULL);
        if(!selectstart1[i]){
            allegro_message("../../Menu/image/selectstart2%d (Personnalisé).bmp",i);
            exit(EXIT_FAILURE);
        }

        sprintf(nomDeFichier,"../Games/Guitar_hero/image/selectregle%d.bmp",i);
        selectrules[i]= load_bitmap(nomDeFichier,NULL);
        if(!selectrules[i]){
            allegro_message("../../image/selectrules%d.bmp",i);
            exit(EXIT_FAILURE);
        }
        sprintf(nomDeFichier,"../Games/Guitar_hero/image/selectexit%d.bmp",i);
        selectexit[i]= load_bitmap(nomDeFichier,NULL);
        if(!selectexit[i]){
            allegro_message("../Menu/image/selectexit%d (Personnalisé).bmp",i);
            exit(EXIT_FAILURE);
        }
    }

    // Boucle principale
    while (!key[KEY_ESC]) {
        clear_bitmap(buffer);
        clear_to_color(buffer, makecol(255, 255, 255)); // Effacer l'écran en blanc
        stretch_blit(fond, buffer, 0, 0, fond->w, fond->h, 0, 0, WIDTH, HEIGHT);
        switch (option) {
            case 0:
                draw_sprite(buffer,selectstart[1],xselect,yselectstart);
                draw_sprite(buffer,selectstart1[0],xselect,yselectstart1);
                draw_sprite(buffer,selectrules[0],xselect,yselectrules);
                draw_sprite(buffer,selectexit[0],xselect,yselectexit);
                draw_sprite(buffer,enterkey,xenter,yenter);
                break;
            case 1:
                draw_sprite(buffer,fond2,0,0);
                draw_sprite(buffer,selectstart[0],xselect,yselectstart);
                draw_sprite(buffer,selectstart1[1],xselect,yselectstart1);
                draw_sprite(buffer,selectrules[0],xselect,yselectrules);
                draw_sprite(buffer,selectexit[0],xselect,yselectexit);
                draw_sprite(buffer,enterkey,xenter,yenter);
                break;
            case 2:
                draw_sprite(buffer,selectstart[0],xselect,yselectstart);
                draw_sprite(buffer,selectstart1[0],xselect,yselectstart1);
                draw_sprite(buffer,selectrules[1],xselect,yselectrules);
                draw_sprite(buffer,selectexit[0],xselect,yselectexit);
                draw_sprite(buffer,enterkey,xenter,yenter);
                break;
            case 3:
                draw_sprite(buffer,selectstart[0],xselect,yselectstart);
                draw_sprite(buffer,selectstart1[0],xselect,yselectstart1);
                draw_sprite(buffer,selectrules[0],xselect,yselectrules);
                draw_sprite(buffer,selectexit[1],xselect,yselectexit);
                draw_sprite(buffer,enterkey,xenter,yenter);
                break;
        }

        // Affichage du buffer à l'écran
        blit(buffer, screen, 0, 0, 0, 0, WIDTH, HEIGHT);

        // Gestion de l'entrée utilisateur
        if (key[KEY_UP]) { // Flèche du haut
            option--;
            if (option<0){
                option=3;
            }
            rest(250); // Pause pour éviter les mouvements trop rapides
        }
        if (key[KEY_DOWN]) { // Flèche du bas
            option++;
            if (option>3){
                option=0;
            }
            rest(250); // Pause pour éviter les mouvements trop rapides
        }
        if (key[KEY_ENTER]) { // Touche Entrée

            if (option == 0) { // Option Jouer
                stop_sample(sound);
                playguitar1();
                play_sample(sound, 255, 128, 1000, 1);
            } else if (option == 1) { // Option Lire les règles
                rest(250); // Pause pour éviter les mouvements trop rapides
                stop_sample(sound);
                animation_guitare();
                playguitar();
                play_sample(sound, 255, 128, 1000, 1);
            } else if (option == 2) { // Option Quitter
                //stop_sample(sound);
                rest(250); // Pause pour éviter les mouvements trop rapides
                while(!key[KEY_ENTER]){
                    draw_sprite(buffer,regle,((WIDTH/2)-(regle->w)/2),-50);
                    blit(buffer, screen, 0, 0, 0, 0, WIDTH, HEIGHT);
                }
                rest(250); // Pause pour éviter les mouvements trop rapides

            } else{
                stop_sample(sound);
                rest(250); // Pause pour éviter les mouvements trop rapides
                //allegro_exit(); // Quitte Allegro
                break; // Sortie de la boucle principale
            }
        }
        rest(10); // Pause pour libérer un peu le processeur
    }
    destroy_sample(sound);
}
void playguitar1(){
    rest(200); // Pause de 10 ms pour rafraîchir l'écran
    BITMAP *buffer;
    BITMAP *note= load_bitmap("../Games/Guitar_hero/image/boulefeu.bmp",NULL);;
    BITMAP *fond= load_bitmap("../Games/Guitar_hero/image/fondguitar3.bmp",NULL);
    BITMAP *gratte= load_bitmap("../Games/Guitar_hero/image/gratte.bmp",NULL);
    SAMPLE *musique= load_sample("../Games/Guitar_hero/musique/musique0.wav");
    BITMAP *enterkey= load_bitmap("../Games/Course_Chevaux/image/enterkey.bmp",NULL);
    set_trans_blender(0, 0, 0, 128);
    if (!musique) {
        allegro_message("Erreur : impossible de charger la musique");
        allegro_exit();
        exit(EXIT_FAILURE);
    }

    int nbnote = 4*bat;
    int xnote[nbnote];
    int ynote[nbnote];
    int nombreAleatoire=20;
    int memo;
    char message[50];
    int score;
    int vitesse;
    int nbjoueur=2;
    int joueurscore[nbjoueur];
    int ticket=0;
    int xenter=WIDTH-400;
    int yenter=HEIGHT-80;
// Joue la musique en boucle
//play_sample(musique, 255, 128, 100, 1);
    // Initialisation de la fonction rand() avec la fonction srand()
    srand(time(NULL));
    if(!gratte){
        allegro_message("../image/gratte.bmp");
        exit(EXIT_FAILURE);
    }
    if(!note){
        allegro_message("../image/note.bmp");
        exit(EXIT_FAILURE);
    }
    if(!fond){
        allegro_message("../image/fondguitar0.bmp ");
        allegro_exit();
        exit(EXIT_FAILURE);
    }
    buffer=create_bitmap(WIDTH,HEIGHT);

    for (int tour = 0; tour < nbjoueur; ++tour) {
        joueurs[tour].nbTickets-=1;
        play_sample(musique, 255, 128, 1000, 1);
        memo=0;
        for (int j = 0; j < bat; ++j) {
            for(int i=0;i<nbnote/bat;i++){
                xnote[i+j*(nbnote/bat)]=i*155+WIDTH*0.34;
                ynote[i+j*(nbnote/bat)]=j*(-200*(i+1));
            }
        }
        vitesse=70;
        score=0;
        rest(150); // Pause de 10 ms pour rafraîchir l'écran
        while (!key[KEY_ESC] && memo ==0) {
            clear_bitmap(buffer);
            clear_to_color(buffer, makecol(255, 255, 255)); // Effacer l'écran en blanc
            // Obtenir les coordonnées de la souris
            stretch_blit(fond,buffer,0,0,fond->w,fond->h,0,0,WIDTH,HEIGHT);
            int x=mouse_x;
            int y=mouse_y;
            draw_sprite(buffer,gratte,(x - ((gratte->w)/2)),(y - ((gratte->h)/2)));
            for (int i=0; i<nbnote; i++){
                // Génération d'un nombre aléatoire compris entre 8 et 20
                //nombreAleatoire = 8+rand() % 20;
                ynote[i]+=nombreAleatoire;
                if (xnote[i] <= (x) && (x) <= (xnote[i] + note->w) && ynote[i] <= (y) && (y) <= (ynote[i] + note->h)){
                    ynote[i]=-200;
                    score+=1;
                    vitesse-=1;
                    // Collision détectée !
                }
                //textprintf_ex(buffer, font, 50, 50, makecol(255, 255, 255), -1, "score: %d", score);

                draw_sprite(buffer,note,xnote[i],ynote[i]);
                if (ynote[i] >= HEIGHT ){
                    memo=1;
                    // Collision détectée !
                }
            }
            textprintf_ex(buffer, font, 10, 10, makecol(255, 255, 255), -1, "score: %d", score);
            blit(buffer,screen,0,0,0,0,WIDTH,HEIGHT);
            rest(vitesse); // Pause de 10 ms pour rafraîchir l'écran
        }
        while (!key[KEY_ENTER]) {
            draw_sprite(buffer,enterkey,xenter,yenter);
            stop_sample(musique);
            sprintf(message,"Perdu enculé");
            joueurs[tour].score_guitare[joueurs[tour].nb_essaie_guitare]=score;
            textout_centre_ex(buffer, font, message, WIDTH / 2, HEIGHT / 2, makecol(255, 0, 0), -1);
            blit(buffer,screen,0,0,0,0,WIDTH,HEIGHT);
            rest(100); // Pause de 10 ms pour rafraîchir l'écran
        }
        joueurs[tour].nb_essaie_guitare+=1;
    }
    rest(150); // Pause de 10 ms pour rafraîchir l'écran
    clear_bitmap(buffer);
    clear_to_color(buffer, makecol(255, 255, 255)); // Effacer l'écran en blanc
    while (!key[KEY_ESC]) {
        if (joueurs[0].score_guitare[joueurs[0].nb_essaie_guitare-1]<joueurs[1].score_guitare[joueurs[1].nb_essaie_guitare-1]){
            sprintf(message,"%s a gagné 1 ticket",joueurs[1].nom);
            if(ticket==0){
                joueurs[1].nbTickets+=2;
                ticket=1;
            }
            if (highscore[2].score < (joueurs[1].score_guitare[joueurs[1].nb_essaie_guitare-1])) {
                saveMiniGame(joueurs,"Guitar1",(joueurs[1].score_guitare[joueurs[1].nb_essaie_guitare-1]),1);
                loadHighScore(highscore);
            }
        }
        else if(joueurs[0].score_guitare[joueurs[0].nb_essaie_guitare-1]>joueurs[1].score_guitare[joueurs[1].nb_essaie_guitare-1]){
            sprintf(message,"%s a gagné 1 ticket",joueurs[0].nom);
            if(ticket==0){
                joueurs[0].nbTickets+=2;
                ticket=1;
            }
            if (highscore[2].score < (joueurs[0].score_guitare[joueurs[0].nb_essaie_guitare-1])) {
                saveMiniGame(joueurs,"Guitar1",(joueurs[0].score_guitare[joueurs[0].nb_essaie_guitare-1]),0);
                loadHighScore(highscore);
            }
        }
        else {
            sprintf(message,"egalite");
            if(ticket==0){
                joueurs[0].nbTickets+=1;
                joueurs[1].nbTickets+=1;
                ticket=1;
            }
            if (highscore[2].score < (joueurs[0].score_guitare[joueurs[0].nb_essaie_guitare-1])) {
                saveMiniGame(joueurs,"Guitar1",(joueurs[0].score_guitare[joueurs[0].nb_essaie_guitare-1]),0);
                loadHighScore(highscore);
            }
        }
        textout_centre_ex(buffer, font, message, WIDTH / 2, HEIGHT / 2, makecol(255, 0, 0), -1);
        blit(buffer,screen,0,0,0,0,WIDTH,HEIGHT);
        rest(100); // Pause de 10 ms pour rafraîchir l'écran
    }
    rest(150); // Pause de 10 ms pour rafraîchir l'écran
}
void playguitar(){
    rest(200); // Pause de 10 ms pour rafraîchir l'écran
    BITMAP *buffer;
    BITMAP *compteur[10];
    BITMAP *note= load_bitmap("../Games/Guitar_hero/image/boulefeu.bmp",NULL);
    BITMAP *bouclier= load_bitmap("../Games/Guitar_hero/image/boulefeu1.bmp",NULL);
    BITMAP *fond= load_bitmap("../Games/Guitar_hero/image/tetedragon1.bmp",NULL);
    BITMAP *enterkey= load_bitmap("../Games/Course_Chevaux/image/enterkey.bmp",NULL);
    SAMPLE *musique= load_sample("../Games/Guitar_hero/musique/kingGT.wav");
    FONT *police = load_font("arial.pcx", NULL, NULL);
    set_trans_blender(0, 0, 0, 128);
    if (!musique) {
        allegro_message("Erreur : impossible de charger la musique");
        allegro_exit();
        exit(EXIT_FAILURE);
    }

    int score;
    int score1=0;
    int score2=0;
    int score3=0;
    int xcompteur=0;
    int ycompteur=0;

    int nbnote = 4*batt;
    int xnote[nbnote];
    int ynote[nbnote];
    int nombreAleatoire=20;
    int memo;
    char message[50];
    char nomDeFichier[50];

    int vitesse;
    int nbjoueur=2;
    int note1=0*155+WIDTH*0.34;
    int note2=1*155+WIDTH*0.34;
    int note3=2*155+WIDTH*0.34;
    int note4=3*155+WIDTH*0.34;
    int notey=HEIGHT/1.5;
    int xenter=WIDTH-400;
    int yenter=HEIGHT-80;

    int ok[4];
    ok[0]=0;
    ok[1]=0;
    ok[2]=0;
    ok[3]=0;

    srand(time(NULL));
    // Initialisation de la fonction rand() avec la fonction srand()
    if(!note){
        allegro_message("../image/note.bmp");
        exit(EXIT_FAILURE);
    }
    if(!fond){
        allegro_message("../image/fondguitar0.bmp ");
        allegro_exit();
        exit(EXIT_FAILURE);
    }
    buffer=create_bitmap(WIDTH,HEIGHT);
    for(int i=0;i<10;i++){
        sprintf(nomDeFichier,"../Games/Guitar_hero/compteur/%d.bmp",i);
        compteur[i]= load_bitmap(nomDeFichier,NULL);
        if(!compteur[i]){
            allegro_message("../Games/compteur/%d.bmp",i);
            exit(EXIT_FAILURE);
        }
    }

    for (int tour = 0; tour < nbjoueur; ++tour) {
        joueurs[tour].nbTickets-=1;
        stop_sample(musique);
        play_sample(musique, 255, 128, 1000, 1);
        memo=0;
        for (int j = 0; j < batt; ++j) {
            for(int i=0;i<nbnote/batt;i++){
                xnote[i+j*(nbnote/batt)]=i*155+WIDTH*0.34;
                ynote[i+j*(nbnote/batt)]=(j+1)*(-200*(i+1));
            }
        }
        vitesse=60;
        score=0;
        rest(150); // Pause de 10 ms pour rafraîchir l'écran
        while (!key[KEY_ESC] && memo ==0) {
            clear_bitmap(buffer);
            clear_to_color(buffer, makecol(255, 255, 255)); // Effacer l'écran en blanc

            stretch_blit(fond,buffer,0,0,fond->w,fond->h,0,0,WIDTH,HEIGHT);

            for (int i=0; i<nbnote; i++) {

                ynote[i] += nombreAleatoire;
                draw_sprite(buffer,note,xnote[i],ynote[i]);
                draw_sprite(buffer,bouclier,note1,notey);
                draw_sprite(buffer,bouclier,note2,notey);
                draw_sprite(buffer,bouclier,note3,notey);
                draw_sprite(buffer,bouclier,note4,notey);

                if (ynote[i] >= HEIGHT ){
                    memo=1;
                    // Collision détectée !
                }
            }
            if (key[KEY_G] && ok[0] == 0) {
                if (xnote[0] <= (note1 + note->w) && (note1) <= (xnote[0] + note->w) &&
                    ynote[0] <= (notey + note->h) && (notey) <= (ynote[0] + note->h)) {
                    ynote[0] = -300+ rand() % 250;
                    score += 1;
                    vitesse -= 1;
                    ok[0] = 1;
                    // Collision détectée !
                } else {
                    memo = 1;
                }
            }
            if (key[KEY_H] && ok[1] == 0) {
                if (xnote[1] <= (note2 + note->w) && (note2) <= (xnote[1] + note->w) &&
                    ynote[1] <= (notey + note->h) && (notey) <= (ynote[1] + note->h)) {
                    ynote[1] = -300+ rand() % 250;
                    score += 1;
                    vitesse -= 1;
                    ok[1] = 1;
                    // Collision détectée !
                } else {
                    memo = 1;
                }
            }

            if (key[KEY_J] && ok[2] == 0) {
                if (xnote[2] <= (note3 + note->w) && (note3) <= (xnote[2] + note->w) &&
                    ynote[2] <= (notey + note->h) && (notey) <= (ynote[2] + note->h)) {
                    ynote[2] = -300+ rand() % 250;
                    score += 1;
                    vitesse -= 1;
                    // Collision détectée !
                    ok[2] = 1;
                } else {
                    memo = 1;
                }
            }
            if (key[KEY_K] && ok[3] == 0) {
                if (xnote[3] <= (note4 + note->w) && (note4) <= (xnote[3] + note->w) &&
                    ynote[3] <= (notey + note->h) && (notey) <= (ynote[3] + note->h)) {
                    ynote[3] = -300+ rand() % 250;
                    score += 1;
                    vitesse -= 1;
                    // Collision détectée !
                    ok[3] = 1;
                } else {
                    memo = 1;
                }
            }
            if (!key[KEY_G]) {
                ok[0] = 0;
            }
            if (!key[KEY_H]) {
                ok[1] = 0;
            }
            if (!key[KEY_J]) {
                ok[2] = 0;
            }
            if (!key[KEY_K]) {
                ok[3] = 0;
            }
            score1=score%10;
            score2=((score-score1)/10)%10;
            score3=((score-(score1+ 10*score2))/100)%10;
            draw_sprite(buffer,compteur[score3],xcompteur,ycompteur);
            draw_sprite(buffer,compteur[score2],xcompteur+(compteur[0]->w),ycompteur);
            draw_sprite(buffer,compteur[score1],xcompteur+2*(compteur[0]->w),ycompteur);
            textprintf_ex(buffer, font, 10, 10, makecol(255, 255, 255), -1, "score: %d", score);
            blit(buffer,screen,0,0,0,0,WIDTH,HEIGHT);
            if (vitesse<1){
                vitesse=1;
            }
            rest(vitesse); // Pause de 10 ms pour rafraîchir l'écran
        }
        while (!key[KEY_ENTER]) {
            draw_sprite(buffer,enterkey,xenter,yenter);
            stop_sample(musique);
            sprintf(message,"Perdu enculé");
            joueurs[tour].score_guitare[joueurs[tour].nb_essaie_guitare]=score;
            textout_centre_ex(buffer, font, message, WIDTH / 2, HEIGHT / 2, makecol(255, 0, 0), -1);
            blit(buffer,screen,0,0,0,0,WIDTH,HEIGHT);
            rest(100); // Pause de 10 ms pour rafraîchir l'écran
        }
        joueurs[tour].nb_essaie_guitare+=1;
    }
    rest(150); // Pause de 10 ms pour rafraîchir l'écran
    clear_bitmap(buffer);
    clear_to_color(buffer, makecol(255, 255, 255)); // Effacer l'écran en blanc
    animation_guitarEnd();
    rest(150); // Pause de 10 ms pour rafraîchir l'écran
}