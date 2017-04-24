#define TAILLE_BLOC         34 // Taille d'un bloc (carré) en pixels
#define NB_BLOCS_LARGEUR    12
#define NB_BLOCS_HAUTEUR    12
#define LARGEUR_FENETRE     TAILLE_BLOC * NB_BLOCS_LARGEUR
#define HAUTEUR_FENETRE     TAILLE_BLOC * NB_BLOCS_HAUTEUR
enum {VIDE, MUR, CAISSE, CAISSE2, OBJECTIF, MARIO}; // VIDE = 0, MUR = 1, CAISSE = 2 etc..

void chargerImg(SDL_Surface * surf, SDL_Surface * img) {
	*surf = *img;
}
void initTab(int carte[NB_BLOCS_LARGEUR][NB_BLOCS_HAUTEUR]) {
	int i, j;
	for (i = 0; i < 12; i++) { 
		for (j = 0; j < 12; j++){ 
				carte[i][j] = MUR;
		}
	}
}
void niveau1(int carte[NB_BLOCS_LARGEUR][NB_BLOCS_HAUTEUR]) {
	initTab(carte);
	int i;
	for (i =2; i < 10; i++)
		carte[i][6] = VIDE;
	carte[1][6] = OBJECTIF;
	carte[9][6] = CAISSE;
	carte[10][6] = MARIO;
}
void niveau2(int carte[NB_BLOCS_LARGEUR][NB_BLOCS_HAUTEUR]) {
	initTab(carte);
	int i;	
	carte[2][4] = MARIO;
	carte[3][4] = CAISSE;
	for (i = 4; i < 8; i++)
		carte[i][4] = VIDE;
	for (i = 3; i < 9; i++) {
		carte[6][i] = VIDE;
		carte[7][i] = VIDE;
	}
	carte[8][7] = VIDE;
	for (i = 2; i < 9; i++)
		carte[i][8] = VIDE;
	for (i = 7; i < 10; i++) {
		carte[2][i] = VIDE;
		if (i != 9)
			carte[3][i] = VIDE;
	}
	carte[2][10] = OBJECTIF;
}
void niveau3(int carte[NB_BLOCS_LARGEUR][NB_BLOCS_HAUTEUR]) {
	initTab(carte);
	int i;	
	carte[3][3] = MARIO;
	for (i = 4; i < 8; i++)
		carte[i][3] = VIDE;
	carte[6][4] = CAISSE;
	carte[7][4] = CAISSE2;
	carte[7][5] = VIDE;
	carte[7][6] = OBJECTIF;
	for (i = 5; i < 9; i++)
		carte[6][i] = VIDE;
	carte[6][9] = OBJECTIF;
}
void majMap(SDL_Surface * fenetre, SDL_Surface * mario, SDL_Surface * caisse, SDL_Surface * caisse2, SDL_Surface * mur, SDL_Surface * objectif, int carte[NB_BLOCS_LARGEUR][NB_BLOCS_HAUTEUR]) {
	SDL_FillRect(fenetre, NULL, SDL_MapRGB(fenetre->format, 255, 255, 255));
	SDL_Rect position;
	int i, j;
	for (i = 0; i < 12; i++)
	{
		for (j = 0; j < 12; j++)
		{
			// printf("%d\t", carte[j][i]);
			position.x = i * TAILLE_BLOC;
			position.y = j * TAILLE_BLOC;
			if(carte[i][j] == MUR) 
				SDL_BlitSurface(mur, NULL, fenetre, &position);
			else if(carte[i][j] == OBJECTIF)
				SDL_BlitSurface(objectif, NULL, fenetre, &position);
			else if(carte[i][j] == MARIO)
				SDL_BlitSurface(mario, NULL, fenetre, &position);
			else if(carte[i][j] == CAISSE)
				SDL_BlitSurface(caisse, NULL, fenetre, &position);
			else if(carte[i][j] == CAISSE2)
				SDL_BlitSurface(caisse2, NULL, fenetre, &position);
		}
		// printf("\n");
	}
	// puts("----------------------------------------------------------------");
	SDL_Flip(fenetre);
}
void moove(char inclinaison, SDL_Surface * caisse, SDL_Rect * positionMario, SDL_Rect * positionCaisse, int xm, int ym, int xc, int yc, int newpositionM, int newpositionC, int carte[NB_BLOCS_LARGEUR][NB_BLOCS_HAUTEUR], int * niveau) {
	if (carte[xm][ym] != MUR) {
		// printf("%d\n", carte[xm][ym]);
		if (carte[xm][ym] == CAISSE && carte[xc][yc] != MUR) {
			carte[positionCaisse->x/34][positionCaisse->y/34] = VIDE;
			if (inclinaison == 'h')
				positionCaisse->x=newpositionC;
			else
				positionCaisse->y=newpositionC;
			if(carte[positionCaisse->x/34][positionCaisse->y/34] == OBJECTIF) {
				chargerImg(caisse, IMG_Load("mario/caisse_ok.jpg"));
				*niveau += 1;
			}
			// if (carte[xm][ym] == CAISSE2)
			// 	carte[positionCaisse->x/34][positionCaisse->y/34] = CAISSE2;
			// else
				carte[positionCaisse->x/34][positionCaisse->y/34] = CAISSE;		
		}
		if (carte[xm][ym] == VIDE) {
			carte[positionMario->x/34][positionMario->y/34] = VIDE;
			if (inclinaison == 'h')
				positionMario->x=newpositionM;
			else				
				positionMario->y=newpositionM;
			carte[positionMario->x/34][positionMario->y/34] = MARIO;
		}
	}
}
void deplacement(SDL_Surface * caisse, SDL_Surface * mario, SDL_Rect * positionMario, SDL_Rect * positionCaisse, int carte[NB_BLOCS_LARGEUR][NB_BLOCS_HAUTEUR], char direction, int * niveau) { // 'u' = up, 'd' = down, 'l' = left et 'r' = right.
	switch(direction) {
		case 'u' :
			chargerImg(mario, IMG_Load("mario/mario_haut.gif"));
			moove('v',caisse, positionMario, positionCaisse, positionMario->x/34, positionMario->y/34 - 1, positionCaisse->x/34, positionCaisse->y/34 - 1, positionMario->y-34, positionCaisse->y-34, carte, niveau);
			// if (*niveau == 3)
			// 	moove('v',caisse2, positionMario, positionCaisse2, positionMario->x/34, positionMario->y/34 - 1, positionCaisse2->x/34, positionCaisse2->y/34 - 1, positionMario->y-34, positionCaisse2->y-34, carte, niveau);
			break;
		case 'd' :
			chargerImg(mario, IMG_Load("mario/mario_bas.gif"));
			moove('v',caisse, positionMario, positionCaisse, positionMario->x/34, positionMario->y/34 + 1, positionCaisse->x/34, positionCaisse->y/34 + 1, positionMario->y+34, positionCaisse->y+34,carte, niveau);
			// if (*niveau == 3)
			// 	moove('v',caisse2, positionMario, positionCaisse2, positionMario->x/34, positionMario->y/34 + 1, positionCaisse2->x/34, positionCaisse2->y/34 + 1, positionMario->y+34, positionCaisse2->y+34,carte, niveau);
			break;
		case 'l' :
			chargerImg(mario, IMG_Load("mario/mario_gauche.gif"));
			moove('h', caisse, positionMario, positionCaisse, positionMario->x/34 - 1, positionMario->y/34, positionCaisse->x/34 - 1, positionCaisse->y/34, positionMario->x-34, positionCaisse->x-34,carte, niveau);
			// if (*niveau == 3)
			// 	moove('h', caisse2, positionMario, positionCaisse2, positionMario->x/34 - 1, positionMario->y/34, positionCaisse2->x/34 - 1, positionCaisse2->y/34, positionMario->x-34, positionCaisse2->x-34,carte, niveau);
			break;
		case 'r' :
			chargerImg(mario, IMG_Load("mario/mario_droite.gif"));
			moove('h', caisse, positionMario, positionCaisse, positionMario->x/34 + 1, positionMario->y/34, positionCaisse->x/34 + 1, positionCaisse->y/34, positionMario->x+34, positionCaisse->x+34,carte, niveau);
			// if (*niveau == 3)
			// 	moove('h', caisse2, positionMario, positionCaisse2, positionMario->x/34 + 1, positionMario->y/34, positionCaisse2->x/34 + 1, positionCaisse2->y/34, positionMario->x+34, positionCaisse2->x+34,carte, niveau);
			break;
	}
}
// void freeSurface(int nb , ...) {
// 	int i;
// 	for (i = 0; i <= nb; ++i)
// 	{
		
// 	}
// }