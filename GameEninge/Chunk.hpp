#ifndef CHUNK_H_
#define CHUNK_H_

#include <string>
#include <memory>

struct Mix_Chunk;

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