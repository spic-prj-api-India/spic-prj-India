#pragma once
#include "IEngineExtension.hpp"
#include <map>
#include <regex>
#include <memory>
#include <mutex>

class GameEngine {
private:
	static GameEngine* pinstance_;
	static std::mutex mutex_;
protected:
	GameEngine();
	~GameEngine();

	std::map<std::string, std::shared_ptr<IEngineExtension>> _extensions;
public:
	GameEngine(GameEngine& other) = delete;
	GameEngine(GameEngine&& other) = delete;
	void operator=(const GameEngine&) = delete;
	GameEngine& operator=(GameEngine&& other) = delete;
	static GameEngine* GetInstance();

	template <typename T>
	void AddExtension(std::shared_ptr<T> extension) {
		_extensions[GetTypeName<T>()] = extension;
	}

	template <typename T>
	std::weak_ptr<T> GetExtension() {
		return std::dynamic_pointer_cast<T>(_extensions[GetTypeName<T>()]);
	}

	template <typename T>
	bool HasExtension() {
		return _extensions.count(GetTypeName<T>());
	}

	template <typename T>
	void RemoveExtension() {
		std::string typeName = GetTypeName<T>();
		std::shared_ptr<T> deletePtr = std::dynamic_pointer_cast<T>(_extensions[typeName]);
		_extensions.erase(typeName);
		do {
			deletePtr.reset();
		} while (deletePtr.use_count() != 0);
	}
private:
	template <typename T>
	std::string GetTypeName() {
		std::string typeName = typeid(T).name();
		std::string strippedName = std::regex_replace(typeName, std::regex("class "), "");
		return strippedName;
	}
};