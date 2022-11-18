#ifndef GAMEENGINE_H_
#define GAMEENGINE_H_

#include <map>
#include <regex>
#include <memory>
#include <mutex>
#include "IEngineExtension.hpp"
#include "Scene.hpp"

namespace spic {
	/**
	 * @brief The main class of the engine, has multiple functions to configure engine and load scenes.
	 *				The GameEngine class implements a singleton pattern.
	 */
	class GameEngine {
	private:
		static GameEngine* pinstance_;
		static std::mutex mutex_;
	protected:
		GameEngine();
		~GameEngine();

		std::map<std::string, std::shared_ptr<spic::internal::extensions::IEngineExtension>> _extensions;
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
		* @brief Gets extensions of type IEngineExtension.
		* @spicapi
		*/
		template <typename T>
		std::vector<std::weak_ptr<T>> GetExtensions()
		{
			std::vector<std::weak_ptr<T>> extensions;
			for (const auto& extension : _extensions) {
				std::weak_ptr<T> weakExtension = std::dynamic_pointer_cast<T>(extension.second);
				bool isOfType = weakExtension.lock() != nullptr;
				if (isOfType)
					extensions.emplace_back(weakExtension);
			}
			return extensions;
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
		/**
		* @brief Gets name of type
		* @spicapi
		*/
		template <typename T>
		std::string GetTypeName() const
		{
			std::string typeName = typeid(T).name();
			std::string strippedName = std::regex_replace(typeName, std::regex("class "), "");
			return strippedName;
		}

		/**
		* @brief Checks if type is of type IEngineExtension
		* @spicapi
		*/
		template <typename T>
		bool IsEngineExtension(std::shared_ptr<T> extension) const
		{
			auto castedEngineExtension = std::dynamic_pointer_cast<spic::internal::extensions::IEngineExtension>(extension);
			return castedEngineExtension != nullptr;
		}

		/*
		@brief Load the specified scene.
		@param scene: The name of the scene you want to load.
		*/
		void LoadScene(std::shared_ptr<Scene> scene);
		/*
		@brief Destroy the current scene.
		@param forceDelete: Whether you also want to delete all GameObjects in the scene which are set to not be destroyed on load.
		*/
		void DestroyScene(bool forceDelete);
	};
}

#endif // GAMEENGINE_H_