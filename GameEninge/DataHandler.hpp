#ifndef DATAHANDLER_H_
#define DATAHANDLER_H_

#include "GameObject.hpp"
#include <map>
#include "Persistable.hpp"

namespace spic
{
	namespace internal
	{
		/**
		* @brief Wrapper class for xml functions. Gets destroyed in the destructor of the DataHandler.
		*/
		class SaveDocument;
	}

	/**
	 * @brief The memento which serves as a snapshot, containing the objects and their properties to be saved.
	*/
	struct IMemento
	{
		std::vector<IMemento> contents;
		std::map<std::string, std::string> properties;
	};

	/**
	 * @brief Handles various methods for saving and loading values to/from local save files.
	*/
	class DataHandler
	{

	public:
		/**
		 * @brief Handles various methods for saving and loading values to/from local save files.
		 * @param fileName The name of the save file to be saved/loaded.
		*/
		DataHandler(const std::string& fileName);
		~DataHandler();
		DataHandler(const DataHandler& other) = delete;
		DataHandler(DataHandler&& other) = delete;
		DataHandler& operator=(const DataHandler& other) = delete;
		DataHandler& operator=(DataHandler&& other) = delete;

		/**
		* @brief Creates the scene elements of the save file and passes the scene entities to the methods for adding entity elements.
		* @param entities List of entities
		*/
		void AddScene(const std::vector<std::shared_ptr<spic::GameObject>>& entities);

		/**
		* @brief Adds custom settings to be saved to a save file.
		* @param settings The map with keys and values to be saved.
		*/
		void AddSettings(const std::map<std::string, std::string>& settings);

		/**
		* @brief Saves a local save file.
		*/
		void Save();

		/**
		* @brief Gets the latest saved scene, loads xml data, updates and creates entities with the xml data
		* @param entities List of entities
		*/
		void LoadScene(const std::vector<std::shared_ptr<spic::GameObject>>& entities);

		/**
		* @brief Loads saved settings from a save file.
		* @param entities The values to load
		*/
		void LoadSettings(std::map<std::string, std::string>& values);

	private:

		/**
		* @brief Places the persistable entities to be saved in the memento.
		* @param isPersistable Whether the entity is persistable or not
		* @param entity The entity to check whether it's persistable
		* @param memento The temporary memento
		*/
		void AddContent(bool& isPersistable, const std::shared_ptr<spic::GameObject>& entity, IMemento& memento);

		/**
		* @brief Adds the properties of the entity to the memento.
		* @param entity The entity of which the properties will be added to the memento.
		* @param memento The temporary memento
		*/
		void AddProperties(const std::shared_ptr<spic::Persistable>& entity, IMemento& memento);

		/**
		* @brief Loads an entity.
		* @param memento The temporary memento in which to place the entity to be loaded.
		* @param entity The entity to be loaded.
		* @return The persistable entity to be loaded, with its children added to it (if any).
		*/
		std::shared_ptr<spic::GameObject> LoadContent(IMemento parent, std::shared_ptr<spic::GameObject> entity);

		/**
		* @brief Sets the properties to an entity.
		* @param entity The entity of which the properties should be set.
		* @param attributes The map containing the properties to be set to the entity.
		*/
		void LoadProperties(const std::shared_ptr<spic::Persistable>& entity, const std::map<std::string, std::string> attributes);

	private:
		/**
		* @brief Wrapper class for TinyXml functions.
		*/
		spic::internal::SaveDocument* saveDocument;
	};
}

#endif // DATAHANDLER_H_