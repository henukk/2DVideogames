#ifndef _LEVEL_INCLUDE
#define _LEVEL_INCLUDE

#include "Scene.h"
#include "TileMap.h"
#include "Player.h"
#include "Sprite.h"
#include "ShaderProgram.h"
#include "UIManager.h"

class Level : public Scene {
public:
    virtual ~Level();

    virtual void init() override = 0;
    virtual void update(int deltaTime) override;
    virtual void render() override;

protected:
    void initShaders();
    virtual void loadLevelData() = 0;
    virtual void loadBackground();

protected:
    Texture spritesheet;
    Sprite* backgroundSprite = nullptr;
    TileMap* map = nullptr;
    Player* player = nullptr;
    ShaderProgram texProgram;
    float currentTime = 0.f;
    glm::mat4 projection;
};

#endif // _LEVEL_INCLUDE
