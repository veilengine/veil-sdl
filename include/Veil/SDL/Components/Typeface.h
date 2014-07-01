#ifndef __VeilSystemSDLTypeface__
#define __VeilSystemSDLTypeface__

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include <Veil/Components/Component.h>

namespace Veil {
namespace SDL {

class SDLTypeface : public Component {
	const TTF_Font* typeface;

	public:
		SDLTypeface(TTF_Font* _typeface)
			: typeface(_typeface) {};
};

} // namespace SDL
} // namespace Veil

#endif /* defined(__VeilSystemSDLTypeface__) */
