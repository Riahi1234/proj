
#ifndef ENIGME_H_INCLUDED
#define ENIGME_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h> 
#include <SDL/SDL_mixer.h>
#include <time.h>
typedef struct 
{
	SDL_Surface *background[2];
	SDL_Surface *boutons[5];
        SDL_Surface *boutonsVrai[5];
	SDL_Surface *reponses[5];
	SDL_Surface *question;
	SDL_Surface *win;
	SDL_Surface *lost;
	
	SDL_Rect posRepones[5];

	SDL_Rect posQuestion;

	int choix_question;
	int image_courrante;
	int positionVraiReponse;
          
      
}Enigme;


void genererEnigme(Enigme *e,char nom[],int v);//generer enigme

void afficher_Enigme(Enigme *e,SDL_Surface *ecran);
int resolutionEnigme(Enigme *e,int *Game,SDL_Surface *ecran);
int Play_Enigme(Enigme *e,SDL_Surface *ecran,int *Game);




#endif
