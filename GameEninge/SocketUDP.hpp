#ifndef SOCKETUDP_H_
#define SOCKETUDP_H_

#include "INetworkExtension.hpp"
#include <thread>
#include "ThreadWrapper.hpp"


namespace spic {
	
	/**
	 * @brief An basic udp send/recieve client
	 * @details Socket buffer is max 64k and a basic message is around a 100~200 bytes.
	*/
	class SocketUDP : public spic::INetworkExtension
	{
	public:
		void InitSocket(const int inputBufferSize, const int outputBufferSize) override;
		void InitListener(const int port) override;
		void InitSender(const std::string& ip, const int port) override;
		void StopConnections() override;
		void SocketReset() override;
		void Convert(const NetworkPacket& data) override;
		void SendData() override;
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