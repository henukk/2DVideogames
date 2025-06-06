#ifndef _LEVEL1_INCLUDE
#define _LEVEL1_INCLUDE

#include "Level.h"

class Level1 : public Level {
public:
    void init() override;

private:
    void loadLevelData() override;
};

#endif // _LEVEL1_INCLUDE
