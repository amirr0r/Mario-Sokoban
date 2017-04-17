/*
main.c
------

Par mateo21, pour Le Site du Zéro (www.siteduzero.com)

Rôle : menu du jeu. Permet de choisir entre l'éditeur et le jeu lui-même.
*/

#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL_image.h>

#include "constantes.h"
#include "jeu.h"
#include "editeur.h"

int main(int argc, char *argv[])
{
    SDL_Surface *ecran = NULL, *menu = NULL;
    SDL_Rect positionMenu;
    SDL_Event event;

    int continuer = 1;

    SDL_Init(SDL_INIT_VIDEO);

    SDL_WM_SetIcon(IMG_Load("caisse.jpg"), NULL); // L'icône doit être chargée avant SDL_SetVideoMode
    ecran = SDL_SetVideoMode(LARGEUR_FENETRE, HAUTEUR_FENETRE, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    SDL_WM_SetCaption("Mario Sokoban", NULL);

    menu = IMG_Load("menu.jpg");
    positionMenu.x = 0;
    positionMenu.y = 0;

    // Elements
    SDL_Surface *mario[4] = {NULL}; // 4 surfaces pour 4 directions de mario
    SDL_Surface *mur = NULL, *caisse = NULL, *caisseOK = NULL, *objectif = NULL, *marioActuel = NULL;
    SDL_Rect position, positionJoueur;
    SDL_Event event;
    int continuer = 1, objectifsRestants = 0, i = 0, j = 0;
    int carte[NB_BLOCS_LARGEUR][NB_BLOCS_HAUTEUR] = {0};

    // Chargement des sprites (décors, personnage...)
    mur = IMG_Load("mur.jpg");
    caisse = IMG_Load("caisse.jpg");
    caisseOK = IMG_Load("caisse_ok.jpg");
    objectif = IMG_Load("objectif.png");
    mario[BAS] = IMG_Load("mario_bas.gif");
    mario[GAUCHE] = IMG_Load("mario_gauche.gif");
    mario[HAUT] = IMG_Load("mario_haut.gif");
    mario[DROITE] = IMG_Load("mario_droite.gif");
    marioActuel = mario[BAS]; // Mario sera dirigé vers le bas au départ
    // Chargement du niveau
    if (!chargerNiveau(carte))
    exit(EXIT_FAILURE); // On arrête le jeu si on n'a pas pu charger le niveau
    // Recherche de la position de Mario au départ
    for (i = 0 ; i < NB_BLOCS_LARGEUR ; i++)
    {
        for (j = 0 ; j < NB_BLOCS_HAUTEUR ; j++)
        {
            if (carte[i][j] == MARIO) // Si Mario se trouve à cette position
            {
                positionJoueur.x = i;
                positionJoueur.y = j;
                carte[i][j] = VIDE;
            }
        }
    }
    // Activation de la répétition des touches
    SDL_EnableKeyRepeat(100, 100);
    while (continuer)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                continuer = 0;
                break;
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym)
                {
                    case SDLK_ESCAPE:
                        continuer = 0;
                        break;
                    case SDLK_UP:
                        marioActuel = mario[HAUT];
                        deplacerJoueur(carte, &positionJoueur, HAUT);
                        break;
                    case SDLK_DOWN:
                        marioActuel = mario[BAS];
                        deplacerJoueur(carte, &positionJoueur, BAS);
                        break;
                    case SDLK_RIGHT:
                        marioActuel = mario[DROITE];
                        deplacerJoueur(carte, &positionJoueur, DROITE);
                        break;
                    case SDLK_LEFT:
                        marioActuel = mario[GAUCHE];
                        deplacerJoueur(carte, &positionJoueur, GAUCHE);
                        break;
                }
                break;
        }

        // Effacement de l'écran
        SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));
        SDL_BlitSurface(menu, NULL, ecran, &positionMenu);
        SDL_Flip(ecran);
        // Placement des objets à l'écran
        objectifsRestants = 0;

        for (i = 0 ; i < NB_BLOCS_LARGEUR ; i++)
        {
            for (j = 0 ; j < NB_BLOCS_HAUTEUR ; j++)
            {
                position.x = i * TAILLE_BLOC;
                position.y = j * TAILLE_BLOC;

                switch(carte[i][j])
                {
                    case MUR:
                        SDL_BlitSurface(mur, NULL, ecran, &position);
                        break;
                    case CAISSE:
                        SDL_BlitSurface(caisse, NULL, ecran, &position);
                        break;
                    case CAISSE_OK:
                        SDL_BlitSurface(caisseOK, NULL, ecran, &position);
                        break;
                    case OBJECTIF:
                        SDL_BlitSurface(objectif, NULL, ecran, &position);
                        objectifsRestants = 1;
                        break;
                }
            }
        }
    }

    SDL_FreeSurface(menu);
    SDL_Quit();

    return EXIT_SUCCESS;
}