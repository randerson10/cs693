#ifndef __Tank_HPP__
#define __Tank_HPP__

#include "SDL2/SDL.h"
#include "GameObject.hpp"

class Tank : public GameObject {
public:
   Tank(const float xpos, const float ypos, const float xvel, const float yvel);
   ~Tank();

   void update(const float dt);
   void render();

private:

};

#endif