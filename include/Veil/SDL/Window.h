#ifndef __VeilSDLWindow__
#define __VeilSDLWindow__

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

class Window : public System {
  SDL_Renderer* renderer;
  SDL_Window* window;

  // Construct default components for
  // objects that don't include them
  static Position* defaultPosition;
  static Rotation* defaultRotation;
  static Offset* defaultOffset;

  // Abstract fetching of common components
  // so we can apply the default states
  Position* getPosition(Entity* e);
  Rotation* getRotation(Entity* e);
  Offset* getOffset(Entity* e);
  Size* getSize(Entity* e, SDL_Texture* texture);

  // Lazy-load sdl textures
  SDL_Texture* getTexture(Entity* e);
  SDL_Texture* getText(Entity* e);

  // Handle different types of entity rendering
  void renderTexture(Entity* e);
  void renderText(Entity* e);

  // Window state
  SDL_Renderer* getRenderer();
  SDL_Window* getWindow();
  const char* title;
  Position* position;
  bool fullscreen;
  Size* size;

  // Cleanup renderer and window
  void cleanRenderer();
  void cleanWindow();

  public:
    // Window();
    ~Window();
    void render();

    // Set window properties
    void setTitle(const char*);
    void setPosition(int, int);
    void setFullscreen(bool);
    void setSize(int, int);
};

} // namespace SDL
} // namespace Veil

#endif /* defined(__VeilSDLWindow__) */
