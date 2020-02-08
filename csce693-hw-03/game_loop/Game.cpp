
#include "Game.hpp"
#include <iostream>

Game::Game(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{
   Uint32 flags{};
   if (fullscreen) {
      flags = SDL_WINDOW_FULLSCREEN;
   }

   if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
      std::cout << "Subsystems initialized..." << std::endl;
      window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
      if (window) {
         std::cout << "Window created..." << std::endl;
      } else {
         //error creating the window so quit SDL and throw an exception
         SDL_Quit();
         throw std::runtime_error("Error creating window");
      }

      renderer = SDL_CreateRenderer(window, -1, 0);
      
      if (renderer) {
         SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
         std::cout << "Renderer created..." << std::endl;
      } else { 
         //error creating the renderer so destroy the window, quit SDL and throw an expection
         SDL_DestroyWindow(window);
         SDL_Quit();
         throw std::runtime_error("Error creating renderer");
      }

      is_running = true;
   } else {
      is_running = false;
      //could not initialize SDL so throw an expection
      throw std::runtime_error("Error initializing SDL");
   }
}

Game::~Game()
{
   SDL_DestroyRenderer(renderer);
   SDL_DestroyWindow(window);
   SDL_Quit();
   std::cout << "Game cleaned..." << std::endl;
}

void Game::handle_events()
{
   SDL_Event event;
   SDL_PollEvent(&event);
   switch (event.type) {
      case SDL_QUIT:
         is_running = false;
         break;
      default:
         break;
   }
}

void Game::update()
{
   counter++;
   std::cout << counter << std::endl;
}

void Game::render()
{
   SDL_RenderClear(renderer);
   // this is where we would add stuff to render
   SDL_RenderPresent(renderer);
}

