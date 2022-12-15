#ifndef DATAHANDLER_H_
#define DATAHANDLER_H_

#include "GameObject.hpp"
#include <map>
#include "tinyxml.h"
#include "Persistable.hpp"

namespace spic
{
	class SaveDocument;

	struct IMemento
	{
		std::vector<IMemento> contents;
		std::map<std::string, std::string> properties;
	};

	class DataHandler
	{

	public:
		DataHandler(const std::string& fileName);
		~DataHandler();
		DataHandler(const DataHandler& other) = delete;
		DataHandler(DataHandler&& other) = delete;
		DataHandler& operator=(const DataHandler& other) = delete;
		DataHandler& operator=(DataHandler&& other) = delete;

		/**
		* @brief Creates the scene elements of the save file and passes the scene entities to the methods for adding entity elements.
		* @param entities: List of entitites
		*/
		void AddScene(const std::vector<std::shared_ptr<spic::GameObject>>& entities);
		
		/**
		* @brief Saves a local save file.
		*/
		void Save();

		/**
		* @brief Defines an xml document to load, and calls the method for parsing the saved scene file. 
		* @param entities: List of entitites
		*/
		void LoadScene(const std::vector<std::shared_ptr<spic::GameObject>>& entities);

	private:
		/**
		* @brief Recursively adds the scene entities and their to the memento
		* @param entities: List of entitites
		* @param memento: The temporary memento snapshot
		*/
		void AddContent(const std::shared_ptr<spic::GameObject>& entity, IMemento& memento);
		
		/**
		* @brief Adds the properties of the entity to the memento.
		* @param entities: List of entitites
		* @param memento: The temporary memento snapshot
		*/
		void AddProperties(const std::shared_ptr<spic::GameObject>& entity, IMemento& memento);

		/**
		* @brief Sets the entity's properties from the save file.
		* @param entity: The entity of which the properties should be set.
		* @param element: The xml element of the save file to get the attributes from.
		*/
		void AddPropertiesToEntity(const std::shared_ptr<spic::GameObject>& entity, TiXmlElement* element);

		/**
		* @brief Starts parsing the save file which contains the saved entities.
		* @param sceneElement: The root xml element of the save file.
		*/
		void ParseScene(TiXmlElement* root, const std::vector<std::shared_ptr<spic::GameObject>>& entities);

	private:
		spic::SaveDocument* saveDocument;

	};
}

#endif // DATAHANDLER_H_