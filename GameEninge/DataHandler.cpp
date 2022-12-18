#include "DataHandler.hpp"
#include <tinyxml.h>
#include "TypeHelper.hpp"
#include "Persistable.hpp"
#include "EntityManager.hpp"
#include "GameEngine.hpp"
#include "ContainerHelper.hpp"

class spic::SaveDocument {
public:
	SaveDocument(const std::string& fileName)
	{
		this->path = "save_files/" + fileName + ".save";
		this->xmlDoc = {};
		struct stat buffer;
		const bool fileExist = (stat(this->path.c_str(), &buffer) == 0);
		if (fileExist) {
			xmlDoc.LoadFile(this->path);
			if (xmlDoc.Error())
				throw std::exception(xmlDoc.ErrorDesc());
		}
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

	void LoadContent(spic::IMemento& parentMemento, const TiXmlElement& parentElement)
	{
		const TiXmlElement& contents = *parentElement.FirstChildElement();
		const TiXmlElement& properties = *contents.NextSiblingElement();
		for (const TiXmlElement* parent = contents.FirstChildElement(); parent != nullptr; parent = parent->NextSiblingElement())
		{
			spic::IMemento subMemento = spic::IMemento();
			LoadContent(subMemento, *parent);
			parentMemento.contents.emplace_back(subMemento);
		}
		for (const TiXmlAttribute* att = properties.FirstAttribute(); att != nullptr; att = att->Next())
		{
			parentMemento.properties[att->Name()] = att->Value();
		}
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
}

void spic::DataHandler::Save()
{
	this->saveDocument->SaveFile();
}

const TiXmlElement* GetLastestSavedScene(const TiXmlElement& scenes)
{
	const TiXmlElement* sceneElement = scenes.FirstChildElement();
	while (sceneElement->NextSiblingElement() != nullptr)
		sceneElement = sceneElement->NextSiblingElement();
	return sceneElement;
}

void spic::DataHandler::LoadScene(const std::vector<std::shared_ptr<spic::GameObject>>& entities)
{
	// Get latest saved scene
	const TiXmlElement& scenes = *this->saveDocument->FirstChildElement();
	const TiXmlElement* sceneElement = GetLastestSavedScene(scenes);
	if (sceneElement == nullptr)
		return;

	// Load xml data into struct
	std::vector<IMemento> scene;
	for (const TiXmlElement* parentElement = sceneElement->FirstChildElement(); parentElement != nullptr; parentElement = parentElement->NextSiblingElement())
	{
		IMemento parentMemento = IMemento();
		this->saveDocument->LoadContent(parentMemento, *parentElement);
		scene.emplace_back(parentMemento);
	}

	// Update and create entities with data
	for (const auto& parent : scene) {
		const std::string& name = parent.properties.at("name");
		auto entity = ContainerHelper::Find<GameObject>(entities, [name](std::shared_ptr<GameObject> entity) {return entity->Name() == name; });
		auto loadedEntity = LoadContent(parent, entity);
		if(entity == nullptr)
			spic::internal::EntityManager::GetInstance()->AddEntity(loadedEntity);
	}
}

std::shared_ptr<spic::GameObject> spic::DataHandler::LoadContent(IMemento parent, std::shared_ptr<spic::GameObject> entity)
{
	// Find or create entity if not exist
	if (entity == nullptr) {
		const std::string& name = parent.properties["name"];
		entity = GameObject::Find(name);
		if (entity == nullptr) {
			entity = spic::GameEngine::GetInstance()->CreateType(parent.properties["type_name"]);
			entity->Name(parent.properties["name"]);
		}
	}
	// if entity is persistable load properties
	if (spic::TypeHelper::SharedPtrIsOfType<Persistable>(entity))
		LoadProperties(spic::TypeHelper::CastSharedPtrToType<Persistable>(entity), parent.properties);
	
	// Add/Update all children to/of entity
	auto children = entity->GetChildren();
	for (const auto& child : parent.contents) {
		const std::string& name = child.properties.at("name");
		auto childEntity = ContainerHelper::Find<GameObject>(children, [name](std::shared_ptr<GameObject> entity) {return entity->Name() == name; });
		auto loadedChild = LoadContent(child, childEntity);
		if (childEntity == nullptr)
			entity->AddChild(loadedChild);
	}
	return entity;
}


void spic::DataHandler::LoadProperties(const std::shared_ptr<spic::Persistable>& entity, const std::map<std::string, std::string> attributes)
{
	auto loadProperties = entity->LoadProperties();
	for (const auto& attribute : attributes)
	{
		for (const auto& propertyPair : loadProperties) {
			const std::string name = propertyPair.first;
			auto setter = propertyPair.second;
			const std::string attributeName = attribute.first;
			if (attributeName == name)
				setter(attribute.second);
		}
	}
}
