#include <stdlib.h>
#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>
// #include <SDL_ttf.h>

int main(int argc, char const *argv[])
{
	// Gérer les erreurs : fprintf(stderr, "Error SDL %s\n", SDL_GetError());
	SDL_Init(SDL_INIT_VIDEO);
	// TTF_Init();
	// le contenu du programme
	SDL_Surface * fenetre = NULL, * mario = NULL; //* carre = NULL, *texte = NULL;
	// TTF_Font * font;
	// SDL_Color fontColor = {0,0,0};
	// char chrono[20];
	// sprintf(chrono, "%d", SDL_GetTicks());
	
	fenetre = SDL_SetVideoMode(500, 500, 32, SDL_HWSURFACE);
	// Uint32 grey = SDL_MapRGB(fenetre->format, 128, 128, 128);
 	// carre = SDL_CreateRGBSurface(SDL_HWSURFACE, 50, 50, 32, 0, 0, 0, 0);
	mario = IMG_Load("mario/mario_bas.gif");
	// font = TTF_OpenFont("FFF_Tusj.ttf", 22);
	// texte = TTF_RenderText_Blended(font, chrono, fontColor);

	SDL_Rect positionMario; // postexte;
	positionMario.x = 0;
	positionMario.y = 0;	
	// postexte.x = 0;
	// postexte.y = fenetre->h - texte->h;

	// Modification des couleurs du background
	SDL_FillRect(fenetre, NULL, SDL_MapRGB(fenetre->format, 255, 255, 255));
	// SDL_FillRect(carre, NULL, grey);
	// SDL_BlitSurface(texte, NULL, fenetre, &postexte);
	SDL_BlitSurface(mario, NULL, fenetre, &positionMario);
	// Actualisation de la fenêtre
	SDL_Flip(fenetre);
	// Boucle "pseudo" infini (BASE DU PROGRAMME)
	int continuer = 1; 
	// int now = 0, before = 0, interval = 1000;
	SDL_EnableKeyRepeat(100, 100);
	while(continuer) {
		SDL_Event event;
		// now = SDL_GetTicks();
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
                    	mario = IMG_Load("mario/mario_haut.gif");
                       	positionMario.y-=10;
                        break;
                    case SDLK_DOWN:
                        mario = IMG_Load("mario/mario_bas.gif");
                        positionMario.y+=10;
                        break;
                    case SDLK_RIGHT:
                        mario = IMG_Load("mario/mario_droite.gif");
                        positionMario.x+=10;
                        break;
                    case SDLK_LEFT:
                        mario = IMG_Load("mario/mario_gauche.gif");
                        positionMario.x-=10;
                        break;
                }
            // if (now-before < interval)
            // 	SDL_Delay(interval-(now-before));
			SDL_FillRect(fenetre, NULL, SDL_MapRGB(fenetre->format, 255, 255, 255));                
            SDL_BlitSurface(mario, NULL, fenetre, &positionMario);
			// sprintf(chrono, "%d", SDL_GetTicks());
			// texte = TTF_RenderText_Blended(font, chrono, fontColor);
			// SDL_BlitSurface(texte, NULL, fenetre, &postexte);
			// Actualisation de la fenêtre
			SDL_Flip(fenetre);
			// before = now;
            break;
		}
	}
	// printf("%d\n", SDL_GetTicks());
	// Libérer la mémoire
	SDL_FreeSurface(fenetre);
	// SDL_FreeSurface(texte);
	SDL_FreeSurface(mario);
	// SDL_FreeSurface(carre);
	// TTF_Quit();
	SDL_Quit();
	return 0;
}