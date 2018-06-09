#ifndef FLAPIMAC_H
	#define FLAPIMAC_H

	#include <SDL/SDL.h>
	#include <SDL/SDL_image.h>
	#include <GL/gl.h>
	#include <GL/glu.h>
	#include <stdlib.h>
	#include <stdio.h>
	#include <assert.h>
	#include <time.h>
	#include "world.h"
	#include "player.h"
	#include "spaceship.h"
	#include "physic.h"
	#include "bonus.h"
	
	/* Number of elements initialized in function initializeWorld */
	int MAP_WIDTH;
	int MAP_HEIGHT;
	/* Number of textures */
	int MAX_TEXTURE = 13;

	/* Size of window */
	static unsigned int WINDOW_WIDTH = 1080;
	static unsigned int WINDOW_HEIGHT = 720;

	/* Number of bit per pixel of window */
	static const unsigned int BIT_PER_PIXEL = 32;

	/* Minimal number (in ms) between two frames */
	static const Uint32 FRAMERATE_MILLISECONDS = 1000/20;

	/* Set Viewport */
	void resizeViewport() {
	    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
	    glMatrixMode(GL_PROJECTION);
	    glLoadIdentity();
	    gluOrtho2D(0., 24, 0., 16);
	    SDL_SetVideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, BIT_PER_PIXEL, SDL_OPENGL | SDL_RESIZABLE);
	}


#endif