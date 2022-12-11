#include "SocketUDP.hpp"
#include "NetworkPacket.hpp"
import UDP;

using namespace spic;


void SocketUDP::InitSocket(const int inputBufferSize, const int outputBufferSize)
{
	this->outputBufferSize = inputBufferSize;
	this->inputBufferSize = outputBufferSize;
}

void Helper(const int port)
{
	Receiver(port);
}

void SocketUDP::InitListener(const int port)
{
	auto temp = new int(port);
	ThreadWrapper thwp1(&Receiver, port);
	vecOfThreads.push_back(std::move(thwp1));
	std::this_thread::sleep_for(std::chrono::milliseconds(2000));
}

void SocketUDP::InitSender(const std::string& ip, const int port)
{
	this->port = port;
	this->ip = ip;
}

void SocketUDP::StopConnections()
{
	StopRunning();
	vecOfThreads.clear();
}

void SocketUDP::SocketReset()
{
	this->outputBufferSize = 0;
	this->inputBufferSize = 0;
	this->port = 0;
	this->ip = "";
}

void SocketUDP::Convert(const NetworkPacket& data)
{
	this->inputBuffer.push_back(data.Serialize().str());
}

void SocketUDP::SendData()
{
	for (auto string : inputBuffer)
	{
		Sender(string, ip, port);
	}
	inputBuffer.clear();
}

std::vector<NetworkPacket> SocketUDP::RetrieveData()
{
	std::vector<std::string> vect2;

	// Copying vector by copy function 
	bufferMutex.lock();
	copy(buffer.begin(), buffer.end(), back_inserter(vect2));
	buffer.clear();
	bufferMutex.unlock();
	std::vector<NetworkPacket> temp;

	for (std::string string: vect2)
	{
		try
		{
			NetworkPacket dat;
			dat.Deserialize(string);
			temp.push_back(dat);
		}
		catch (...)
		{

		}
	}
	return temp;
}
