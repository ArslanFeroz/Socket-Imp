#include "IPEndPoint.h"
#include <assert.h>

namespace Pnet {
	IPEndPoint::IPEndPoint(const char* ip_String, unsigned short port)
	{
		this->port = port;
		
		// The IP, given to us is in Presentation form, we need to convert it to a form which can be used by the kernel
		// the in_addr struct stores the IP in this form, we just need to convert it using a function and store it in the struct

		in_addr addr;
		int result = inet_pton(AF_INET, ip_String, &addr);

		if (result == 1) {
			this->ip_string = ip_String;
			this->hostname = ip_String;
			ip_version = IPVersion::IPv4;

			// getting the ip bytes
			ip_bytes.resize(sizeof(ULONG));
			memcpy(&ip_bytes[0], &addr.S_un.S_addr, sizeof(ULONG));
		}
		else {
			// resolving the IP
			addrinfo info = {};
			info.ai_family = AF_INET;

			addrinfo* result = nullptr;
			int res = getaddrinfo(ip_String, NULL, &info, &result);

			if (res == 0) {
				sockaddr_in* sockaddr = (sockaddr_in*)result->ai_addr;
				ip_string.resize(16);
				// converting from network form to presentation form
				inet_ntop(AF_INET, &sockaddr->sin_addr, &ip_string[0], 16);


				ip_bytes.resize(sizeof(ULONG));
				memcpy(&ip_bytes[0], &sockaddr->sin_addr.S_un.S_addr, sizeof(ULONG));

				this->hostname = ip_String;
				ip_version = IPVersion::IPv4;

				freeaddrinfo(result);
			}

		}
	}
	sockaddr_in IPEndPoint::getAddr()
	{
		assert(ip_version == IPVersion::IPv4);

		sockaddr_in addr = {};
		addr.sin_family = AF_INET;
		memcpy(&addr.sin_addr, &ip_bytes[0], sizeof(ULONG));
		addr.sin_port = htons(port);
		return addr;
	}
	IPVersion Pnet::IPEndPoint::getIpversion()
	{
		return ip_version;
	}

	std::string Pnet::IPEndPoint::getHostName()
	{
		return hostname;
	}

	std::string Pnet::IPEndPoint::getip_string()
	{
		return ip_string;
	}

	std::vector<uint8_t> IPEndPoint::getIPBytes()
	{
		return ip_bytes;
	}

	unsigned short Pnet::IPEndPoint::getPort()
	{
		return port;
	}

}
