#include "Parc.h"

void park(){
    int isPaused = 0; // Variable pour indiquer si le jeu est en pause
    int buffersizew = WIDTH / 6;
    int buffersizeh = HEIGHT / 8;
    BITMAP *buffer2= create_bitmap(buffersizew, buffersizeh);
    BITMAP *parchemin = load_bitmap("../Parc/imagepnj/parchemin2.bmp", NULL);
    BITMAP *buffer= create_bitmap(WIDTH, HEIGHT);
    BITMAP *pacman[grille][action][posirang];
    BITMAP *porte[4];
    BITMAP *chateau = load_bitmap("../Parc/image/porte/chateauEnd1.bmp", NULL);
    BITMAP *barbare[2];
    //BITMAP *portail[12];
    BITMAP *fond = load_bitmap("../Parc/image/fond/fondplage3.bmp", NULL);
    BITMAP *fondmap = load_bitmap("../Parc/image/fond/mapfond3.bmp", NULL);
    BITMAP *bitcoin[8];
    BITMAP *cheval[13];
    BITMAP *hippodrome = load_bitmap("../Parc/image/batiment/hippodrome2.bmp", NULL);  //image des attractions/mini-jeux
    BITMAP *guitar = load_bitmap("../Parc/image/batiment/concert2.bmp", NULL);
    BITMAP *casino = load_bitmap("../Parc/image/batiment/casino0.bmp", NULL);
    BITMAP *river1 = load_bitmap("../Parc/image/batiment/lac1.bmp", NULL);
    BITMAP *serpent = load_bitmap("../Parc/image/batiment/river0.bmp", NULL);
    BITMAP *tirballon = load_bitmap("../Parc/image/batiment/futuroscope0.bmp", NULL);
    BITMAP *labyrinthe = load_bitmap("../Parc/image/batiment/labyrinthe0.bmp", NULL);
    BITMAP *taupe = load_bitmap("../Parc/image/batiment/cirque0.bmp", NULL);
    BITMAP *canard = load_bitmap("../Parc/image/batiment/parc1.bmp", NULL);
    BITMAP *panneau = load_bitmap("../Parc/image/batiment/telephone0.bmp", NULL);
    BITMAP *enterkey = load_bitmap("../Parc/image/enterkey.bmp", NULL);
    BITMAP *affichageScore = load_bitmap("../Parc/image/affichageScore6.bmp", NULL);
    BITMAP *dragon[4][3];
    BITMAP* scroll = load_bitmap("../Games/Shoot/image/scroll.bmp", NULL);
    BITMAP * fonfin= load_bitmap("../Parc/image/fondfin.bmp", NULL);
    BITMAP * congrats= load_bitmap("../Parc/image/congrats.bmp", NULL);

    BITMAP *lettre[37];//+10 pour les chiffre//police d ecriture

    SAMPLE *clear1 = load_wav("../Games/Shoot/musique/marioclear.wav");
    SAMPLE *sound[nbMusique];
    sound[0] = load_wav("../Parc/musique/GameTrone.wav");//GameTrone  HouseDragon
    SAMPLE *effet[2];
    SAMPLE *ambiance = load_wav("../Parc/musique/ambiance.wav");


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
    srand(time(NULL));
    int ximgfond = -4150+WIDTH;  //coordonnée de l image de fond-4200+WIDTH
    int yimgfond= -2720 +HEIGHT;//-2700 +HEIGHT

    int xserpent = ximgfond + 1700; //coordonnée des mini-jeux (ximgfond + coordonnée paint)
    int yserpent = yimgfond + 830;
    int xguitar = ximgfond + 2260;
    int yguitar = yimgfond + 510;
    int xdragon = xguitar;
    int ydragon = yguitar;
    int xdrag = 0;
    int ydrag = 0;
    int posdrag=0;
    int directdrag=0;
    int cmptdrag=0;
    int cmpdrag=0;
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
    int xenter=WIDTH-400;
    int yenter=HEIGHT-80;

    int xpanneau = ximgfond + 3060;
    int ypanneau = yimgfond + 1930;

    int xchateauEnd = ximgfond + 3350;
    int ychateauEnd = yimgfond + 2060;
    int xporte = ((xchateauEnd + (chateau->w)/2));//-((porte[0]->w)/2)
    int yporte = ychateauEnd+ (chateau->h)/2;
    int posx = 0; //position des sprite du personnage
    int posx2 = 0;
    int actionperso = 0;
    int actionperso2 = 0;
    int xperso2=WIDTH/2;
    int yperso2=HEIGHT/2-50;
    int persochoisit=0;
    int tourjoueur=0;
    int tourjoueur2=1;
    int activateperso2=1;

    int vitesseimage=0;
    int xbitcoin = 0;
    int ybitcoin = 0;
    int posbitcoin = 0;

    int numlettre=0;
    int nblettre=40;
    int xlettre;
    int ylettre;
    char message[8][nblettre];
    int activatescore=1;

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
    int selectperso=10;

    int poscheval = 0;
    int cmpt = 0;
    int cmp = 0;

    int posxbuff2 = (WIDTH / 2) - (buffersizew / 2);//WIDTH/2
    int posybuff2 = (HEIGHT / 3) - (buffersizeh / 2);//HEIGHT/2

    char nomjoueur[2][20];
    // Initialisation de la fonction rand() avec la fonction srand()
    srand(time(NULL));
    //Verifie si les image sont bien la

    int yguitarM;
    int yserpentM;
    int yriverM;
    int ycasinoM;
    int yhippodromeM;
    int ychateauEndM;
    int yporteM;
    int yimgfondM;
    int ytirM;
    int ylabyrintheM;
    int ytaupeM;
    int ycanardM;
    int ypanneauM;
    int yperso2M;
    //int yportailM;
    int xguitarM;
    int xserpentM;
    int xriverM;
    int xcasinoM;
    int xhippodromeM;
    int xchateauEndM;
    int xporteM;
    int ximgfondM;
    int xtirM;
    int xlabyrintheM;
    int xtaupeM;
    int xcanardM;
    int xpanneauM;
    //int xportailM;
    int xchevalM[nbCheval];
    int ychevalM[nbCheval];
    int xperso2M;
    //sprite porte de fin
    for (int j = 0; j < 4; j++) {
        sprintf(tabporte, "../Parc/image/porte/portEnd%d.bmp", j);
        porte[j] = load_bitmap(tabporte, NULL);
        if (!porte[j]) {
            allegro_message("../image/porte/portEnd%d.bmp", j);
            exit(EXIT_FAILURE);
        }
    }
    //sprite portail
    /*for (int j = 0; j < 12; j++) {
        sprintf(tabporte, "../Parc/image/portail/%d.bmp", j);
        portail[j] = load_bitmap(tabporte, NULL);
        if (!portail[j]) {
            allegro_message("../image/portail/%d.bmp", j);
            exit(EXIT_FAILURE);
        }
    }*/
    for(int i=0;i<37;i++){ //+10
        if (i<27){
            sprintf(nomDeFichier,"../police/lettre12/%c.bmp",i+97);
        } else{
            sprintf(nomDeFichier,"../police/lettre12/%d.bmp",i-27);
        }
        lettre[i]= load_bitmap(nomDeFichier,NULL);
        if(!lettre[i]){
            allegro_message("../police/lettre12/%c.bmp",i+97);
            exit(EXIT_FAILURE);
        }
    }
    //sprite bitcoin
    for (int j = 0; j < 8; j++) {
        sprintf(tabporte, "../Parc/image/bitcoin/bitcoin%d.bmp", j);
        bitcoin[j] = load_bitmap(tabporte, NULL);
        if (!bitcoin[j]) {
            allegro_message("../image/bitcoin/bitcoin%d.bmp", j);
            exit(EXIT_FAILURE);
        }
    }
    //position chevaux
    for (int i = 0; i < nbcheval; i++) {
        xcheval[i] = ximgfond + 2670 - i * 21;
        ycheval[i] = yimgfond + 1305 + i * 9;
    }
    //sprite mini chevaux
    for (int i = 0; i < 12; i++) {
        sprintf(nomDeFichier, "../Games/Course_Chevaux/image/cheval%d (Personnalisé).bmp", i);
        cheval[i] = load_bitmap(nomDeFichier, NULL);
        if (!cheval[i]) {
            allegro_message("../Games/Course_Chevaux/image/cheval%d.bmp", i);
            exit(EXIT_FAILURE);
        }
    }
    for (int j = 0; j < 4; ++j) {
        for (int i = 0; i < 3; i++) {
            sprintf(nomDeFichier, "../Parc/image/dragon/direction%d/%d.bmp", j, i);
            dragon[j][i] = load_bitmap(nomDeFichier, NULL);
            if (!dragon[j][i]) {
                allegro_message("../Games/image/dragon%d%d.bmp", j, i);
                exit(EXIT_FAILURE);
            }
        }
    }
    //bruit barbare
    for (int i = 0; i < 2; i++) {
        sprintf(nomDeFichier, "../Parc/musique/musiquebarbare%d.wav", i);
        effet[i] = load_wav(nomDeFichier);
        if (!effet[i]) {
            allegro_message("../musiquebarbare%d.wav", i);
            exit(EXIT_FAILURE);
        }
    }
    //musique parc
    /*for (int i = 0; i < nbMusique; i++) {
        sprintf(nomDeFichier, "../Parc/musique/musique%d.wav", i);
        sound[i] = load_wav(nomDeFichier);
        if (!sound[i]) {
            allegro_message("../musique%d.wav", i);
            exit(EXIT_FAILURE);
        }
    }*/
    //sprite perso
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
    //int xportail = xPacman - (portail[0]->w) / 2;
    //int yportail = yPacman - (portail[0]->h) / 2;
    int xcoordonnee;
    int ycoordonnee;
    int ycoordonneeb;

    //buffer = create_bitmap(WIDTH, HEIGHT);
   // buffer2 = create_bitmap(buffersizew, buffersizeh);

/////////////////////////////////////////////////////////////////////////////////////


    while (end == 0) {  //boucle principale
        //choix d une musique aleatoire
        if (musique == 1) {
            musiquealeatoire = rand() % nbMusique;
            play_sample(sound[musiquealeatoire], 255, 128, 1000, 1);
            //allegro_message("../image/musique%d.wav",musiquealeatoire);
            musique = 0;
        }

        xcenter = pacman[0][0][1]->w / 2;
        ycenter = pacman[0][0][1]->w / 2;
        xcoordonnee = -(ximgfond-xPacman-(pacman[0][0][0]->w)/2);
        ycoordonnee = -(yimgfond-yPacman-pacman[0][0][0]->h)-20;
        ycoordonneeb = -(yimgfond-yPacman-(pacman[0][0][0]->h)+50);
        draw_sprite(buffer, fond, ximgfond, yimgfond);
        int pixel_colorb = getpixel(fond, xcoordonnee, ycoordonneeb);
        int pixel_rb = getr(pixel_colorb);
        int pixel_vb = getg(pixel_colorb);
        int pixel_bb = getb(pixel_colorb);
        int pixel_color = getpixel(fond, xcoordonnee, ycoordonnee);
        int pixel_r = getr(pixel_color);
        int pixel_v = getg(pixel_color);
        int pixel_b = getb(pixel_color);
        if ((pixel_r==0 && pixel_v==0 && pixel_b==255)||(pixel_rb==0 && pixel_vb==0 && pixel_bb==255)){
            yguitar=yguitarM;
            yserpent=yserpentM;
            yriver=yriverM;
            ycasino= ycasinoM;
            yhippodrome=yhippodromeM;
            ychateauEnd=ychateauEndM;
            yporte=yporteM;
            yimgfond=yimgfondM;
            ytir=ytirM;
            ylabyrinthe=ylabyrintheM;
            ytaupe=ytaupeM;
            ycanard=ycanardM;
            ypanneau=ypanneauM;
            yperso2=yperso2M;
            //yportail=yportailM;
            xguitar=xguitarM;
            xserpent=xserpentM;
            xriver=xriverM;
            xcasino=xcasinoM;
            xhippodrome=xhippodromeM;
            xchateauEnd=xchateauEndM;
            xporte=xporteM;
            ximgfond=ximgfondM;
            xtir=xtirM;
            xlabyrinthe=xlabyrintheM;
            xtaupe=xtaupeM;
            xcanard=xcanardM;
            xpanneau=xpanneauM;
            xperso2=xperso2M;
            //xportail=xportailM;
            /*for (int i = 0; i < nbcheval; ++i) {
                xcheval[i] = xchevalM[i];
            }
            for (int i = 0; i < nbcheval; ++i) {
                ycheval[i] = ychevalM[i];
            }*/
            for (int i = 0; i < nbcheval; i++) {
                xcheval[i] = ximgfond + 2670 - i * 21;
                ycheval[i] = yimgfond + 1305 + i * 9;
            }
            cmpt=0;
            cmp=0;
        }
        if (pixel_r==0 && pixel_v==255 && pixel_b==0){
            dx=7;
            dy=4;
            vitesseimage=0;
        }
        else {
            dx=20;
            dy=11;
            vitesseimage=1;
        }
        yguitarM=yguitar;
        yserpentM=yserpent;
        yriverM=yriver;
        ycasinoM= ycasino;
        yhippodromeM=yhippodrome;
        ychateauEndM=ychateauEnd;
        yporteM=yporte;
        yimgfondM=yimgfond;
        ytirM=ytir;
        ylabyrintheM=ylabyrinthe;
        ytaupeM=ytaupe;
        ycanardM=ycanard;
        ypanneauM=ypanneau;
        yperso2M=yperso2;
        //yportailM=yportail;
        xguitarM=xguitar;
        xserpentM=xserpent;
        xriverM=xriver;
        xcasinoM=xcasino;
        xhippodromeM=xhippodrome;
        xchateauEndM=xchateauEnd;
        xporteM=xporte;
        ximgfondM=ximgfond;
        xtirM=xtir;
        xlabyrintheM=xlabyrinthe;
        xtaupeM=xtaupe;
        xcanardM=xcanard;
        xpanneauM=xpanneau;
        xperso2M=xperso2;
        //xportailM=xportail;
        for (int i = 0; i < nbcheval; ++i) {
            xchevalM[i] = xcheval[i];
        }
        for (int i = 0; i < nbcheval; ++i) {
            ychevalM[i] = ycheval[i];
        }
        //if (pixel_r >= r - 50 && pixel_r <= r + 50 && pixel_v >= v - 50 && pixel_v <= v + 50 && pixel_b >= b - 50 && pixel_b <= b + 50) {
        /*if (getpixel(buffer, xcenter, ycenter) == makecol(0, 0, 255)) {
            dx=5;
            dy=2;
        }
        else{
            dx=15;
            dy=8;
        }*/
        xdragon = xguitar-30;
        ydragon = yguitar-60;
        clear_bitmap(buffer);
        clear_to_color(buffer, makecol(255, 255, 255)); // Effacer l'écran en blanc
        // Obtenir les coordonnées de la souris
        //draw_sprite(buffer,fond,ximgfond,yimgfond);
        //stretch_blit(fond,buffer,0,0,fond->w,fond->h,0,0,WIDTH,HEIGHT);
        //image de fond qui bouge
        draw_sprite(buffer, fondmap, ximgfond, yimgfond);
        //draw_sprite(buffer, fond, ximgfond, yimgfond);
        //textprintf_ex(buffer, font, 500, 10, makecol(255, 255, 255), -1, "red: %d, vert: %d, blu: %d", pixel_r, pixel_v,pixel_b);
        draw_sprite(buffer, chateau, xchateauEnd, ychateauEnd);
        draw_sprite(buffer, porte[order], xporte, yporte);
        //draw_sprite(buffer,hippodrome,xhippodrome,yhippodrome);
        draw_sprite(buffer, tirballon, xtir, ytir);
        draw_sprite(buffer, labyrinthe, xlabyrinthe, ylabyrinthe);
        draw_sprite(buffer, canard, xcanard, ycanard);
        draw_sprite(buffer, taupe, xtaupe, ytaupe);
        draw_sprite(buffer, guitar, xguitar, yguitar);
        draw_sprite(buffer, casino, xcasino, ycasino);
        draw_sprite(buffer, river1, xriver, yriver);
        draw_sprite(buffer, serpent, xserpent, yserpent);
        draw_sprite(buffer,panneau,xpanneau,ypanneauM);
        if (activateperso2==1){
            draw_sprite(buffer, pacman[joueurs[tourjoueur2].persoChoisi][actionperso2][posx2], xperso2, yperso2);
        }
        if (key[KEY_H]){
            activateperso2++;
            if (activateperso2>=2){
                activateperso2=0;
            }
            rest(200);
        }
        //draw_sprite(buffer,dragon[0][0],xdragon,ydragon);
        //draw_sprite(buffer, portail[posbitcoin], xportail, yportail);

        //gestion dragon

        if (cmptdrag >= 30) {
            cmptdrag = 0;
            cmpdrag += 1;
            if (cmpdrag >= 4) {
                cmpdrag = 0;
            }
        }
        cmptdrag += 1;
        if (cmpdrag == 0) {
            directdrag=0;
            xdrag += 9/3 ;
            ydrag -= 5 ;
            xdragon+=xdrag;
            ydragon+=ydrag;
            draw_sprite(buffer, dragon[directdrag][posdrag], xdragon, ydragon);
        }
        else if(cmpdrag==1){
            directdrag=2;
            xdrag += 9 ;
            ydrag += 5/3;
            xdragon+=xdrag;
            ydragon+=ydrag;
            draw_sprite(buffer, dragon[directdrag][posdrag], xdragon, ydragon);
        }
        else if(cmpdrag==2){
            directdrag=1;
            xdrag -= 9/3;
            ydrag += 5 ;
            xdragon+=xdrag;
            ydragon+=ydrag;
            draw_sprite(buffer, dragon[directdrag][posdrag], xdragon, ydragon);
        }
        else {
            directdrag=3;
            xdrag -= 9 ;
            ydrag -= 5/3;
            xdragon+=xdrag;
            ydragon+=ydrag;
            draw_sprite(buffer, dragon[directdrag][posdrag], xdragon, ydragon);
        }

        posdrag += 1;
        if (posdrag >= 3) {
            posdrag = 0;
        }

        //gestion mini chevaux
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
                xcheval[i] += 15 / 5;
                ycheval[i] += 8 / 4;
                draw_sprite(buffer, cheval[poscheval], xcheval[i], ycheval[i]);
            } else {
                xcheval[i] -= 15 / 5;
                ycheval[i] -= 8 / 4;
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
        //gestion point
        if(key[KEY_J]){
            activatescore++;
            if (activatescore>=2){
                activatescore=0;
            }
            rest(200);
        }
        if(activatescore==1){
            for (int i = 0; i < 2; ++i) {
                draw_sprite(buffer, affichageScore, i*(WIDTH-affichageScore->w), 0);
                draw_sprite(buffer, pacman[joueurs[i].persoChoisi][0][0], (affichageScore->w)+i*(WIDTH-2*(affichageScore->w)-pacman[0][0][0]->w), 0);

                sprintf(message[0],"%s",joueurs[i].nom);
                nblettre = strlen(message[0]);
                for (int j = 0; j < nblettre; ++j) {

                    numlettre = (message[0][j] - '0') - 49;
                    if (numlettre < 0 || numlettre > 25) {
                        if (numlettre > -33 && numlettre < -6) {
                            numlettre += 32;
                        } else if (numlettre > -50 && numlettre < -39) {
                            numlettre += 49 + 27;//26+49 pour les chiffre on remplace 49 par ca
                        } else {
                            numlettre = 26;
                        }
                    }
                    ylettre = 10;
                    xlettre = j*(lettre[0]->w)+55+(i*(WIDTH-545));
                    draw_sprite(buffer, lettre[numlettre], xlettre, ylettre);
                }
                for (int j = 0; j < joueurs[0].nbTickets; ++j) {//joueurs[0].nbTickets
                    draw_sprite(buffer, bitcoin[posbitcoin],  (j*50 +25+(i*(WIDTH-545))), 42);
                    //draw_sprite(buffer, bitcoin[posbitcoin],  (j*50 +85+(i*(WIDTH-660))), 45);
                    //draw_sprite(buffer, bitcoin[posbitcoin],  ((-i)*(j*50 +85)+(i*(WIDTH-660))), 45);

                }
                //textprintf_ex(buffer, font, 220+(i*(WIDTH-660)), 20, makecol(0, 0, 0), -1, "%s, bitcoin(s) : %d", joueurs[i].nom, joueurs[i].nbTickets);
                //textprintf_ex(buffer, font, 220+(i*(WIDTH-660)), 20, makecol(0, 0, 0), -1, "%s, bitcoin(s) : %d", joueurs[i].nom, joueurs[i].nbTickets);
            }
        }
        //collision porte end
        if (xPacman <= (xporte + porte[1]->w) && xporte <= (xPacman + pacman[0][0][1]->w) && yPacman <= (yporte + porte[1]->h) && yporte <= (yPacman + pacman[0][0][1]->h)){
            order++;
            if (order > 3) {
                end = 1;
            }
            // Collision détectée !
            //textout_centre_ex(buffer, font, "Collision !", WIDTH / 2, HEIGHT / 2, makecol(255, 0, 0), -1);
        }
        //collision activité hippodrome
        if (xPacman <= (xhippodrome + (hippodrome->w)/2) && (xhippodrome + (hippodrome->w)/2) <= (xPacman + pacman[0][0][1]->w) && yPacman <= (yhippodrome+(hippodrome->h)/2) && (yhippodrome+(hippodrome->h)/2) <= (yPacman + pacman[0][0][1]->h)){
            stop_sample(sound[musiquealeatoire]);
            //pari();
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
            ychateauEnd -= pacman[0][0][1]->h;
            ypanneau -= pacman[0][0][1]->h;
            //yportail -= pacman[0][0][1]->h;
            for (int i = 0; i < nbcheval; i++) {
                xcheval[i] = ximgfond + 2670 - i * 21;
                ycheval[i] = yimgfond + 1305 + i * 9;
            }
            tourjoueur2=tourjoueur;
            tourjoueur+=1;
            if(tourjoueur>=NB_JOUEURS){
                tourjoueur=0;
            }
            cmpt=0;
            cmp=0;
            // Collision détectée !
            //textout_centre_ex(buffer, font, "Collision !", WIDTH/2, HEIGHT/2, makecol(255, 0, 0), -1);
        }
        if (xPacman <= (xtir + (tirballon->w)/2) && (xtir + (tirballon->w)/2) <= (xPacman + pacman[0][0][1]->w) && yPacman <= (ytir+tirballon->h) && (ytir+tirballon->h) <= (yPacman + pacman[0][0][1]->h)){
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
            ychateauEnd -= pacman[0][0][1]->h;
            ypanneau -= pacman[0][0][1]->h;
            //yportail -= pacman[0][0][1]->h;
            for (int i = 0; i < nbcheval; i++) {
                xcheval[i] = ximgfond + 2670 - i * 21;
                ycheval[i] = yimgfond + 1305 + i * 9;
            }
            tourjoueur2=tourjoueur;
            tourjoueur+=1;
            if(tourjoueur>=NB_JOUEURS){
                tourjoueur=0;
            }
            cmpt = 0;
            cmp = 0;
            // Collision détectée !
            //textout_centre_ex(buffer, font, "Collision !", WIDTH / 2, HEIGHT / 2, makecol(255, 0, 0), -1);
        }

        if (xPacman <= (xlabyrinthe + (labyrinthe->w)/2) && (xlabyrinthe + (labyrinthe->w)/2) <= (xPacman + pacman[0][0][1]->w) && yPacman <= (ylabyrinthe) && (ylabyrinthe) <= (yPacman + pacman[0][0][1]->h)){
            stop_sample(sound[musiquealeatoire]);
            //pari();
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
            ychateauEnd -= pacman[0][0][1]->h;
            ypanneau -= pacman[0][0][1]->h;
            //yportail -= pacman[0][0][1]->h;
            for (int i = 0; i < nbcheval; i++) {
                xcheval[i] = ximgfond + 2670 - i * 21;
                ycheval[i] = yimgfond + 1305 + i * 9;
            }
            tourjoueur2=tourjoueur;
            tourjoueur+=1;
            if(tourjoueur>=NB_JOUEURS){
                tourjoueur=0;
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
            ychateauEnd -= pacman[0][0][1]->h;
            ypanneau -= pacman[0][0][1]->h;
            //yportail -= pacman[0][0][1]->h;
            for (int i = 0; i < nbcheval; i++) {
                xcheval[i] = ximgfond + 2670 - i * 21;
                ycheval[i] = yimgfond + 1305 + i * 9;
            }
            tourjoueur2=tourjoueur;
            tourjoueur+=1;
            if(tourjoueur>=NB_JOUEURS){
                tourjoueur=0;
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
            ychateauEnd -= pacman[0][0][1]->h;
            ypanneau -= pacman[0][0][1]->h;
            //yportail -= pacman[0][0][1]->h;
            for (int i = 0; i < nbcheval; i++) {
                xcheval[i] = ximgfond + 2670 - i * 21;
                ycheval[i] = yimgfond + 1305 + i * 9;
            }
            tourjoueur2=tourjoueur;
            tourjoueur+=1;
            if(tourjoueur>=NB_JOUEURS){
                tourjoueur=0;
            }
            cmpt = 0;
            cmp = 0;
            // Collision détectée !
            textout_centre_ex(buffer, font, "Collision !", WIDTH / 2, HEIGHT / 2, makecol(255, 0, 0), -1);
        }
        if (xPacman <= (xguitar + (guitar->w)/2) && (xguitar + (guitar->w)/2) <= (xPacman + pacman[0][0][1]->w) && yPacman <= (yguitar+(guitar->h)/2) && (yguitar+(guitar->h)/2) <= (yPacman + pacman[0][0][1]->h)){
            stop_sample(sound[musiquealeatoire]);
            menuguitar();
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
            ychateauEnd -= pacman[0][0][1]->h;
            ypanneau -= pacman[0][0][1]->h;
            //yportail -= pacman[0][0][1]->h;
            for (int i = 0; i < nbcheval; i++) {
                xcheval[i] = ximgfond + 2670 - i * 21;
                ycheval[i] = yimgfond + 1305 + i * 9;
            }
            tourjoueur2=tourjoueur;
            tourjoueur+=1;
            if(tourjoueur>=NB_JOUEURS){
                tourjoueur=0;
            }
            cmpt = 0;
            cmp = 0;
            // Collision détectée !
            textout_centre_ex(buffer, font, "Collision !", WIDTH / 2, HEIGHT / 2, makecol(255, 0, 0), -1);
        }
        if (xPacman <= (xcasino + (casino->w)/2) && (xcasino + (casino->w)/2) <= (xPacman + pacman[0][0][1]->w) && yPacman <= (ycasino+(casino->h)/2) && (ycasino+(casino->h)/2) <= (yPacman + pacman[0][0][1]->h)){
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
            ychateauEnd -= pacman[0][0][1]->h;
            ypanneau -= pacman[0][0][1]->h;
            //yportail -= pacman[0][0][1]->h;
            for (int i = 0; i < nbcheval; i++) {
                xcheval[i] = ximgfond + 2670 - i * 21;
                ycheval[i] = yimgfond + 1305 + i * 9;
            }
            tourjoueur2=tourjoueur;
            tourjoueur+=1;
            if(tourjoueur>=NB_JOUEURS){
                tourjoueur=0;
            }
            cmpt = 0;
            cmp = 0;
            // Collision détectée !
            textout_centre_ex(buffer, font, "Collision !", WIDTH / 2, HEIGHT / 2, makecol(255, 0, 0), -1);
        }
        if (xPacman <= (xriver + (river1->w)/2) && (xriver + (river1->w)/2) <= (xPacman + pacman[0][0][1]->w) && yPacman <= (yriver) && (yriver) <= (yPacman + pacman[0][0][1]->h)){
            stop_sample(sound[musiquealeatoire]);
            river();
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
            ychateauEnd -= pacman[0][0][1]->h;
            ypanneau -= pacman[0][0][1]->h;
            //yportail -= pacman[0][0][1]->h;
            for (int i = 0; i < nbcheval; i++) {
                xcheval[i] = ximgfond + 2670 - i * 21;
                ycheval[i] = yimgfond + 1305 + i * 9;
            }
            tourjoueur2=tourjoueur;
            tourjoueur+=1;
            if(tourjoueur>=NB_JOUEURS){
                tourjoueur=0;
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
            ychateauEnd -= pacman[0][0][1]->h;
            ypanneau -= pacman[0][0][1]->h;
            //yportail -= pacman[0][0][1]->h;
            for (int i = 0; i < nbcheval; i++) {
                xcheval[i] = ximgfond + 2670 - i * 21;
                ycheval[i] = yimgfond + 1305 + i * 9;
            }
            tourjoueur2=tourjoueur;
            tourjoueur+=1;
            if(tourjoueur>=NB_JOUEURS){
                tourjoueur=0;
            }
            cmpt = 0;
            cmp = 0;
            // Collision détectée !
            textout_centre_ex(buffer, font, "Collision !", WIDTH / 2, HEIGHT / 2, makecol(255, 0, 0), -1);
        }
        if (xPacman <= (xpanneau + panneau->w)
            &&(xpanneau) <= (xPacman + pacman[0][0][1]->w)
            && yPacman <= (ypanneau + panneau->h)
            && (ypanneau) <= (yPacman + pacman[0][0][1]->h)){
            draw_sprite(buffer,enterkey,xenter,yenter);
        }
        if (xPacman <= (xpanneau + panneau->w)
        &&(xpanneau) <= (xPacman + pacman[0][0][1]->w)
        && yPacman <= (ypanneau + panneau->h)
        && (ypanneau) <= (yPacman + pacman[0][0][1]->h)
        && key[KEY_ENTER]){
            stop_sample(sound[musiquealeatoire]);
            tableau_score();
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
            ychateauEnd -= pacman[0][0][1]->h;
            ypanneau -= pacman[0][0][1]->h;
            //yportail -= pacman[0][0][1]->h;
            for (int i = 0; i < nbcheval; i++) {
                xcheval[i] = ximgfond + 2670 - i * 21;
                ycheval[i] = yimgfond + 1305 + i * 9;
            }
            cmpt = 0;
            cmp = 0;
            // Collision détectée !
            textout_centre_ex(buffer, font, "Collision !", WIDTH / 2, HEIGHT / 2, makecol(255, 0, 0), -1);
        }
        //xperso2 = WIDTH/2;
        //yperso2 = HEIGHT/2 +50;
        if ((xperso2 + (pacman[0][0][0]->w)/2)<=((WIDTH/2)-100)) {
            if ((yperso2 + (pacman[0][0][0]->h)/2)>=((HEIGHT/2)+70)) {
                if(vitesseimage==0){
                    actionperso2 = 13;
                } else{
                    actionperso2 = 15;
                }
                yperso2 -= dy;

            } else if ((yperso2 + (pacman[0][0][0]->h)/2)<=((HEIGHT/2)-70)) {
                if(vitesseimage==0){
                    actionperso2 = 5;
                } else{
                    actionperso2 = 7;
                }
                yperso2 += dy;

            } else {
                if(vitesseimage==0){
                    actionperso2 = 8;
                } else{
                    actionperso2 = 10;
                }
            }
            posx2++;
            xperso2 += dx;

            if (posx2 > 3) {
                posx2 = 0;
            }
        } else if ((xperso2 + (pacman[0][0][0]->w)/2)>=((WIDTH/2)+100)) {
            if ((yperso2 + (pacman[0][0][0]->h)/2)>=((HEIGHT/2)+70)) {
                if(vitesseimage==0){
                    actionperso2 = 9;
                } else{
                    actionperso2 = 11;
                }
                yperso2 -= dy;

            } else if ((yperso2 + (pacman[0][0][0]->h)/2)<=((HEIGHT/2)-70)) {
                if(vitesseimage==0){
                    actionperso2 = 1;
                } else{
                    actionperso2 = 3;
                }
                yperso2 += dy;

            } else {
                if(vitesseimage==0){
                    actionperso2 = 4;
                } else{
                    actionperso2 = 6;
                }
            }
            posx2++;
            xperso2 -= dx;

            if (posx2 > 3) {
                posx2 = 0;
            }
        } else if ((yperso2 + (pacman[0][0][0]->h)/2)>=((HEIGHT/2)+100)) {
            if(vitesseimage==0){
                actionperso2 = 12;
            } else{
                actionperso2 = 14;
            }
            posx2++;
            yperso2 -= dy;

            if (posx2 > 3) {
                posx2 = 0;
            }
        } else if ((yperso2 + (pacman[0][0][0]->h)/2)<=((HEIGHT/2)-100)) {
            if(vitesseimage==0){
                actionperso2 = 0;
            } else{
                actionperso2 = 2;
            }
            posx2++;
            yperso2 += dy;

            if (posx2 > 3) {
                posx2 = 0;
            }
        }
        else{
            posx2=0;
            actionperso2=0;
        }
        if (key[KEY_DOWN] || key[KEY_UP] || key[KEY_LEFT] || key[KEY_RIGHT]) {
            if (key[KEY_RIGHT] && ((WIDTH + 1) < (fondmap->w + ximgfond))) {
                if (key[KEY_UP] && yimgfond < 0) {
                    if(vitesseimage==0){
                        actionperso = 13;
                    } else{
                        actionperso = 15;
                    }
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
                    ychateauEnd += dy;
                    ypanneau += dy;
                    yperso2 += dy;
                    //yportail += dy;
                    for (int i = 0; i < nbcheval; ++i) {
                        ycheval[i] += dy;
                    }
                } else if (key[KEY_DOWN] && ((HEIGHT + 1) < (fondmap->h + yimgfond))) {
                    if(vitesseimage==0){
                        actionperso = 5;
                    } else{
                        actionperso = 7;
                    }
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
                    ychateauEnd -= dy;
                    ypanneau -= dy;
                    yperso2 -= dy;
                    //yportail -= dy;
                    for (int i = 0; i < nbcheval; ++i) {
                        ycheval[i] -= dy;
                    }
                } else {
                    if(vitesseimage==0){
                        actionperso = 8;
                    } else{
                        actionperso = 10;
                    }
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
                xchateauEnd -= dx;
                xpanneau -= dx;
                xperso2 -= dx;

                //xportail -= dx;
                for (int i = 0; i < nbcheval; ++i) {
                    xcheval[i] -= dx;
                }
                if (posx > 3) {
                    posx = 0;
                }
            } else if (key[KEY_LEFT] && ximgfond < 0) {
                if (key[KEY_UP] && yimgfond < 0) {
                    if(vitesseimage==0){
                        actionperso = 9;
                    } else{
                        actionperso = 11;
                    }
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
                    ychateauEnd += dy;
                    ypanneau += dy;
                    yperso2 += dy;
                    //yportail += dy;
                    for (int i = 0; i < nbcheval; ++i) {
                        ycheval[i] += dy;
                    }
                } else if (key[KEY_DOWN] && ((HEIGHT + 1) < (fondmap->h + yimgfond))) {
                    if(vitesseimage==0){
                        actionperso = 1;
                    } else{
                        actionperso = 3;
                    }
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
                    ychateauEnd -= dy;
                    ypanneau -= dy;
                    yperso2 -= dy;
                    //yportail -= dy;
                    for (int i = 0; i < nbcheval; ++i) {
                        ycheval[i] -= dy;
                    }
                } else {
                    if(vitesseimage==0){
                        actionperso = 4;
                    } else{
                        actionperso = 6;
                    }
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
                xchateauEnd += dx;
                xpanneau += dx;
                xperso2 += dx;
                //xportail += dx;
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
                if(vitesseimage==0){
                    actionperso = 12;
                } else{
                    actionperso = 14;
                }
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
                ychateauEnd += dy;
                ypanneau += dy;
                yperso2 += dy;
                //yportail += dy;
                for (int i = 0; i < nbcheval; ++i) {
                    ycheval[i] += dy;
                }
                if (posx > 3) {
                    posx = 0;
                }
            } else if (key[KEY_DOWN] && ((HEIGHT + 1) < (fondmap->h + yimgfond))) {
                if(vitesseimage==0){
                    actionperso = 0;
                } else{
                    actionperso = 2;
                }
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
                ychateauEnd -= dy;
                ypanneau -= dy;
                yperso2 -= dy;
                //yportail -= dy;
                for (int i = 0; i < nbcheval; ++i) {
                    ycheval[i] -= dy;
                }
                if (posx > 3) {
                    posx = 0;
                }
            }
            draw_sprite(buffer, pacman[joueurs[tourjoueur].persoChoisi][actionperso][posx], xPacman, yPacman);
        } else {
            draw_sprite(buffer, pacman[joueurs[tourjoueur].persoChoisi][0][0], xPacman, yPacman);
        }
        if (stop == 0) {
            stop_sample(sound[musiquealeatoire]);
            play_sample(ambiance, 255, 128, 1000, 1);
            for (int i = 0; i < NB_JOUEURS; ++i) {
                play_sample(effet[i], 255, 128, 1000, 0);
                while (!key[KEY_ENTER] && stop == 0 || strlen(text_input)>10) {
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

                    if(key[KEY_LEFT]){
                        joueurs[i].persoChoisi-=1;
                        if(joueurs[i].persoChoisi==selectperso){
                            joueurs[i].persoChoisi-=1;
                        }
                    }
                    else if(joueurs[i].persoChoisi==selectperso){
                        joueurs[i].persoChoisi+=1;
                    }
                    else if(key[KEY_RIGHT]){
                        joueurs[i].persoChoisi +=1;
                        if(joueurs[i].persoChoisi==selectperso){
                            joueurs[i].persoChoisi+=1;
                        }
                    }
                    if(joueurs[i].persoChoisi>=grille){
                        joueurs[i].persoChoisi=0;
                    }
                    if(joueurs[i].persoChoisi<0){
                        joueurs[i].persoChoisi=4;
                    }


                    draw_sprite(buffer, parchemin, ((WIDTH/2)-(parchemin->w)/2), 0);
                    draw_sprite(buffer, pacman[joueurs[i].persoChoisi][0][0], ((WIDTH/2)-50), HEIGHT-470);
                    blit(buffer2, buffer, 0, 0, posxbuff2, posybuff2, WIDTH, HEIGHT);
                    rest(200);
                }
                selectperso=joueurs[i].persoChoisi;
                if(strlen(text_input)==0){
                    sprintf(text_input,"%s%d%d%d%d","Player",rand()%10,rand()%10,rand()%10,rand()%10);
                }
                //sprintf(nomjoueur[i], "%s", text_input);
                while(strlen(text_input)!=10){
                    sprintf(text_input,"%s%s",text_input," ");
                }
                sprintf(joueurs[i].nom,"%s",text_input);
                memset(text_input, '\0', sizeof(text_input)); //effacer tout le tableau
                rest(300);
                stop_sample(effet[i]);
            }
            musique=1;

            //choix(&*buffer2,&*parchemin,&*buffer,&*pacman,&*barbare);
        }
        stop_sample(ambiance);
        //textprintf_ex(buffer, font, 200, 100, makecol(255, 255, 255), -1, "%s", nomjoueur[0]);
        //textprintf_ex(buffer, font, 1700, 100, makecol(255, 255, 255), -1, "%s", nomjoueur[1]);
        stop = 1;
       /* draw_sprite(buffer, affichageScore, 1200, 30);
        for (int i = 0; i < joueurs[0].nbTickets; ++i) {
            draw_sprite(buffer, bitcoin[posbitcoin], 1320 + i*50 , 170);
        }
        for (int i = 0; i < joueurs[1].nbTickets; ++i) {
            draw_sprite(buffer, bitcoin[posbitcoin], 1320 + i*50 , 280);
        }

        textprintf_ex(buffer, font, 1340, 150, makecol(0, 0, 0), -1, "%s, Tickets : %d", joueurs[0].nom, joueurs[0].nbTickets);
        textprintf_ex(buffer, font, 1340, 260, makecol(0, 0, 0), -1, "%s, Tickets : %d", joueurs[1].nom, joueurs[1].nbTickets);
        */
        stop=1;
        blit(buffer,screen,0,0,0,0,WIDTH,HEIGHT);



        if (key[KEY_P]) {
            isPaused = 1; // Mettre le jeu en pause
            rest(200); // Attendre un peu pour éviter les pressions répétées de la touche P
        }

        // Si le jeu est en pause
        while (isPaused) {
            clear_keybuf(); // Effacer le tampon des touches pressées pendant la pause

            // Afficher le menu de pause
            clear(buffer);
            draw_sprite(buffer, fondmap, ximgfond, yimgfond);
            rectfill(buffer,(WIDTH/2)-100,(HEIGHT/2)-100,(WIDTH/2)+100,(HEIGHT/2)+100, makecol(0,0,0));
            textprintf_centre_ex(buffer, font, WIDTH/2, HEIGHT/2 - 40, makecol(255, 255, 255), -1, "MENU PAUSE");
            textprintf_centre_ex(buffer, font, WIDTH/2, HEIGHT/2     , makecol(255, 255, 255), -1, "1 - Sauvegarder");
            textprintf_centre_ex(buffer, font, WIDTH/2, HEIGHT/2 + 20, makecol(255, 255, 255), -1, "2 - Charger");
            textprintf_centre_ex(buffer, font, WIDTH/2, HEIGHT/2 + 40, makecol(255, 255, 255), -1, "3 - Reprise");

            blit(buffer, screen, 0, 0, 0, 0, WIDTH, HEIGHT);

            if (key[KEY_1]) {

                char saveFileName[100];
                // Afficher le menu de pause
                while (!key[KEY_ENTER]){
                clear(buffer);
                draw_sprite(buffer, fondmap, ximgfond, yimgfond);
                rectfill(buffer, (WIDTH / 2) - 100, (HEIGHT / 2) - 100, (WIDTH / 2) + 100, (HEIGHT / 2) + 100,
                         makecol(0, 0, 0));
                textprintf_centre_ex(buffer, font, WIDTH / 2, HEIGHT / 2 - 40, makecol(255, 255, 255), -1,"MENU PAUSE");
                textprintf_centre_ex(buffer, font, WIDTH / 2, HEIGHT / 2, makecol(255, 255, 255), -1,"Nom de la sauvegarde : ");
                textout_centre_ex(buffer, font, text_input, WIDTH / 2, HEIGHT / 2 + 20, makecol(255, 255, 255), -1);
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
                blit(buffer, screen, 0, 0, 0, 0, WIDTH, HEIGHT);
                rest(120);
            }

                sprintf(saveFileName,"%s",text_input);
                memset(text_input, '\0', sizeof(text_input)); //effacer tout le tableau
                // Option de sauvegarde
                saveGame(joueurs, saveFileName); // Sauvegarder le jeu (adapté à votre structure de joueurs et nom de sauvegarde)
                isPaused = 0; // Reprendre le jeu
            } else if (key[KEY_2]) {


                char loadFileName[100];
                // Afficher le menu de pause
                while (!key[KEY_ENTER]){
                    clear(buffer);
                    draw_sprite(buffer, fondmap, ximgfond, yimgfond);
                    rectfill(buffer, (WIDTH / 2) - 100, (HEIGHT / 2) - 100, (WIDTH / 2) + 100, (HEIGHT / 2) + 100,
                             makecol(0, 0, 0));
                    textprintf_centre_ex(buffer, font, WIDTH / 2, HEIGHT / 2 - 40, makecol(255, 255, 255), -1,"MENU PAUSE");
                    textprintf_centre_ex(buffer, font, WIDTH / 2, HEIGHT / 2, makecol(255, 255, 255), -1,"Nom de la sauvegarde : ");
                    textout_centre_ex(buffer, font, text_input, WIDTH / 2, HEIGHT / 2 + 20, makecol(255, 255, 255), -1);
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
                    blit(buffer, screen, 0, 0, 0, 0, WIDTH, HEIGHT);
                    rest(120);
                }

                sprintf(loadFileName,"%s",text_input);
                memset(text_input, '\0', sizeof(text_input)); //effacer tout le tableau
                // Option de chargement
                loadGame(joueurs, loadFileName); // Charger le jeu (adapté à votre structure de joueurs et nom de sauvegarde)
                isPaused = 0; // Reprendre le jeu
            } else if (key[KEY_3]||key[KEY_ESC]) {
                // Option de reprise
                isPaused = 0; // Reprendre le jeu
            }

            rest(200); // Pause de 100 ms pour rafraîchir l'écran
        }


        if (key[KEY_ESC]){
            isPaused = 1; // Mettre le jeu en pause
            rest(200); // Attendre un peu pour éviter les pressions répétées de la touche P
        }

        // Si le jeu est en pause
        while (isPaused) {
            clear_keybuf(); // Effacer le tampon des touches pressées pendant la pause

            // Afficher le menu de pause
            clear(buffer);
            draw_sprite(buffer, fondmap, ximgfond, yimgfond);
            rectfill(buffer, (WIDTH / 2) - 400, (HEIGHT / 2) - 100, (WIDTH / 2) + 400, (HEIGHT / 2) + 100,
                     makecol(0, 0, 0));
            textprintf_centre_ex(buffer, font, WIDTH / 2, HEIGHT / 2 - 40, makecol(255, 255, 255), -1, "MENU QUITTER");
            textprintf_centre_ex(buffer, font, WIDTH / 2, HEIGHT / 2, makecol(255, 255, 255), -1,
                                 "Etes vous sûr de vouloir quitter ?");
            textprintf_centre_ex(buffer, font, WIDTH / 2, HEIGHT / 2 + 20, makecol(255, 255, 255), -1,
                                 "Votre partie ne sera pas sauvegardée si vous n'avez pas sauvegardé au préalable");
            textprintf_centre_ex(buffer, font, WIDTH / 2, HEIGHT / 2 + 40, makecol(255, 255, 255), -1,
                                 "Appuyez sur Entrée pour quitter ECE-WORLD, appuyez sur echap pour revenir au jeu");

            blit(buffer, screen, 0, 0, 0, 0, WIDTH, HEIGHT);

            if (key[KEY_ESC]) {
                isPaused = 0;
            } else if (key[KEY_ENTER]) {
                end = 1;
                isPaused = 0;

            }
            rest(100); // Pause de 100 ms pour rafraîchir l'écran
        }


        if (key[KEY_SPACE]) {
            rest(10);
        } else
        rest(60); // Pause de 10 ms pour rafraîchir l'écran
        for (int i = 0; i < 2; ++i) {
            switch (joueurs[i].nbTickets) {
                case 0:
                    stop_sample(sound[musiquealeatoire]);
                    while (!key[KEY_ENTER]) {
                        clear_bitmap(buffer);
                        play_sample(clear1, 255, 128, 1000, 0);
                        draw_sprite(buffer, fonfin, 0, 0);
                        draw_sprite(buffer, scroll, WIDTH / 2 - 200, HEIGHT / 2 - 200);
                        draw_sprite(buffer, congrats, WIDTH / 2 - 50, HEIGHT / 2 - 500);
                        textprintf_ex(buffer, font, (WIDTH/2)-100, (HEIGHT/2)-25, makecol(0, 0, 0), -1, "%s a perdu, son coéquipier remporte la quête du Bitcoin !",joueurs[0].nom);
                        textprintf_ex(buffer, font, (WIDTH/2)-110, (HEIGHT/2)-15, makecol(0, 0, 0), -1, "Gloire à ce preux chevalier :) !");
                        blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
                    }
                    break;
                case 10:
                    stop_sample(sound[musiquealeatoire]);
                    while (!key[KEY_ENTER]) {
                        clear_bitmap(buffer);
                        play_sample(clear1, 255, 128, 1000, 0);
                        draw_sprite(buffer, fonfin, 0, 0);
                        draw_sprite(buffer, scroll, WIDTH / 2 - 200, HEIGHT / 2 - 200);
                        draw_sprite(buffer, congrats, WIDTH / 2 - 50, HEIGHT / 2 - 500);
                        textprintf_ex(buffer, font, (WIDTH/2)-100, (HEIGHT/2)-25, makecol(0, 0, 0), -1, "%s a terminée la quête du Bitcoin !",joueurs[0].nom);
                        textprintf_ex(buffer, font, (WIDTH/2)-110, (HEIGHT/2)-15, makecol(0, 0, 0), -1, "Gloire à ce preux chevalier :) !");
                        blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
                    }
                    break;
                }
            }
        }
    stop_sample(sound[musiquealeatoire]);
}
/*void choix(BITMAP *buffer2,BITMAP *parchemin,BITMAP *buffer,BITMAP *pacman[grille][action][posirang],BITMAP *barbare[2]){
    int xbarbare[2];
    int ybarbare[2];
    char text_input[128] = {0}; // variable pour stocker la saisie clavier
    int stop = 0;
    int buffersizew = WIDTH / 6;
    int buffersizeh = HEIGHT / 8;
    int posxbuff2 = (WIDTH / 2) - (buffersizew / 2);//WIDTH/2
    int posybuff2 = (HEIGHT / 3) - (buffersizeh / 2);//HEIGHT/2
    xbarbare[0] = WIDTH - (barbare[0]->w);
    xbarbare[1] = 0;
    ybarbare[0] = HEIGHT - (barbare[0]->h);
    ybarbare[1] = HEIGHT - (barbare[1]->h);
    SAMPLE *sound[nbMusique];
    sound[0] = load_wav("../Parc/musique/GameTrone.wav");//GameTrone  HouseDragon
    SAMPLE *effet[2];
    SAMPLE *ambiance = load_wav("../Parc/musique/ambiance.wav");
    play_sample(ambiance, 255, 128, 1000, 1);
    for (int i = 0; i < NB_JOUEURS; ++i) {
        play_sample(effet[i], 255, 128, 1000, 0);
        while (!key[KEY_ENTER] && stop == 0 || strlen(text_input)>10) {
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
                joueurs[i].persoChoisi +=1;
            }
            if(key[KEY_LEFT]){
                joueurs[i].persoChoisi-=1;
            }
            if(joueurs[i].persoChoisi>=grille){
                joueurs[i].persoChoisi=0;
            }
            if(joueurs[i].persoChoisi<0){
                joueurs[i].persoChoisi=4;
            }

            draw_sprite(buffer, parchemin, ((WIDTH/2)-(parchemin->w)/2), 0);
            draw_sprite(buffer, pacman[joueurs[i].persoChoisi][0][0], ((WIDTH/2)-50), HEIGHT-470);
            blit(buffer2, buffer, 0, 0, posxbuff2, posybuff2, WIDTH, HEIGHT);
            rest(120);
        }
        if(strlen(text_input)==0){
            sprintf(text_input,"%s%d%d%d%d","Player",rand()%10,rand()%10,rand()%10,rand()%10);
        }
        //sprintf(nomjoueur[i], "%s", text_input);
        while(strlen(text_input)!=10){
            sprintf(text_input,"%s%s",text_input," ");
        }
        sprintf(joueurs[i].nom,"%s",text_input);
        memset(text_input, '\0', sizeof(text_input)); //effacer tout le tableau
        rest(300);
        stop_sample(effet[i]);
    }
}*/