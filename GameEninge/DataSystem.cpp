#include "DataSystem.hpp"
#include "GameEngine.hpp"
#include "TypeHelper.hpp"

namespace spic::internal::systems {
	DataSystem::DataSystem()
	{}

	void DataSystem::Start(std::vector<std::shared_ptr<spic::GameObject>>& entities, Scene& currentScene)
	{
		// Data ophalen uit xml's
		// Door de data loopen
			// In de loop checken of het gameObject/presistable bestaat
			// Zo ja verstuur data naar Load
			// zo niet maak game object met de functie van Game Engine (CreateType), gebruik hier dan de type name uit de xml data
		for (const std::shared_ptr<spic::Persistable>& persistable : GetPersistableEntities(entities)) {
			persistable->Load();
		}
	}

	void DataSystem::Update(std::vector<std::shared_ptr<spic::GameObject>>& entities, Scene& currentScene)
	{
	}

	std::vector<std::shared_ptr<spic::Persistable>> DataSystem::GetPersistableEntities(const std::vector<std::shared_ptr<spic::GameObject>>& entities) const
	{
		// Eerst alle childs in de lijst, daarna pas omhoog werken en parent toevoegen
		using namespace spic::helper_functions::type_helper;
		std::vector<std::shared_ptr<spic::Persistable>> persistableEntities;
		for (const auto& entity : entities) 
		{
			if (SharedPtrIsOfType<spic::Persistable>(entity))
				persistableEntities.emplace_back(CastSharedPtrToType<spic::Persistable>(entity));

			for (const auto& child : entity->GetChildren()) 
				if (SharedPtrIsOfType<spic::Persistable>(child))
					persistableEntities.emplace_back(CastSharedPtrToType<spic::Persistable>(child));
		}

		return persistableEntities;
	}
}