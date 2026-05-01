#include "Network.h"

namespace Pnet {
	bool Network::initialyze()
	{
		WSADATA wsadata;
		int res = WSAStartup(MAKEWORD(2, 2), &wsadata);
		if (res != 0) {
			std::cout << "Failed to Start Winsock" << std::endl;
			return false;
		}

		if (LOBYTE(wsadata.wVersion) != 2 || HIBYTE(wsadata.wVersion) != 2) {
			std::cout << "Could Not find the specified version" << std::endl;
			return false;
		}
		return true;;
	}
	void Network::cleanup()
	{
		WSACleanup();
	}
}
