#ifndef _UNBREAKABLE_BLOCK_INCLUDE
#define _UNBREAKABLE_BLOCK_INCLUDE

#include "GameObject.h"

class UnbreakableBlock : public GameObject {
public:
	void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram) override;
	void update(int deltaTime) override;
	void onCollision(GameObject* other) override;
};

#endif // _UNBREAKABLE_BLOCK_INCLUDE
