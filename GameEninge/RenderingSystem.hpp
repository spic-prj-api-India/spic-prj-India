#ifndef RENDERINGSYSTEM_H_
#define RENDERINGSYSTEM_H_

#include <codeanalysis\warnings.h>
#pragma warning( push )
#pragma warning ( disable : ALL_CODE_ANALYSIS_WARNINGS )
#include "SDL2/SDL.h"
#pragma warning( pop )
#include "ISystem.hpp"
#include "FPSlistener.hpp"

/**
* @brief A system that calls the Start and Update method in scripts of entities
*/
namespace spic::internal::systems {
	class RenderingSystem :
		public spic::systems::ISystem
	{
	public:
		RenderingSystem();
		~RenderingSystem();
		RenderingSystem(RenderingSystem& other) = delete;
		RenderingSystem(RenderingSystem&& other) = delete;
		void operator=(const RenderingSystem& other) = delete;
		RenderingSystem& operator=(RenderingSystem&& other) = delete;

		/**
		* @brief Initiliazes system
		* @spicapi
		*/
		void Start(std::vector<std::shared_ptr<spic::GameObject>>& entities, Scene& currentScene) override;

		/**
		* @brief Renders all entities in current scene
		* @spicapi
		*/
		void Update(std::vector<std::shared_ptr<spic::GameObject>>& entities, Scene& currentScene) override;
	private:

		/**
		 * @brief The keylistiner bound to show fps
		*/
		std::shared_ptr<FPSListener> fps;
		/**
		 * @brief Filters entities between UI and non UI
		 * @spicapi
		 */
		std::vector<std::vector<std::shared_ptr<spic::GameObject>>> GetFilteredEntities(const std::vector<std::shared_ptr<spic::GameObject>>& entities) const;

		/**
		 * @brief Calls draw colliders method in physics extensions.
		 * @spicapi
		 */
		void DrawColliders();
	};
}

#endif // RENDERINGSYSTEM_H_