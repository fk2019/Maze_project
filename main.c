#include "./headers/demo.h"

int init_instance(SDL_Instance *instance)
{
	/* initialize SDL */
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		fprintf(stderr, "Unable to initialize SDL: %s\n", SDL_GetError());
		return (1);
	}
	/* create a new window instance */
	instance->window = SDL_CreateWindow("Maze Project", SDL_WINDOWPOS_CENTERED,
				  SDL_WINDOWPOS_CENTERED, 1260, 720, 0);
	if (instance->window == NULL)
	{
		fprintf(stderr, "SDL_CreateWindow Error: %s\n", SDL_GetError());
		return (1);
	}
	/* create a new renderer instance linked to the window */
	instance->renderer = SDL_CreateRenderer(instance->window, -1,
				      SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (instance->renderer == NULL)
	{
		fprintf(stderr, "SDL_CreateRenderer Error: %s\n", SDL_GetError());
		SDL_Quit();
		return (1);
	}
	return (0);
}

void draw_stuff(SDL_Instance instance)
{
	/* draw a line*/
	SDL_SetRenderDrawColor(instance.renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderDrawLine(instance.renderer, 10, 10, 100, 100);
}
int poll_events()
{
	SDL_Event event;
	SDL_KeyboardEvent key;
	while (SDL_PollEvent(&event))
	{
		switch(event.type)
		{
		case SDL_QUIT:
			return (1);
		case SDL_KEYDOWN:
			key = event.key;
			/* if ESCAPE is pressed */
			if (key.keysym.scancode == 0x29)
				return (1);
			break;
		}
	}
	return (0);
}

int main(void)
{
	SDL_Instance instance;

	if (init_instance(&instance) != 0)
		return (1);
	while ("C is awesome")
	{
		SDL_SetRenderDrawColor(instance.renderer, 0, 0, 0, 0);
		SDL_RenderClear(instance.renderer);
		if (poll_events() == 1)
			break;
		draw_stuff(instance);
		SDL_RenderPresent(instance.renderer);
	}
	SDL_DestroyRenderer(instance.renderer);
	SDL_DestroyWindow(instance.window);
	SDL_Quit();
	return (0);
}
