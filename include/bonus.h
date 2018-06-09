#ifndef BONUS_H
	#define BONUS_H

	#include <SDL/SDL.h>
	#include <GL/gl.h>
	#include <GL/glu.h>
	#include <stdlib.h>
	#include <stdio.h>
	#include <SDL/SDL_image.h>
	#include <assert.h>
	#include <time.h>
	#include "player.h"

	extern int MAP_WIDTH;
	extern int MAP_HEIGHT;


	typedef struct bonus {
	    Coord Pmin;
	    Coord Pmax;
	    Color c;
	    GLuint textureID;
	    int type;
	struct bonus *next;
	} Bonus, *Buffs;

	/*
	*   allocates memory to a bonus
	*   parameters are : x : position x
	*                    y : position y
	*   @return Buffs
	*/
	Buffs allocBonus(int x, int y);

	/*
	*   adds bonus to the buffs list
	*   parameters are : *b : buffs list pointer
	*                    x : position x
	*                    y : position y
	*/
	void addBonus(Buffs *b, int x, int y);

	/*
	*   deletes a BONUS from the buffs list and free memory
	*   parameters are : *buffs : buffs list pointer
	*                    *bonus : bonus pointer
	*/
	void deleteBonusFromBuffs(Buffs *buffs, Bonus *bonus);

	/*
	*   goes through the buffs list and set randomly the type of bonus
	*   parameters are : *b : buffs list pointer
	*/
	void randomizerBuffs(Buffs *b);

	/*
	*   draws a bonus thanks to the bonus bouding box
	*   parameter is : b : bonus
	*/
	void drawBonus(Bonus b);

	/*
	*   goes through the buffs list and calls the drawing function for each elements
	*   parameter is : b : buffs list
	*/
	void drawBuffs(Buffs b);

	/*
	*   adds a bonus to the player and set the timer of it
	*   parameter are : *p : player pointer
	*					 b : bonus
	*/
	void addBonusToPlayer(Player *p, Bonus b);
	/*
	*   reset the player bonus if the duration is past
	*   parameter is : *p : player pointer
	*/
	void resetBonus(Player *p);

	/*
	*   reset the player bonus if the duration is past
	*   parameter are : p : player (to draw according to the player coords)
	*					*textureID : array that contains the ID of the textures
	*/
	void drawCurrentBonus(Player p, GLuint *textureID);


#endif