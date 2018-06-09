#include "spaceship.h"

/*
*   allocates memory to a spaceship
*   parameters are : x : position x
*                    y : position y
*   @return Enemies
*/
Enemies allocSpaceship(int x, int y){
	Enemies e;
	e = malloc(sizeof(Spaceship));
	if( e != NULL){
		e->Pmin.x = x;
		e->Pmin.y = y;
		e->Pmax.x = x + 1;
		e->Pmax.y = y + 1;

		e->next = NULL;
	}
	return e;
}


/*
*   adds spaceship to the enemies list
*   parameters are : *e : enemies list pointer
*                    x : position x
*					 y : position y
*/
void addSpaceship(Enemies *e, int x, int y){
	if(*e == NULL){
		*e = allocSpaceship(x, y);
	}
	else{
		addSpaceship(&(*e)->next, x, y);
	}
}

/*
*   deletes a spaceship from the enemies list and free memory
*   parameters are : *e : enemies list pointer
*                    *s : spaceship pointer
*/
void deleteSpaceshipFromEnemies(Enemies *e, Spaceship *s){
	if( *e != NULL ){
		if( *e == s){
			Spaceship *tmp = *e;
			*e = (*e)->next;
			free(tmp);
		}
		else{
			Spaceship *tmp = (*e)->next;
			Spaceship *prev = *e;
			while( s != tmp){
				prev = tmp;
				tmp = tmp->next;
			}
			prev->next = tmp->next;
			free(tmp);
		}
	}
}

/*
*   draws a spaceship thanks to the spaceship bouding box
*   parameter is : s : spaceship
*/
void drawSpaceship(Spaceship s){
	glBindTexture(GL_TEXTURE_2D, s.textureID);
    glBegin(GL_QUADS);
   		glTexCoord2f(0,0);
		glVertex2f(s.Pmax.x-1, s.Pmax.y);
		glTexCoord2f(1,0);
		glVertex2f(s.Pmax.x, s.Pmax.y);
		glTexCoord2f(1,1);
        glVertex2f(s.Pmin.x+1, s.Pmin.y);
        glTexCoord2f(0,1);
		glVertex2f(s.Pmin.x, s.Pmin.y);
	glEnd();
}

/*
*   goes through the enemies list and calls the drawing function for each elements
*   parameter is : e : enemies list
*/
void drawEnemies(Enemies e){
	if(e != NULL){
		drawSpaceship(*e);
		drawEnemies(e->next);
	}
}

/*
*   allocates memory to an enemy missile
*   parameters are : x : position x
*                    y : position y
*					 textureID : the id of the enemy missile texture
*   @return Eshot
*/
Eshot allocEmissile(float x, float y, GLuint textureID){
    Eshot m;
    m = malloc(sizeof(Emissile));
    if( m != NULL){
        m->Pmin.x = x;
        m->Pmin.y = y;
        m->Pmax.x = x + 1;
        m->Pmax.y = y + 1;

        m->c.red = 0;
        m->c.green = 255;
        m->c.blue = 0;

        m->textureID = textureID;
        m->next = NULL;
    }
    return m;
}

/*
*   allows enemies to randomly shot
*   parameter are : *es enemies shots list pointer
*					 e : enemies list
*				  	 p : player (to only allows enemies that are in the player range to shot)
* 					 textureID : texture ID of an enemy missile
*/
void RandomizerEshot(Eshot *es, Enemies e, Player p, GLuint textureID){
	float coordScreenSpaceship;
	while( e != NULL){
		coordScreenSpaceship = e->Pmax.x - p.Pmax.x;
		if(coordScreenSpaceship > 0 && coordScreenSpaceship < MAP_WIDTH){
			
			int randomised = rand()%40;
			if(randomised == 3){
				addEmissile(es, *e, textureID);
			}
		}
		e = e->next;
	}
}

/*
*   deletes a missile from the enemies shots list and free memory
*   parameters are : *es : enemies shots list pointer
*                    *em : enemy missile pointer
*/
void deleteMissileFromEshot(Eshot *es, Emissile *em){
	if( *es != NULL ){
		if( *es == em){
			Emissile *tmp = *es;
			*es = (*es)->next;
			free(tmp);
		}
		else{
			Emissile *tmp = (*es)->next;
			Emissile *prev = *es;
			while( em != tmp){
				prev = tmp;
				tmp = tmp->next;
			}
			prev->next = tmp ->next;
			free(tmp);
		}
	}
}

/*
*   adds missile to the enemies shots list
*   parameters are : *s : enemiesr shots list pointer
*                    spaceship : spaceship
*					 textureID : the id of the enemy missile texture
*/
void addEmissile(Eshot *s, Spaceship spaceship, GLuint textureID){
    if(*s == NULL){
        *s = allocEmissile(spaceship.Pmin.x, spaceship.Pmin.y, textureID);
    }
    else{
        addEmissile(&(*s)->next, spaceship, textureID);
    }
}

/*
*   draws an enemy missile thanks to the enemy missile bouding box
*   parameter is : em : enemy missile
*/
void drawEmissile(Emissile em){
    glBindTexture(GL_TEXTURE_2D, em.textureID);
    glBegin(GL_QUADS);
    	glTexCoord2f(0,0);
        glVertex2f(em.Pmax.x-1, em.Pmax.y);
        glTexCoord2f(1,0);
        glVertex2f(em.Pmax.x, em.Pmax.y);
        glTexCoord2f(1,1);
        glVertex2f(em.Pmin.x+1, em.Pmin.y);
        glTexCoord2f(0,1);
        glVertex2f(em.Pmin.x, em.Pmin.y);
    glEnd();
}

/*
*   goes through the enemies shots list and calls the drawing function for each elements
*   parameter is : es : enemies shots list
*/
void drawEshot(Eshot es){
    if(es != NULL){
        drawEmissile(*es);
        drawEshot(es->next);
    }
}

/*
*   moves each enemies shot
*   parameter is : *es enemies shots list pointer
*/
void moveEshot(Eshot *es){
    if(*es != NULL){
        (*es)->Pmin.x = (*es)->Pmin.x - 0.2;
        (*es)->Pmax.x = (*es)->Pmax.x - 0.2;
        moveEshot(&(*es)->next);
    }
}