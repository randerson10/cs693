
#ifndef __GameObject_HPP__
#define __GameObject_HPP__

#include "SDL2/SDL.h"

class GameObject {
public:

   virtual void update(const float dt) = 0;
   virtual void render() = 0;

private:

};

#endif

