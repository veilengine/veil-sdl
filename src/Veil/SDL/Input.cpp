#include <Veil/SDL/Input.h>

namespace Veil {
namespace SDL {

void Input::update (double dt) {
  while (SDL_PollEvent(&event)) {
    switch (event.type) {
      case SDL_QUIT:
        world->stop();
        break;
    }
  }
}

} // namespace SDL
} // namespace Veil
