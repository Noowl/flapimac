#ifndef SPACESHIP_H
    #define SPACESHIP_H

    #include <SDL/SDL.h>
    #include <GL/gl.h>
    #include <GL/glu.h>
    #include <stdlib.h>
    #include <stdio.h>
    #include <assert.h>
    #include <time.h>
    #include "player.h"

    typedef struct spaceship {
        Coord Pmin;
        Coord Pmax;
        Color c;
        GLuint textureID;
        struct spaceship *next;
    } Spaceship, *Enemies;

    typedef struct eMissile {
        Coord Pmin;
        Coord Pmax;
        Color c;
        GLuint textureID;
        struct eMissile *next;
    } Emissile, *Eshot;


    /*
    *   allocates memory to a spaceship
    *   parameters are : x : position x
    *                    y : position y
    *   @return Enemies
    */
    Enemies allocSpaceship(int x, int y);


    /*
    *   adds spaceship to the enemies list
    *   parameters are : *e : enemies list pointer
    *                    x : position x
    *                    y : position y
    */
    void addSpaceship(Enemies *e, int x, int y);

    /*
    *   deletes a spaceship from the enemies list and free memory
    *   parameters are : *e : enemies list pointer
    *                    *s : spaceship pointer
    */
    void deleteSpaceshipFromEnemies(Enemies *e, Spaceship *s);

    /*
    *   draws a spaceship thanks to the spaceship bouding box
    *   parameter is : s : spaceship
    */
    void drawSpaceship(Spaceship s);

    /*
    *   goes through the enemies list and calls the drawing function for each elements
    *   parameter is : e : enemies list
    */
    void drawEnemies(Enemies e);

    /*
    *   allocates memory to an enemy missile
    *   parameters are : x : position x
    *                    y : position y
    *                    textureID : the id of the enemy missile texture
    *   @return Eshot
    */
    Eshot allocEmissile(float x, float y, GLuint textureID);

    /*
    *   allows enemies to randomly shot
    *   parameter are : *es enemies shots list pointer
    *                    e : enemies list
    *                    p : player (to only allows enemies that are in the player range to shot)
    *                    textureID : texture ID of an enemy missile
    */
    void RandomizerEshot(Eshot *es, Enemies e, Player p, GLuint textureID);

    /*
    *   deletes a missile from the enemies shots list and free memory
    *   parameters are : *es : enemies shots list pointer
    *                    *em : enemy missile pointer
    */
    void deleteMissileFromEshot(Eshot *es, Emissile *em);

    /*
    *   adds missile to the enemies shots list
    *   parameters are : *s : enemiesr shots list pointer
    *                    spaceship : spaceship
    *                    textureID : the id of the enemy missile texture
    */
    void addEmissile(Eshot *s, Spaceship spaceship, GLuint textureID);

    /*
    *   draws an enemy missile thanks to the enemy missile bouding box
    *   parameter is : em : enemy missile
    */
    void drawEmissile(Emissile em);

    /*
    *   goes through the enemies shots list and calls the drawing function for each elements
    *   parameter is : es : enemies shots list
    */
    void drawEshot(Eshot es);

    /*
    *   moves each enemies shot
    *   parameter is : *es enemies shots list pointer
    */
    void moveEshot(Eshot *es);


#endif