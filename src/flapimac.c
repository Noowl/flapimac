#include "flapimac.h"

int main(int argc, char** argv) {
    /* Variable initialization */
    Player player;

    Enemies enemies;
    enemies = NULL;
        
    Walls walls;
    walls = NULL;

    Buffs buffs;
    buffs = NULL;

    Pshot ps;
    ps = NULL;

    Eshot es;
    es = NULL;

    Winline winline;
    winline = NULL;

    int loop = 1;
    int i;
    int action = 0;
    int mode = 0;
    int mapID = 1;
    int selection;
    int gameState = 0;


    /* SDL Initialization */
    if(-1 == SDL_Init(SDL_INIT_VIDEO)) {
        fprintf(stderr, "Impossible to inititialize SDL. End of the program.\n");
        return EXIT_FAILURE;
    }
    
    /* Ouverture d'une fenêtre et création d'un contexte OpenGL */
    if(NULL == SDL_SetVideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, BIT_PER_PIXEL, SDL_OPENGL | SDL_RESIZABLE)) {
        fprintf(stderr, "Impossible to open window. End of the program.\n");
        return EXIT_FAILURE;
    }
    SDL_WM_SetCaption("Space Flapimacintosh", NULL);
    resizeViewport();
    
    /* Texturing variables initialization */
    SDL_Surface* picturePath[MAX_TEXTURE];
    picturePath[0] = IMG_Load("img/player.png");
    picturePath[1] = IMG_Load("img/spaceship.png");
    picturePath[2] = IMG_Load("img/obstacle.png");
    picturePath[3] = IMG_Load("img/bonus1.png");
    picturePath[4] = IMG_Load("img/bonus2.png");
    picturePath[5] = IMG_Load("img/bonus3.png");
    picturePath[6] = IMG_Load("img/pshot.png");
    picturePath[7] = IMG_Load("img/eshot.png");
    picturePath[8] = IMG_Load("img/background-start.jpg");
    picturePath[9] = IMG_Load("img/background-lost.JPG");
    picturePath[10] = IMG_Load("img/background-win.JPG");
    picturePath[11] = IMG_Load("img/background.png");
    picturePath[12] = IMG_Load("img/checkpoint.jpg");
    GLuint textureID[MAX_TEXTURE];
    initializeTextures(picturePath, textureID);
    
    /* Rendering loop */
    while(loop) {

        /* Get time at the start of the loop */
        Uint32 startTime = SDL_GetTicks();
        
        /* Clear the buffer */
        glClear(GL_COLOR_BUFFER_BIT); 

        /* Behaviour of the game */
        switch(gameState){
            case(0): /* starting screen */
                glEnable(GL_TEXTURE_2D);
                    drawStartingBackground(textureID[8]);
                glDisable(GL_TEXTURE_2D);
            break;

            case(1): /* game */
                if(checkWin(player, winline) == 1){
                    gameState = 3;
                }
                else{
                    /* delete all elements that past the screen */
                    cleanWorld(player, &enemies, &ps, &es, &walls, &buffs);

                    /* Enable enemies to randomly shot */
                    RandomizerEshot(&es, enemies, player, textureID[7]);
                    

                    /* draw elements*/
                    glEnable(GL_BLEND);
                    glEnable(GL_TEXTURE_2D);
                        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
                        displayFullScreen(textureID[11], player);
                        drawEnemies(enemies);
                        drawWalls(walls);
                        drawBuffs(buffs);
                        drawWinline(winline);
                        drawShot(ps);
                        drawEshot(es);
                        drawCurrentBonus(player, textureID);
                        drawPlayer(player);
                    glDisable(GL_TEXTURE_2D);
                    glDisable(GL_BLEND);

                    /* move elements */
                    staticPlayer(&player);
                    moveShot(&ps);
                    moveEshot(&es);
                    glTranslatef(-0.2,0,0);
                    if (mode == 1){
                        movePlayer(&player, action);
                    }

                    /* collision detection */
                    if(collisionEnemies(&player, enemies) == 1){
                        gameState = 2;
                    }
                    if(collisionObstacles(&player, walls) == 1){
                        gameState = 2;
                    }
                    if(collisionEshotPlayer(&player, &es) == 1){
                        gameState = 2;
                    }
                    collisionPshotEnemies(&enemies, &ps, player);
                    collisionPshotWalls(&walls, &ps, player);
                    collisionBuffs(&player, &buffs);

                    /* check if the player bonus is ended */
                    if( player.currentBonus != 0){
                        resetBonus(&player);
                    }
                    
                }
            break;

            case(2): /* losing screen */
                glEnable(GL_TEXTURE_2D);
                    displayFullScreen(textureID[9], player);
                glDisable(GL_TEXTURE_2D);
            break;

            case(3): /* winning screen */
                glEnable(GL_TEXTURE_2D);
                    displayFullScreen(textureID[10], player);
                glDisable(GL_TEXTURE_2D);
            break;
        }
    

        /* Events loop */
        SDL_Event e;
        while(SDL_PollEvent(&e)) {

            /* Window closed : */
            if(e.type == SDL_QUIT) {
                loop = 0;
                break;
            }
            
            /* Events behaviour : */
            
            switch(e.type){
                case SDL_KEYDOWN:
                    selection = e.key.keysym.sym;
                    /* up and down player */
                    if (selection == SDLK_UP){
                        mode = 1;
                        action = 1;
                    }
                    if (selection == SDLK_DOWN){
                        mode = 1;
                        action = 0;
                    }
                    break;

                case SDL_KEYUP:
                    selection = e.key.keysym.sym;
                    mode = 0;
                    switch(gameState){
                        case(0): /* starting screen */
                            /* Set the map chose by the user */
                            if(selection == SDLK_KP1)
                                mapID = 1;
                            if(selection == SDLK_KP2)
                                mapID = 2;
                            if(selection == SDLK_KP3)
                                mapID = 3;
                            if(selection == SDLK_SPACE){
                                initializeWorld(&player, &enemies, &walls, &buffs, &winline, mapID); /* initialize world depending of the map chose */
                                randomizerBuffs(&buffs); /* randomize buffs */
                                setTextureID(&player, &enemies, &walls, &buffs, &winline, textureID); /* set texture elements*/
                                gameState = 1;  /* Start the game */
                            }
                        break;

                        case(1): /* game */
                            if (selection == SDLK_SPACE){
                                mode = 2;
                            }
                            if (mode == 2){
                                if(player.currentBonus == 3){ /* bonus which allows player to shoot  bullets */
                                    addMissile(&ps, player, 0.6, 0.3, textureID[6]);
                                    addMissile(&ps, player, 0.6, 0.2, textureID[6]);
                                    addMissile(&ps, player, 0.6, 0.1, textureID[6]);
                                    addMissile(&ps, player, 0.6, 0, textureID[6]);
                                    addMissile(&ps, player, 0.6, -0.1, textureID[6]);
                                    addMissile(&ps, player, 0.6, -0.2, textureID[6]);
                                    addMissile(&ps, player, 0.6, -0.3, textureID[6]);
                                }
                                else{
                                    addMissile(&ps, player, 0.4, 0, textureID[6]);
                                }
                            }
                        break;

                        case(2): /* losing screen */
                            if(selection == SDLK_SPACE){
                                resetWorld(&player, &enemies, &walls, &buffs, &winline, &ps, &es); /* free elements resources */
                                glTranslatef(player.Pmin.x-1,0,0); /* reset the camera */
                                gameState = 0; /* return to the starting screen */
                            }
                        break;
                        case(3): /* winning screen */
                            if(selection == SDLK_SPACE){
                                resetWorld(&player, &enemies, &walls, &buffs, &winline, &ps, &es); /* free elements resources */
                                glTranslatef(player.Pmin.x-1,0,0); /* reset the camera */
                                gameState = 0; /* return to the starting screen */
                            }
                        break;
                    }     
                break;
                
            }
        }

        /* swap beteween front and back buffer : window actualise */
        SDL_GL_SwapBuffers();

        /* time spend */
        Uint32 elapsedTime = SDL_GetTicks() - startTime;

        /* If the time spend is bigger than framerate, program paused */
        if(elapsedTime < FRAMERATE_MILLISECONDS) {
            SDL_Delay(FRAMERATE_MILLISECONDS - elapsedTime);
        }
    }

    /* Free elements resources */ 
    resetWorld(&player, &enemies, &walls, &buffs, &winline, &ps, &es);
    /* Free texturing resources */ 
    for(i = 0; i < MAX_TEXTURE; i++){
        glDeleteTextures(1, &textureID[i]);
        SDL_FreeSurface(picturePath[i]);
    }
    /* Free SDL resources */ 
    SDL_Quit();

    return EXIT_SUCCESS;
}
