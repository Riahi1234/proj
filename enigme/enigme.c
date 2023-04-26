
#include "enigme.h"

void genererEnigme(Enigme *e,char nom[],int v)
{
        SDL_Color couleurNoire={0,0,0};
	TTF_Font *police;
	TTF_Init();


	e->background[0]=IMG_Load("enigme_pic/Backg.png");//background enigme
	e->background[1]=IMG_Load("enigme_pic/enigmes.png");//background ou les questions 

	srand(time(NULL));

        Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024);  
        Mix_Music *music ;
        music=Mix_LoadMUS("son/time.mp3");
        Mix_PlayMusic(music,-1);
	Mix_VolumeMusic(v);

	for(int i=1;i<5;i++)
	{
		char str[30];
		sprintf(str,"enigme_pic/%d.png",i);//i entier ===> chaine de char
		e->boutons[i]=IMG_Load(str);
	}


	e->choix_question=rand()%4;//num de question aleatoire
//***********************************************
	while(e->choix_question==0)
        {
		
		e->choix_question=rand()%4;
	}

//***********************************************	



	police = TTF_OpenFont("text/spacerangeracad.ttf", 50);
	char question[150];
	FILE *fichier;
        fichier=fopen(nom,"r");
        int i=1,boucle=1;




//question
    if(fichier!=NULL)
    {
    	while(fgets((question),15,fichier)!=NULL && boucle==1)
    	{
    		if(e->choix_question==i)

    		{
    			e->question = TTF_RenderText_Blended (police,question,couleurNoire);//chargement de la question
    			boucle=0;//en quit le boucle while
    		}
    		else
                {
    			i++;
    		}
    		
    	} 	
    	fclose(fichier);
    }
    
//reponses
    FILE *fic;
    fic=fopen("reponses.txt", "r");
    int min,max;
    switch(e->choix_question)
    {
    	case 1:
    	{
    		min=1;
    		max=3;
    		break;
    	}
    	case 2:
    	{
    		min=4;
    		max=6;
    		break;
    	}
    	case 3:
    	{
    		min=7;
    		max=9;
    		break;
    	}
    }
    int j=1;
    if(fic!=NULL)
    {
    	char reponses[150];
    	while(fgets((reponses),15,fic)!=NULL && j<=max)
    	{	
    		if(j>min || j==min)
    		{
    			e->reponses[j-min+1]= TTF_RenderText_Blended (police,reponses,couleurNoire);  //chargement des reponses

    		}
    		j++;
    		
    	}
    	fclose(fic);
    }
    

//reponses vrais
    FILE *f;
    f=fopen("vraireponses.txt", "r");
    char vraiReponse[150];
    int k=1,boucle1=1;
    if(f!=NULL)
    {
    	while(fgets((vraiReponse),15,f)!=NULL && boucle1==1)
    	{
    		if(e->choix_question==k)
    		{
    			e->reponses[4]= TTF_RenderText_Blended (police,vraiReponse,couleurNoire);//chargement de la reponse vrai
    			
    			boucle1=0;//en quit le boucle while
    		}
    		else{
    			k++;
    		}
    		
    	} 	
    	fclose(f);
    }
    

    
        e->posRepones[1].x=590;
	e->posRepones[1].y=350;

	e->posRepones[2].x=590;
	e->posRepones[2].y=440;

	e->posRepones[3].x=590;
	e->posRepones[3].y=490;

	e->posRepones[4].x=590;
	e->posRepones[4].y=560;

	e->posQuestion.x=540;
	e->posQuestion.y=250;

	e->image_courrante=1;


	
//***************************************************
	e->positionVraiReponse=rand()%5;

	while(e->positionVraiReponse==0)
	{
		
		e->positionVraiReponse=rand()%5;
	}

}

//***************************************************
void afficher_Enigme(Enigme *e,SDL_Surface *ecran)
{
	SDL_Rect position;
	position.x = 430 ;
	position.y = 200 ;
	SDL_BlitSurface(e->background[0],NULL,ecran,NULL);
	SDL_BlitSurface(e->background[1],NULL,ecran,&position);

	SDL_BlitSurface(e->boutons[e->image_courrante],NULL,ecran,&position);


	switch(e->positionVraiReponse)
	{
		case 1:
		{
			SDL_BlitSurface(e->reponses[1],NULL,ecran,&(e->posRepones[2]));
			SDL_BlitSurface(e->reponses[2],NULL,ecran,&(e->posRepones[3]));
			SDL_BlitSurface(e->reponses[3],NULL,ecran,&(e->posRepones[4]));
			break;
		}
		case 2:
		{
			SDL_BlitSurface(e->reponses[1],NULL,ecran,&(e->posRepones[1]));
			SDL_BlitSurface(e->reponses[2],NULL,ecran,&(e->posRepones[3]));
			SDL_BlitSurface(e->reponses[3],NULL,ecran,&(e->posRepones[4]));
			break;
		}
		case 3:
		{
			SDL_BlitSurface(e->reponses[1],NULL,ecran,&(e->posRepones[1]));
			SDL_BlitSurface(e->reponses[2],NULL,ecran,&(e->posRepones[2]));
			SDL_BlitSurface(e->reponses[3],NULL,ecran,&(e->posRepones[4]));
			break;
		}
		case 4:
		{
			SDL_BlitSurface(e->reponses[1],NULL,ecran,&(e->posRepones[1]));
			SDL_BlitSurface(e->reponses[2],NULL,ecran,&(e->posRepones[2]));
			SDL_BlitSurface(e->reponses[3],NULL,ecran,&(e->posRepones[3]));
			break;
		}
	}
	

	SDL_BlitSurface(e->reponses[4],NULL,ecran,&(e->posRepones[e->positionVraiReponse]));//la vrai reponse


	SDL_BlitSurface(e->question,NULL,ecran,&(e->posQuestion));
	SDL_Flip(ecran);
}
//
int resolutionEnigme(Enigme *e,int *Game,SDL_Surface *ecran)
{
	if(e->positionVraiReponse==e->image_courrante)
	{
		(*Game)=1;
		return 1;//win
	}
	else
	{
		(*Game)=0;
		return 0;//lost
	}
}

int Play_Enigme(Enigme *e,SDL_Surface *ecran,int *Game)
{
	afficher_Enigme(e,ecran);
	SDL_Event event;
	int c=1;
	while(c)
	{
		afficher_Enigme(e,ecran);

		while(SDL_PollEvent(&event))
		{
		switch (event.type)
		{ 
			case SDL_KEYDOWN:
			{
				if(event.key.keysym.sym==SDLK_UP)
				{
					e->image_courrante--;
					if(e->image_courrante<1)
					{
						e->image_courrante=4;
					}
				}
				else if(event.key.keysym.sym==SDLK_DOWN)
				{
					e->image_courrante++;
					if(e->image_courrante>4)
					{
						e->image_courrante=1;
					}
		
				}
				else if(event.key.keysym.sym==SDLK_RETURN)
				{
					return resolutionEnigme(e,Game,ecran);
				}
				break;
			}

			case SDL_MOUSEBUTTONUP:
			{

				if(event.motion.x>280 && event.motion.x<525 && event.motion.y>255 && event.motion.y<290)
				{
					e->image_courrante=1;	 
					if (event.button.button == SDL_BUTTON_LEFT)
					{ 
						return resolutionEnigme(e,Game,ecran);
					}
					break;
				}
				else if(event.motion.x>280 && event.motion.x<525 && event.motion.y>300 && event.motion.y<335)
				{
					e->image_courrante=2;			 
					if (event.button.button == SDL_BUTTON_LEFT)
					{ 
						return resolutionEnigme(e,Game,ecran);
					}
					break;
				}
				else if(event.motion.x>280 && event.motion.x<525 && event.motion.y>350 && event.motion.y<380)
				{
					e->image_courrante=3;	
					if (event.button.button == SDL_BUTTON_LEFT)
					{ 
						return resolutionEnigme(e,Game,ecran);
					}
					break;
				}
				else if(event.motion.x>280 && event.motion.x<525 && event.motion.y>395 && event.motion.y<425)
				{
					e->image_courrante=4;	
					if (event.button.button == SDL_BUTTON_LEFT)
					{ 
						return resolutionEnigme(e,Game,ecran);
					}
					break;
				}
				break;
			}
		}
}
	}
}
