#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <cstdio>
#include <string>
#include "init.h"

init::init(int width, int height, std::string windowName){
	mIsClosed = false;
	SCR_WIDTH = width;
	SCR_HEIGHT = height;
	//Initializing SDL
	if(SDL_Init(SDL_INIT_VIDEO) != 0){
		printf("SDL failed to initialize! SDL_Error: %s\n", SDL_GetError());
	}else{
		//Setting OpenGL Version
		//SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
		//SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
		//Setting OpenGL color buffers red, green, blue and alpha to 8 bits
		SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
		SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
		SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
		SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
		//Setting buffersize to 32
		SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
		//Setting Doublebuffer so we can have two displays which can switch, one is shown, on second we can draw
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
		//creates SDL window with parameter SDL_WINDOW_OPENGL so we can use OpenGL context
		mWindow = SDL_CreateWindow(windowName.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCR_WIDTH, SCR_HEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
		//Checking SDL Window for error
		if(mWindow == NULL){
			printf("SDL failed to create window! SDL_Error: %s\n", SDL_GetError());
			mIsClosed = true;
		}
		//Creating OpenGL Context
		mContext = SDL_GL_CreateContext(mWindow);
		//Initializing glew to check if there isn't any errors
		GLenum status = glewInit();
		if(status != GLEW_OK){
			printf("GLEW could not be initialized!");
			mIsClosed = true;
		}
	}
}

unsigned int init::getScreenWidth(){
	return SCR_WIDTH;
}

unsigned int init::getScreenHeight(){
	return SCR_HEIGHT;
}

void init::swapBuffers(){
	SDL_GL_SwapWindow(mWindow);
}

void init::clearScreen(float r, float g, float b, float a){
	glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT);
}

void init::close(){
	SDL_GL_DeleteContext(mContext);
	SDL_DestroyWindow(mWindow);
	mWindow = NULL;
	SDL_Quit();
}

bool init::getIsClosed(){
	return mIsClosed;
}

void init::setIsClosed(){
	mIsClosed = true;
}

SDL_Window* init::getWindow(){
	return mWindow;
}

init::~init(){
	close();
}
