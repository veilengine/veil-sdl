#ifndef __VeilSystemSDLSound__
#define __VeilSystemSDLSound__

#include <unordered_map>
#include <functional>
#include <iostream>

#include <SDL2/SDL_mixer.h>

namespace Veil {
namespace SDL {

class Sound {
  std::unordered_map<const char*, Mix_Music*> music;
  std::unordered_map<const char*, Mix_Chunk*> sounds;
  int channels;

  Sound();
  ~Sound();

  void onChannelEnd(int channel);

  Mix_Music* getMusic(const char*);
  Mix_Chunk* getSound(const char*);

  void init();
  void quit();

  public:
    static Sound* instance() {
      static Sound* singleton;
      if ( ! singleton) {
        singleton = new Sound;
      }
      return singleton;
    }

    void playMusic(const char* path);
    void playSound(const char* path);

    void removeChannel();
    void addChannel();
};

} // namespace SDL
} // namespace Veil

#endif /* defined(__VeilSystemSDLSound__) */
