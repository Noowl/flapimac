#include "player.h"

/*
*   allocates memory to the player
*   parameters are : x : position x
*                    y : position y
*   @return Player
*/
Player allocPlayer(int x, int y){
	Player p;
	p.Pmin.x = x;
	p.Pmin.y = y;
	p.Pmax.x = x + 1;
	p.Pmax.y = y + 1;
    
    p.c.red = 248;
    p.c.green = 254;
    p.c.blue = 14;

    p.speedX = 0.5;
    p.speedY = 0.5;

    p.currentBonus = 0;

	return p;
}


/*
*   draw the player thanks to the player bouding box
*   parameter is : p : player
*/
void drawPlayer(Player p){
    glBindTexture(GL_TEXTURE_2D, p.textureID);
    glBegin(GL_QUADS);
        glTexCoord2f(0,0);
        glVertex2f(p.Pmax.x-1, p.Pmax.y);
        glTexCoord2f(1,0);
        glVertex2f(p.Pmax.x, p.Pmax.y);
        glTexCoord2f(1,1);
        glVertex2f(p.Pmin.x+1, p.Pmin.y);
        glTexCoord2f(0,1);
        glVertex2f(p.Pmin.x, p.Pmin.y);
    glEnd();
}

/*
*   up and down the player depending of the int parameters (0 goes down, 1 goes up)
*   parameter are : *p : player pointer
*                   action : int specifying direction 
*/
void movePlayer(Player *p, int action){
    if (action == 1){
        if (p->Pmax.y < MAP_HEIGHT){
            p->Pmin.y += p->speedX;
            p->Pmax.y += p->speedX;
        }
    }
    else if (p->Pmin.y > 0){
        p->Pmin.y -= p->speedX;
        p->Pmax.y -= p->speedX;
    }
}

/*
*   fix the x coords of the player
*   parameter are : *p : player pointer
*/
void staticPlayer(Player *p){
    p->Pmin.x = p->Pmin.x + 0.2;
    p->Pmax.x = p->Pmax.x + 0.2;
}

/*
*   allocates memory to a player missile
*   parameters are : x : position x
*                    y : position y
*                    speedX : speed for the x position
*                    speedY : speed for the y position
*                    textureID : texture ID of a player missile
*   @return Pshot
*/
Pshot allocPmissile(float x, float y, float speedX, float speedY, GLuint textureID){
    Pshot m;
    m = malloc(sizeof(Pmissile));
    if( m != NULL){
        m->Pmin.x = x;
        m->Pmin.y = y;
        m->Pmax.x = x + 1;
        m->Pmax.y = y + 1;

        m->c.red = 248;
        m->c.green = 254;
        m->c.blue = 14;

        m->textureID = textureID;

        m->speedX = speedX;
        m->speedY = speedY;

        m->next = NULL;
    }
    return m;
}

/*
*   add missile to the player shots list
*   parameters are : *s : player shots list pointer
*                    p : player
*                    speedX : speed of the x position
*                    speedY : speed of the y position
*/
void addMissile(Pshot *s, Player p, float speedX, float speedY, GLuint textureID){
    if(*s == NULL){
        *s = allocPmissile(p.Pmin.x, p.Pmin.y, speedX, speedY, textureID);
    }
    else{
        addMissile(&(*s)->next, p, speedX, speedY, textureID);
    }
}

/*
*   delete a missile from the player shots lists and free memory
*   parameters are : *ps : player shots list pointer
*                    pm : player missile
*/
void deleteMissileFromPshot(Pshot *ps, Pmissile *pm){
    if( *ps != NULL ){
        if( *ps == pm){
            Pmissile *tmp = *ps;
            *ps = (*ps)->next;
            free(tmp);
        }
        else{
            Pmissile *tmp = (*ps)->next;
            Pmissile *prev = *ps;
            while( pm != tmp){
                prev = tmp;
                tmp = tmp->next;
            }
            prev->next = tmp ->next;
            free(tmp);
        }
    }
}

/*
*   draw the player missile thanks to the player missile bouding box
*   parameter is : pm : player missile
*/
void drawMissile(Pmissile pm){
    glBindTexture(GL_TEXTURE_2D, pm.textureID);
    glBegin(GL_QUADS);
        glTexCoord2f(0,0);
        glVertex2f(pm.Pmax.x-1, pm.Pmax.y);
        glTexCoord2f(1,0);
        glVertex2f(pm.Pmax.x, pm.Pmax.y);
        glTexCoord2f(1,1);
        glVertex2f(pm.Pmin.x+1, pm.Pmin.y);
        glTexCoord2f(0,1);
        glVertex2f(pm.Pmin.x, pm.Pmin.y);
    glEnd();
}

/*
*   go through the player shots list and call the drawing function for each elements
*   parameter is : ps : player shots list
*/
void drawShot(Pshot ps){
    if(ps != NULL){
        drawMissile(*ps);
        drawShot(ps->next);
    }
}

/*
*   move each player shots according to their speed
*   parameter are : *ps : player shots list pointer
*/
void moveShot(Pshot *ps){
    if(*ps != NULL){
        (*ps)->Pmin.x += (*ps)->speedX;
        (*ps)->Pmax.x += (*ps)->speedX;
        (*ps)->Pmin.y += (*ps)->speedY;
        (*ps)->Pmax.y += (*ps)->speedY;
        
        moveShot(&(*ps)->next);
    }
}