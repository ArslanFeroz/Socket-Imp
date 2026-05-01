
#include <Pnet/IncludeMe.h>
using namespace Pnet;
using namespace std;
int main() {
	if (Network::initialyze()) {
		cout << "Winsock Activated Successfully" << endl;
		

		Socket socket;
		if (socket.create() == PResult::P_Success) {
			cout << "Socket created successfully" << endl;
			if (socket.Connect(IPEndPoint("127.0.0.1", 4790)) == PResult::P_Success) {
				cout << "Connected to Server" << endl;


				while (true) {
					// 1?? Client sends first
					char sendBuff[256] = {};
					cout << "Client msg (type exit to quit): ";
					cin.getline(sendBuff, 256);

					if (strcmp(sendBuff, "exit") == 0)
						break;

					socket.sendData(sendBuff, (int)strlen(sendBuff));

					// 2?? Receive from server
					char recvBuff[256] = {};
					int bytesReceived = socket.recieveData(recvBuff, sizeof(recvBuff));

					if (bytesReceived != PResult::P_Success) {
						cout << "Server disconnected" << endl;
						break;
					}

					cout << "Server: " << recvBuff << endl;
				}

				
				/*const char* msg = "Hello world server";
				int len = (int)strlen(msg);

				if (socket.sendData(msg, len) == PResult::P_Success) {
					cout << "Data Sent Successfully" << endl;
				}*/

			}
			else {
				cout << "Failed to connect to server" << endl;
			}
			socket.stop();
		}


		Network::cleanup();
		system("pause");
	}
	else {
		cout << "Failed to Activate Winsock" << endl;
	}
}