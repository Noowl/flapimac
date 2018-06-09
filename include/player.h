#ifndef PLAYER_H
    #define PLAYER_H

    #include <SDL/SDL.h>
    #include <GL/gl.h>
    #include <GL/glu.h>
    #include <stdlib.h>
    #include <stdio.h>
    #include <time.h>  
    #include <SDL/SDL_image.h>
    #include <assert.h>

    extern int MAP_WIDTH;
    extern int MAP_HEIGHT;
    

    typedef struct coord {
        float x;
        float y;
    } Coord;

    typedef struct color {
        int red;
        int green;
        int blue;
    } Color;

    typedef struct player {
        Coord Pmin;
        Coord Pmax;
        Color c;
        float speedX;
        float speedY;
        GLuint textureID;
        int currentBonus;
        struct tm timeBonus;
    } Player;

    typedef struct pMissile {
    	Coord Pmin;
        Coord Pmax;
        Color c;
        GLuint textureID;
        float speedX;
        float speedY;

        struct pMissile *next;
    } Pmissile, *Pshot;

    /*
    *   allocates memory to the player
    *   parameters are : x : position x
    *                    y : position y
    *   @return Player
    */
    Player allocPlayer(int x, int y);


    /*
    *   draws the player thanks to the player bouding box
    *   parameter is : p : player
    */
    void drawPlayer(Player p);
    /*
    *   ups and downs the player depending of the int parameters (0 goes down, 1 goes up)
    *   parameter are : *p : player pointer
    *                   action : int specifying direction 
    */
    void movePlayer(Player *p, int action);

    /*
    *   fixes the x coords of the player
    *   parameter are : *p : player pointer
    */
    void staticPlayer(Player *p);

    /*
    *   allocates memory to a player missile
    *   parameters are : x : position x
    *                    y : position y
    *                    speedX : speed for the x position
    *                    speedY : speed for the y position
    *                    textureID : texture ID of a player missile
    *   @return Pshot
    */
    Pshot allocPmissile(float x, float y, float speedX, float speedY, GLuint textureID);

    /*
    *   adds missile to the player shots list
    *   parameters are : *s : player shots list pointer
    *                    p : player
    *                    speedX : speed of the x position
    *                    speedY : speed of the y position
    */
    void addMissile(Pshot *s, Player p, float speedX, float speedY, GLuint textureID);

    /*
    *   deletes a missile from the player shots lists and free memory
    *   parameters are : *ps : player shots list pointer
    *                    pm : player missile
    */
    void deleteMissileFromPshot(Pshot *ps, Pmissile *pm);

    /*
    *   draw the player missile thanks to the player missile bouding box
    *   parameter is : pm : player missile
    */
    void drawMissile(Pmissile pm);

    /*
    *   goes through the player shots list and calls the drawing function for each elements
    *   parameter is : ps : player shots list
    */
    void drawShot(Pshot ps);

    /*
    *   moves each player shot according to their speed
    *   parameter are : *ps : player shots list pointer
    */
    void moveShot(Pshot *ps);


#endif