#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include <string>
#include <SDL2/SDL_image.h>
#include "constants.h"
#include "types.h"

class Player
{
  public:
    Player(float16 x, float16 y);
    ~Player(void);

    void move(float16 distance, float16 direction);
    void getPosition(float16* x, float16* y);
    void teleport(float16 x, float16 y);
    void changeState(MOVEMENT movement);
    void setTextures(SDL_Renderer* renderer);

    float16 getX();
    float16 getY();
    SDL_Texture* getTexture();
  private:
    float16 x;
    float16 y;
    SDL_Surface* images[4];
    SDL_Texture* textures[4];
    MOVEMENT currentState;
};

#endif // PLAYER_H_INCLUDED
