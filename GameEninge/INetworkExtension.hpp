#ifndef NETWORKEXTENSION_H_
#define NETWORKEXTENSION_H_

#include "IEngineExtension.hpp"
#include <string>
#include <vector>
#include "NetworkPacket.hpp"
namespace spic {

	/**
	 * @brief An interface for all networkextensions
	*/
	class INetworkExtension : public spic::internal::extensions::IEngineExtension
	{
	public:

		/**
		 * @brief Sets the inputbufferSize and outputBufferSize of the implementation
		 * @param inputBufferSize 
		 * @param outputBufferSize 
		*/
		virtual void InitSocket(const int inputBufferSize, const int outputBufferSize) = 0;

		/**
		 * @brief Sets up a port listiner
		 * @param port 
		*/
		virtual void InitListener(const int port) = 0;

		/**
		 * @brief Sets up a destination
		 * @param ip 
		 * @param port 
		*/
		virtual void InitSender(const std::string& ip, const int port) = 0;

		/**
		 * @brief Stops all connections
		*/
		virtual void StopConnections() = 0;

		/**
		 * @brief Reset send socket
		*/
		virtual void SocketReset() = 0;

		/**
		 * @brief Converts NetworkPacket to our protocol
		 * @param data 
		*/
		virtual void Convert(const NetworkPacket& data) = 0;

		/**
		 * @brief Sends data to destination
		*/
		virtual void SendData() = 0;

		/**
		 * @brief Retrieves everything in the socket buffer
		 * @return An unsorted list of NetworkPackets
		*/
		virtual std::vector<NetworkPacket> RetrieveData() = 0;
	};
}
#endif