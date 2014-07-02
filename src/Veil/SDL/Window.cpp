#include <Veil/SDL/Window.h>

namespace Veil {
namespace SDL {

Window::~Window() {
  cleanWindow();
}

void Window::cleanWindow() {
  if (window) {
    cleanRenderer();
    SDL_DestroyWindow(window);
  }
}

void Window::cleanRenderer() {
  if (renderer) {
    SDL_DestroyRenderer(renderer);
  }
}

void Window::setTitle(const char* _title) {
  title = _title;
}
void Window::setFullscreen(bool _fullscreen) {
  fullscreen = _fullscreen;
}
void Window::setPosition(int x, int y) {
  position = new Position(x, y);
}
void Window::setSize(int x, int y) {
  size = new Size(x, y);
}

// Lazy window initialization
SDL_Window* Window::getWindow() {
  if ( ! window) {
    if ( ! fullscreen) setFullscreen(false);
    if ( ! position) setPosition(0, 0);
    if ( ! size) setSize(0, 0);
    if ( ! title) setTitle("");

    int flags = fullscreen ? SDL_WINDOW_FULLSCREEN : 0;

    std::cout << "Creating " << size->width << " x " << size->height
      << " window at " << position->x << " x " << position->y << std::endl;

    window = SDL_CreateWindow(
      title,
      position->x,
      position->y,
      size->width,
      size->height,
      flags
    );
    if (window == 0) {
      std::cout << "Failed to create window" << std::endl;
      return 0;
    }

    std::cout << "success!" << std::endl;

    if (renderer) {
      SDL_DestroyRenderer(renderer);
    }
  }

  return window;
}

// Lazy renderer initialization
SDL_Renderer* Window::getRenderer() {
  if ( ! renderer) {
    std::cout << "Creating renderer" << std::endl;
    renderer = SDL_CreateRenderer(getWindow(), -1, SDL_RENDERER_ACCELERATED);
    if (renderer == 0) {
      std::cout << "Failed to create renderer" << std::endl;
      return 0;
    }

    std::cout << "success!" << std::endl;

    // Draw blank background
    SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);
  }

  return renderer;
}

void Window::render() {
  SDL_RenderClear(getRenderer());

  for (Entity* e : world->getEntities()) {
    if (e->has<Texture>()) {
      renderTexture(e);
    } else if (e->has<Typeface>() && e->has<Text>()) {
      renderText(e);
    }
  }

  SDL_RenderPresent(getRenderer());
}

void Window::renderText(Entity* e) {
  SDL_Texture* texture = getText(e);

  if (texture != NULL) {
    Position* position = getPosition(e);
    Rotation* rotation = getRotation(e);
    Size* size = getSize(e, texture);

    SDL_RendererFlip flip = SDL_FLIP_NONE;
    SDL_Rect srcRect;
    SDL_Rect destRect;
    srcRect.x = 0;
    srcRect.y = 0;
    srcRect.w = destRect.w = size->width;
    srcRect.h = destRect.h = size->height;
    destRect.x = position->x;
    destRect.y = position->y;

    SDL_RenderCopyEx(getRenderer(), texture, &srcRect, &destRect, int(rotation->angle * 360), 0, flip);
  }
}

void Window::renderTexture(Entity* e) {
  SDL_Texture* texture = getTexture(e);

  if (texture != NULL) {
    Position* position = getPosition(e);
    Rotation* rotation = getRotation(e);
    Offset* offset = getOffset(e);
    Size* size = getSize(e, texture);

    SDL_RendererFlip flip = SDL_FLIP_NONE;
    SDL_Rect srcRect;
    SDL_Rect destRect;
    srcRect.x = offset->x;
    srcRect.y = offset->y;
    srcRect.w = destRect.w = size->width;
    srcRect.h = destRect.h = size->height;
    destRect.x = position->x;
    destRect.y = position->y;

    SDL_RenderCopyEx(getRenderer(), texture, &srcRect, &destRect, int(rotation->angle * 360), 0, flip);
  }
}

SDL_Texture* Window::getTexture(Entity* e) {
  Texture* texture = e->as<Texture>();
  if (texture == NULL) {
    return 0;
  }

  if ( ! texture->has<SDLTexture>()) {
    SDL_Surface* surface = IMG_Load(texture->path);
    texture->add(new SDLTexture(surface, getRenderer()));
    SDL_FreeSurface(surface);
  }

  return texture->as<SDLTexture>()->texture;
}

SDL_Texture* Window::getText(Entity* e) {
  Typeface* typeface = e->as<Typeface>();
  Text* text = e->as<Text>();
  if (typeface == NULL || text == NULL) {
    return 0;
  }

  if ( ! typeface->has<SDLTexture>()) {
    char* sdl_path = SDL_GetBasePath();
    std::string path(sdl_path);
    path += typeface->path;

    TTF_Font* font = TTF_OpenFont(path.c_str(), typeface->size);
    if (font == NULL) {
      return 0;
    }

    Color* c = typeface->getColor();
    SDL_Color color = { c->red, c->green, c->blue };
    SDL_Surface* surface = TTF_RenderText_Blended(font, text->text, color);

    typeface->add(new SDLTexture(surface, getRenderer()));

    SDL_FreeSurface(surface);
    TTF_CloseFont(font);
  }

  return typeface->as<SDLTexture>()->texture;
}

// Default enforcers
Position* Window::defaultPosition = new Position(0, 0);
Rotation* Window::defaultRotation = new Rotation(0.0);
Offset* Window::defaultOffset = new Offset(0, 0);

Position* Window::getPosition(Entity* e) {
  Position* p = e->as<Position>();
  if (p) return p;
  return defaultPosition;
}

Offset* Window::getOffset(Entity* e) {
  Offset* o = e->as<Offset>();
  if (o) return o;
  return defaultOffset;
}

Size* Window::getSize(Entity* e, SDL_Texture* texture) {
  Size* s = e->as<Size>();
  if (s) return s;

  int width, height;
  SDL_QueryTexture(texture, NULL, NULL, &width, &height);
  e->add(new Size(width, height));
  return e->as<Size>();
}

Rotation* Window::getRotation(Entity* e) {
  Rotation* r = e->as<Rotation>();
  if (r) return r;
  return defaultRotation;
}

} // namespace SDL
} // namespace Veil
