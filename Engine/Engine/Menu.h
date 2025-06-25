#ifndef _MENU_INCLUDE
#define _MENU_INCLUDE

#include "Scene.h"
#include "Texture.h"
#include "Sprite.h"
#include "ShaderProgram.h"


namespace Scenes {
    class Menu : public Scene {
    public:
        virtual ~Menu();

        void init();
        void update(int deltaTime) override;
        void render() override;

    private:
        void initShaders();
        void loadBackground();
        void loadLogo();

    private:
        enum class Option { START = 0, CREDITS, COUNT };

        Option selected = Option::START;

        Texture background, banner;
        Sprite* backgroundSprite = nullptr;
        Sprite* bannerSprite = nullptr;

        glm::mat4 projection;

        ShaderProgram textureProgram, textProgram;

    };
}
#endif // _Menu_INCLUDE