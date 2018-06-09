#ifndef PHYSIC_H
	#define PHYSIC_H

	#include <SDL/SDL.h>
	#include <GL/gl.h>
	#include <GL/glu.h>
	#include <stdlib.h>
	#include <stdio.h>
	#include <SDL/SDL_image.h>
	#include <assert.h>
	#include "world.h"

	extern int MAP_WIDTH;
	extern int MAP_HEIGHT;
	

	/*
	*   compares coords of two elements
	*   parameters are : Amin : bounding box min of the first element
	*                    Amax : bounding box max of the first element
	*					 Bmin : bounding box min of the second element
	*                    Bmax : bounding box max of the second element
	*   @return 1 if a collision is detected else 0
	*/
	int compareCoord(Coord Amin, Coord Amax, Coord Bmin, Coord Bmax);

	/*
	*   go through the walls list and check if a collision with the player is detected
	*   parameters are : *p : player pointer
	*                    w : wall list
	*   @return 1 if a collision is detected else 0
	*/
	int collisionObstacles(Player *p, Walls w);

	/*
	*   go through the walls list and the player shots lists and check if a collision beteween them exists. Deletes elements then.
	*   parameters are : *w : walls list pointer
	*                    *s : player shots list
	*					 p : player (to check the current bonus)
	*/
	void collisionPshotWalls(Walls *w, Pshot *s, Player p);

	/*
	*   go through the enemies list and the player shots lists and check if a collision beteween them exists. Deletes elements then.
	*   parameters are : *e : enemies list pointer
	*                    *s : player shots list
	*					 p : player (to check the current bonus)
	*/
	void collisionPshotEnemies(Enemies *e, Pshot *s, Player p);

	/*
	*   go through the enemies list and check if a collision with the player exist.
	*   parameters are : *p : player pointer
	*					 e : enemies list 
	*   @return 1 if a collision is detected else 0
	*/
	int collisionEnemies(Player *p, Enemies e);

	/*
	*   go through the enemies shots list and check if a collision with the player exist.
	*   parameters are : *p : player pointer
	*					 *s : enemies shots list pointer 
	*   @return 1 if a collision is detected else 0
	*/
	int collisionEshotPlayer(Player *p, Eshot *s);
	/*
	*   go through the buffs list and check if a collision with the player exist. Give the bonus to the player if there is.
	*   parameters are : *p : player pointer
	*					 *b : buffs list pointer 
	*   @return 1 if a collision is detected else 0
	*/
	int collisionBuffs(Player *p, Buffs *b);
	/*
	*   go through the winline list and check if a collision with the player exist.
	*   parameters are : p : player
	*					 w : winline list
	*   @return 1 if a collision is detected else 0
	*/
	int checkWin(Player p, Winline w);

#endif