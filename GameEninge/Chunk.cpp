#include "Chunk.hpp"
// Use to remove SDL2 warnings from error list
#include <codeanalysis\warnings.h>
#pragma warning( push )
#pragma warning ( disable : ALL_CODE_ANALYSIS_WARNINGS )
#include <SDL2/SDL_mixer.h>
#pragma warning( pop )

using namespace spic::internal::audio::impl;

Chunk::Chunk(const std::string& path) : chunk(Mix_LoadWAV(path.c_str()), Mix_FreeChunk)
{
}

Mix_Chunk* Chunk::GetChunk() const
{
	return chunk.get();
}