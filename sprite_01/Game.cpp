
#include "Game.hpp"

#include <iostream>
#include "SDL2/SDL_image.h"
#include "sol/sol.hpp"

#include "AssetManager.hpp"
#include "EntityManager.hpp"
#include "Entity.hpp"
#include "components/TransformComponent.hpp"
#include "components/SpriteComponent.hpp"

SDL_Renderer* Game::renderer{};

EntityManager entity_mgr;
AssetManager* Game::asset_manager{new AssetManager()};

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
      }
      renderer = SDL_CreateRenderer(window, -1, 0);
      if (renderer) {
         SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
         std::cout << "Renderer created..." << std::endl;
      }
   is_running = true;
   } else {
      is_running = false;
   }

   load_level(1);
}

Game::~Game()
{
   SDL_DestroyRenderer(renderer);
   SDL_DestroyWindow(window);
   SDL_Quit();
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

void Game::update(const float dt)
{
   entity_mgr.update(dt);
}

void Game::render()
{
   SDL_RenderClear(renderer);
   entity_mgr.render();
   SDL_RenderPresent(renderer);
}

void Game::load_level(const int number)
{
   sol::state lua;

   // Initialize Lua via sol and load the config file
   try {
      lua.open_libraries(sol::lib::base, sol::lib::package);
      // throw sol::error("Forced error after opening Lua libs for testing");
   }
   catch (const sol::error& e) {
      std::cerr << e.what() << std::endl;
      throw std::runtime_error("Couldn't open lua libraries");
   }

   try {
      lua.script_file("config.lua");
   }
   catch (const sol::error& e) {
      std::cerr << e.what() << std::endl;
      throw std::runtime_error("Error loading lua config file");
   }

   //iterate over the assets table and add all ids and filenames to asset manager
   sol::table assets = lua["assets"];
   for(const auto& key_value_pair : assets) {
      sol::object key = key_value_pair.first;
      sol::object value = key_value_pair.second;

      std::string id = key.as<std::string>();
      std::string filename = value.as<std::string>();
      
      // add assets to asset manager
      asset_manager->add_texture(id, filename.c_str());
   } 

   //iterate over the entities table
   sol::table entities = lua["entities"];
   for(const auto& key_value_pair : entities) {
      //the key is the entity name
      sol::object key = key_value_pair.first;

      //extract the tranform attributes for this entity
      sol::table transform = lua["entities"][key.as<std::string>()]["transform"];
      int xpos = static_cast<int>(transform["position_x"]);
      int ypos = static_cast<int>(transform["position_y"]); 
      int xvel = static_cast<int>(transform["velocity_x"]);
      int yvel = static_cast<int>(transform["velocity_y"]);
      int width = static_cast<int>(transform["width"]);
      int height = static_cast<int>(transform["height"]);
      int scale = static_cast<int>(transform["scale"]);

      //extract the sprite attributes for this entity
      sol::table sprite = lua["entities"][key.as<std::string>()]["sprite"];
      std::string id = static_cast<std::string>(sprite["texture_id"]);

      //add a new entity and attach the components found above
      Entity& entity(entity_mgr.add_entity(key.as<std::string>()));
      entity.add_component<TransformComponent>(xpos, ypos, xvel, yvel, width, height, scale);
      entity.add_component<SpriteComponent>(id);
   } 

   entity_mgr.list_all_entities();
}

void Game::initialize() {
   entity_mgr.initialize();
}
