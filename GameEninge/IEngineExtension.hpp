#ifndef IENGINEEXTENSION_H_
#define IENGINEEXTENSION_H_

/**
 * @brief Contains all extensions where you can pick and choose from
*/
namespace spic::extensions 
{
	/**
	 * @brief A interface for the engine extensions
	 */
	class IEngineExtension {
	public:
		IEngineExtension() = default;

		/**
		 * @brief Needs to declare virtual destructor,
		 *			otherwise can't be used as interface
		 */
		virtual ~IEngineExtension() = default;
		IEngineExtension(const IEngineExtension& other) = default;
		IEngineExtension(IEngineExtension&& other) = default;
		virtual IEngineExtension& operator=(const IEngineExtension& other) = default;
		virtual IEngineExtension& operator=(IEngineExtension&& other) = default;
	private:
	};
}

#endif // IENGINEEXTENSION_H_