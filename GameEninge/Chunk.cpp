#include "Chunk.hpp"



using namespace spic::internal::audio;

Chunk::Chunk(const std::string& path) : chunk(Mix_LoadWAV(path.c_str()), Mix_FreeChunk)
{
}

Mix_Chunk* Chunk::GetChunk() const
{
	return chunk.get();
}

