#include "physic.h"

/*
*   compares coords of two elements
*   parameters are : Amin : bounding box min of the first element
*                    Amax : bounding box max of the first element
*					 Bmin : bounding box min of the second element
*                    Bmax : bounding box max of the second element
*   @return 1 if a collision is detected else 0
*/
int compareCoord(Coord Amin, Coord Amax, Coord Bmin, Coord Bmax){
	return (abs(Amin.x - Bmin.x) * 2 < 2) && (abs(Amax.y - Bmax.y) * 2 < 2);
}

/*
*   go through the walls list and check if a collision with the player is detected
*   parameters are : *p : player pointer
*                    w : wall list
*   @return 1 if a collision is detected else 0
*/
int collisionObstacles(Player *p, Walls w){
	if(p->currentBonus != 1){
	    while(w != NULL){
			if (compareCoord(p->Pmin, p->Pmax, w->Pmin, w->Pmax) == 1){
	            return 1;
		    }
			w = w->next;
		}
	    return 0;
	}
	return 0;
}

/*
*   go through the walls list and the player shots lists and check if a collision beteween them exists. Deletes elements then.
*   parameters are : *w : walls list pointer
*                    *s : player shots list
*					 p : player (to check the current bonus)
*/
void collisionPshotWalls(Walls *w, Pshot *s, Player p){
	Walls tmpW = *w;
	Pshot tmpS = *s;

	while(tmpW != NULL){
		while(tmpS != NULL){
			if(compareCoord(tmpW->Pmin, tmpW->Pmax, tmpS->Pmin, tmpS->Pmax) == 1){
				if(p.currentBonus != 2){
					deleteMissileFromPshot(s, tmpS);
				}
				else{
					deleteObstacleFromWalls(w, tmpW);
				}
			}
			tmpS = tmpS->next;
		}
		tmpS = *s;
		tmpW = tmpW->next;
	}
}

/*
*   go through the enemies list and the player shots lists and check if a collision beteween them exists. Deletes elements then.
*   parameters are : *e : enemies list pointer
*                    *s : player shots list
*					 p : player (to check the current bonus)
*/
void collisionPshotEnemies(Enemies *e, Pshot *s, Player p){
	Enemies tmpE = *e;
	Pshot tmpS = *s;

	while(tmpE != NULL){
		while(tmpS != NULL){
			if(compareCoord(tmpE->Pmin, tmpE->Pmax, tmpS->Pmin, tmpS->Pmax) == 1){
				deleteSpaceshipFromEnemies(e, tmpE);
				if(p.currentBonus != 2){
					deleteMissileFromPshot(s, tmpS);
				}
			}
			tmpS = tmpS->next;
		}
		tmpS = *s;
		tmpE = tmpE->next;
	}
}

/*
*   go through the enemies list and check if a collision with the player exist.
*   parameters are : *p : player pointer
*					 e : enemies list 
*   @return 1 if a collision is detected else 0
*/
int collisionEnemies(Player *p, Enemies e){
	if(p->currentBonus != 1){
		while(e != NULL){
			if (compareCoord(p->Pmin, p->Pmax, e->Pmin, e->Pmax) == 1){
		        return 1;
		    }
			e = e->next;
		}
		return 0;
	}
	return 0;
}

/*
*   go through the enemies shots list and check if a collision with the player exist.
*   parameters are : *p : player pointer
*					 *s : enemies shots list pointer 
*   @return 1 if a collision is detected else 0
*/
int collisionEshotPlayer(Player *p, Eshot *s){
	if(p->currentBonus != 1){
		Eshot tmpS = *s;
		while(tmpS != NULL){
			if(compareCoord(p->Pmin, p->Pmax, tmpS->Pmin, tmpS->Pmax) == 1){
				return 1;
			}
			tmpS = tmpS->next;
		}
		return 0;
	}
	return 0;
}

/*
*   go through the buffs list and check if a collision with the player exist. Give the bonus to the player if there is.
*   parameters are : *p : player pointer
*					 *b : buffs list pointer 
*   @return 1 if a collision is detected else 0
*/
int collisionBuffs(Player *p, Buffs *b){
	Buffs tmpB = *b;
	while(tmpB != NULL){
		if ( compareCoord(p->Pmin, p->Pmax, (*b)->Pmin, (*b)->Pmax) == 1){
	        addBonusToPlayer(p, *tmpB);
	        deleteBonusFromBuffs(b, tmpB);
	        return 1;
	    }
		tmpB = tmpB->next;
	}
	return 0;
}

/*
*   go through the winline list and check if a collision with the player exist.
*   parameters are : p : player
*					 w : winline list
*   @return 1 if a collision is detected else 0
*/
int checkWin(Player p, Winline w){
	while(w != NULL){
		if( compareCoord(p.Pmin, p.Pmax, w->Pmin, w->Pmax) == 1){
			return 1;
		}
		w = w->next;
	}
	return 0;
}