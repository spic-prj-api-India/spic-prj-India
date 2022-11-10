#ifndef IENGINEEXTENSION_H_
#define IENGINEEXTENSION_H_

namespace extensions {
	class IEngineExtension {
	public:
		IEngineExtension() {};
		virtual ~IEngineExtension() {}
		IEngineExtension(const IEngineExtension& other) = delete;
		IEngineExtension(IEngineExtension&& other) = delete;
		IEngineExtension& operator=(const IEngineExtension& other) = delete;
		IEngineExtension& operator=(IEngineExtension&& other) = delete;
	private:
	};
}

#endif // IENGINEEXTENSION_H_