#define TAILLE_BLOC         34 // Taille d'un bloc (carré) en pixels
#define NB_BLOCS_LARGEUR    12
#define NB_BLOCS_HAUTEUR    12
#define LARGEUR_FENETRE     TAILLE_BLOC * NB_BLOCS_LARGEUR
#define HAUTEUR_FENETRE     TAILLE_BLOC * NB_BLOCS_HAUTEUR
enum {VIDE, MUR, CAISSE, OBJECTIF, MARIO, CAISSE_OK}; // VIDE = 0, MUR = 1, CAISSE = 2 etc..
void placerMur(SDL_Surface * fenetre, SDL_Surface * mur, SDL_Rect positionMur, int carte[NB_BLOCS_LARGEUR][NB_BLOCS_HAUTEUR]);
void caseMur(int carte[NB_BLOCS_LARGEUR][NB_BLOCS_HAUTEUR], int i, int j) {
    if (carte[i][j] == 1) 
        printf("carte[%d][%d]\n", i, j);
}
void deplacerMario(SDL_Surface * mario, SDL_Rect * positionMario, SDL_Surface * img, int carte[NB_BLOCS_LARGEUR][NB_BLOCS_HAUTEUR], int x, int y, char * direction);