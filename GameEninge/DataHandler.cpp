#include "DataHandler.hpp"
#include <tinyxml.h>
#include "TypeHelper.hpp"
#include "Persistable.hpp"
#include "EntityManager.hpp"

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
		if (!TypeHelper::SharedPtrIsOfType<Persistable>(entity))
			continue;
		IMemento entityMemento;
		AddContent(entity, entityMemento);
		TiXmlElement* contentElement = new TiXmlElement("parent");
		this->saveDocument->AddContent(entityMemento, contentElement);
		sceneElement->LinkEndChild(contentElement);
	}
}

void spic::DataHandler::AddContent(const std::shared_ptr<spic::GameObject>& entity, IMemento& memento)
{
	for (const auto& child : entity->GetChildren())
	{
		IMemento subMemento;
		AddContent(child, subMemento);
		memento.contents.emplace_back(subMemento);
	}
	AddProperties(entity, memento);
}

void spic::DataHandler::AddProperties(const std::shared_ptr<spic::GameObject>& entity, IMemento& memento)
{
	const auto name = entity->Name();
	if (!name.empty())
		memento.properties["name"] = name;

	const auto tag = entity->Tag();
	if (!tag.empty())
		memento.properties["tag"] = tag;

	const auto active = entity->Active();
	if (active || !active)
		memento.properties["active"] = std::to_string(active);

	const auto layer = entity->Layer();
	if (layer)
		memento.properties["layer"] = std::to_string(layer);

	const auto position = entity->Position();
	if (position.x && position.y)
	{
		memento.properties["pos_x"] = std::to_string(position.x);
		memento.properties["pos_y"] = std::to_string(position.y);
	}

	const auto rotation = entity->Rotation();
	if (rotation)
		memento.properties["rotation"] = std::to_string(rotation);

	const auto scale = entity->Scale();
	if (scale)
		memento.properties["scale"] = std::to_string(scale);

	const auto dont_destroy_on_load = entity->DontDestroyOnLoad();
	if (dont_destroy_on_load || !dont_destroy_on_load)
		memento.properties["dont_destroy_on_load"] = std::to_string(dont_destroy_on_load);

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

void spic::DataHandler::AddPropertiesToEntity(const std::shared_ptr<spic::GameObject>& entity, TiXmlElement* element)
{
	for (const TiXmlAttribute* att = element->FirstAttribute(); att != nullptr; att = att->Next())
	{
		std::string result = att->Value();

		std::string active = "active";
		std::string tag = "tag";
		std::string layer = "layer";
		std::string pos_x = "pos_x";
		std::string pos_y = "pos_y";
		std::string rotation = "rotation";
		std::string scale = "scale";
		std::string dont_destroy_on_load = "dont_destroy_on_load";


		if (att->Name() == active) {
			entity->Active(std::stoi(result));
		}
		else if (att->Name() == tag) {
			entity->Tag(result);
		}
		else if (att->Name() == layer) {
			entity->Layer(std::stoi(result));
		}
		else if (att->Name() == pos_x) {
			entity->Transform()->position.x = std::stof(result);
		}
		else if (att->Name() == pos_y) {
			entity->Transform()->position.y = std::stof(result);
		}
		else if (att->Name() == rotation) {
			entity->Transform()->rotation = std::stof(result);
		}
		else if (att->Name() == scale) {
			entity->Transform()->scale = std::stof(result);
		}
		else if (att->Name() == dont_destroy_on_load && (att->ValueStr() == "1" || att->ValueStr() == "0")) {
			entity->DontDestroyOnLoad(std::stoi(result));
		}
	}
}

void spic::DataHandler::ParseScene(TiXmlElement* root, const std::vector<std::shared_ptr<spic::GameObject>>& entities)
{
	for (TiXmlElement* element = root->FirstChildElement(); element != nullptr; element = element->NextSiblingElement())
	{
		ParseScene(element, entities);

		if (element->ValueStr() == "properties")
		{
			const auto& entity = GameObject::Find(element->Attribute("name"));

			if (entity != nullptr)
			{
				AddPropertiesToEntity(entity, element);
			}
			else
			{
				std::shared_ptr<GameObject> newEntity = std::make_shared<GameObject>(element->Attribute("name"));
				AddPropertiesToEntity(newEntity, element);
				spic::internal::EntityManager::GetInstance()->AddEntity(newEntity);
			}
		}
	}
}