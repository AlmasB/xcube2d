#include "ResourceManager.h"

std::map<std::string, SDL_Texture *> ResourceManager::textures;
std::map<std::string, TTF_Font *> ResourceManager::fonts;
std::map<std::string, Mix_Chunk *> ResourceManager::sounds;
std::map<std::string, Mix_Music *> ResourceManager::mp3files;

SDL_Texture * ResourceManager::loadTexture(std::string file, SDL_Color trans) {
	SDL_Texture * texture = nullptr;

	SDL_Surface * surf = IMG_Load(file.c_str());
	if (nullptr == surf)
		throw EngineException(IMG_GetError(), file);

	SDL_SetColorKey(surf, SDL_TRUE, SDL_MapRGB(surf->format, trans.r, trans.g, trans.b));
	
	texture = GFX::createTextureFromSurface(surf);
	if (nullptr == texture)
		throw EngineException(SDL_GetError(), file);

	SDL_FreeSurface(surf);

	return texture;
}

TTF_Font * ResourceManager::loadFont(std::string file, const int & pt) {
	TTF_Font * font = TTF_OpenFont(file.c_str(), pt);
	if (nullptr == font)
		throw EngineException(TTF_GetError(), file);
	fonts[file] = font;
	return font;
}

Mix_Chunk * ResourceManager::loadSound(std::string file) {
	Mix_Chunk * sound = Mix_LoadWAV(file.c_str());
	if (nullptr == sound)
		throw EngineException(Mix_GetError(), file);
	sounds[file] = sound;
	return sound;
}

Mix_Music * ResourceManager::loadMP3(std::string file) {
	Mix_Music * mp3 = Mix_LoadMUS(file.c_str());
	if (nullptr == mp3)
		throw EngineException(Mix_GetError(), file);
	mp3files[file] = mp3;
	return mp3;
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
