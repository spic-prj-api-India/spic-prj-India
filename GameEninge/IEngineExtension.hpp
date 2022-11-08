#pragma once

class IEngineExtension {
public:
    IEngineExtension();
	virtual ~IEngineExtension() {}
    IEngineExtension(const IEngineExtension& other) = delete;
    IEngineExtension(IEngineExtension&& other) = delete;
    IEngineExtension& operator=(const IEngineExtension& other) = delete;
    IEngineExtension& operator=(IEngineExtension&& other) = delete;
private:
};