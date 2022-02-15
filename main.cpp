#include <cstdio>
#include <cstdlib>
#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <string>
#include <vector>
#include <math.h>
#include "init.h"
#include "shader.h"
#include "mesh.h"
#include "transform.h"
#include "shapes.h"
#include "player.h"
#include "ray.h"
#define PI 3.14159265359
#define P2 PI/2
#define P3 3*PI/2
#define DEGREE 0.0174532925

float dist(float ax, float ay, float bx, float by, float ang){
    //printf("ax: %f, ay: %f, bx: %f, by: %f angle: %f\n", ax, ay, bx, by, ang);
    return sqrt((bx - ax) * (bx - ax) + (by - ay) * (by - ay));
}

int main(){
    //making mapArray;
	unsigned int mapArray[64] = {
	    1, 1, 1, 1, 1, 1, 1, 1,
	    1, 0, 0, 0, 1, 0, 0, 1,
	    1, 0, 1, 0, 1, 0, 0, 1,
	    1, 0, 0, 0, 1, 1, 0, 1,
	    1, 0, 0, 0, 0, 0, 0, 1,
	    1, 0, 1, 0, 0, 1, 1, 1,
	    1, 0, 1, 0, 0, 0, 0, 1,
        1, 1, 1, 1, 1, 1, 1, 1
	};
	//Making init object from init class
	init init(512, 512, "window1");
	unsigned int oneCounter = 0;
	for(unsigned int i = 0; i < 64; i++){
		if(mapArray[i] >= 1){
            oneCounter++;
		}
	}
	printf("OneCounter: %d", oneCounter);

	std::vector<rect*> rectArr;
	std::vector<rect*> linesXArr;
	std::vector<rect*> linesYArr;

	rectArr.reserve(oneCounter);
	linesXArr.reserve(6);
	linesYArr.reserve(6);

	for(unsigned int i = 0; i < oneCounter; i++){
		rectArr.push_back(new rect(64, 64, init.getScreenWidth(), init.getScreenHeight(), glm::vec4(1.0f, 0.0f, 0.0f, 1.0f)));
	}

	for(int i = 0; i < 7; i++){
        linesXArr.push_back(new rect(1, init.getScreenHeight(), init.getScreenWidth(), init.getScreenHeight(), glm::vec4(0.2f, 0.2f, 0.2f, 1.0f)));
        linesYArr.push_back(new rect(init.getScreenWidth(), 1, init.getScreenWidth(), init.getScreenHeight(), glm::vec4(0.2f, 0.2f, 0.2f, 1.0f)));
	}
    player mainPlayer(glm::vec3(0.0f, 0.0f, 0.0f), init.getScreenWidth(), init.getScreenHeight(), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
	SDL_Event e;
	unsigned int counter = 0;
	float playerXPos = -0.2f;
	float playerYPos = 0.1f;
	float playerXDelta = 0.0f;
	float playerYDelta = 0.0;
	float playerAngle = P2;
	float rayAngle = playerAngle;
    bool changeView = true;
	int dof = 0;
	int next = 0;
	playerXDelta = cos(playerAngle);
    playerYDelta = sin(playerAngle);
	float startGapX = -1.0f - rectArr[0]->getUniformWidth()/2;
    float startGapY = 1.0f + rectArr[0]->getUniformHeight()/2;
    std::vector<glm::vec3> lineCoords;
    std::vector<glm::vec3> rayCoords;
    rayCoords.reserve(4);

    for(int i = 0; i < 4; i++){
        rayCoords.push_back(glm::vec3(0.0f, 0.0f, 0.0f));
    }
    ray baseRay;
    ray viewRay;
	while(!init.getIsClosed()){
		while(SDL_PollEvent(&e) != 0){
			if(e.type == SDL_QUIT){
				init.setIsClosed();
			}else if(e.type == SDL_KEYDOWN){
                switch(e.key.keysym.sym){
                    case SDLK_UP:
                        playerYPos += ( 0.01 * playerYDelta );
                        playerXPos += ( 0.01 * playerXDelta );
                        break;
                    case SDLK_DOWN:
                        playerYPos -= (0.01 * playerYDelta);
                        playerXPos -= (0.01 * playerXDelta);
                        break;
                    case SDLK_LEFT:
                        playerAngle += 2 * DEGREE;
                        if(playerAngle > 2 * PI ){
                            playerAngle -= 2 * PI;
                        }
                        playerXDelta = cos(playerAngle);
                        playerYDelta = sin(playerAngle);
                        break;
                    case SDLK_RIGHT:
                        playerAngle -= 2 * DEGREE;
                        if(playerAngle < 0.0f ){
                            playerAngle += 2 * PI;
                        }
                        playerXDelta = cos(playerAngle);
                        playerYDelta = sin(playerAngle);
                        break;
                    case SDLK_m:
                        changeView = !changeView;
                        break;
                }
			}
		}
		 if(playerXPos > 1.0f){
            playerXPos = 1.0f;
        }else if(playerXPos < -1.0f){
            playerXPos = -1.0f;
        }
        if(playerYPos > 1.0f){
            playerYPos = 1.0f;
        }else if(playerYPos < -1.0f){
            playerYPos = -1.0f;
        }
		init.clearScreen(0.0, 0.0, 0.0, 1.0);
		if(!changeView){
            for(int i = 0; i < 8; i++){
                for(int y = 0; y < 8; y++){
                    if(mapArray[next] != 0){
                        rectArr[counter]->transformRectPos(glm::vec3(startGapX + (y + 1.0f) * rectArr[0]->getUniformWidth(), startGapY - (i + 1.0f) * rectArr[0]->getUniformHeight(), 0.0f));
                        rectArr[counter]->drawRect();
                        counter++;

                    }
                    next++;
                    if(counter > 30){
                        counter = 30;
                    }
                }
            }
            next = 0;
            counter = 0;
		}
		if(!changeView){
            for(unsigned int i = 0; i < 7; i++){
                linesXArr[i]->transformRectPos(glm::vec3((-1.0f + (i + 1) *rectArr[0]->getUniformWidth()), 0.0f, 0.0f));
                linesXArr[i]->drawRect();
                linesYArr[i]->transformRectPos(glm::vec3(0.0f, (1.0f - (i + 1) *rectArr[0]->getUniformWidth()), 0.0f));
                linesYArr[i]->drawRect();
            }
            mainPlayer.changePlayerPosition(glm::vec3(playerXPos, playerYPos, 0.0f));
            mainPlayer.drawPlayer();
		}
        rayAngle = playerAngle + DEGREE * 30;
        if(rayAngle < 0){
            rayAngle += 2 * PI;
        }
        if(rayAngle > 2 * PI){
            rayAngle -= 2 * PI;
        }
        for(unsigned int r = 0; r < 60; r++){
            dof = 0;
            float rayPosX = 0.0f;
            float rayPosY = 0.0f;
            float distT = 0.0f;
            float red = 0.0f;
            float aTan = -1/tan(rayAngle);
            float nTan = -tan(rayAngle);
            float yOffset = 0.0f;
            float xOffset = 0.0f;
            float distH = 1000000;
            float hx = playerXPos;
            float hy = playerYPos;
            int mapX = 0;
            int mapY = 0;
            int mapPos = 0;
            dof = 0;
            //horizontal
            if(rayAngle > PI){
                rayPosY =  floor((playerYPos) / rectArr[0]->getUniformHeight()) * rectArr[0]->getUniformHeight();
                if(rayPosY == -0.0f){
                    rayPosY = 0.0f;
                }
                rayPosX = (playerYPos - rayPosY) * aTan + playerXPos;
                if(rayPosX == -0.0f){
                    rayPosX = 0.0f;
                }
                yOffset = -rectArr[0]->getUniformHeight();
                xOffset = -yOffset * aTan;
            }

            if(rayAngle < PI){
                rayPosY =  ceil((playerYPos) / rectArr[0]->getUniformHeight()) * rectArr[0]->getUniformHeight();
                if(rayPosY == -0.0f){
                    rayPosY = 0.0f;
                }
                rayPosX = (playerYPos - rayPosY) * aTan + playerXPos;
                if(rayPosX == -0.0f){
                    rayPosX = 0.0f;
                }
                yOffset = rectArr[0]->getUniformHeight();
                xOffset = -yOffset * aTan;
            }
            if(rayAngle == PI || rayAngle == 0.0f){
                rayPosX = playerXPos;
                dof = 8;
            }
            while(dof < 8){
                mapX = 4 + (rayPosX / rectArr[0]->getUniformWidth());
                mapY = 4 - (rayPosY / rectArr[0]->getUniformWidth());
                if(rayAngle < PI)
                    mapPos = (mapY * 8 + mapX) - 8;
                else if(rayAngle > PI){
                    mapPos = mapY * 8 + mapX;
                }
                if(mapX > 8){
                    mapX = 16;
                }
                if(mapX < 0){
                    mapX = 16;
                }
                if(mapY > 8){
                    mapY = 16;
                }
                if(mapY < 0){
                    mapY = 16;
                }
                if(mapPos > 0 && mapPos < 64 && mapArray[mapPos] >= 1){
                    hx = rayPosX;
                    hy = rayPosY;
                    distH = dist((2.0f - playerXPos), (2.0f - playerYPos), (2.0f - hx), (2.0f - hy), rayAngle);
                    dof = 8;
                }else{
                    rayPosX += xOffset;
                    rayPosY += yOffset;
                    dof++;
                }
            }
            dof = 0;
            //vertical
            float distV = 1000000;
            float vx = playerXPos;
            float vy = playerYPos;
            if(rayAngle > P2 && rayAngle < P3){
                rayPosX =  floor((playerXPos) / rectArr[0]->getUniformHeight()) * rectArr[0]->getUniformHeight();
                if(rayPosX == -0.0f){
                    rayPosX = 0.0f;
                }
                rayPosY = (playerXPos - rayPosX) * nTan + playerYPos;
                xOffset = -rectArr[0]->getUniformHeight();
                yOffset = -xOffset * nTan;
            }

            if(rayAngle < P2 || rayAngle > P3){
                rayPosX =  ceil((playerXPos) / rectArr[0]->getUniformHeight()) * rectArr[0]->getUniformHeight();
                if(rayPosX == -0.0f){
                    rayPosX = 0.0f;
                }
                rayPosY = (playerXPos - rayPosX) * nTan + playerYPos;
                if(rayPosX == -0.0f){
                    rayPosX = 0.0f;
                }

                xOffset = rectArr[0]->getUniformHeight();
                yOffset = -xOffset * nTan;
            }
            if(rayAngle == PI || rayAngle == 0.0f){
                rayPosX = playerXPos;
                dof = 8;
            }
            while(dof < 8){
                mapX = 4 + (rayPosX / rectArr[0]->getUniformWidth());
                mapY = 4 - (rayPosY / rectArr[0]->getUniformWidth());

                if(mapX > 8){
                    mapX = 16;
                }
                if(mapX < 0){
                    mapX = 16;
                }
                if(mapY > 8){
                    mapY = 16;
                }
                if(mapY < 0){
                    mapY = 16;
                }
                if(rayAngle < P2 || rayAngle > P3){
                    mapPos = (mapY * 8) + mapX;
                }else if(rayAngle > P2 && rayAngle < P3){
                    mapPos = (mapY * 8) + (mapX-1);
                }
                if(mapPos > 0 && mapPos < 64 && mapArray[mapPos] == 1){
                    vx = rayPosX;
                    vy = rayPosY;
                    distV = dist((2.0f - playerXPos), (2.0f - playerYPos), (2.0f - vx), (2.0f - vy), rayAngle);
                    dof = 8;
                }else{
                    rayPosX += xOffset;
                    rayPosY += yOffset;
                    dof++;
                }
            }
            dof = 0;
            if(distV < distH){
                rayPosX = vx;
                rayPosY = vy;
                rayCoords[1] = glm::vec3(rayCoords[0].x, (rayCoords[0].y + baseRay.getUniformRaySize()), 0.0f);
                rayCoords[2] = glm::vec3(playerXPos, playerYPos, 0.0f);
                rayCoords[3] = glm::vec3(playerXPos, (playerYPos  + baseRay.getUniformRaySize()), 0.0f);
                distT = distV;
                red = 0.9f;
            }
            if(distV > distH){
                rayPosX = hx;
                rayPosY = hy;
                rayCoords[1] = glm::vec3((rayCoords[0].x + baseRay.getUniformRaySize()), rayCoords[0].y, 0.0f);
                rayCoords[2] = glm::vec3(playerXPos, playerYPos, 0.0f);
                rayCoords[3] = glm::vec3((playerXPos + baseRay.getUniformRaySize()), playerYPos, 0.0f);
                distT = distH;
                red = 1.0f;
            }
            rayCoords[0].x = rayPosX;
            rayCoords[0].y = rayPosY;
            rayCoords[0].z = 0.0f;

            if(!changeView){
                baseRay.changeRayPosition(rayCoords);
                baseRay.drawRay();
            }
            rayAngle -= DEGREE;
            if(rayAngle < 0){
                rayAngle += 2 * PI;
            }
            if(rayAngle > 2 * PI){
                rayAngle -= 2 * PI;
            }
            if(changeView){
                float cosAngle = playerAngle - rayAngle;
                if(cosAngle < 0){
                    cosAngle += 2 * PI;
                }
                if(cosAngle > 2 * PI){
                    cosAngle -= 2 * PI;
                }
                distT = distT * cos(cosAngle);
                float lineH = (2.0f/distT)/10;
                float x = 0.0f;
                if(lineH > 1.0f){
                    lineH = 1.0f;

                }
                if(lineH < 0.0f){
                    lineH = 0.0f;

                }

                x = -1.0f + (r*0.033);
                rayCoords[0] = glm::vec3(0.0f, 1.0f, 0.0f);
                rayCoords[1] = glm::vec3(0.0f, -1.0f, 0.0f);
                rayCoords[2] = glm::vec3(0.033f, 1.0f, 0.0f);
                rayCoords[3] = glm::vec3(0.033f, -1.0f, 0.0f);
                viewRay.changeRayPosition(rayCoords);
                viewRay.changeRayColor(glm::vec4(red, 0.0f, 0.0f, 1.0f));
                viewRay.transformRayPos(glm::vec3(x, 0.0f, 0.0f));
                viewRay.transformRayScale(glm::vec3(1.0f, lineH, 1.0f));
                viewRay.drawRay();
            }
        }
		init.swapBuffers();
	}
	init.close();
	return 0;
}
