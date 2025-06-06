#ifndef _PLAYER_INCLUDE
#define _PLAYER_INCLUDE

#include "DynamicObject.h"
#include "ShaderProgram.h"

class Player : public DynamicObject {
public:
    Player(TileMap* tileMap);
    ~Player() override = default;

    void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram) override;
    void update(int deltaTime) override;

private:
    bool bJumping;
    int jumpAngle, startY;

    static constexpr int JUMP_ANGLE_STEP = 4;
    static constexpr int JUMP_HEIGHT = 96;
    static constexpr int FALL_STEP = 4;

    enum PlayerAnims {
        STAND_LEFT, STAND_RIGHT, MOVE_LEFT, MOVE_RIGHT
    };
};

#endif // _PLAYER_INCLUDE
