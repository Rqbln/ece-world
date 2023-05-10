#include "Parc.h"

//Structure pour les joueurs

void parc2(){
    BITMAP *buffer2;
    BITMAP *bulle[2];
    bulle[0] = load_bitmap("../Parc/imagepnj/bullegauche.bmp", NULL);
    bulle[1] = load_bitmap("../Parc/imagepnj/bulledroite.bmp", NULL);
    BITMAP *parchemin = load_bitmap("../Parc/imagepnj/parchemin.bmp", NULL);

    BITMAP *buffer;
    BITMAP *pacman[grille][action][posirang];
    BITMAP *porte[4];
    BITMAP *portail[12];
    BITMAP *fond = load_bitmap("../Parc/image/fond/fondplage1.bmp", NULL);
    BITMAP *fondmap = load_bitmap("../Parc/image/fond/mapfond2.bmp", NULL);
    BITMAP *bitcoin[8];
    BITMAP *cheval[13];
    BITMAP *hippodrome = load_bitmap("../Parc/image/batiment/hippodrome2.bmp", NULL);  //image des attractions/mini-jeux
    BITMAP *guitar = load_bitmap("../Parc/image/batiment/concert2.bmp", NULL);
    BITMAP *casino = load_bitmap("../Parc/image/batiment/casino0.bmp", NULL);
    BITMAP *river = load_bitmap("../Parc/image/batiment/lac1.bmp", NULL);
    BITMAP *serpent = load_bitmap("../Parc/image/batiment/river0.bmp", NULL);
    BITMAP *tirballon = load_bitmap("../Parc/image/batiment/futuroscope0.bmp", NULL);
    BITMAP *labyrinthe = load_bitmap("../Parc/image/batiment/labyrinthe0.bmp", NULL);
    BITMAP *taupe = load_bitmap("../Parc/image/batiment/cirque0.bmp", NULL);
    BITMAP *canard = load_bitmap("../Parc/image/batiment/parc1.bmp", NULL);

    BITMAP *barbare[2];
    barbare[0] = load_bitmap("../Parc/image/pnjbarbare/barbare0.bmp", NULL);
    //barbare[0]=load_bitmap("../Parc/imagepnj/perso0/action0/0.bmp",NULL);
    //barbare[1]=load_bitmap("../Parc/imagepnj/perso1/action0/0.bmp",NULL);
    barbare[1] = load_bitmap("../Parc/image/pnjbarbare/barbare1.bmp", NULL);
    int xbarbare[2];
    int ybarbare[2];
    xbarbare[0] = WIDTH - (barbare[0]->w);
    xbarbare[1] = 0;
    ybarbare[0] = HEIGHT - (barbare[0]->h);
    ybarbare[1] = HEIGHT - (barbare[1]->h);

    SAMPLE *sound[nbMusique];
    SAMPLE *effet[2];
    SAMPLE *ambiance = load_wav("../Parc/musique/ambiance.wav");

    int ximgfond = -4080+WIDTH;  //coordonnée de l image de fond-4200+WIDTH
    int yimgfond= -2640 +HEIGHT;//-2700 +HEIGHT

    int xserpent = ximgfond + 1700; //coordonnée des mini-jeux (ximgfond + coordonnée paint)
    int yserpent = yimgfond + 950;
    int xguitar = ximgfond + 2260;
    int yguitar = yimgfond + 510;
    int xriver = ximgfond + 2310;
    int yriver = yimgfond + 2020;
    int xcasino = ximgfond + 2680;
    int ycasino = yimgfond + 1910;
    int xhippodrome = ximgfond + 2463;
    int yhippodrome = yimgfond + 1236;
    int xtir = ximgfond + 2000;
    int ytir = yimgfond + 1510;
    int xlabyrinthe = ximgfond + 1400;
    int ylabyrinthe = yimgfond + 1010;
    int xtaupe = ximgfond + 1000;
    int ytaupe = yimgfond + 1510;
    int xcanard = ximgfond + 1940;
    int ycanard = yimgfond + 2100;
    int xcheval[nbcheval];
    int ycheval[nbcheval];

    int xporte = ximgfond + 2000;
    int yporte = yimgfond + 950;
    int posx = 0; //position des sprite du personnage
    int actionperso = 0;
    int xbitcoin = 0;
    int ybitcoin = 0;
    int posbitcoin = 0;

    int dx = 15;//vitesse
    int dy = 8;
    int xcenter;//centre du personnage
    int ycenter;
    int order = 0;//position des sprite de la porte
    int r = 0, v = 0, b = 255; //couleur RGB
    int end = 0;//condition de fin
    int musique = 1;
    int musiquealeatoire;
    char tabporte[80];//tableau nom d image
    char nomDeFichier[80];
    char text_input[128] = {0}; // variable pour stocker la saisie clavier
    int stop = 0;

    int poscheval = 0;
    int cmpt = 0;
    int cmp = 0;

    int buffersizew = WIDTH / 6;
    int buffersizeh = HEIGHT / 6;
    int posxbuff2 = (WIDTH / 2) - (buffersizew / 2);//WIDTH/2
    int posybuff2 = (HEIGHT / 2) - (buffersizeh / 2);//HEIGHT/2
    t_joueurs joueurs [NB_JOUEURS];
    char nomjoueur[2][20];
    // Initialisation de la fonction rand() avec la fonction srand()
    srand(time(NULL));
    //Verifie si les image sont bien la
    for (int j = 0; j < 4; j++) {
        sprintf(tabporte, "../Parc/image/porte/portEnd%d.bmp", j);
        porte[j] = load_bitmap(tabporte, NULL);
        if (!porte[j]) {
            allegro_message("../image/porte/portEnd%d.bmp", j);
            exit(EXIT_FAILURE);
        }
    }
    for (int j = 0; j < 12; j++) {
        sprintf(tabporte, "../Parc/image/portail/%d.bmp", j);
        portail[j] = load_bitmap(tabporte, NULL);
        if (!portail[j]) {
            allegro_message("../image/portail/%d.bmp", j);
            exit(EXIT_FAILURE);
        }
    }
    for (int j = 0; j < 8; j++) {
        sprintf(tabporte, "../Parc/image/bitcoin/bitcoin%d.bmp", j);
        bitcoin[j] = load_bitmap(tabporte, NULL);
        if (!bitcoin[j]) {
            allegro_message("../image/bitcoin/bitcoin%d.bmp", j);
            exit(EXIT_FAILURE);
        }
    }
    for (int i = 0; i < nbcheval; i++) {
        xcheval[i] = ximgfond + 2670 - i * 21;
        ycheval[i] = yimgfond + 1305 + i * 9;
    }
    for (int i = 0; i < 12; i++) {
        sprintf(nomDeFichier, "../Games/Course_Chevaux/image/cheval%d (Personnalisé).bmp", i);
        cheval[i] = load_bitmap(nomDeFichier, NULL);
        if (!cheval[i]) {
            allegro_message("../Games/Course_Chevaux/image/cheval%d.bmp", i);
            exit(EXIT_FAILURE);
        }
    }
    for (int i = 0; i < 2; i++) {
        sprintf(nomDeFichier, "../Parc/musique/musiquebarbare%d.wav", i);
        effet[i] = load_wav(nomDeFichier);
        if (!effet[i]) {
            allegro_message("../musiquebarbare%d.wav", i);
            exit(EXIT_FAILURE);
        }
    }
    for (int i = 0; i < nbMusique; i++) {
        sprintf(nomDeFichier, "../Parc/musique/musique%d.wav", i);
        sound[i] = load_wav(nomDeFichier);
        if (!sound[i]) {
            allegro_message("../musique%d.wav", i);
            exit(EXIT_FAILURE);
        }
    }
    for (int g = 0; g < grille; ++g) {
        for (int a = 0; a < action; ++a) {
            for (int i = 0; i < posirang; i++) {
                sprintf(nomDeFichier, "../Parc/imagepnj/perso%d/action%d/%d.bmp", g, a, i);
                pacman[g][a][i] = load_bitmap(nomDeFichier, NULL);
                if (!pacman[g][a][i]) {
                    allegro_message("../image/batiment/perso%d/action%d/%d.bmp", g, a, i);
                    exit(EXIT_FAILURE);
                }
            }
        }
    }
    int xPacman = (WIDTH / 2) - (pacman[0][0][0]->w) / 2;
    int yPacman = (HEIGHT / 2) - (pacman[0][0][0]->h) / 2;
    int xportail = xPacman - (portail[0]->w) / 2;
    int yportail = yPacman - (portail[0]->h) / 2;
    int xcoordonnee;
    int ycoordonnee;


    buffer = create_bitmap(WIDTH, HEIGHT);
    buffer2 = create_bitmap(buffersizew, buffersizeh);

/////////////////////////////////////////////////////////////////////////////////////


    while (!key[KEY_ESC] && end == 0) {  //boucle principale
        if (musique == 1) {
            musiquealeatoire = rand() % nbMusique;
            play_sample(sound[musiquealeatoire], 255, 128, 1000, 1);
            //allegro_message("../image/musique%d.wav",musiquealeatoire);
            musique = 0;
        }

        xcenter = pacman[0][0][1]->w / 2;
        ycenter = pacman[0][0][1]->w / 2;
        xcoordonnee = -(ximgfond-xPacman-pacman[0][0][0]->w);
        ycoordonnee = -(yimgfond-yPacman-pacman[0][0][0]->h);
        draw_sprite(buffer, fond, ximgfond, yimgfond);
        int pixel_color = getpixel(fond, xcoordonnee, ycoordonnee);
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
        draw_sprite(buffer, fondmap, ximgfond, yimgfond);
        //draw_sprite(buffer, fond, ximgfond, yimgfond);
        textprintf_ex(buffer, font, 500, 10, makecol(255, 255, 255), -1, "red: %d, vert: %d, blu: %d", pixel_r, pixel_v,pixel_b);
        draw_sprite(buffer, porte[order], xporte, yporte);
        //draw_sprite(buffer,hippodrome,xhippodrome,yhippodrome);
        draw_sprite(buffer, tirballon, xtir, ytir);
        draw_sprite(buffer, labyrinthe, xlabyrinthe, ylabyrinthe);
        draw_sprite(buffer, canard, xcanard, ycanard);
        draw_sprite(buffer, taupe, xtaupe, ytaupe);
        draw_sprite(buffer, guitar, xguitar, yguitar);
        draw_sprite(buffer, casino, xcasino, ycasino);
        draw_sprite(buffer, river, xriver, yriver);
        draw_sprite(buffer, serpent, xserpent, yserpent);
        draw_sprite(buffer, bitcoin[posbitcoin], xbitcoin, ybitcoin);
        draw_sprite(buffer, portail[posbitcoin], xportail, yportail);

        for (int i = 0; i < nbcheval; ++i) {
            if (cmpt >= 280) {
                cmpt = 0;
                cmp += 1;
                if (cmp >= 2) {
                    cmp = 0;
                }
            }
            cmpt += 1;
            if (cmp == 0) {
                xcheval[i] += dx / 5;
                ycheval[i] += dy / 4;
                draw_sprite(buffer, cheval[poscheval], xcheval[i], ycheval[i]);
            } else {
                xcheval[i] -= dx / 5;
                ycheval[i] -= dy / 4;
                draw_sprite_h_flip(buffer, cheval[poscheval], xcheval[i], ycheval[i]);
            }
        }
        poscheval += 1;
        if (poscheval >= 12) {
            poscheval = 0;
        }
        posbitcoin += 1;
        if (posbitcoin >= 8) {
            posbitcoin = 0;
        }
        //collision porte end
        if (xPacman <= (xporte + porte[1]->w) && xporte <= (xPacman + pacman[0][0][1]->w) && yPacman <= (yporte + porte[1]->h) && yporte <= (yPacman + pacman[0][0][1]->h)){
            order++;
            if (order > 3) {
                end = 1;
            }
            // Collision détectée !
            textout_centre_ex(buffer, font, "Collision !", WIDTH / 2, HEIGHT / 2, makecol(255, 0, 0), -1);
        }
        //collision activité hippodrome
        if (xPacman <= (xhippodrome + (hippodrome->w)/2) && (xhippodrome + (hippodrome->w)/2) <= (xPacman + pacman[0][0][1]->w) && yPacman <= (yhippodrome) && (yhippodrome) <= (yPacman + pacman[0][0][1]->h)){
            stop_sample(sound[musiquealeatoire]);
            pari();
            anim_horse();
            musique = 1;
            yguitar -= pacman[0][0][1]->h;
            yserpent -= pacman[0][0][1]->h;
            yriver -= pacman[0][0][1]->h;
            ycasino -= pacman[0][0][1]->h;
            yhippodrome -= pacman[0][0][1]->h;
            yporte -= pacman[0][0][1]->h;
            yimgfond -= pacman[0][0][1]->h;
            ytir -= pacman[0][0][1]->h;
            ylabyrinthe -= pacman[0][0][1]->h;
            ytaupe -= pacman[0][0][1]->h;
            ycanard -= pacman[0][0][1]->h;
            yportail -= pacman[0][0][1]->h;
            for (int i = 0; i < nbcheval; i++) {
                xcheval[i] = ximgfond + 2670 - i * 21;
                ycheval[i] = yimgfond + 1305 + i * 9;
            }
            cmpt=0;
            cmp=0;
            // Collision détectée !
            textout_centre_ex(buffer, font, "Collision !", WIDTH/2, HEIGHT/2, makecol(255, 0, 0), -1);
        }
        if (xPacman <= (xtir + (tirballon->w)/2) && (xtir + (tirballon->w)/2) <= (xPacman + pacman[0][0][1]->w) && yPacman <= (ytir) && (ytir) <= (yPacman + pacman[0][0][1]->h)){
            shoot();
            stop_sample(sound[musiquealeatoire]);
            musique = 1;
            yguitar -= pacman[0][0][1]->h;
            yserpent -= pacman[0][0][1]->h;
            yriver -= pacman[0][0][1]->h;
            ycasino -= pacman[0][0][1]->h;
            yhippodrome -= pacman[0][0][1]->h;
            yporte -= pacman[0][0][1]->h;
            yimgfond -= pacman[0][0][1]->h;
            ytir -= pacman[0][0][1]->h;
            ylabyrinthe -= pacman[0][0][1]->h;
            ytaupe -= pacman[0][0][1]->h;
            ycanard -= pacman[0][0][1]->h;
            yportail -= pacman[0][0][1]->h;
            for (int i = 0; i < nbcheval; i++) {
                xcheval[i] = ximgfond + 2670 - i * 21;
                ycheval[i] = yimgfond + 1305 + i * 9;
            }
            cmpt = 0;
            cmp = 0;
            // Collision détectée !
            textout_centre_ex(buffer, font, "Collision !", WIDTH / 2, HEIGHT / 2, makecol(255, 0, 0), -1);
        }
        if (xPacman <= (xlabyrinthe + (labyrinthe->w)/2) && (xlabyrinthe + (labyrinthe->w)/2) <= (xPacman + pacman[0][0][1]->w) && yPacman <= (ylabyrinthe) && (ylabyrinthe) <= (yPacman + pacman[0][0][1]->h)){
            stop_sample(sound[musiquealeatoire]);
            pari();
            anim_horse();
            musique = 1;
            yguitar -= pacman[0][0][1]->h;
            yserpent -= pacman[0][0][1]->h;
            yriver -= pacman[0][0][1]->h;
            ycasino -= pacman[0][0][1]->h;
            yhippodrome -= pacman[0][0][1]->h;
            yporte -= pacman[0][0][1]->h;
            yimgfond -= pacman[0][0][1]->h;
            ytir -= pacman[0][0][1]->h;
            ylabyrinthe -= pacman[0][0][1]->h;
            ytaupe -= pacman[0][0][1]->h;
            ycanard -= pacman[0][0][1]->h;
            yportail -= pacman[0][0][1]->h;
            for (int i = 0; i < nbcheval; i++) {
                xcheval[i] = ximgfond + 2670 - i * 21;
                ycheval[i] = yimgfond + 1305 + i * 9;
            }
            cmpt = 0;
            cmp = 0;
            // Collision détectée !
            textout_centre_ex(buffer, font, "Collision !", WIDTH / 2, HEIGHT / 2, makecol(255, 0, 0), -1);
        }
        if (xPacman <= (xcanard + (canard->w)/2) && (xcanard + (canard->w)/2) <= (xPacman + pacman[0][0][1]->w) && yPacman <= (ycanard) && (ycanard) <= (yPacman + pacman[0][0][1]->h)){
            stop_sample(sound[musiquealeatoire]);
            ducky();
            musique = 1;
            yguitar -= pacman[0][0][1]->h;
            yserpent -= pacman[0][0][1]->h;
            yriver -= pacman[0][0][1]->h;
            ycasino -= pacman[0][0][1]->h;
            yhippodrome -= pacman[0][0][1]->h;
            yporte -= pacman[0][0][1]->h;
            yimgfond -= pacman[0][0][1]->h;
            ytir -= pacman[0][0][1]->h;
            ylabyrinthe -= pacman[0][0][1]->h;
            ytaupe -= pacman[0][0][1]->h;
            ycanard -= pacman[0][0][1]->h;
            yportail -= pacman[0][0][1]->h;
            for (int i = 0; i < nbcheval; i++) {
                xcheval[i] = ximgfond + 2670 - i * 21;
                ycheval[i] = yimgfond + 1305 + i * 9;
            }
            cmpt = 0;
            cmp = 0;
            // Collision détectée !
            textout_centre_ex(buffer, font, "Collision !", WIDTH / 2, HEIGHT / 2, makecol(255, 0, 0), -1);
        }
        if (xPacman <= (xtaupe + (taupe->w) / 2) && (xtaupe + (taupe->w) / 2) <= (xPacman + pacman[0][0][1]->w) &&
            yPacman <= (ytaupe) && (ytaupe) <= (yPacman + pacman[0][0][1]->h)) {
            stop_sample(sound[musiquealeatoire]);
            jeu_taupe();
            musique = 1;
            yguitar -= pacman[0][0][1]->h;
            yserpent -= pacman[0][0][1]->h;
            yriver -= pacman[0][0][1]->h;
            ycasino -= pacman[0][0][1]->h;
            yhippodrome -= pacman[0][0][1]->h;
            yporte -= pacman[0][0][1]->h;
            yimgfond -= pacman[0][0][1]->h;
            ytir -= pacman[0][0][1]->h;
            ylabyrinthe -= pacman[0][0][1]->h;
            ytaupe -= pacman[0][0][1]->h;
            ycanard -= pacman[0][0][1]->h;
            yportail -= pacman[0][0][1]->h;
            for (int i = 0; i < nbcheval; i++) {
                xcheval[i] = ximgfond + 2670 - i * 21;
                ycheval[i] = yimgfond + 1305 + i * 9;
            }
            cmpt = 0;
            cmp = 0;
            // Collision détectée !
            textout_centre_ex(buffer, font, "Collision !", WIDTH / 2, HEIGHT / 2, makecol(255, 0, 0), -1);
        }
        if (xPacman <= (xguitar + (guitar->w)/2) && (xguitar + (guitar->w)/2) <= (xPacman + pacman[0][0][1]->w) && yPacman <= (yguitar) && (yguitar) <= (yPacman + pacman[0][0][1]->h)){
            stop_sample(sound[musiquealeatoire]);
            playguitar();
            musique = 1;
            yserpent -= pacman[0][0][1]->h;
            yriver -= pacman[0][0][1]->h;
            ycasino -= pacman[0][0][1]->h;
            yguitar -= pacman[0][0][1]->h;
            yhippodrome -= pacman[0][0][1]->h;
            yporte -= pacman[0][0][1]->h;
            yimgfond -= pacman[0][0][1]->h;
            ytir -= pacman[0][0][1]->h;
            ylabyrinthe -= pacman[0][0][1]->h;
            ytaupe -= pacman[0][0][1]->h;
            ycanard -= pacman[0][0][1]->h;
            yportail -= pacman[0][0][1]->h;
            for (int i = 0; i < nbcheval; i++) {
                xcheval[i] = ximgfond + 2670 - i * 21;
                ycheval[i] = yimgfond + 1305 + i * 9;
            }
            cmpt = 0;
            cmp = 0;
            // Collision détectée !
            textout_centre_ex(buffer, font, "Collision !", WIDTH / 2, HEIGHT / 2, makecol(255, 0, 0), -1);
        }
        if (xPacman <= (xcasino + (casino->w)/2) && (xcasino + (casino->w)/2) <= (xPacman + pacman[0][0][1]->w) && yPacman <= (ycasino) && (ycasino) <= (yPacman + pacman[0][0][1]->h)){
            stop_sample(sound[musiquealeatoire]);
            jackpot();
            musique = 1;
            yguitar -= pacman[0][0][1]->h;
            yserpent -= pacman[0][0][1]->h;
            yriver -= pacman[0][0][1]->h;
            ycasino -= pacman[0][0][1]->h;
            yhippodrome -= pacman[0][0][1]->h;
            yporte -= pacman[0][0][1]->h;
            yimgfond -= pacman[0][0][1]->h;
            ytir -= pacman[0][0][1]->h;
            ylabyrinthe -= pacman[0][0][1]->h;
            ytaupe -= pacman[0][0][1]->h;
            ycanard -= pacman[0][0][1]->h;
            yportail -= pacman[0][0][1]->h;
            for (int i = 0; i < nbcheval; i++) {
                xcheval[i] = ximgfond + 2670 - i * 21;
                ycheval[i] = yimgfond + 1305 + i * 9;
            }
            cmpt = 0;
            cmp = 0;
            // Collision détectée !
            textout_centre_ex(buffer, font, "Collision !", WIDTH / 2, HEIGHT / 2, makecol(255, 0, 0), -1);
        }
        if (xPacman <= (xriver + (river->w)/2) && (xriver + (river->w)/2) <= (xPacman + pacman[0][0][1]->w) && yPacman <= (yriver) && (yriver) <= (yPacman + pacman[0][0][1]->h)){
            stop_sample(sound[musiquealeatoire]);
            //playguitar();
            musique = 1;
            yguitar -= pacman[0][0][1]->h;
            yserpent -= pacman[0][0][1]->h;
            yriver -= pacman[0][0][1]->h;
            ycasino -= pacman[0][0][1]->h;
            yhippodrome -= pacman[0][0][1]->h;
            yporte -= pacman[0][0][1]->h;
            yimgfond -= pacman[0][0][1]->h;
            ytir -= pacman[0][0][1]->h;
            ylabyrinthe -= pacman[0][0][1]->h;
            ytaupe -= pacman[0][0][1]->h;
            ycanard -= pacman[0][0][1]->h;
            yportail -= pacman[0][0][1]->h;
            for (int i = 0; i < nbcheval; i++) {
                xcheval[i] = ximgfond + 2670 - i * 21;
                ycheval[i] = yimgfond + 1305 + i * 9;
            }
            cmpt = 0;
            cmp = 0;
            // Collision détectée !
            textout_centre_ex(buffer, font, "Collision !", WIDTH / 2, HEIGHT / 2, makecol(255, 0, 0), -1);
        }
        if (xPacman <= (xserpent + (serpent->w)/2) && (xserpent + (serpent->w)/2) <= (xPacman + pacman[0][0][1]->w) && yPacman <= (yserpent) && (yserpent) <= (yPacman + pacman[0][0][1]->h)){
            stop_sample(sound[musiquealeatoire]);
            snake();
            musique = 1;
            yguitar -= pacman[0][0][1]->h;
            yserpent -= pacman[0][0][1]->h;
            yriver -= pacman[0][0][1]->h;
            ycasino -= pacman[0][0][1]->h;
            yhippodrome -= pacman[0][0][1]->h;
            yporte -= pacman[0][0][1]->h;
            yimgfond -= pacman[0][0][1]->h;
            ytir -= pacman[0][0][1]->h;
            ylabyrinthe -= pacman[0][0][1]->h;
            ytaupe -= pacman[0][0][1]->h;
            ycanard -= pacman[0][0][1]->h;
            yportail -= pacman[0][0][1]->h;
            for (int i = 0; i < nbcheval; i++) {
                xcheval[i] = ximgfond + 2670 - i * 21;
                ycheval[i] = yimgfond + 1305 + i * 9;
            }
            cmpt = 0;
            cmp = 0;
            // Collision détectée !
            textout_centre_ex(buffer, font, "Collision !", WIDTH / 2, HEIGHT / 2, makecol(255, 0, 0), -1);
        }
        if (key[KEY_DOWN] || key[KEY_UP] || key[KEY_LEFT] || key[KEY_RIGHT]) {
            if (key[KEY_RIGHT] && ((WIDTH + 1) < (fondmap->w + ximgfond))) {
                if (key[KEY_UP] && yimgfond < 0) {
                    actionperso = 13;
                    yguitar += dy;
                    yserpent += dy;
                    yriver += dy;
                    ycasino += dy;
                    yhippodrome += dy;
                    yporte += dy;
                    yimgfond += dy;
                    ytir += dy;
                    ylabyrinthe += dy;
                    ytaupe += dy;
                    ycanard += dy;
                    yportail += dy;
                    for (int i = 0; i < nbcheval; ++i) {
                        ycheval[i] += dy;
                    }
                } else if (key[KEY_DOWN] && ((HEIGHT + 1) < (fondmap->h + yimgfond))) {
                    actionperso = 5;
                    yguitar -= dy;
                    yserpent -= dy;
                    yriver -= dy;
                    ycasino -= dy;
                    yhippodrome -= dy;
                    yporte -= dy;
                    yimgfond -= dy;
                    ytir -= dy;
                    ylabyrinthe -= dy;
                    ytaupe -= dy;
                    ycanard -= dy;
                    yportail -= dy;
                    for (int i = 0; i < nbcheval; ++i) {
                        ycheval[i] -= dy;
                    }
                } else {
                    actionperso = 8;
                }
                posx++;
                xguitar -= dx;
                xserpent -= dx;
                xriver -= dx;
                xcasino -= dx;
                xhippodrome -= dx;
                xporte -= dx;
                ximgfond -= dx;
                xtir -= dx;
                xlabyrinthe -= dx;
                xtaupe -= dx;
                xcanard -= dx;
                xportail -= dx;
                for (int i = 0; i < nbcheval; ++i) {
                    xcheval[i] -= dx;
                }
                if (posx > 3) {
                    posx = 0;
                }
            } else if (key[KEY_LEFT] && ximgfond < 0) {
                if (key[KEY_UP] && yimgfond < 0) {
                    actionperso = 9;
                    yguitar += dy;
                    yserpent += dy;
                    yriver += dy;
                    ycasino += dy;
                    yhippodrome += dy;
                    yporte += dy;
                    yimgfond += dy;
                    ytir += dy;
                    ylabyrinthe += dy;
                    ytaupe += dy;
                    ycanard += dy;
                    yportail += dy;
                    for (int i = 0; i < nbcheval; ++i) {
                        ycheval[i] += dy;
                    }
                } else if (key[KEY_DOWN] && ((HEIGHT + 1) < (fondmap->h + yimgfond))) {
                    actionperso = 1;
                    yguitar -= dy;
                    yserpent -= dy;
                    yriver -= dy;
                    ycasino -= dy;
                    yhippodrome -= dy;
                    yporte -= dy;
                    yimgfond -= dy;
                    ytir -= dy;
                    ylabyrinthe -= dy;
                    ytaupe -= dy;
                    ycanard -= dy;
                    yportail -= dy;
                    for (int i = 0; i < nbcheval; ++i) {
                        ycheval[i] -= dy;
                    }
                } else {
                    actionperso = 4;
                }
                posx++;
                xguitar += dx;
                xserpent += dx;
                xriver += dx;
                xcasino += dx;
                xhippodrome += dx;
                xporte += dx;
                ximgfond += dx;
                xtir += dx;
                xlabyrinthe += dx;
                xtaupe += dx;
                xcanard += dx;
                xportail += dx;
                for (int i = 0; i < nbcheval; ++i) {
                    xcheval[i] += dx;
                }
                if (xPacman > WIDTH) {
                    xPacman = 0;
                }
                if (posx > 3) {
                    posx = 0;
                }
            } else if (key[KEY_UP] && yimgfond < 0) {
                actionperso = 12;
                posx++;
                yguitar += dy;
                yserpent += dy;
                yriver += dy;
                ycasino += dy;
                yhippodrome += dy;
                yporte += dy;
                yimgfond += dy;
                ytir += dy;
                ylabyrinthe += dy;
                ytaupe += dy;
                ycanard += dy;
                yportail += dy;
                for (int i = 0; i < nbcheval; ++i) {
                    ycheval[i] += dy;
                }
                if (posx > 3) {
                    posx = 0;
                }
            } else if (key[KEY_DOWN] && ((HEIGHT + 1) < (fondmap->h + yimgfond))) {
                actionperso = 0;
                posx++;
                yguitar -= dy;
                yserpent -= dy;
                yriver -= dy;
                ycasino -= dy;
                yhippodrome -= dy;
                yporte -= dy;
                yimgfond -= dy;
                ytir -= dy;
                ylabyrinthe -= dy;
                ytaupe -= dy;
                ycanard -= dy;
                yportail -= dy;
                for (int i = 0; i < nbcheval; ++i) {
                    ycheval[i] -= dy;
                }
                if (posx > 3) {
                    posx = 0;
                }
            }
            draw_sprite(buffer, pacman[0][actionperso][posx], xPacman, yPacman);
        } else {
            draw_sprite(buffer, pacman[0][0][0], xPacman, yPacman);
        }
        if (stop == 0) {
            stop_sample(sound[musiquealeatoire]);
            play_sample(ambiance, 255, 128, 1000, 1);
            for (int i = 0; i < 2; ++i) {
                play_sample(effet[i], 255, 128, 1000, 0);
                while (!key[KEY_ENTER] && stop == 0) {
                    clear_bitmap(buffer2);
                    clear_to_color(buffer2, makecol(253, 208, 146)); // Effacer l'écran en blanc
                    // Afficher la zone de saisie clavier
                    textout_centre_ex(buffer2, font, "entrez votre nom : ", buffersizew/2, 3, makecol(0, 0, 0), -1);
                    textout_centre_ex(buffer2, font, text_input, buffersizew/2, buffersizeh/2, makecol(0, 0, 0), -1);
                    draw_sprite(buffer,barbare[i],xbarbare[i],ybarbare[i]);
                    // Lire la saisie clavier
                    //draw_sprite(buffer, bulle[i], (xbarbare[i] + barbare[i]->w), ybarbare[i]);

                    blit(buffer, screen, 0, 0, 0, 0, WIDTH, HEIGHT);
                    while (keypressed()) {
                        int cle = readkey();
                        if (cle >> 8 == KEY_BACKSPACE && strlen(text_input) > 0) {
                            text_input[strlen(text_input) - 1] = '\0';
                        } else if (strlen(text_input) < 128 && (cle & 0xFF) >= ' ' && (cle & 0xFF) <= '~') {
                            text_input[strlen(text_input)] = cle & 0xFF;
                        }
                    }
                    // Rafraîchir l'écran
                    vsync();
                    if(key[KEY_RIGHT]){

                    }

                    draw_sprite(buffer, parchemin, ((WIDTH/2)-(parchemin->w)/2), 0);
                    draw_sprite(buffer, pacman[0][0][0], ((WIDTH/2)-pacman[0][0][0]->w), HEIGHT-200);
                    blit(buffer2, buffer, 0, 0, posxbuff2, posybuff2, WIDTH, HEIGHT);
                }
                //sprintf(nomjoueur[i], "%s", text_input);
                sprintf(joueurs[i].nom,"%s",text_input);
                memset(text_input, '\0', sizeof(text_input)); //effacer tout le tableau
                rest(300);
                stop_sample(effet[i]);
            }
            musique=1;
        }
        stop_sample(ambiance);
        //textprintf_ex(buffer, font, 200, 100, makecol(255, 255, 255), -1, "%s", nomjoueur[0]);
        //textprintf_ex(buffer, font, 1700, 100, makecol(255, 255, 255), -1, "%s", nomjoueur[1]);
        stop = 1;
        blit(buffer, screen, 0, 0, 0, 0, WIDTH, HEIGHT);
        textprintf_ex(buffer, font, 200, 100, makecol(255, 255, 255), -1, "%s", joueurs[0].nom);
        textprintf_ex(buffer, font, 1700, 100, makecol(255, 255, 255), -1, "%s", joueurs[1].nom);
        stop=1;
        blit(buffer,screen,0,0,0,0,WIDTH,HEIGHT);
        if (key[KEY_SPACE]) {
            rest(10);
        } else
            rest(60); // Pause de 10 ms pour rafraîchir l'écran
    }
}
