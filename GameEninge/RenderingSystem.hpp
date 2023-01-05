#ifndef RENDERINGSYSTEM_H_
#define RENDERINGSYSTEM_H_

#include "ISystem.hpp"
#include "FPSlistener.hpp"

namespace spic::internal::systems 
{
	/**
	 * @brief A system that renders all game entities
	 */
	class RenderingSystem :
		public spic::internal::systems::ISystem
	{
	public:
		RenderingSystem();
		~RenderingSystem() = default;
		RenderingSystem(RenderingSystem& other) = delete;
		RenderingSystem(RenderingSystem&& other) = delete;
		void operator=(const RenderingSystem& other) = delete;
		RenderingSystem& operator=(RenderingSystem&& other) = delete;

		/**
		* @brief Initiliazes system
		*/
		void Start(std::vector<std::shared_ptr<spic::GameObject>>& entities, Scene& currentScene) override;

		/**
		* @brief Renders all entities in current scene
		*/
		void Update(std::vector<std::shared_ptr<spic::GameObject>>& entities, Scene& currentScene) override;
	private:
		/**
		 * @brief Filters entities between UI and non UI
		 */
		std::vector<std::vector<std::shared_ptr<spic::GameObject>>> GetFilteredEntities(const std::vector<std::shared_ptr<spic::GameObject>>& entities) const;

		/**
		 * @brief Calls draw colliders method in physics extensions.
		 */
		void DrawColliders();
	private:
		/**
		 * @brief The keylistiner bound to show fps
		*/
		std::shared_ptr<spic::internal::input::FPSListener> fps;
	};
}

#endif // RENDERINGSYSTEM_H_