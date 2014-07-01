#ifndef __VeilSystemSDLTexture__
#define __VeilSystemSDLTexture__

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <Veil/Components/Component.h>

namespace Veil {
namespace SDL {

struct SDLTexture : public Component {
	SDL_Renderer* renderer;
	SDL_Texture* texture;

	SDLTexture(SDL_Surface* surface, SDL_Renderer* _renderer)
		: renderer(_renderer) {
			texture = SDL_CreateTextureFromSurface(renderer, surface);
		};
};

} // namespace SDL
} // namespace Veil

#endif /* defined(__VeilSystemSDLTexture__) */
