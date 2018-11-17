#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include <SDL2/SDL.h>
#include "types.h"
#include "iniFile.h"

class Game
{
  public:
    Game(void);
    ~Game(void);
    bool8 start(void);

  private:
    void initSDL(void);
    void initIMG(void);
    void initSDLttf(void);
    bool8 createWindow(void);
    bool8 createRenderer(void);
    void waitForKeyPressed(void);
    void destroyWindow(void);
    void destroyRenderer(void);

    SDL_Window* window;
    SDL_Renderer* renderer;
    uint32 width;
    uint32 height;

    INIFile iniGame;
};

#endif // GAME_H_INCLUDED
