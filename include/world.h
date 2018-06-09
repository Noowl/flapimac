#ifndef WORLD_H
	#define WORLD_H

	#include <SDL/SDL.h>
	#include <SDL/SDL_image.h>
	#include <GL/gl.h>
	#include <GL/glu.h>
	#include <stdlib.h>
	#include <stdio.h>
	#include <assert.h>
	#include "world.h"
	#include "player.h"
	#include "spaceship.h"
	#include "bonus.h"

	extern int MAP_WIDTH;
	extern int MAP_HEIGHT;
	extern int MAX_TEXTURE;

	#define MAX 1000

	typedef struct obstacle {
	    Coord Pmin;
	    Coord Pmax;
	    Color c;
	    GLuint textureID;
	    struct obstacle *next;
	} Obstacle, *Walls;

	typedef struct checkpoint {
	    Coord Pmin;
	    Coord Pmax;
	    Color c;
	    GLuint textureID;
	    struct checkpoint *next;
	} Checkpoint, *Winline;


	/*
	*   allocates memory to wall
	*   parameters are : x : position x
	*                    y : position y
	*   @return Walls
	*/
	Walls allocObstacle(int x, int y);

	/*
	*   adds obstacle to the walls list
	*   parameters are : *w : Walls list pointer
	*					 x : position x
	*                    y : position y
	*/
	void addObstacle(Walls *w, int x, int y);

	/*
	*   deletes obstacle from the walls list and free memory
	*   parameters are : *w : Walls list pointer
	*					 *o : obstacle pointer
	*/
	void deleteObstacleFromWalls(Walls *w, Obstacle *o);

	/*
	*   draws obstacle thanks to the obstacle bouding box
	*	parameter is : o : obstacle
	*/
	void drawObstacle(Obstacle o);

	/*
	*   goes through the walls list and calls the drawing function for each elements
	*	parameter is : w : walls list
	*/
	void drawWalls(Walls w);

	/*
	*   allocates memory to winline
	*   parameters are : x : position x
	*                    y : position y
	*   @return Winline
	*/
	Winline allocCheckpoint(int x, int y);

	/*
	*   adds checkpoint to the winline list
	*   parameters are : *w : winline list pointer
	*					 x : position x
	*                    y : position y
	*/
	void addCheckpoint(Winline *w, int x, int y);

	/*
	*   deletes checkpoint from the winlist and free memory
	*   parameters are : *w : Winline list pointer
	*					 *c : checkpoint pointer
	*/
	void deleteCheckpointFromWinline(Winline *w, Checkpoint *c);

	/*
	*   draws checkpoint thanks to the checkpoint bouding box
	*	parameter is : c : checkpoint
	*/
	void drawCheckpoint(Checkpoint c);

	/*
	*   goes through the winline list and calls the drawing function for each elements
	*	parameter is : w : winline list
	*/
	void drawWinline(Winline w);

	/*
	*   initializes lists of game elements by opening a ppm file ty to and ID
	*	parameters are : *p : player pointer
	* 					 *e : enemies list pointer
	*					 *w : walls list pointer
	*					 *buffs : buffs list pointer
	*					 *winline : winline list pointer
	*					 mapID : int which represent the map chose by the player
	*/
	void initializeWorld(Player *p, Enemies *e, Walls *w, Buffs *buffs, Winline *winline, int mapID);

	/*
	*   deletes elements and free memory when they leave the window
	*	parameters are : player : player (needed for the position of elements compared to the player)		 
	* 					 *e : enemies list pointer
	*					 *ps : player shots list pointer
	*					 *es : enemies shots list pointer
	*					 *w : walls list pointer
	*					 *buffs : buffs list pointer
	*/
	void cleanWorld(Player p, Enemies *e, Pshot *ps, Eshot *es, Walls *w, Buffs *b);

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
	void resetWorld(Player *p, Enemies *e, Walls *w, Buffs *buffs, Winline *winline, Pshot *ps, Eshot *es);

	/*
	*   generates and binds textures
	*	parameters are : picturePath[MAX_TEXTURE] : array which contains the path of the textures
	* 					 *textureID : array which contains all the textures ID
	*/
	void initializeTextures(SDL_Surface* picturePath[MAX_TEXTURE], GLuint *textureID);

	/*
	*   goes through all elements lists and sets the element->textureID corresponding to the id texture
	*	parameters are : *player : player pointer		 
	* 					 *e : enemies list pointer
	*					 *w : walls list pointer
	*					 *buffs : buffs list pointer
	*					 *winline : winline list pointer
	*    				 *textureID : array which contains all the textures ID
	*/
	void setTextureID(Player *p, Enemies *e, Walls *w, Buffs *buffs, Winline *winline, GLuint *textureID);

	/*
	*   draws a texture in full screen by taking the player coords into account
	*	parameters are : textureID : the ID of the texture needed to draw
	*    				  p : player 
	*/
	void displayFullScreen(GLuint textureID, Player p);

	/*
	*   draws the starting background in full page
	*	parameter is : textureID : the id of the starting background texture
	*/
	void drawStartingBackground(GLuint textureID);

#endif