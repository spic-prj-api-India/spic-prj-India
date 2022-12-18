#include "DataHandler.hpp"
#include <tinyxml.h>
#include "TypeHelper.hpp"
#include "Persistable.hpp"
#include "EntityManager.hpp"
#include "GameEngine.hpp"

class spic::SaveDocument {
public:
	SaveDocument(const std::string& fileName)
	{
		this->path = "save_files/" + fileName + ".save";
		this->xmlDoc = {};
	}

	TiXmlElement* FirstChildElement()
	{
		return this->xmlDoc.FirstChildElement();
	}

	void LinkEndChild(TiXmlElement* child)
	{
		this->xmlDoc.LinkEndChild(child);
	}

	void AddContent(const spic::IMemento& memento, TiXmlElement* root)
	{
		TiXmlElement* contents = new TiXmlElement("children");
		for (auto& sub_memento : memento.contents)
		{
			TiXmlElement* object = new TiXmlElement("parent");
			AddContent(sub_memento, object);
			contents->LinkEndChild(object);
		}
		root->LinkEndChild(contents);
		TiXmlElement* properties = new TiXmlElement("properties");
		for (auto& [key, value] : memento.properties)
		{
			properties->SetAttribute(key, value);
		}
		root->LinkEndChild(properties);
	}

	void SaveFile()
	{
		this->xmlDoc.SaveFile(this->path);
	}

	std::string Path()
	{
		return this->path;
	}

private:
	TiXmlDocument xmlDoc;
	std::string path;
};

spic::DataHandler::DataHandler(const std::string& fileName)
{
	this->saveDocument = new spic::SaveDocument(fileName);
}

spic::DataHandler::~DataHandler()
{
	delete saveDocument;
}

void spic::DataHandler::AddScene(const std::vector<std::shared_ptr<spic::GameObject>>& entities)
{
	TiXmlElement* scenes = this->saveDocument->FirstChildElement();
	if (scenes == nullptr) {
		scenes = new TiXmlElement("scenes");
		this->saveDocument->LinkEndChild(scenes);
	}
	TiXmlElement* sceneElement = new TiXmlElement("scene");
	scenes->LinkEndChild(sceneElement);

	for (const auto& entity : entities)
	{
		IMemento entityMemento;
		bool isPersistable = false;
		AddContent(isPersistable, entity, entityMemento);
		if (!isPersistable)
			continue;
		TiXmlElement* contentElement = new TiXmlElement("parent");
		this->saveDocument->AddContent(entityMemento, contentElement);
		sceneElement->LinkEndChild(contentElement);
	}
}

void spic::DataHandler::AddContent(bool& isPersistable, const std::shared_ptr<spic::GameObject>& entity, IMemento& memento)
{
	for (const auto& child : entity->GetChildren())
	{
		IMemento subMemento;
		AddContent(isPersistable, child, subMemento);
		memento.contents.emplace_back(subMemento);
	}
	memento.properties["name"] = entity->Name();
	if (TypeHelper::SharedPtrIsOfType<Persistable>(entity)) {
		AddProperties(TypeHelper::CastSharedPtrToType<Persistable>(entity), memento);
		isPersistable = true;
	}
}

void spic::DataHandler::AddProperties(const std::shared_ptr<spic::Persistable>& entity, IMemento& memento)
{
	for (const auto& propertyPair : entity->SaveProperties()) {
		const std::string name = propertyPair.first;
		const std::string& value = propertyPair.second();
		if (!value.empty())
			memento.properties[name] = value;
	}
	memento.properties["type_name"] = spic::TypeHelper::GetTypeName(entity);
}

void spic::DataHandler::Save()
{
	this->saveDocument->SaveFile();
}

void spic::DataHandler::LoadScene(const std::vector<std::shared_ptr<spic::GameObject>>& entities)
{
	TiXmlDocument xmlDoc;
	xmlDoc.LoadFile(this->saveDocument->Path());
	if (xmlDoc.Error()) {
		throw std::exception(xmlDoc.ErrorDesc());
	}

	TiXmlElement* root = xmlDoc.RootElement();

	ParseScene(root, entities);
}

void spic::DataHandler::GetPersistableEntities(std::map<std::string, std::shared_ptr<spic::Persistable>>& persistables, const std::vector<std::shared_ptr<spic::GameObject>>& entities)
{
	for (const auto& entity : entities) {
		GetPersistableEntities(persistables, entity->GetChildren());
		const std::string& name = entity->Name();
		if (persistables.count(name) != 0)
			continue;
		if (spic::TypeHelper::SharedPtrIsOfType<spic::Persistable>(entity))
			persistables[name] = spic::TypeHelper::CastSharedPtrToType<spic::Persistable>(entity);
	}
}

void spic::DataHandler::LoadProperties(const std::shared_ptr<spic::Persistable>& entity, TiXmlElement* element)
{
	auto loadProperties = entity->LoadProperties();
	for (const TiXmlAttribute* att = element->FirstAttribute(); att != nullptr; att = att->Next())
	{
		for (const auto& propertyPair : loadProperties) {
			const std::string name = propertyPair.first;
			auto setter = propertyPair.second;
			const std::string attributeName = att->Name();
			if (attributeName == name)
				setter(att->Value());
		}
	}
}

void spic::DataHandler::ParseScene(TiXmlElement* sceneElement, const std::vector<std::shared_ptr<spic::GameObject>>& entities)
{
	std::map<std::string, std::shared_ptr<spic::Persistable>> persistables;
	GetPersistableEntities(persistables, entities);

	for (TiXmlElement* element = sceneElement->FirstChildElement(); element != nullptr; element = element->NextSiblingElement())
	{
		ParseScene(element, entities);
		if (element->ValueStr() == "properties")
		{
			const std::string& name = element->Attribute("name");
			const auto& entity = GameObject::Find(name);

			if (entity != nullptr)
			{
				LoadProperties(spic::TypeHelper::CastSharedPtrToType<Persistable>(entity), element);
			}
			else
			{
				std::shared_ptr<GameObject> newEntity = spic::GameEngine::GetInstance()->CreateType(element->Attribute("type_name"));
				LoadProperties(spic::TypeHelper::CastSharedPtrToType<Persistable>(entity), element);
				spic::internal::EntityManager::GetInstance()->AddEntity(newEntity);
			}
		}
	}
}