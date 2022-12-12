#ifndef RANDOM_H_
#define RANDOM_H_

namespace spic::internal::math 
{
	//returns a random float between zero and 1
	float RandomFloat();

	//returns a random float in the range -1 < n < 1
	float RandomClamped();
}

#endif // RANDOM_H_
