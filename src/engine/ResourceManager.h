#ifndef __RESOURCE_MANAGER_H__
#define __RESOURCE_MANAGER_H__

#include <map>
#include <vector>

#include "GraphicsEngine.h"
#include "AudioEngine.h"

class ResourceManager {
	private:
		static std::map<std::string, SDL_Texture *> textures;
		static std::map<std::string, Mix_Chunk *> sounds;
		static std::map<std::string, Mix_Music *> mp3files;
		static std::map<std::string, TTF_Font *> fonts;
	public:

		/**
		* Call to free all resource files
		* All subsequent calls to get* will return nullptr or cause undefined behaviour
		*/
		static void freeResources();

		/**
		* load* functions will load the resource into cache (map)
		* for later use as well as return the resource directly
		*
		* After load* functions, the loaded resource can also be retrieved
		* by calling get* with appropriate filename
		*/
		static SDL_Texture * loadTexture(std::string fileName, SDL_Color transparent);
		static TTF_Font * loadFont(std::string fileName, const int & pointSize);
		static Mix_Chunk * loadSound(std::string fileName);
		static Mix_Music * loadMP3(std::string fileName);

		static SDL_Texture * getTexture(std::string fileName);
		static TTF_Font * getFont(std::string fileName);
		static Mix_Chunk * getSound(std::string fileName);
		static Mix_Music * getMP3(std::string fileName);
};

#endif
