#ifndef ICOLLISIONLISTENER_H_
#define ICOLLISIONLISTENER_H_

#include <functional>
#include "GameObject.hpp"

namespace spic::extensions {
	/**
	* @brief An interface for physic collision listeners
	*/
	class ICollisionListener {
	public:
		ICollisionListener();
		/**
		* @brief Constructor for all callback methods
		* @spicapi
		*/
		ICollisionListener(std::function<void(const std::shared_ptr<spic::GameObject>, const std::shared_ptr<spic::Collider>)> enterCallback,
			std::function<void(const std::shared_ptr<spic::GameObject>, const std::shared_ptr<spic::Collider>)> exitCallback,
			std::function<void(const std::shared_ptr<spic::GameObject>, const std::shared_ptr<spic::Collider>)> stayCallback);
		virtual ~ICollisionListener() = default;
		ICollisionListener(const ICollisionListener& other) = delete;
		ICollisionListener(ICollisionListener&& other) = delete;
		virtual ICollisionListener& operator=(const ICollisionListener& other) = delete;
		virtual ICollisionListener& operator=(ICollisionListener&& other) = delete;
	};
}

#endif // ICOLLISIONLISTENER_H_