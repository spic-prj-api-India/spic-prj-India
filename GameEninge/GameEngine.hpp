#ifndef GAMEENGINE_H_
#define GAMEENGINE_H_

#include <map>
#include <regex>
#include <memory>
#include <mutex>
#include "IEngineExtension.hpp"

namespace spic {
	/**
	 * @brief The main class of the engine, has multiple functions to configure engine and load scenes.
	 */
	class GameEngine {
	private:
		static GameEngine* pinstance_;
		static std::mutex mutex_;
	protected:
		GameEngine();
		~GameEngine();

		std::map<std::string, std::shared_ptr<extensions::IEngineExtension>> _extensions;
	public:
		GameEngine(GameEngine& other) = delete;
		GameEngine(GameEngine&& other) = delete;
		void operator=(const GameEngine& other) = delete;
		GameEngine& operator=(GameEngine&& other) = delete;
		static GameEngine* GetInstance();

		/**
		* @brief Adds extensions to engine.
		* @param extension A IEngineExtension is used by the engine to
		*        configure the base functionality of the engine 
		* @spicapi
		*/
		template <typename T>
		void AddExtension(std::shared_ptr<T> extension)
		{
			_extensions[GetTypeName<T>()] = extension;
		}

		/**
		* @brief Gets extension of type IEngineExtension.
		* @spicapi
		*/
		template <typename T>
		std::weak_ptr<T> GetExtension()
		{
			return std::dynamic_pointer_cast<T>(_extensions[GetTypeName<T>()]);
		}

		/**
		* @brief Checks if extension exists.
		* @spicapi
		*/
		template <typename T>
		bool HasExtension()
		{
			return _extensions.count(GetTypeName<T>());
		}

		/**
		* @brief removes extension from engine.
		* @spicapi
		*/
		template <typename T>
		void RemoveExtension()
		{
			std::string typeName = GetTypeName<T>();
			std::shared_ptr<T> deletePtr = std::dynamic_pointer_cast<T>(_extensions[typeName]);
			_extensions.erase(typeName);
			do {
				deletePtr.reset();
			} while (deletePtr.use_count() != 0);
		}
	private:
		template <typename T>
		std::string GetTypeName() const
		{
			std::string typeName = typeid(T).name();
			std::string strippedName = std::regex_replace(typeName, std::regex("class "), "");
			return strippedName;
		}
		template <typename T>
		bool IsEngineExtension(std::shared_ptr<T> extension) const
		{
			std::shared_ptr<extensions::IEngineExtension> castedEngineExtension = std::dynamic_pointer_cast<extensions::IEngineExtension>(extension);
			return castedEngineExtension != nullptr;
		}
	};
}

#endif // GAMEENGINE_H_