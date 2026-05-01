#include "Socket.h"
#include <assert.h>


namespace Pnet {
	Socket::Socket(IPVersion version, SocketHandle handle)
	{
		this->ipversion = version;
		this->handle = handle;
		assert(ipversion == IPVersion::IPv4);
	}

	PResult Pnet::Socket::create()
	{
		assert(ipversion == IPVersion::IPv4);
		if (handle != INVALID_SOCKET) {
			return PResult::P_NotYetImplemented;
		}

		// creating a socket
		// for Ipv4 AF_INET, and IPv6 AF_INET6
		handle = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

		if (handle == INVALID_SOCKET) {
			int error = WSAGetLastError();
			return PResult::P_NotYetImplemented;
		}

		// creating options
		if (setSocketOption(TCP_NoDelay, TRUE) != PResult::P_Success) {
			return PResult::P_NotYetImplemented;
		}

		return PResult::P_Success;
	}

	PResult Pnet::Socket::stop()
	{
		if (handle == INVALID_SOCKET)
			return PResult::P_NotYetImplemented;

		int res = closesocket(handle);
		if (res != 0) {
			int error = WSAGetLastError();
			return PResult::P_NotYetImplemented;
		}

		handle = INVALID_SOCKET;
		return PResult::P_Success;
	}

	PResult Socket::bindSocket(IPEndPoint ip)
	{
		sockaddr_in addr = ip.getAddr();
		int result = bind(handle, (sockaddr*)&addr, sizeof(sockaddr_in));
		if (result != 0) {
			int error = GetLastError();
			return PResult::P_NotYetImplemented;
		}
		return PResult::P_Success;
	}


	PResult Socket::Listen(IPEndPoint ip, int backlog)
	{
		// Binding then listening
		if (bindSocket(ip) != PResult::P_Success)
			return PResult::P_NotYetImplemented;

		int result = listen(handle, backlog);
		if (result != 0) {
			int error = WSAGetLastError();
			return PResult::P_NotYetImplemented;
		}
		return PResult::P_Success;
	}

	PResult Socket::Accept(Socket& s)
	{
		sockaddr_in client = {};
		int len = sizeof(client);
		SocketHandle s_ = accept(handle,(sockaddr*)&client, &len);
		if (s_ == INVALID_SOCKET)
			return PResult::P_NotYetImplemented;

		s = Socket(IPVersion::IPv4, s_);
		std::cout << "--- Data Regarding Client ---" << std::endl;

		// extracting the client IP
		char buff[256];
		inet_ntop(AF_INET, &client.sin_addr, buff, 256);
		unsigned short port_ = ntohs(client.sin_port);
		std::cout << "IP : " << buff << std::endl;
		std::cout << "Port : " << port_ << std::endl;
		return PResult::P_Success;
	}

	PResult Socket::Connect(IPEndPoint ip)
	{
		sockaddr_in addr = ip.getAddr();
		int res = connect(handle, (sockaddr*)&addr, sizeof(addr));
		if (res != 0) {
			int error = WSAGetLastError();
			return PResult::P_NotYetImplemented;
		}
		return PResult::P_Success;
	}

	PResult Pnet::Socket::sendData(const char* buff, int len)
	{
		int byteSent = 0;
		byteSent = send(handle, buff, len, 0);
		if (byteSent > 0) {
			//std::cout << "Data Transmitted Successfully" << std::endl;
			return PResult::P_Success;
		}

		int error = WSAGetLastError();
		return PResult::P_NotYetImplemented;
	}

	PResult Pnet::Socket::recieveData(char* buff, int len)
	{
		int byterecieved = 0;
		byterecieved = recv(handle, buff, len, 0);
		if (byterecieved > 0)
			return PResult::P_Success;
		int error = WSAGetLastError();
		return PResult::P_NotYetImplemented;
	}


	IPVersion Pnet::Socket::getIPversion()
	{
		return ipversion;
	}
	SocketHandle Socket::getHandle()
	{
		return handle;
	}
	PResult Socket::setSocketOption(SocketOption option, BOOL value)
	{
		int result = 0;
		switch (option)
		{
		case SocketOption::TCP_NoDelay: 
			{
				result = setsockopt(handle, IPPROTO_TCP, TCP_NODELAY, (const char*)&value, sizeof(value));
				break;
			}
		default:
			return PResult::P_NotYetImplemented;
		}

		if (result != 0) {
			int error = WSAGetLastError();
			return PResult::P_NotYetImplemented;
		}
		return PResult::P_Success;
	}
}

