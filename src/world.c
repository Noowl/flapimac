#include "world.h"

/*
*   allocates memory to wall
*   parameters are : x : position x
*                    y : position y
*   @return Walls
*/
Walls allocObstacle(int x, int y){
	Walls w;
	w = malloc(sizeof(Obstacle));
	if( w != NULL){
		w->Pmin.x = x;
		w->Pmin.y = y;
		w->Pmax.x = x + 1;
		w->Pmax.y = y + 1;
		
		w->c.red = 255;
		w->c.green = 0;
		w->c.blue = 0;
		w->next = NULL;
	}
	return w;	
}

/*
*   adds obstacle to the walls list
*   parameters are : *w : Walls list pointer
*					 x : position x
*                    y : position y
*/
void addObstacle(Walls *w, int x, int y){
	if(*w == NULL){
		*w = allocObstacle(x, y);
	}
	else{
		addObstacle(&(*w)->next, x, y);

	}
}

/*
*   deletes obstacle from the walls list and free memory
*   parameters are : *w : Walls list pointer
*					 *o : obstacle pointer
*/
void deleteObstacleFromWalls(Walls *w, Obstacle *o){
	if( *w != NULL ){
		if( *w == o){
			Obstacle *tmp = *w;
			*w = (*w)->next;
			free(tmp);
		}
		else{
			Obstacle *tmp = (*w)->next;
			Obstacle *prev = *w;
			while( o != tmp){
				prev = tmp;
				tmp = tmp->next;
			}
			prev->next = tmp->next;
			free(tmp);
		}
	}
}

/*
*   draws obstacle thanks to the obstacle bouding box
*	parameter is : o : obstacle
*/
void drawObstacle(Obstacle o){
    glBindTexture(GL_TEXTURE_2D, o.textureID);
    glBegin(GL_QUADS);
    	glTexCoord2f(0,0);
		glVertex2f(o.Pmax.x-1, o.Pmax.y);
		glTexCoord2f(1,0);
		glVertex2f(o.Pmax.x, o.Pmax.y);
		glTexCoord2f(1,1);
        glVertex2f(o.Pmin.x+1, o.Pmin.y);
        glTexCoord2f(0,1);
		glVertex2f(o.Pmin.x, o.Pmin.y);
	glEnd();
}

/*
*   goes through the walls list and calls the drawing function for each elements
*	parameter is : w : walls list
*/
void drawWalls(Walls w){
	if(w != NULL){
		drawObstacle(*w);
		drawWalls(w->next);
	}
}

/*
*   allocates memory to winline
*   parameters are : x : position x
*                    y : position y
*   @return Winline
*/
Winline allocCheckpoint(int x, int y){
	Winline w;
	w = malloc(sizeof(Checkpoint));
	if( w != NULL){
		w->Pmin.x = x;
		w->Pmin.y = y;
		w->Pmax.x = x + 1;
		w->Pmax.y = y + 1;
		
		w->c.red = 50;
		w->c.green = 255;
		w->c.blue = 50;
		w->next = NULL;
	}
	return w;	
}

/*
*   adds checkpoint to the winline list
*   parameters are : *w : winline list pointer
*					 x : position x
*                    y : position y
*/
void addCheckpoint(Winline *w, int x, int y){
	if(*w == NULL){
		*w = allocCheckpoint(x, y);
	}
	else{
		addCheckpoint(&(*w)->next, x, y);

	}
}

/*
*   deletes checkpoint from the winlist and free memory
*   parameters are : *w : Winline list pointer
*					 *c : checkpoint pointer
*/
void deleteCheckpointFromWinline(Winline *w, Checkpoint *c){
	if( *w != NULL ){
		if( *w == c){
			Checkpoint *tmp = *w;
			*w = (*w)->next;
			free(tmp);
		}
		else{
			Checkpoint *tmp = (*w)->next;
			Checkpoint *prev = *w;
			while( c != tmp){
				prev = tmp;
				tmp = tmp->next;
			}
			prev->next = tmp->next;
			free(tmp);
		}
	}
}

/*
*   draws checkpoint thanks to the checkpoint bouding box
*	parameter is : c : checkpoint
*/
void drawCheckpoint(Checkpoint c){
    glBindTexture(GL_TEXTURE_2D, c.textureID);
    glBegin(GL_QUADS);
    	glTexCoord2f(0,0);
		glVertex2f(c.Pmax.x-1, c.Pmax.y);
		glTexCoord2f(1,0);
		glVertex2f(c.Pmax.x, c.Pmax.y);
		glTexCoord2f(1,1);
        glVertex2f(c.Pmin.x+1, c.Pmin.y);
        glTexCoord2f(0,1);
		glVertex2f(c.Pmin.x, c.Pmin.y);
	glEnd();
}

/*
*   goes through the winline list and calls the drawing function for each elements
*	parameter is : w : winline list
*/
void drawWinline(Winline w){
	if(w != NULL){
		drawCheckpoint(*w);
		drawWinline(w->next);
	}
}

/*
*   initializes lists of game elements by opening a ppm file ty to and ID
*	parameters are : *p : player pointer
* 					 *e : enemies list pointer
*					 *w : walls list pointer
*					 *buffs : buffs list pointer
*					 *winline : winline list pointer
*					 mapID : int which represent the map chose by the player
*/
void initializeWorld(Player *p, Enemies *e, Walls *w, Buffs *buffs, Winline *winline, int mapID){
	FILE *map;
	/* Open the map chose by the player */
	switch(mapID){
		case(1):
			map = fopen("map/level1.ppm", "r");
		break;
		case(2):
			map = fopen("map/level2.ppm", "r");
		break;
		case(3):
			map = fopen("map/level3.ppm", "r");
		break;
	}
	
	if(map != NULL){
		int i, j;
		int r, v, b;
		char encoding[MAX];
		char informations[MAX];
		int max;
		/* get first fine of the file which can be P3 or P6 (encoding type) and the second which are files informations */
		if( fgets( encoding, MAX, map ) == NULL || fgets( informations, MAX, map ) == NULL)
			exit(EXIT_FAILURE);
		/* get the third line which is the number of pixels for width and height */
		if( fscanf(map,"%d", &MAP_WIDTH) == EOF || fscanf(map,"%d", &MAP_HEIGHT) == EOF || fscanf(map,"%d", &max) == EOF)
			exit(EXIT_FAILURE);
		
		/* Go through the file 3 by 3 to set elements */
		for(i = 0; i < MAP_HEIGHT; i++){
			for(j = 0; j < MAP_WIDTH; j++){
				if( fscanf(map,"%d", &r) == EOF || fscanf(map,"%d", &v) == EOF || fscanf(map,"%d", &b) == EOF )
					exit(EXIT_FAILURE);

				if(v == 0 && b == 0){ /* if the pixel represent an obstacle */
					addObstacle(w, j, i);	
				}
				else if( r == 0 && b == 0 ){ /* if the pixel represent a spaceship */
					addSpaceship(e, j, i);
				}
				else if( r == 0 && v == 0 ){ /* if the pixel represent a bonus */
					addBonus(buffs, j, i);
				}
				else if( r == 248 && v == 254 && b == 14){ /* if the pixel represent the player */
					*p = allocPlayer(j, i);
				}
				else if( r == 50 && v == 255 && b == 50){ /* if the pixel represent a checkpoint */
					addCheckpoint(winline, j, i);
				}
			}
		}
	}
}

/*
*   deletes elements and free memory when they leave the window
*	parameters are : player : player (needed for the position of elements compared to the player)		 
* 					 *e : enemies list pointer
*					 *ps : player shots list pointer
*					 *es : enemies shots list pointer
*					 *w : walls list pointer
*					 *buffs : buffs list pointer
*/
void cleanWorld(Player p, Enemies *e, Pshot *ps, Eshot *es, Walls *w, Buffs *b){
	float coordScreenPmissile;
	float coordScreenEmissile;
	float coordScreenSpaceship;
	float coordScreenObstacle;
	float coordScreenBonus;
	if( *ps != NULL){
		coordScreenPmissile = (*ps)->Pmax.x - (p.Pmin.x - 1); /* Coords calculted thanks to the player coords */
		if(coordScreenPmissile > MAP_WIDTH || (*ps)->Pmax.y > MAP_HEIGHT){ 
			deleteMissileFromPshot(ps, *ps);
		}
	}
	if( *es != NULL){
		coordScreenEmissile = (*es)->Pmax.x - p.Pmax.x; /* Coords calculted thanks to the player coords */
		if(coordScreenEmissile <= 0){
			deleteMissileFromEshot(es, *es);
		}
	}
	if( *w != NULL){
		coordScreenObstacle = (*w)->Pmax.x - (p.Pmin.x); /* Coords calculted thanks to the player coords */
		if(coordScreenObstacle <= 0){
			deleteObstacleFromWalls(w, *w);
		}
	}
	if( *e != NULL){
		coordScreenSpaceship = (*e)->Pmax.x - (p.Pmin.x - 1); /* Coords calculted thanks to the player coords */
		if(coordScreenSpaceship <= 0){
			deleteSpaceshipFromEnemies(e, *e);
		}
	}
	if( *b != NULL){
		coordScreenBonus = (*b)->Pmax.x - (p.Pmin.x - 1); /* Coords calculted thanks to the player coords */
		if(coordScreenBonus <= 0){
			deleteBonusFromBuffs(b, *b);
		}
	}
}

/*
*   deletes all elements and free memory
*	parameters are : *player : player pointer	 
* 					 *e : enemies list pointer
*					 *w : walls list pointer
*					 *buffs : buffs list pointer
*					 *winline : winline list pointer
*					 *ps : player shots list pointer
*					 *es : enemies shots list pointer
*/
void resetWorld(Player *p, Enemies *e, Walls *w, Buffs *buffs, Winline *winline, Pshot *ps, Eshot *es){
	p = NULL;
	while(*e != NULL){
		deleteSpaceshipFromEnemies(e, *e);
	}
	while(*w != NULL){
		deleteObstacleFromWalls(w, *w);
	}
	while(*buffs != NULL){
		deleteBonusFromBuffs(buffs, *buffs);
	}
	while(*winline != NULL){
		deleteCheckpointFromWinline(winline, *winline);
	}
	while(*ps != NULL){
		deleteMissileFromPshot(ps, *ps);
	}
	while(*es != NULL){
		deleteMissileFromEshot(es, *es);
	}
}

/*
*   generates and binds textures
*	parameters are : picturePath[MAX_TEXTURE] : array which contains the path of the textures
* 					 *textureID : array which contains all the textures ID
*/
void initializeTextures(SDL_Surface* picturePath[MAX_TEXTURE], GLuint *textureID){
	int i;
    for(i = 0; i < MAX_TEXTURE; i++){
		glGenTextures(1, &textureID[i]);
	    glBindTexture(GL_TEXTURE_2D, textureID[i]);
	    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	    if(i>7){ /* jpg files */
	    	glTexImage2D(GL_TEXTURE_2D,0, GL_RGB, picturePath[i]->w, picturePath[i]->h, 0, GL_RGB, GL_UNSIGNED_BYTE, picturePath[i]->pixels);
	    }
	    else{ /* png files */
	    	glTexImage2D(GL_TEXTURE_2D,0, GL_RGBA, picturePath[i]->w, picturePath[i]->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, picturePath[i]->pixels);
    	}
	}
}

/*
*   goes through all elements lists and sets the element->textureID corresponding to the id texture
*	parameters are : *player : player pointer		 
* 					 *e : enemies list pointer
*					 *w : walls list pointer
*					 *buffs : buffs list pointer
*					 *winline : winline list pointer
*    				 *textureID : array which contains all the textures ID
*/
void setTextureID(Player *p, Enemies *e, Walls *w, Buffs *buffs, Winline *winline, GLuint *textureID){
	p->textureID = textureID[0];
	Enemies tmpE = *e;
	while( tmpE != NULL){
	    tmpE->textureID = textureID[1];
	    tmpE = tmpE->next;
	}
	Walls tmpW = *w;
	while( tmpW != NULL){
	    tmpW->textureID = textureID[2];
	    tmpW = tmpW->next;
	}
	Winline tmpWin = *winline;
	while( tmpWin != NULL){
	    tmpWin->textureID = textureID[12];
	    tmpWin = tmpWin->next;
	}
	Buffs tmpB = *buffs;
	while( tmpB != NULL){
	    if( tmpB->type == 1){
	        tmpB->textureID = textureID[3];
	        tmpB = tmpB->next;
	    }
	    else if( tmpB->type == 2 ){
	        tmpB->textureID = textureID[4];
	        tmpB = tmpB->next;
	    }
	    else{
	        tmpB->textureID = textureID[5];
	        tmpB = tmpB->next;
	    }
	    
	}
}

/*
*   draws a texture in full screen by taking the player coords into account
*	parameters are : textureID : the ID of the texture needed to draw
*    				  p : player 
*/
void displayFullScreen(GLuint textureID, Player p){
    glBindTexture(GL_TEXTURE_2D, textureID);
    glPushMatrix();
        glTranslatef(p.Pmin.x-1,0,0);
        glBegin(GL_QUADS);
        glTexCoord2f(0,0);
          glVertex2f(0,16);
        glTexCoord2f(1,0);
          glVertex2f(24,16);
        glTexCoord2f(1,1);
          glVertex2f(24,0);
        glTexCoord2f(0,1);
          glVertex2f(0,0);
        glEnd();
    glPopMatrix();
}

/*
*   draws the starting background in full page
*	parameter is : textureID : the id of the starting background texture
*/
void drawStartingBackground(GLuint textureID){
	glBindTexture(GL_TEXTURE_2D, textureID);
    glBegin(GL_QUADS);
    glTexCoord2f(0,0);
      glVertex2f(0,16);
    glTexCoord2f(1,0);
      glVertex2f(24,16);
    glTexCoord2f(1,1);
      glVertex2f(24,0);
    glTexCoord2f(0,1);
      glVertex2f(0,0);
    glEnd();
}