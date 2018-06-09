#include "bonus.h"
static unsigned int BUFF_DURATION = 5;

/*
*   allocates memory to a bonus
*   parameters are : x : position x
*                    y : position y
*   @return Buffs
*/
Buffs allocBonus(int x, int y){
	Buffs b;
	b = malloc(sizeof(Bonus));
	if( b != NULL){
		b->Pmin.x = x;
		b->Pmin.y = y;
		b->Pmax.x = x + 1;
		b->Pmax.y = y + 1;

		b->c.red = 0;
		b->c.green = 0;
		b->c.blue = 255;
		b->type = 0;
		b->next = NULL;
	}
	return b;
}

/*
*   adds bonus to the buffs list
*   parameters are : *b : buffs list pointer
*                    x : position x
*                    y : position y
*/
void addBonus(Buffs *b, int x, int y){
	if(*b == NULL){
		*b = allocBonus(x, y);
	}
	else{
		addBonus(&(*b)->next, x, y);
	}
}

/*
*   deletes a BONUS from the buffs list and free memory
*   parameters are : *buffs : buffs list pointer
*                    *bonus : bonus pointer
*/
void deleteBonusFromBuffs(Buffs *buffs, Bonus *bonus){
	if( *buffs != NULL ){
		if( *buffs == bonus){
			Bonus *tmp = *buffs;
			*buffs = (*buffs)->next;
			free(tmp);
		}
		else{
			Bonus *tmp = (*buffs)->next;
			Bonus *prev = *buffs;
			while( bonus != tmp){
				prev = tmp;
				tmp = tmp->next;
			}
			prev->next = tmp->next;
			free(tmp);
		}
	}
}

/*
*   goes through the buffs list and set randomly the type of bonus
*   parameters are : *b : buffs list pointer
*/
void randomizerBuffs(Buffs *b){
	Buffs tmpB = *b;
	time_t t;
	srand( (unsigned)time(&t) );
	while( tmpB != NULL){
		tmpB->type = rand()%3 + 1;
		tmpB = tmpB->next;
	}
}

/*
*   draws a bonus thanks to the bonus bouding box
*   parameter is : b : bonus
*/
void drawBonus(Bonus b){
    glBindTexture(GL_TEXTURE_2D, b.textureID);
    glBegin(GL_QUADS);
    	glTexCoord2f(0,0);
		glVertex2f(b.Pmax.x-1, b.Pmax.y);
		glTexCoord2f(1,0);
		glVertex2f(b.Pmax.x, b.Pmax.y);
		glTexCoord2f(1,1);
        glVertex2f(b.Pmin.x+1, b.Pmin.y);
        glTexCoord2f(0,1);
		glVertex2f(b.Pmin.x, b.Pmin.y);
	glEnd();
}

/*
*   goes through the buffs list and calls the drawing function for each elements
*   parameter is : b : buffs list
*/
void drawBuffs(Buffs b){
	if(b != NULL){
		drawBonus(*b);
		drawBuffs(b->next);
	}
}

/*
*   adds a bonus to the player and set the timer of it
*   parameter are : *p : player pointer
*					 b : bonus
*/
void addBonusToPlayer(Player *p, Bonus b){
	p->currentBonus = b.type;
	time_t now = time (NULL);
    struct tm tm_now =*localtime(&now); 
    p->timeBonus = tm_now;
}

/*
*   reset the player bonus if the duration is past
*   parameter is : *p : player pointer
*/
void resetBonus(Player *p){
	time_t now = time (NULL);
    struct tm tm_now = *localtime(&now);
	if( difftime(mktime(&tm_now), mktime(&(p->timeBonus))) > BUFF_DURATION ){
		p->currentBonus = 0;
	}
}

/*
*   reset the player bonus if the duration is past
*   parameter are : p : player (to draw according to the player coords)
*					*textureID : array that contains the ID of the textures
*/
void drawCurrentBonus(Player p, GLuint *textureID){
	if(p.currentBonus != 0){
		switch(p.currentBonus){
			case(1):
				glBindTexture(GL_TEXTURE_2D, textureID[3]);
			break;
			case(2):
				glBindTexture(GL_TEXTURE_2D, textureID[4]);
			break;
			case(3):
				glBindTexture(GL_TEXTURE_2D, textureID[5]);
			break;
		}
		glPushMatrix();
        glTranslatef(p.Pmin.x-1,0,0);
	    glBegin(GL_QUADS);
	    glTexCoord2f(0,0);
	      glVertex2f(0,16);
	    glTexCoord2f(1,0);
	      glVertex2f(1,16);
	    glTexCoord2f(1,1);
	      glVertex2f(1,15);
	    glTexCoord2f(0,1);
	      glVertex2f(0,15);
	    glEnd();
	   glPopMatrix();
	}
}