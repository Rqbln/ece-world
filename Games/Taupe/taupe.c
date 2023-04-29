#include "taupe.h"
#include "../../Init_Allegro/allegro.h"

 void taupe() {
     int score = 0;
     int gameOver = 0;
     char messageFin[60];
     int isClicked = 0;

     int targetSize = TAILLE_INITIALE;
     int target_x = rand() % WIDTH;
     int target_y = rand() % HEIGHT;

     show_mouse(screen);

     while (!gameOver && !key[KEY_ESC]) {
         clear_bitmap(screen);

         circlefill(screen, target_x, target_y, targetSize, makecol(255, 0, 0));
         targetSize--;
         if (mouse_b & 1 && !isClicked) {
             int mx = mouse_x;
             int my = mouse_y;


             if (mx >= target_x - targetSize && mx <= target_x + targetSize
                 && my >= target_y - targetSize && my <= target_y + targetSize) {
                 score++;
                 targetSize = TAILLE_INITIALE;
                 target_x = rand() % WIDTH;
                 target_y = rand() % HEIGHT;
             }
             isClicked = 1;

         } else if (!(mouse_b & 1) && isClicked) {
             isClicked = 0;
         } else if (targetSize < 1) {
             targetSize = TAILLE_INITIALE;
             target_x = rand() % WIDTH;
             target_y = rand() % HEIGHT;
         }
         textprintf_centre_ex(screen, font, WIDTH / 2, 10, makecol(255, 255, 255), -1, "Score: %d", score);

         // Mettre à jour l'écran
         vsync();
         blit(screen, screen, 0, 0, 0, 0, WIDTH, HEIGHT);

         // Attendre un peu pour éviter que les serpents ne se déplace trop rapidement
         rest(50);

         if (score == 5) {
             gameOver = 1;
             clear_bitmap(screen);
         }
     }


     while (!key[KEY_ESC]) {
         if (score == 5) {
             clear_bitmap(screen);
             sprintf(messageFin, "Le joueur 1 a atteint 5 points, fin de la partie !");
             textout_centre_ex(screen, font, messageFin, WIDTH / 2, HEIGHT / 2, makecol(255, 255, 255), -1);
         }
         // Mettre à jour l'écran

         rest(10); // Pause de 10 ms pour rafraîchir l'écran
         vsync();
         blit(screen, screen, 0, 0, 0, 0, WIDTH, HEIGHT);

     }
 }