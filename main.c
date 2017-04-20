#include <stdlib.h>
#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>
#include "init.h"

int main(int argc, char const *argv[])
{
	SDL_Init(SDL_INIT_VIDEO);
	SDL_Surface * fenetre = NULL, * mario = NULL, *mur = NULL, *caisse = NULL, *objectif=NULL;
	int carte[NB_BLOCS_LARGEUR][NB_BLOCS_HAUTEUR] = {0};
	fenetre = SDL_SetVideoMode(LARGEUR_FENETRE, HAUTEUR_FENETRE, 32, SDL_HWSURFACE);
	mario = IMG_Load("mario/mario_bas.gif");
	mur = IMG_Load("mario/mur.jpg");
	caisse = IMG_Load("mario/caisse.jpg");
	objectif = IMG_Load("mario/objectif.png");

	SDL_Rect positionMario, positionMur, positionCaisse, positionObj;
	positionMario.x = 344;	
	positionMario.y = fenetre->h /2;	
	positionObj.x = 35;	// puisqu'un block fait 34 pixels et qu'il n'y en a qu'un à gauche de l'obj
	positionObj.y = fenetre->h /2;
	positionCaisse.x = 315;	// x de mario - w de mario
	positionCaisse.y = fenetre->h /2;	

	carte[positionCaisse.x/34][positionCaisse.y/34] = CAISSE;
	carte[positionObj.x/34][positionObj.y/34] = OBJECTIF;
	printf("CAISSE : x-%d y-%d\nOBJECTIF : x-%d y-%d\n", positionCaisse.x/34, positionCaisse.y/34, positionObj.x/34, positionObj.y/34);
	// Modification des couleurs du background
	SDL_FillRect(fenetre, NULL, SDL_MapRGB(fenetre->format, 255, 255, 255));
	placerMur(fenetre, mur, positionMur, carte);
	SDL_BlitSurface(mario, NULL, fenetre, &positionMario);
	SDL_BlitSurface(objectif, NULL, fenetre, &positionObj);
	SDL_BlitSurface(caisse, NULL, fenetre, &positionCaisse);

	// Placement Mur
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
                    	deplacerMario(mario, caisse, &positionMario, &positionCaisse,IMG_Load("mario/mario_haut.gif"), carte, positionMario.x/34, positionMario.y/34 - 1, "up");
                        break;
                    case SDLK_DOWN:
                    	deplacerMario(mario, caisse, &positionMario, &positionCaisse,IMG_Load("mario/mario_bas.gif"), carte, positionMario.x/34, positionMario.y/34 + 1, "down");
                        break;
                    case SDLK_RIGHT:
                    	deplacerMario(mario, caisse, &positionMario, &positionCaisse,IMG_Load("mario/mario_droite.gif"), carte, positionMario.x/34 + 1, positionMario.y/34, "right");
                        break;
                    case SDLK_LEFT:
                    	deplacerMario(mario, caisse, &positionMario, &positionCaisse,IMG_Load("mario/mario_gauche.gif"), carte, (positionMario.x -1)/34 -1, positionMario.y/34, "left");
                        break;
                }
            break;
		}
		carte[positionCaisse.x/34][positionCaisse.y/34] = CAISSE;
		SDL_FillRect(fenetre, NULL, SDL_MapRGB(fenetre->format, 255, 255, 255));
		SDL_BlitSurface(mario, NULL, fenetre, &positionMario);
		SDL_BlitSurface(objectif, NULL, fenetre, &positionObj);
		SDL_BlitSurface(caisse, NULL, fenetre, &positionCaisse);
		placerMur(fenetre, mur, positionMur, carte);
		SDL_Flip(fenetre);
	}
	// Désactivation de la répétition des touches (remise à 0)
    SDL_EnableKeyRepeat(0, 0);
	// Libérer la mémoire
	SDL_FreeSurface(fenetre);
	SDL_FreeSurface(mario);
	SDL_FreeSurface(mur);
	SDL_FreeSurface(caisse);
	SDL_FreeSurface(objectif);
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

void deplacerMario(SDL_Surface * mario, SDL_Surface * caisse, SDL_Rect * positionMario, SDL_Rect * positionCaisse, SDL_Surface * img, int carte[NB_BLOCS_LARGEUR][NB_BLOCS_HAUTEUR], int x, int y, char * direction) {
	if (carte[x][y] != MUR)  {// S'il y a un mur, on arrête
		*mario = *img;
		if(direction == "up")
		 	positionMario->y-=10; 
		else if(direction == "down")
		 	positionMario->y+=10;
		else if(direction == "left") {
			printf("MARIO : x-%d y-%d CAISSE : x-%d y-%d\n", positionMario->x/34, positionMario->y/34, positionCaisse->x/34, positionCaisse->y/34);
		 		positionMario->x-=10;
		 	if ((positionCaisse->x) + 19 == positionMario->x)
		 		positionCaisse->x-=10;
			// if (carte[positionCaisse->x/34][positionCaisse->y/34] == OBJECTIF)
			if (positionCaisse->x == 35)
		 		chargerImg(caisse, IMG_Load("mario/caisse_ok.jpg"));
		 	
		}
		else if(direction == "right")
		 	positionMario->x+=10;

   }
}
void chargerImg(SDL_Surface * surf, SDL_Surface * img) {
	*surf = *img;
}