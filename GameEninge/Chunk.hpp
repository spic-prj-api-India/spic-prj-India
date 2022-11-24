#ifndef CHUNK_H_
#define CHUNK_H_

// Use to remove SDL2 warnings from error list
#include <codeanalysis\warnings.h>
#pragma warning( push )
#pragma warning ( disable : ALL_CODE_ANALYSIS_WARNINGS )
#include <SDL2/SDL_mixer.h>
#pragma warning( pop )
#include <string>
#include <memory>

namespace spic::internal::audio {
	/// @brief Holds a loaded audio chunk
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

#endif // CHUNK_H_