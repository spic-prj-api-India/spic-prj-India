#ifndef PERSISTABLE_H_
#define PERSISTABLE_H_

#include "GameObject.hpp"
#include <map>
#include <functional>

namespace spic {
	class Persistable
	{
	public:
		Persistable(GameObject* gameObject);
		/**
		 * @brief Needs to declare virtual destructor,
		 *			otherwise can't be used as interface
		 */
		virtual ~Persistable() = default;
		Persistable(const Persistable& other) = delete;
		Persistable(Persistable&& other) = delete;
		Persistable& operator=(const Persistable& other) = delete;
		Persistable& operator=(Persistable&& other) = delete;

		virtual std::map<std::string, std::function<std::string()>> SaveProperties();
		virtual std::map<std::string, std::function<void(const std::string&)>> LoadProperties();
	private:
		GameObject* gameObject;
	};
}

#endif // PERSISTABLE_H_