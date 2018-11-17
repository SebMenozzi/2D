#include <SDL2/SDL.h>
#include "map.h"

Map::Map()
{
  this->images[WALL] = IMG_Load("images/mur.jpg");
  this->images[BOX] = IMG_Load("images/caisse.jpg");
  this->images[REDBOX] = IMG_Load("images/caisse_ok.jpg");
  this->images[GOAL] = IMG_Load("images/objectif.png");
}

Map::~Map()
{
  // For each state => destroy image and texture
  for (size_t i = 0 ; i < 4 ; i++) {
    SDL_FreeSurface(images[i]);
    SDL_DestroyTexture(textures[i]);
  }

  //delete this->map;
}

void Map::setTextures(SDL_Renderer *renderer)
{
  this->textures[WALL] = SDL_CreateTextureFromSurface(renderer, this->images[WALL]);
  this->textures[BOX] = SDL_CreateTextureFromSurface(renderer, this->images[BOX]);
  this->textures[REDBOX] = SDL_CreateTextureFromSurface(renderer, this->images[REDBOX]);
  this->textures[GOAL] = SDL_CreateTextureFromSurface(renderer, this->images[GOAL]);
}

bool8 Map::load(const char* path)
{
  FILE *file = NULL;
  char line[NB_BLOCKS_WIDTH * NB_BLOCKS_HEIGHT + 1] = {0};
  int i = 0, j = 0;

  file = fopen(path, "r");
  if (file == NULL) {
    return FALSE;
  }

  fgets(line, NB_BLOCKS_WIDTH * NB_BLOCKS_HEIGHT + 1, file);

  for (i = 0 ; i < NB_BLOCKS_WIDTH ; i++) {
    for (j = 0 ; j < NB_BLOCKS_HEIGHT ; j++) {
      switch (line[(i * NB_BLOCKS_WIDTH) + j]) {
        case '0':
          this->map[j][i] = EMPTY;
          break;
        case '1':
          this->map[j][i] = WALL;
          break;
        case '2':
          this->map[j][i] = BOX;
          break;
        case '3':
          this->map[j][i] = REDBOX;
          break;
        case '4':
          this->map[j][i] = GOAL;
          break;
      }
    }
  }

  fclose(file);
  return TRUE;
}

bool8 Map::save(const char* path)
{
    FILE* file = NULL;
    int i = 0, j = 0;

    file = fopen(path, "w");
    if (file == NULL) {
      return FALSE;
    }

    for (i = 0 ; i < NB_BLOCKS_WIDTH ; i++) {
      for (j = 0 ; j < NB_BLOCKS_HEIGHT ; j++) {
        fprintf(file, "%d", this->map[j][i]);
      }
    }

    fclose(file);
    return TRUE;
}

SDL_Texture* Map::getTexture(BLOCK_TYPE type)
{
  return this->textures[type];
}

BLOCK_TYPE Map::getTile(size_t i, size_t j)
{
  return this->map[i][j];
}
