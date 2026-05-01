#pragma once
#define WIN32_LEAN_AND_MEAN
#include <winsock2.h>
#include <iostream>
namespace Pnet {
	class Network {
	public:
		static bool initialyze();
		static void cleanup();
	private:

	};
}