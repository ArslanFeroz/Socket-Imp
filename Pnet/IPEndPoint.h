#pragma once
#include <string>
#include <WS2tcpip.h>
#include "IpVersion.h"
#include <iostream>
#include <vector>
namespace Pnet {
	class IPEndPoint {

	public:

		// constructor
		IPEndPoint(const char* ip_String, unsigned short port);

		sockaddr_in getAddr();


		// getters
		IPVersion getIpversion();
		std::string getHostName();
		std::string getip_string();
		std::vector<uint8_t> getIPBytes();
		unsigned short getPort();
	private:
		std::string hostname = "";
		std::string ip_string = "";
		unsigned short port = 0;
		std::vector<uint8_t> ip_bytes;
		IPVersion ip_version = IPVersion::UNKNOWN;
	};
}