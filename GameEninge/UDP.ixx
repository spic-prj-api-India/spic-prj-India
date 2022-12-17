module;

#define _WIN32_WINNT _WIN32_WINNT_WIN10
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#pragma comment(lib, "Ws2_32.lib")

#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <boost/bind/bind.hpp>
#include <thread>
#include <iostream>
#include <winsock2.h>
#include <memory>
#include <boost/algorithm/string/case_conv.hpp>
#include <boost/algorithm/string.hpp>
#include "Debug.hpp"

export module UDP;

using boost::asio::ip::udp;
using boost::asio::ip::tcp;
using boost::asio::ip::address;

export std::vector<std::string> buffer;
export std::mutex bufferMutex;
boost::asio::io_service io_service;

struct Client {
    udp::socket socket{ io_service };
    boost::array<char, 65536> recv_buffer;
    udp::endpoint remote_endpoint;

    ~Client()
    {
        socket.close();
    }

    void handle_receive(const boost::system::error_code& error, size_t bytes_transferred) {

        if (error.failed()) {
            spic::Debug::LogError("Receive failed: " + error.message());
            return;
        }

        bufferMutex.lock();
        auto in = std::string(recv_buffer.begin(), recv_buffer.begin() + bytes_transferred);
        std::vector<std::string> strs;
        boost::split(strs, in, boost::is_any_of("~"));

        for (auto str : strs)
        {
            if(str != "")
                buffer.push_back(str);
        }
        bufferMutex.unlock();
        wait();
    }

    void wait() {
        socket.async_receive_from(boost::asio::buffer(recv_buffer),
            remote_endpoint,
            boost::bind(&Client::handle_receive, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
    }

};

std::mutex listenersMutex;
std::vector<std::unique_ptr<Client>> listeners;

export void Receiver(const int UDP_PORT)
{
    try {
        listeners.emplace_back(std::make_unique<Client>());
        auto& client = listeners.back();
        client->socket.open(udp::v4());
        client->socket.bind(udp::endpoint(udp::v4(), UDP_PORT));

        client->wait();

        io_service.run();
    }
    catch (const std::exception& ex) {
        const std::string& message = ex.what();
        spic::Debug::LogError("Receive failed: " + message);
    }
}

export void StopRunning()
{
    listeners.clear();
}

export void Sender(const std::string& in, const std::string& IPADDRESS, const int UDP_PORT)
{
    boost::asio::io_service io_service;
    udp::socket socket(io_service);

    udp::endpoint remote_endpoint = udp::endpoint(address::from_string(IPADDRESS), UDP_PORT);
    socket.open(udp::v4());

    boost::system::error_code error;
    auto sent = socket.send_to(boost::asio::buffer(in), remote_endpoint, 0, error);
    socket.close();
    if(error.failed())
        spic::Debug::LogError("Send failed: " + error.message());
}