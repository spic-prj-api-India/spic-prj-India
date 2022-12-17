#include "Debug.hpp"
#include "Renderer.hpp"
#include <iostream>
#include <chrono>

std::string CurrentTimeString() {
	auto now = std::chrono::system_clock::now();
	std::time_t nowTime = std::chrono::system_clock::to_time_t(now);
	struct tm ptm;
	localtime_s(&ptm, &nowTime);
	char buffer[32];
	std::strftime(buffer, 32, "%a, %d.%m.%Y %H:%M:%S", &ptm);
	return buffer;
}

std::string GetLogMessage(const std::string& logLevel, const std::string& message)
{
	return "[" + CurrentTimeString() + "] " + logLevel + ": " + message;
}

namespace spic {
	void Debug::DrawLine(const spic::Point& start, const spic::Point& end, const spic::Color& color)
	{
		if(DEBUG_MODE)
			spic::internal::Rendering::DrawLine(start, end, color);
	}

	void Debug::Log(const std::string& message)
	{
		if (DEBUG_MODE)
			std::cout << GetLogMessage("INFO", message) << std::endl;
	}

	void Debug::LogError(const std::string& error)
	{
		if (DEBUG_MODE)
			std::cerr << GetLogMessage("ERROR", error) << std::endl;
	}

	void Debug::LogWarning(const std::string& warning)
	{
		if (DEBUG_MODE)
			std::cout << GetLogMessage("WARNING", warning) << std::endl;
	}
}