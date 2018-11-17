#ifndef SCENE_H_INCLUDED
#define SCENE_H_INCLUDED

#include <string>
#include <SDL2/SDL.h>
#include "types.h"
#include "clock.h"
#include "map.h"
#include "player.h"

class Scene
{
  private:
    SDL_Window *window;
    SDL_Renderer *renderer;
    int width;
    int height;

    Clock clock;
    Map map;

    bool8 quit;
    uint32 timeLastLoop;
    sint32 currentTime;

    void manageEvents(void);
    void animate(void);
    void draw(void);

    Player *player;

  public:
    Scene(SDL_Window *fenetre, SDL_Renderer* renderer);
    ~Scene();
    void start();
    void setPlayer();
};

#endif // SCENE_H_INCLUDED
