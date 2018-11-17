#include "player.h"
#include <math.h>
#include <SDL2/SDL_image.h>
#include "constants.h"

Player::Player(float16 x, float16 y)
{
  this->x = x;
  this->y = y;

  this->images[UP] = IMG_Load("images/mario_haut.gif");
  this->images[DOWN] = IMG_Load("images/mario_bas.gif");
  this->images[LEFT] = IMG_Load("images/mario_gauche.gif");
  this->images[RIGHT] = IMG_Load("images/mario_droite.gif");

  // Idle State
  this->currentState = DOWN;
}

Player::~Player(void)
{
  // For each state => destroy image and texture
  for (size_t i = 0 ; i < 4 ; i++) {
    SDL_FreeSurface(images[i]);
    SDL_DestroyTexture(textures[i]);
  }
}

void Player::move(float16 distance, float16 direction)
{
  float16 newX = this->x - distance * sin(direction * M_PI / 180.0);
  float16 newY = this->y - distance * cos(direction * M_PI / 180.0);

  this->x = newX;
  this->y = newY;
}

void Player::getPosition(float16* x, float16* y)
{
  *x = this->x;
  *y = this->y;
}

void Player::teleport(float16 x, float16 y)
{
  this->x = x;
  this->y = y;
}

void Player::changeState(MOVEMENT movement)
{
  this->currentState = movement;
}

void Player::setTextures(SDL_Renderer* renderer)
{
  this->textures[UP] = SDL_CreateTextureFromSurface(renderer, this->images[UP]);
  this->textures[DOWN] = SDL_CreateTextureFromSurface(renderer, this->images[DOWN]);
  this->textures[LEFT] = SDL_CreateTextureFromSurface(renderer, this->images[LEFT]);
  this->textures[RIGHT] = SDL_CreateTextureFromSurface(renderer, this->images[RIGHT]);
}

float16 Player::getX()
{
  return this->x;
}

float16 Player::getY()
{
  return this->y;
}

SDL_Texture* Player::getTexture()
{
  return this->textures[this->currentState];
}
