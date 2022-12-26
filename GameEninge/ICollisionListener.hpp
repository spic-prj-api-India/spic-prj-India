#ifndef ICOLLISIONLISTENER_H_
#define ICOLLISIONLISTENER_H_

#include <functional>
#include "GameObject.hpp"
#include "Collider.hpp"

namespace spic::extensions {
	/**
	* @brief An interface for physic collision listeners
	*/
	class ICollisionListener {
	public:
		typedef std::function<void(const std::shared_ptr<spic::GameObject>&, const std::shared_ptr<spic::Collider>&)> CollisionCallback;

		ICollisionListener();

		/**
		* @brief Constructor for all callback methods
		 * @param enterCallback Callback that runs OnTriggerEnter2D in behaviour scripts of entity if entity enters collision.
		 *			Format: [](const std::shared_ptr<spic::GameObject>&, const std::shared_ptr<spic::Collider>&){}
		 * @param exitCallback Callback that runs OnTriggerExit2D in behaviour scripts of entity if entity exits collision.
		 *			Format: [](const std::shared_ptr<spic::GameObject>&, const std::shared_ptr<spic::Collider>&){}
		 * @param stayCallback  Callback that runs OnTriggerStay2D in behaviour scripts of entity if entity stays collision.
		 *			Format: [](const std::shared_ptr<spic::GameObject>&, const std::shared_ptr<spic::Collider>&){}
		* @spicapi
		*/
		ICollisionListener(CollisionCallback enterCallback,
			CollisionCallback exitCallback,
			CollisionCallback stayCallback);
		virtual ~ICollisionListener() = default;
		ICollisionListener(const ICollisionListener& other) = delete;
		ICollisionListener(ICollisionListener&& other) = delete;
		virtual ICollisionListener& operator=(const ICollisionListener& other) = delete;
		virtual ICollisionListener& operator=(ICollisionListener&& other) = delete;
	};
}

#endif // ICOLLISIONLISTENER_H_