#ifndef PERSISTABLE_H_
#define PERSISTABLE_H_

#include "GameObject.hpp"
#include <map>

namespace spic
{
	class Persistable
	{
	public:
		Persistable() = default;
		/**
		 * @brief Needs to declare virtual destructor,
		 *			otherwise can't be used as interface
		 */
		virtual ~Persistable() = default;
		Persistable(const Persistable& other) = delete;
		Persistable(Persistable&& other) = delete;
		Persistable& operator=(const Persistable& other) = delete;
		Persistable& operator=(Persistable&& other) = delete;
	};
}

#endif // PERSISTABLE_H_