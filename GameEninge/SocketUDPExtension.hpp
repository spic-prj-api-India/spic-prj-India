#ifndef SOCKETUDP_H_
#define SOCKETUDP_H_

#include "INetworkExtension.hpp"
#include <thread>
#include "ThreadWrapper.hpp"


namespace spic::extensions {
	
	/**
	 * @brief An basic udp send/recieve client
	 * @details Socket buffer is max 64k and a basic message is around a 100~200 bytes. Can only be one listener at the same time
	*/
	class SocketUDPExtension : public spic::extensions::INetworkExtension
	{
	public:

		/**
		 * @brief See INetworkExtension interface
		 * @param inputBufferSize 
		 * @param outputBufferSize 
		*/
		void InitSocket(const int inputBufferSize, const int outputBufferSize) override;

		/**
		 * @brief See INetworkExtension interface
		 * @param port 
		*/
		void InitListener(const int port) override;

		/**
		 * @brief See INetworkExtension interface
		 * @param ip 
		 * @param port 
		*/
		void InitSender(const std::string& ip, const int port) override;

		/**
		 * @brief See INetworkExtension interface
		*/
		void StopConnections() override;

		/**
		 * @brief See INetworkExtension interface
		*/
		void SocketReset() override;

		/**
		 * @brief See INetworkExtension interface
		 * @param data 
		*/
		void Convert(const NetworkPacket& data) override;

		/**
		 * @brief See INetworkExtension interface
		*/
		void SendData() override;

		/**
		 * @brief See INetworkExtension interface
		 * @return 
		*/
		std::vector<NetworkPacket> RetrieveData() override;
	private:
		/**
		 * @brief udp socket listeners 
		*/
		std::vector<ThreadWrapper> vecOfThreads;

		/**
		 * @brief outputBuffer
		*/
		std::vector<NetworkPacket> outputBuffer;

		/**
		 * @brief inputbuffer
		*/
		std::vector<std::string> inputBuffer;

		/**
		 * @brief the ip address to send to
		*/
		std::string ip;

		/**
		 * @brief port to send
		*/
		int port;
		int outputBufferSize;
		int inputBufferSize;
	};
}
#endif //SOCKETUDP_H_