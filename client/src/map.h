#ifndef MAP_H_INCLUDED
#define MAP_H_INCLUDED

#include <iostream>
#include <SDL2/SDL_image.h>
#include "constants.h"
#include "types.h"

class Map
{
  public:
    Map();
    ~Map();
    void setTextures(SDL_Renderer* renderer);
    bool8 load(const char* path);
    bool8 save(const char* path);
    SDL_Texture* getTexture(BLOCK_TYPE type);
    BLOCK_TYPE getTile(size_t i, size_t j);

  private:
    const char* path;
    BLOCK_TYPE map[NB_BLOCKS_WIDTH][NB_BLOCKS_HEIGHT];
    SDL_Surface* images[4];
    SDL_Texture* textures[4];
};

#endif // MAP_H_INCLUDED
