#include "scene.h"
#include <SDL2/SDL.h>
#include <sstream>
#include <iomanip>
#include <cmath>
#include <stdio.h>
#include <iostream>
#include "player.h"

Scene::Scene(SDL_Window *window, SDL_Renderer *renderer)
{
  // Pointers Initialization
  this->window = window;
  this->renderer = renderer;
  this->width = 0;
  this->height = 0;
  this->player = NULL;
  this->clock.adjust(0);

  // Retrieve window's dimension
  SDL_GetWindowSize(this->window, &this->width, &this->height);
}

Scene::~Scene()
{

}

void Scene::start()
{
  // Initialisation of time
  this->timeLastLoop = 0;
  uint32 timeLastLoop = this->clock.getTicks();

  this->quit = FALSE;

  while(!this->quit)
  {
    this->currentTime = this->clock.time();

    this->manageEvents();
    this->animate();

    // Displaying player's position (debugging)
    char title[100] = {0};
    sprintf(title, "x=%f y=%f", this->player->getX(), this->player->getY());
    SDL_SetWindowTitle(this->window, title);

    this->draw();

    // Update time
    this->timeLastLoop = this->clock.getTicks() - timeLastLoop;
    timeLastLoop += this->timeLastLoop;
  }
}

void Scene::draw(void)
{
  // clear the screen
  SDL_RenderClear(this->renderer);

  // retrieve x and y position of the player
  float16 x = 0, y = 0;
  this->player->getPosition(&x, &y);

  // retrieve the dimension of the player texture
  //int w, h;
  //SDL_QueryTexture(this->player->getTexture(), NULL, NULL, &w, &h);

  SDL_Rect playerRect = { x, y , BLOCK_SIZE, BLOCK_SIZE };
  // copy the texture to the rendering context
  SDL_RenderCopy(this->renderer, this->player->getTexture(), NULL, &playerRect);

  // update the screen
  SDL_RenderPresent(this->renderer);
}

void Scene::manageEvents(void)
{
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    switch(event.type) {
      case SDL_QUIT:
        this->quit = TRUE;
        break;

      case SDL_KEYDOWN:
        if (event.key.repeat == 0 && event.key.keysym.sym == SDLK_ESCAPE) {
          this->quit = TRUE;
        }
        break;

      case SDL_MOUSEBUTTONDOWN:
        printf("On tire!");
        break;
    }
  }
}

void Scene::animate(void)
{
  int numberKeys;
  const Uint8 *pKeys = SDL_GetKeyboardState(&numberKeys);
  Uint8 *keys = new Uint8[numberKeys];
  memcpy(keys, pKeys, numberKeys);

  // Avoid absurd behaviors

  // Going forwards and backwards
  if (keys[SDL_GetScancodeFromKey(SDLK_z)] == keys[SDL_GetScancodeFromKey(SDLK_s)]) {
    keys[SDL_GetScancodeFromKey(SDLK_z)] = 0u;
    keys[SDL_GetScancodeFromKey(SDLK_s)] = 0u;
  }
  // Goind left and right
  if (keys[SDL_GetScancodeFromKey(SDLK_q)] == keys[SDL_GetScancodeFromKey(SDLK_d)]) {
    keys[SDL_GetScancodeFromKey(SDLK_q)] = 0u;
    keys[SDL_GetScancodeFromKey(SDLK_d)] = 0u;
  }

  float16 direction;
  bool8 movement = FALSE;

  // Going forwards
  if (keys[SDL_GetScancodeFromKey(SDLK_z)]) {
    movement = TRUE;

    if (keys[SDL_GetScancodeFromKey(SDLK_q)])
      direction = 45.0; // left forwards
    else if (keys[SDL_GetScancodeFromKey(SDLK_d)])
      direction = -45.0; // right forwards
    else
      direction = 0.0; // forwards
  }
  // Going backwards
  else if (keys[SDL_GetScancodeFromKey(SDLK_s)]) {
    movement = TRUE;

    if (keys[SDL_GetScancodeFromKey(SDLK_q)])
      direction = 135.0; // left backwards
    else if (keys[SDL_GetScancodeFromKey(SDLK_d)])
      direction = -135.0; // right backwards
    else
      direction = 180.0; // backwards
  }

  if(movement == FALSE)
  {
    // Going left
    if (keys[SDL_GetScancodeFromKey(SDLK_q)]) {
      direction = 90.0;
      movement = TRUE;
    }
    // Going right
    else if (keys[SDL_GetScancodeFromKey(SDLK_d)]) {
      direction = -90.0;
      movement = TRUE;
    }
  }

  delete[] keys;

  // if there is a movement
  if (movement) {
    #define VELOCITY (10.0f)

    float16 distance = (float) this->timeLastLoop * VELOCITY / 1000.0f;

    // cutting the distance into pieces
    #define DELTA_DISTANCE (0.25f)

    uint32 nbSegments = (uint32) (distance / DELTA_DISTANCE);
    float16 RemainingDistance = fmod(distance, DELTA_DISTANCE);

    // For each segment
    for(uint32 i = 0; i < nbSegments; i++) {
      this->player->move(DELTA_DISTANCE, direction);
    }

    // For the remaining distance
    this->player->move(RemainingDistance, direction);
  }
}

void Scene::setPlayer()
{
  this->player = new Player(10, 10, "images/mario_haut.gif",  "images/mario_bas.gif",  "images/mario_gauche.gif",  "images/mario_droit.gif");
  this->player->setTextures(this->renderer);
}
