#include "DataHandler.hpp"
#include <tinyxml.h>
#include "TypeHelper.hpp"
#include "Persistable.hpp"
#include "EntityManager.hpp"
#include "GameEngine.hpp"
#include "ContainerHelper.hpp"

/**
* @brief Wrapper class for xml functions.
*/
class spic::internal::SaveDocument
{
public:
	/**
	 * @brief Initialise the save file.
	 * @param fileName The name of the save file.
	*/
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

	/**
	 * @brief Get the first child element of the save file.
	 * @return The first element of the save file.
	*/
	TiXmlElement* FirstChildElement()
	{
		return this->xmlDoc.FirstChildElement();
	}

	/**
	 * @brief Adds a child element past the last child element.
	 * @param child The child element to add.
	*/
	void LinkEndChild(TiXmlElement* child)
	{
		this->xmlDoc.LinkEndChild(child);
	}

	/**
	 * @brief Add the correct elements to the save file.
	 * @param memento The memento containing the objects and properties.
	 * @param root The root element of the save file.
	*/
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

	/**
	 * @brief Load the GameObjects and set their properties from a save file.
	 * @param parentMemento The parent memento containing the objects and their properties of a parent GameObject.
	 * @param parentElement The element of a parent GameObject.
	*/
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

	/**
	 * @brief Save a local save file.
	*/
	void SaveFile()
	{
		if (!xmlDoc.NoChildren())
			this->xmlDoc.SaveFile(this->path);
	}

private:
	/**
	 * @brief The xml document which will serve as the save file.
	*/
	TiXmlDocument xmlDoc;
	
	/**
	 * @brief The relative path to the local destination of the save file.
	*/
	std::string path;
};

spic::DataHandler::DataHandler(const std::string& fileName)
{
	this->saveDocument = new spic::internal::SaveDocument(fileName);
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
	if (helper_functions::type_helper::SharedPtrIsOfType<Persistable>(entity))
	{
		AddProperties(helper_functions::type_helper::CastSharedPtrToType<Persistable>(entity), memento);
		isPersistable = true;
	}
}

void spic::DataHandler::AddProperties(const std::shared_ptr<spic::Persistable>& entity, IMemento& memento)
{
	for (const auto& propertyPair : entity->SaveProperties())
	{
		const std::string name = propertyPair.first;
		const std::string& value = propertyPair.second();
		if (!value.empty())
			memento.properties[name] = value;
	}
}

void spic::DataHandler::AddSettings(const std::map<std::string, std::string>& settings)
{
	TiXmlElement* settingsElement = this->saveDocument->FirstChildElement();
	if (settingsElement == nullptr) {
		settingsElement = new TiXmlElement("settings");
		this->saveDocument->LinkEndChild(settingsElement);
	}

	for (const auto& settingsPair : settings)
	{
		const std::string name = settingsPair.first;
		const std::string value = settingsPair.second;
		settingsElement->SetAttribute(name, value);
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
	const TiXmlElement& scenes = *this->saveDocument->FirstChildElement();
	const TiXmlElement* sceneElement = GetLastestSavedScene(scenes);
	if (sceneElement == nullptr)
		return;

	std::vector<IMemento> scene;
	for (const TiXmlElement* parentElement = sceneElement->FirstChildElement(); parentElement != nullptr; parentElement = parentElement->NextSiblingElement())
	{
		IMemento parentMemento = IMemento();
		this->saveDocument->LoadContent(parentMemento, *parentElement);
		scene.emplace_back(parentMemento);
	}

	for (const auto& parent : scene)
	{
		const std::string& name = parent.properties.at("name");
		auto entity = helper_functions::container::Find<GameObject>(entities, [name](std::shared_ptr<GameObject> entity) {return entity->Name() == name; });
		auto loadedEntity = LoadContent(parent, entity);
		if (entity == nullptr)
			spic::internal::EntityManager::GetInstance()->AddEntity(loadedEntity);
	}
}

std::shared_ptr<spic::GameObject> spic::DataHandler::LoadContent(IMemento parent, std::shared_ptr<spic::GameObject> entity)
{
	if (entity == nullptr)
	{
		const std::string& name = parent.properties["name"];
		entity = GameObject::Find(name);
		if (entity == nullptr)
		{
			entity = spic::GameEngine::GetInstance()->CreateType(parent.properties["type_name"]);
			entity->Name(parent.properties["name"]);
		}
	}

	if (helper_functions::type_helper::SharedPtrIsOfType<Persistable>(entity))
		LoadProperties(helper_functions::type_helper::CastSharedPtrToType<Persistable>(entity), parent.properties);

	auto children = entity->GetChildren();
	for (const auto& child : parent.contents)
	{
		const std::string& name = child.properties.at("name");
		auto childEntity = helper_functions::container::Find<GameObject>(children, [name](std::shared_ptr<GameObject> entity) {return entity->Name() == name; });
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
		for (const auto& propertyPair : loadProperties)
		{
			const std::string name = propertyPair.first;
			auto setter = propertyPair.second;
			const std::string attributeName = attribute.first;
			if (attributeName == name)
				setter(attribute.second);
		}
	}
}

void spic::DataHandler::LoadSettings(std::map<std::string, std::string>& values)
{
	const TiXmlElement& settingsElement = *this->saveDocument->FirstChildElement();
	for (const TiXmlAttribute* att = settingsElement.FirstAttribute(); att != nullptr; att = att->Next())
	{
		values[att->Name()] = att->Value();
	}
}