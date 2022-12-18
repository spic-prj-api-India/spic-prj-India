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

		void AddScene(const std::vector<std::shared_ptr<spic::GameObject>>& entities);
		void AddSettings(const std::map<std::string, std::string> settings);
		void Save();
		void LoadScene(const std::vector<std::shared_ptr<spic::GameObject>>& entities);
		/*void LoadSettings(std::map<std::string, std::string>& values);*/

	private:
		void AddContent(bool& isPersistable, const std::shared_ptr<spic::GameObject>& entity, IMemento& memento);
		void AddProperties(const std::shared_ptr<spic::Persistable>& entity, IMemento& memento);
		void LoadProperties(const std::shared_ptr<spic::Persistable>& entity, TiXmlElement* element);
		void GetPersistableEntities(std::map<std::string, std::shared_ptr<spic::Persistable>>&, const std::vector<std::shared_ptr<spic::GameObject>>& entities);
		void ParseScene(TiXmlElement* sceneElement, const std::vector<std::shared_ptr<spic::GameObject>>& entities);

	private:
		spic::SaveDocument* saveDocument;

	};
}

#endif // DATAHANDLER_H_