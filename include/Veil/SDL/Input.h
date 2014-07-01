#ifndef __VeilSDLInput__
#define __VeilSDLInput__

#include <SDL2/SDL.h>

#include <Veil/Systems/System.h>
#include <Veil/Entity.h>

namespace Veil {
namespace SDL {

class Input : public System {
  SDL_Event event;

  public:
    void update(double dt);
};

} // namespace SDL
} // namespace Veil

#endif /* defined(__VeilSDLInput__) */
