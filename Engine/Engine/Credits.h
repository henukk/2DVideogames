#ifndef _CREDITS_INCLUDE
#define _CREDITS_INCLUDE

#include "Scene.h"
#include "Texture.h"
#include "Sprite.h"
#include "ShaderProgram.h"


namespace Scenes {
    class Credits : public Scene {
    public:
        virtual ~Credits();

        void init();
        void update(int deltaTime) override;
        void render() override;

    private:
        void initShaders();
        void loadBackground();

    private:

        Texture background, banner;
        Sprite* backgroundSprite = nullptr;

        glm::mat4 projection;

        ShaderProgram textureProgram, textProgram;

    };
}
#endif // _Credits_INCLUDE