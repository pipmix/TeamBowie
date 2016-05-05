#include "Network.h"

int main(int argc, char **argv){

		int port = 9787;

		char* ser= argv[1];


		USocket Socket;
		string data = "UDP TEST, this is a test";
		char buffer[512];

		Socket.SendTo(ser, port, data.c_str(), data.size());
		//Socket.RecvFrom(buffer, 512);
		//cout << buffer;

		while (1) {
			cin >> data;
			Socket.SendTo(ser, port, data.c_str(), data.size());
			//Socket.RecvFrom(buffer, 512);
		}
	


}