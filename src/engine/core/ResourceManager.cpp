#include "ResourceManager.h"

std::map<std::string, SDL_Texture *> ResourceManager::textures;
std::map<std::string, TTF_Font *> ResourceManager::fonts;
std::map<std::string, Mix_Chunk *> ResourceManager::sounds;
std::map<std::string, Mix_Music *> ResourceManager::mp3files;

void ResourceManager::loadResources(std::vector<std::string> fileNames) {
	for (auto file : fileNames) {
		if (file.find(".ttf") != -1) {
			TTF_Font * font = TTF_OpenFont(file.c_str(), 36);	// hardcode font size ?
			if (nullptr == font)
				throw EngineException(TTF_GetError(), file);
			fonts[file] = font;
		}
		else if (file.find(".wav") != -1) {
			Mix_Chunk * sound = Mix_LoadWAV(file.c_str());
			if (nullptr == sound)
				throw EngineException(Mix_GetError(), file);
			sounds[file] = sound;
		}
		else if (file.find(".mp3") != -1) {
			Mix_Music * mp3 = Mix_LoadMUS(file.c_str());
			if (nullptr == mp3)
				throw EngineException(Mix_GetError(), file);
			mp3files[file] = mp3;
		}
		else if (file.find(".png") != -1 || file.find(".jpg") != -1) {

			
			/*SDL_Surface * surf = IMG_Load(file.c_str());
			if (nullptr == surf)
				throw EngineException(IMG_GetError(), file);

			textures[file] = GFX::createGLTextureFromSurface(surf);
			SDL_FreeSurface(surf);
			if (0 == textures[file])
				throw EngineException("Failed to create GL texture from surface:", file);*/
		}
	}
}

void ResourceManager::freeResources() {
	for (auto pair : fonts) {
		if (pair.second) {
			TTF_CloseFont(pair.second);
#ifdef __DEBUG
			debug("Font freed:");
			debug(pair.first.c_str());
#endif
		}
	}

	for (auto pair : textures) {
		if (pair.second) {
			SDL_DestroyTexture(pair.second);
#ifdef __DEBUG
			debug("Texture destroyed:");
			debug(pair.first.c_str());
#endif
		}
	}

	for (auto pair : sounds) {
		if (pair.second) {
			Mix_FreeChunk(pair.second);
#ifdef __DEBUG
			debug("Sound freed:");
			debug(pair.first.c_str());
#endif
		}
	}

	for (auto pair : mp3files) {
		if (pair.second) {
			Mix_FreeMusic(pair.second);
#ifdef __DEBUG
			debug("MP3 freed:");
			debug(pair.first.c_str());
#endif
		}
	}

#ifdef __DEBUG
	debug("ResourceManager::freeResources() finished");
#endif
}

SDL_Texture * ResourceManager::getTexture(std::string fileName) {
	return textures[fileName];
}

TTF_Font * ResourceManager::getFont(std::string fileName) {
	return fonts[fileName];
}

Mix_Chunk * ResourceManager::getSound(std::string fileName) {
	return sounds[fileName];
}

Mix_Music * ResourceManager::getMP3(std::string fileName) {
	return mp3files[fileName];
}
