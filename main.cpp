
#include <string>
#include <iostream>
#include <SDL.h>

#include <math.h>

bool init();
void quit();
void draw_func(double (*funcPtr)(double),SDL_Renderer *, int, int, int, int, int);

double func(double x)
{
return x * x;
}
double func2(double x)
{
return sin(x);
}

using namespace std;

int SCREEN_WIDTH = 1000;
int SCREEN_HEIGHT = 1000;

SDL_Window *win = NULL;
SDL_Renderer *ren = NULL;

int main(int arhc, char **argv)
{
if (!init())
{
quit();
system("pause");
return 1;
}

SDL_SetRenderDrawColor(ren, 0x00, 0x00, 0x00, 0x00);
SDL_RenderClear(ren);
SDL_SetRenderDrawColor(ren, 0xFF, 0xFF, 0xFF, 0xFF);

draw_func(func,ren, 1000, 10, 10, 50, 10);
draw_func(func2,ren, 1000, 10, 10, 50, 10);


SDL_RenderPresent(ren);

SDL_Delay(5000);

quit();
return 0;
}

///////////////////////////////////////////////////
void draw_func(double (*funcPtr)(double),SDL_Renderer * ren, int size, int devi_x, int devi_y, int step, int sens)
{
int size_2 = size / 2;
SDL_RenderDrawLine(ren, devi_x, size_2 + devi_y, size + devi_x, size_2 + devi_y);
SDL_RenderDrawLine(ren, size_2 + devi_x, devi_y, size_2 + devi_x, size + devi_y);
for (int i = 1; i < size / step; i++)
{
SDL_RenderDrawLine(ren, devi_x + i * step, devi_y + size_2 - 5, devi_x + i * step, devi_y + size_2 + 5);
SDL_RenderDrawLine(ren, devi_x + size_2 + 5, devi_y + i * step, devi_x + size_2 - 5, devi_y + i * step);
}
for (int i = -size_2 * sens; i <= size_2 * sens; i += 1)
{
SDL_RenderDrawPoint(ren, (double)i / sens + devi_x + size_2, size + devi_y - funcPtr((double)i / step / sens) * step - size_2);
}
}

bool init()
{
bool ok = true;

if (SDL_Init(SDL_INIT_VIDEO) != 0)
{
cout << "Can't init SDL: " << SDL_GetError() << endl;
}

win = SDL_CreateWindow("Примитивы", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
if (win == NULL)
{
cout << "Can't create window: " << SDL_GetError() << endl;
ok = false;
}

ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
if (ren == NULL)
{
cout << "Can't create renderer: " << SDL_GetError() << endl;
ok = false;
}
return ok;
}

void quit()
{
SDL_DestroyWindow(win);
win = NULL;

SDL_DestroyRenderer(ren);
ren = NULL;

SDL_Quit;
}
