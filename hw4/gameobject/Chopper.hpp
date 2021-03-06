#ifndef __Chopper_HPP__
#define __Chopper_HPP__

#include "SDL2/SDL.h"
#include "GameObject.hpp"

class Chopper : public GameObject {
public:
   Chopper(const float xpos, const float ypos, const float xvel, const float yvel);
   ~Chopper();

   void update(const float dt);
   void render();

private:

};

#endif