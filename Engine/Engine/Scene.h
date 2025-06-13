#ifndef _SCENE_INCLUDE
#define _SCENE_INCLUDE

#include "AudioManager.h"

class Scene {
public:
    virtual ~Scene() {}

    virtual void init();
    virtual void update(int deltaTime) = 0;
    virtual void render() = 0;
};

#endif // _SCENE_INCLUDE
