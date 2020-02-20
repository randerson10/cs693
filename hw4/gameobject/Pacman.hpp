#ifndef __Pacman_HPP__
#define __Pacman_HPP__

#include "SDL2/SDL.h"
#include "GameObject.hpp"

class Pacman : public GameObject {
public:
   Pacman(const float xpos, const float ypos, const float xvel, const float yvel);
   ~Pacman();

   void update(const float dt);
   void render();

private:

};

#endif