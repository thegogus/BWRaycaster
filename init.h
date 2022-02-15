#ifndef INIT_H
#define INIT_H
#include <SDL2/SDL.h>

class init{
	public:
		init(int width, int height, std::string windowName); //constructor
		void clearScreen(float r, float g, float b, float a);
		void close(); //Closes SDL and OpenGL context
		SDL_Window* getWindow(); //Gets SDL Window from mWindow variable
		void swapBuffers(); //Updates screen by swaping buffers from doublebuffer
		bool getIsClosed(); //Gets value from mIsClosed
		void setIsClosed(); //Sets mIsClosed to true
		unsigned int getScreenWidth();
		unsigned int getScreenHeight();
		~init(); //destructor 

	private:
		SDL_Window* mWindow; //Window is created in this variable	
		SDL_GLContext mContext; //OpenGL context is created to go into mWindow variable, so you can use OpenGL on SDL Window
		bool mIsClosed; //Checks if windows is opened
		unsigned int SCR_WIDTH; //Window width
		unsigned int SCR_HEIGHT; //Window height
};

#endif //INIT_H
