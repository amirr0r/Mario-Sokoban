#include <stdlib.h>
#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>
#include "init.h"
// #include <SDL_ttf.h>
int main(int argc, char const *argv[])
{
	SDL_Init(SDL_INIT_VIDEO);
	// Declaration des surfaces
	SDL_Surface * fenetre = NULL, * mario = NULL, * mur = NULL,* caisse = NULL,* objectif = NULL;

	fenetre = SDL_SetVideoMode(LARGEUR_FENETRE, HAUTEUR_FENETRE, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
	mario = IMG_Load("mario/mario_bas.gif");
	mur = IMG_Load("mario/mur.jpg");
	caisse = IMG_Load("mario/caisse.jpg");
	objectif = IMG_Load("mario/objectif.png");

	// Modif couleur background
	SDL_FillRect(fenetre, NULL, SDL_MapRGB(fenetre->format, 255, 255, 255));

	// Map du jeu
	int carte[NB_BLOCS_LARGEUR][NB_BLOCS_HAUTEUR] = {0};
	int continuer = 1, niveau = 1, tour = 0;
	
	start : ;
	if(niveau == 1)
		niveau1(carte);
	else if(niveau == 2 && tour == 1) {
		niveau2(carte);
		chargerImg(caisse, IMG_Load("mario/caisse.jpg"));
	}
	else if (tour == 3) {
		niveau3(carte);
		chargerImg(caisse, IMG_Load("mario/caisse.jpg"));
	}

	SDL_Flip(fenetre);

	SDL_Rect positionMario, positionCaisse;
	int i, j;
	for (i = 0; i < 12; i++) { 
		for (j = 0; j < 12; j++){ 
				if (carte[i][j] == MARIO) {
					positionMario.x = i*TAILLE_BLOC;
					positionMario.y = j*TAILLE_BLOC;
				}
				else if(carte[i][j] == CAISSE) {
					positionCaisse.x = i*TAILLE_BLOC;
					positionCaisse.y = j*TAILLE_BLOC;
				}
		}
	}
	// Activation de la repetition des touches
	SDL_EnableKeyRepeat(100, 100);
	// Boucle principal
	while(continuer) {
		SDL_Event event;
		// printf("%d %d\n", event.motion.x, event.motion.y);
		SDL_WaitEvent(&event);
		switch(event.type) {
			case SDL_QUIT :
				continuer = 0;
			break;
			case SDL_KEYDOWN :
				switch(event.key.keysym.sym)
                {
                    case SDLK_ESCAPE:
                        continuer = 0; 
                        break;
                    case SDLK_UP:
                    	deplacement(caisse, mario, &positionMario, &positionCaisse, carte, 'u', &niveau);
                        break;
                    case SDLK_DOWN:
                    	deplacement(caisse, mario, &positionMario, &positionCaisse, carte, 'd', &niveau);
                        break;
                    case SDLK_RIGHT:
                    	deplacement(caisse, mario, &positionMario, &positionCaisse, carte, 'r', &niveau);
                        break;
                    case SDLK_LEFT:
                    	deplacement(caisse, mario, &positionMario, &positionCaisse, carte, 'l', &niveau);
                        break;
                }
            break;
		}
		majMap(fenetre, mario, caisse, mur, objectif, carte);
		SDL_Flip(fenetre);
		if (niveau > 1) {
			if ((niveau == 2 && tour == 0) || (niveau == 3 && tour == 1)) {
				tour++;
				goto start;
			}
		}
	}
	SDL_EnableKeyRepeat(0, 0);
    // Libération des surfaces chargées
    SDL_FreeSurface(mario);
    SDL_FreeSurface(mur);
    SDL_FreeSurface(caisse);
    SDL_FreeSurface(objectif);
    SDL_FreeSurface(fenetre);
	SDL_Quit();
	return 0;
}

