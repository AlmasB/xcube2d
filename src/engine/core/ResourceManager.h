#ifndef __RESOURCE_MANAGER_H__
#define __RESOURCE_MANAGER_H__

#include <map>
#include <vector>

#include "../graphics/GraphicsEngine.h"
#include "../audio/AudioEngine.h"

class ResourceManager {
	private:
		static std::map<std::string, SDL_Texture *> textures;
		static std::map<std::string, Mix_Chunk *> sounds;
		static std::map<std::string, Mix_Music *> mp3files;
		static std::map<std::string, TTF_Font *> fonts;
	public:
		/**
		 * Loads all resources into several maps (cache)
		 * to make the program run smoother
		 *
		 * @param fileNames - vector containing names to resource files
		 *
		 * The resources can be retrieved with an appropriate call to get*
		 */
		static void loadResources(std::vector<std::string> fileNames);

		/**
		* Call to free all resource files
		* All subsequent calls to get* will return nullptr or cause undefined behaviour
		*/
		static void freeResources();

		static SDL_Texture * getTexture(std::string fileName);
		static TTF_Font * getFont(std::string fileName);
		static Mix_Chunk * getSound(std::string fileName);
		static Mix_Music * getMP3(std::string fileName);
};

#endif
