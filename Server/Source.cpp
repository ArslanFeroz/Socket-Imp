
#include <Pnet/IncludeMe.h>
#include <string>
using namespace Pnet;
using namespace std;
int main() {
	if (Network::initialyze()) {
		cout << "Winsock Activated Successfully" << endl;
		// creating and IpEndpoint
		IPEndPoint test("www.youtube.com", 4040);
		if (test.getIpversion() == IPVersion::IPv4) {
			cout << "Valid IP" << endl;
			cout << "Host : " << test.getHostName() << endl;
			cout << "IP : " << test.getip_string() << endl;
			cout << "Port : " << test.getPort() << endl;
			cout << "IP Bytes : " <<endl;
			for (auto& dig : test.getIPBytes()) {
				cout << (int)dig << endl;
			}

		}
		else {
			cout << "Invalid IP" << endl;
		}
		// creating a socket
		Socket socket;
		if (socket.create() == PResult::P_Success) {
			cout << "Socket Created Successfully" << endl;

			// Binding the socket
			/*if (socket.bindSocket(test) == PResult::P_Success) {
				cout << "Socket Binded successfully" << endl;
			}
			else {
				cout << "Failed to Bind to socket" << endl;
			}*/


			
			if (socket.Listen(IPEndPoint("127.0.0.1", 4790), SOMAXCONN) == PResult::P_Success) {
				cout << "Socket Successfully Listening" << endl;
				Socket out;
				if (socket.Accept(out) == PResult::P_Success) {
					cout << "Connected Successfully" << endl;


					

					while (true) {
						// 1?? Receive from client
						char recvBuff[256] = {};
						int bytesReceived = out.recieveData(recvBuff, sizeof(recvBuff));

						if (bytesReceived != PResult::P_Success) {
							cout << "Client disconnected" << endl;
							break;
						}

						cout << "Client: " << recvBuff << endl;

						// 2?? Take server input
						char sendBuff[256] = {};
						cout << "Server msg (type exit to quit): ";
						//cin.ignore(numeric_limits<streamsize>::max(), '\n');
						cin.ignore();
						cin.getline(sendBuff, 256);

						if (strcmp(sendBuff, "exit") == 0)
							break;

						// 3?? Send to client
						out.sendData(sendBuff, (int)strlen(sendBuff));
					}

					
				}

			}
			else {
				cout << "Failed to Listen" << endl;
			}

			socket.stop();

		}
		else {
			cout << "Failed to Create the socket" << endl;
		}
		Network::cleanup();
		system("pause");
	}
	else {
		cout << "Failed to Activate Winsock" << endl;
	}
}