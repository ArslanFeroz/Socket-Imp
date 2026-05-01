#pragma once
#include "IpVersion.h"
#include "PResult.h"
#include "SocketHandle.h"
#include "SocketOption.h"
#include "IPEndPoint.h"

namespace Pnet {
	class Socket {
	public:

		// constructor
		Socket(IPVersion version = IPVersion::IPv4, SocketHandle handle = INVALID_SOCKET);
		PResult create();
		PResult stop();
		PResult bindSocket(IPEndPoint ip);
		PResult Listen(IPEndPoint ip, int backlog);
		PResult Accept(Socket& s);
		PResult Connect(IPEndPoint ip);
		PResult sendData(const char* buff, int len);
		PResult recieveData(char * buff, int len);
		// Getting
		IPVersion getIPversion();
		SocketHandle getHandle();
	private:
		PResult setSocketOption(SocketOption option, BOOL value);
		IPVersion ipversion = IPVersion::IPv4;
		SocketHandle handle = INVALID_SOCKET;
	};
}