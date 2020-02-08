
#include "Game.hpp"
#include <chrono>
#include <iostream>
#include <memory>
#include <thread>

int main() {

   std::cout << "Creating game" << std::endl;
   try{
      auto game = std::make_unique<Game>("1st Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, false);
      std::cout << "Starting game loop" << std::endl;
      while (game->running()) {
         //start time
         std::chrono::high_resolution_clock::time_point t1{std::chrono::high_resolution_clock::now()};
         
         game->handle_events();
         game->update();
         game->render();

         //end time
         std::chrono::high_resolution_clock::time_point t2{std::chrono::high_resolution_clock::now()};
         //how much time has elasped
         const auto elasped_time = std::chrono::duration_cast<std::chrono::milliseconds>(t2-t1).count();
         //sleep for the remaining time to establish the 60FPS rate
         std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(floor(16.666f-elasped_time))));
      }
   } catch(std::runtime_error& e) {
      std::cout << e.what() << "\n";
   }

   return 0;
}

