#include "pch.h"
#include <iostream>
#include <vector>
#include <SDL/SDL.h>
#include <GLM/glm.hpp>
#include <stdio.h>
#include <math.h>
#include <thread>
#include <mutex>
#include <Windows.h>
#include <sstream>

#include "RayT.h"
#include "Camera.h"

void pixels(Camera *myCamera, RayT *myTracer, int x1, int x2, int y1, int y2);
//Cheating Static Variable
static glm::vec3 a[600][480];

int main(int argc, char *args[])
{
	//Basic SDL Stuff
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cout << "SDL Crashed" << std::endl;
		return -1;
	}

	//Basic SDL Stuff
	unsigned int lasttime = SDL_GetTicks();
	int winPosX = 100;
	int winPosY = 100;
	int winWidth = 600;
	int winHeight = 480;
	SDL_Window *window = SDL_CreateWindow("GCP - Assignment 1", winPosX, winPosY, winWidth, winHeight, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
	SDL_Renderer * renderer = SDL_CreateRenderer(window, -1, 0);

	//this was for the FPS counter
	int frames = 0;
	double starttime = 0;
	float timepassed;
	time_t start = time(0);

	while (true)
	{
		//this is the FPS Counter, i have no idea if its working correctly
		//if it is thought then it means that the program is only running through
		//about 3-6 frames a second which is insanly slow
		timepassed = difftime(time(0), start);
		frames++;

		if (timepassed - starttime > 0.10 && frames > 10)
		{
			std::cout << (double)frames / (timepassed - starttime) << std::endl;
			starttime = timepassed;
			frames = 0;
		}
		
		//Basic SDL Stuff
		SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0xFF);
		SDL_RenderClear(renderer);

		//allowing me to call functions from these classes
		Camera *myCamera = new Camera();
		RayT *myTracer = new RayT();


		//Create my four threads, i for each corner, they run the pixels function
		//each send their dimentions that they will cover
		std::thread topLeft(pixels, myCamera, myTracer, 0, winWidth / 2, 0, winHeight / 2);
		std::thread topRight(pixels, myCamera, myTracer, winWidth / 2, winWidth, 0, winHeight / 2);
		std::thread botLeft(pixels, myCamera, myTracer, 0, winWidth / 2, winHeight / 2, winHeight);
		std::thread botRight(pixels, myCamera, myTracer, winWidth / 2, winWidth, winHeight / 2, winHeight);

		//I then wait for them all to complete theirs tasks before continuing
		//I had an issue before doing this, my screen would look asif it was torn
		//this fixed it however.
		topLeft.join();
		topRight.join();
		botLeft.join();
		botRight.join();

		//Draw the Pixels
		for (int x = 0; x < winWidth; x++)
		{
			for (int y = 0; y < winHeight; y++)
			{
				SDL_SetRenderDrawColor(renderer, a[x][y].r, a[x][y].g, a[x][y].b, 255);
				SDL_RenderDrawPoint(renderer, x, y);
			}
		}

		SDL_RenderPresent(renderer);

	}

	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}

//This is the function that my threads all call to work on
// they run through the parameter of pixels theyve been assigned, making rays
// and checking them for there colours, then save that colour info into the 2D array
void pixels(Camera *myCamera, RayT *myTracer, int x1, int x2, int y1, int y2)
{
	for (int x = x1; x < x2; x++)
	{
		for (int y = y1; y < y2; y++)
		{
			Ray currentRay = myCamera->genRay(x, y);
			glm::vec3 colour = myTracer->Trace(currentRay);

			a[x][y] = colour;
		}
	}
}