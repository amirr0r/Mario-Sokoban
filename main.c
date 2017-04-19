#include <stdlib.h>
#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>
#include "init.h"
enum {VIDE, MUR, CAISSE, OBJECTIF, MARIO, CAISSE_OK}; // VIDE = 0, MUR = 1, CAISSE = 2 etc..
int main(int argc, char const *argv[])
{
	SDL_Init(SDL_INIT_VIDEO);
	SDL_Surface * fenetre = NULL, * mario = NULL, *mur = NULL;
	int carte[NB_BLOCS_LARGEUR][NB_BLOCS_HAUTEUR] = {0};
	fenetre = SDL_SetVideoMode(LARGEUR_FENETRE, HAUTEUR_FENETRE, 32, SDL_HWSURFACE);
	mario = IMG_Load("mario/mario_bas.gif");
	mur = IMG_Load("mario/mur.jpg");

	SDL_Rect positionMario, positionMur;
	positionMario.x = 344;	
	positionMario.y = fenetre->h /2;	
	// Modification des couleurs du background
	SDL_FillRect(fenetre, NULL, SDL_MapRGB(fenetre->format, 255, 255, 255));
	SDL_BlitSurface(mario, NULL, fenetre, &positionMario);

	// Placement Mur
	placerMur(fenetre, mur, positionMur, carte);
	// Actualisation de la fenêtre
	SDL_Flip(fenetre);
	// Boucle "pseudo" infini (BASE DU PROGRAMME)
	int continuer = 1; 
	SDL_EnableKeyRepeat(100, 100);
	while(continuer) {
		// printf("%d\n", carte[0][0]);
		SDL_Event event;
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
        	            if (carte[positionMario.x/34][positionMario.y/34 - 1] == MUR) // S'il y a un mur, on arrête
        			        break;
                    	mario = IMG_Load("mario/mario_haut.gif");
                       	positionMario.y-=10;
                        break;
                    case SDLK_DOWN:
                    	if (carte[positionMario.x/34][positionMario.y/34 + 1] == MUR) // S'il y a un mur, on arrête
        			        break;
                        mario = IMG_Load("mario/mario_bas.gif");
                        positionMario.y+=10;
                        break;
                    case SDLK_RIGHT:
	                    if (carte[positionMario.x/34 + 1][positionMario.y/34] == MUR) // S'il y a un mur, on arrête
	        			    break;
                        mario = IMG_Load("mario/mario_droite.gif");
                        positionMario.x+=10;
                        break;
                    case SDLK_LEFT:
                    	if (carte[(positionMario.x -1)/34][positionMario.y/34] == MUR) // S'il y a un mur, on arrête
	        			    break;
                        mario = IMG_Load("mario/mario_gauche.gif");
                        positionMario.x-=10;
                        break;
                }
            break;
		}
		SDL_FillRect(fenetre, NULL, SDL_MapRGB(fenetre->format, 255, 255, 255));
		SDL_BlitSurface(mario, NULL, fenetre, &positionMario);
		placerMur(fenetre, mur, positionMur, carte);
		SDL_Flip(fenetre);
	}
	// Désactivation de la répétition des touches (remise à 0)
    SDL_EnableKeyRepeat(0, 0);
	// Libérer la mémoire
	SDL_FreeSurface(fenetre);
	SDL_FreeSurface(mario);
	SDL_FreeSurface(mur);
	SDL_Quit();
	return 0;
}

void placerMur(SDL_Surface * fenetre, SDL_Surface * mur, SDL_Rect positionMur, int carte[NB_BLOCS_LARGEUR][NB_BLOCS_HAUTEUR]) {
	int i = 0, j = 0, x, y;
	for (x = 0; x < HAUTEUR_FENETRE; x+=TAILLE_BLOC)
	{
		j=0;
		for (y = 0; y < LARGEUR_FENETRE; y+=TAILLE_BLOC)
		{
			positionMur.x = x;
			positionMur.y = y;
			if(y != LARGEUR_FENETRE/2 || x == 0 || x == HAUTEUR_FENETRE - TAILLE_BLOC) {
				SDL_BlitSurface(mur, NULL, fenetre, &positionMur);
				carte[i][j] = MUR;
			}
			j++;
		}
		i++;
	}
	
}