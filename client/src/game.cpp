#include "game.h"
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "constants.h"
#include "iniFile.h"
#include "scene.h"
#include "player.h"

Game::Game(void)
{
  this->width = WIDTH_WINDOW;
  this->height = HEIGHT_WINDOW;
  this->window = NULL;
  this->renderer = NULL;

  this->initSDL();
  this->initIMG();
  this->initSDLttf();
}

Game::~Game(void)
{
  TTF_Quit();
  IMG_Quit();
  SDL_Quit();
}

bool8 Game::start(void)
{
  if (this->iniGame.load("game.ini") == FALSE) {
    std::cerr << "Error loading the file game.ini!" << std::endl;
  }

  if (this->createWindow() == FALSE || this->createRenderer() == FALSE)
  {
    return FALSE;
  }

  this->waitForKeyPressed();

  this->destroyRenderer();
  this->destroyWindow();

  this->iniGame.change("username", "seb");
  this->iniGame.change("server", "127.0.0.1");

  this->iniGame.save("game.ini");

  return TRUE;
}

void Game::initSDL(void)
{
  if(SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cerr << "Could not initialize SDL! SDL Error: " <<  SDL_GetError() << std::endl;
    exit(EXIT_FAILURE);
  }
}

void Game::initIMG(void)
{
  if(IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG) {
    std::cerr << "Could not initialize SDL_image" << std::endl;
    exit(EXIT_FAILURE);
  }
}

void Game::initSDLttf(void)
{
  TTF_Init();
}

bool8 Game::createWindow(void)
{
  this->window = SDL_CreateWindow(TITLE,
                                  SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                  this->width, this->height,
                                  0);

  if (this->window == NULL) {
    std::cerr << "Window could not be created! SDL Error: " <<  SDL_GetError() << std::endl;
    return FALSE;
  }

  return TRUE;
}

bool8 Game::createRenderer(void)
{
  this->renderer = SDL_CreateRenderer(this->window, -1, SDL_RENDERER_ACCELERATED);

  if (this->renderer == NULL) {
    std::cerr << "Renderer could not be created! SDL Error: " <<  SDL_GetError() << std::endl;
    return FALSE;
  }
}

void Game::waitForKeyPressed(void)
{
  bool8 quit = FALSE;
  SDL_Event event;

  while(!quit) {
    SDL_PollEvent(&event);

    switch (event.type) {
      case SDL_QUIT:
        quit = TRUE;
        break;

      case SDL_KEYDOWN:
        switch(event.key.keysym.sym) {
          case SDLK_ESCAPE:
            quit = TRUE;
            break;
          case SDLK_RETURN:
            SDL_RaiseWindow(this->window);
            Scene scene(this->window, this->renderer);
            scene.setPlayer();
            scene.start();
            quit = TRUE;
            break;
        }
        break;
    }
  }
}

void Game::destroyRenderer(void)
{
  SDL_DestroyRenderer(this->renderer);
  this->renderer = NULL;
}

void Game::destroyWindow(void)
{
  SDL_DestroyWindow(this->window);
  this->window = NULL;
}
