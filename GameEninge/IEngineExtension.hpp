#ifndef IENGINEEXTENSION_H_
#define IENGINEEXTENSION_H_

namespace spic::internal::extensions {
	/**
	 * @brief A interface for the engine extensions
	 */
	class IEngineExtension {
	public:
		IEngineExtension() {};
		/**
		 * @brief Needs to declare virtual destructor,
		 *			otherwise can't be used as interface
		 */
		virtual ~IEngineExtension() {}
		IEngineExtension(const IEngineExtension& other) = delete;
		IEngineExtension(IEngineExtension&& other) = delete;
		IEngineExtension& operator=(const IEngineExtension& other) = delete;
		IEngineExtension& operator=(IEngineExtension&& other) = delete;
	private:
	};
}

#endif // IENGINEEXTENSION_H_