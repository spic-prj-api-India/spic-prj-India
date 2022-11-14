#pragma once
#include <string>
#include <memory>
#pragma warning(push, 0) // needed to resolve warnings
#include <SDL2/SDL_mixer.h>
#pragma warning(pop)

namespace spic::internal::audio {

	class Chunk
	{
	private:
		std::unique_ptr<Mix_Chunk, void (*)(Mix_Chunk*)> chunk;
	public:

		Mix_Chunk* GetChunk() const;

		/// @brief Constructor
		/// @param path Path to the sound file
		Chunk(const std::string& path);
	};

}
