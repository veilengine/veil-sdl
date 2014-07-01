#ifndef __VeilSDLRenderer__
#define __VeilSDLRenderer__

#include <unordered_map>
#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include <Veil/Systems/System.h>
#include <Veil/Entity.h>
#include <Veil/Components/Component.h>
#include <Veil/Components/Typeface.h>
#include <Veil/Components/Color.h>
#include <Veil/Components/Text.h>
#include <Veil/Components/Texture.h>
#include <Veil/Components/Fullscreen.h>
#include <Veil/Components/WindowTitle.h>
#include <Veil/Components/Rotation.h>
#include <Veil/Components/Position.h>
#include <Veil/Components/Offset.h>
#include <Veil/Components/Size.h>

#include <Veil/SDL/Components/Texture.h>
#include <Veil/SDL/Components/Typeface.h>

namespace Veil {
namespace SDL {

class Renderer {
  bool active = false;

  public:
    void init() {
      if ( ! active) {
        active = true;

        // Initialize SDL systems
        if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
          std::cout << "Failed to initialize sdl" << std::endl;
          exit(1);
          return;
        }

        // Initialize TTF systems
        if (TTF_Init() < 0) {
          std::cout << TTF_GetError() << std::endl;
          return;
        }
      }
    };

    void quit() {
      if (active) {
        TTF_Quit();
        SDL_Quit();
      }
    };

    static Renderer* instance() {
      static Renderer* singleton;
      if ( ! singleton) {
        singleton = new Renderer;
      }
      return singleton;
    }
};

} // namespace SDL
} // namespace Veil

#endif /* defined(__VeilSDLRenderer__) */
