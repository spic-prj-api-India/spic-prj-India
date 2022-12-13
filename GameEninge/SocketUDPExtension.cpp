#include "SocketUdpExtension.hpp"
#include "NetworkPacket.hpp"
import UDP;

using namespace spic;
using namespace spic::extensions;


void SocketUDPExtension::InitSocket(const int inputBufferSize, const int outputBufferSize)
{
	this->outputBufferSize = inputBufferSize;
	this->inputBufferSize = outputBufferSize;
}

void Helper(const int port)
{
	Receiver(port);
}

void SocketUDPExtension::InitListener(const int port)
{
	auto temp = new int(port);
	ThreadWrapper thwp1(&Receiver, port);
	vecOfThreads.push_back(std::move(thwp1));
	std::this_thread::sleep_for(std::chrono::milliseconds(2000));
}

void SocketUDPExtension::InitSender(const std::string& ip, const int port)
{
	this->port = port;
	this->ip = ip;
}

void SocketUDPExtension::StopConnections()
{
	StopRunning();
	vecOfThreads.clear();
}

void SocketUDPExtension::SocketReset()
{
	this->outputBufferSize = 0;
	this->inputBufferSize = 0;
	this->port = 0;
	this->ip = "";
}

void SocketUDPExtension::Convert(const NetworkPacket& data)
{
	this->inputBuffer.push_back(data.Serialize().str());
}

void SocketUDPExtension::SendData()
{
	for (auto string : inputBuffer)
	{
		Sender(string, ip, port);
	}
	inputBuffer.clear();
}

std::vector<NetworkPacket> SocketUDPExtension::RetrieveData()
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
