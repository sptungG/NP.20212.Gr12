#include <iostream>
#include <WS2tcpip.h>
#include <string>
#include <sstream>

#pragma comment (lib, "ws2_32.lib")

using namespace std;

int main()
{
	// Initialze winsock
	WSADATA wsData;
	WORD ver = MAKEWORD(2, 2);

	int wsOk = WSAStartup(ver, &wsData);
	if (wsOk != 0)
	{
		cerr << "Can't Initialize winsock! Quitting" << endl;
		return 99;
	}

	// Create a socket
	SOCKET listening = socket(AF_INET, SOCK_STREAM, 0);
	if (listening == INVALID_SOCKET)
	{
		cerr << "Can't create a socket! Quitting" << endl;
		return 99;
	}

	// Bind the ip address and port to a socket
	sockaddr_in hint;
	hint.sin_family = AF_INET;
	hint.sin_port = htons(54000);
	hint.sin_addr.S_un.S_addr = INADDR_ANY; // Could also use inet_pton .... 

	bind(listening, (sockaddr*)&hint, sizeof(hint));

	// Tell Winsock the socket is for listening 
	listen(listening, SOMAXCONN);

	// Create the master file descriptor set and zero it
	fd_set master;
	FD_ZERO(&master);

	// Add our first socket that we're interested in interacting with; the listening socket!
	// It's important that this socket is added for our server or else we won't 'hear' incoming
	// connections 
	FD_SET(listening, &master);

	// this will be changed by the \quit command (see below, bonus not in video!)
	bool running = true;

	int countGroup = 0;
	string groupName[20];
	int countMember[20];
	string memberOfGroup[20][20];
	
	for (size_t i = 0; i < 20; i++)
	{
		countMember[i] = 0;
	}

	while (running)
	{
		// Make a copy of the master file descriptor set, this is SUPER important because
		// the call to select() is _DESTRUCTIVE_. The copy only contains the sockets that
		// are accepting inbound connection requests OR messages. 

		// E.g. You have a server and it's master file descriptor set contains 5 items;
		// the listening socket and four clients. When you pass this set into select(), 
		// only the sockets that are interacting with the server are returned. Let's say
		// only one client is sending a message at that time. The contents of 'copy' will
		// be one socket. You will have LOST all the other sockets.

		// SO MAKE A COPY OF THE MASTER LIST TO PASS INTO select() !!!

		fd_set copy = master;

		// See who's talking to us
		int socketCount = select(0, &copy, nullptr, nullptr, nullptr);

		// Loop through all the current connections / potential connect
		for (int i = 0; i < socketCount; i++)
		{
			// Makes things easy for us doing this assignment
			SOCKET sock = copy.fd_array[i];

			// Is it an inbound communication?
			if (sock == listening)
			{
				// Accept a new connection
				SOCKET client = accept(listening, nullptr, nullptr);

				// Add the new connection to the list of connected clients
				FD_SET(client, &master);

				// Send a welcome message to the connected client
				string welcomeMsg = "SERVER: Welcome User" + to_string(client) + "  to the Chat Server!";
				send(client, welcomeMsg.c_str(), welcomeMsg.size() + 1, 0);
			}
			else // It's an inbound message
			{
				char buf[4096];
				ZeroMemory(buf, 4096);

				// Receive message
				int bytesIn = recv(sock, buf, 4096, 0);
				if (bytesIn <= 0)
				{
					// Drop the client
					closesocket(sock);
					FD_CLR(sock, &master);
				}
				else {
					string str = string(buf);
					string flag = str.substr(0, str.find("|NULL|"));
					string content = str.substr(str.find("|NULL|") + 6);


					if (flag == "CHAT_ALL")
					{
						// Send message to other clients, and definiately NOT the listening socket
						for (u_int j = 0; j < master.fd_count; j++)
						{
							SOCKET outSock = master.fd_array[j];
							if (outSock == listening)
							{
								continue;
							}

							ostringstream ss;

							if (outSock != sock)
							{
								ss << "$[User" << sock << "]: " << content << "\r\n";
							}
							else
							{
								ss << "[You]: " << content << "\r\n";
							}

							string strOut = ss.str();
							send(outSock, strOut.c_str(), strOut.size() + 1, 0);
						
						}
					}
					else if (flag == "PRIVATE_CHAT") {
						string receiver = content.substr(0, content.find("|NULL|"));
						string ct = content.substr(content.find("|NULL|") + 6);

						bool exist = false;
						for (u_int j = 0; j < master.fd_count; j++)
						{
							SOCKET outSock = master.fd_array[j];
							if (receiver == to_string(outSock))
							{
								exist = true;
								break;
							}
						}
						if (!exist)
						{
							string strOut = "C_PC_FAILURE";
							send(sock, strOut.c_str(), strOut.size() + 1, 0);
						}
						else {
							for (u_int j = 0; j < master.fd_count; j++)
							{
								SOCKET outSock = master.fd_array[j];
								if (outSock == sock || receiver == to_string(outSock))
								{
									if (outSock == listening)
									{
										continue;
									}
									ostringstream ss;
									if (receiver == to_string(outSock))
									{
										ss << "Private - $[User" << sock << "]: " << ct << "\r\n";
									}
									if (outSock == sock)
									{
										ss << "Private - [You]: " << ct << "\r\n";
									}
									string strOut = ss.str();
									send(outSock, strOut.c_str(), strOut.size() + 1, 0);
								}
								
							}
						}
					}
					else if (flag == "GROUP_CHAT") {
						string grName = content.substr(0, content.find("|NULL|"));
						string ct = content.substr(content.find("|NULL|") + 6);

						bool checkGroupExist = false;
						int index;
						for (int j = 0; j < countGroup; j++)
						{
							if (groupName[j] == grName)
							{
								checkGroupExist = true;
								index = j;
								break;
							}
						}

						if (!checkGroupExist)
						{
							groupName[countGroup] = grName;
							memberOfGroup[countGroup][countMember[countGroup]] = to_string(sock);
							countMember[countGroup]++;
							countGroup++;

							string strOut = "GC_ADD_USER|User"+ to_string(sock)+" has joined this group chat.";
							send(sock, strOut.c_str(), strOut.size() + 1, 0);

							ostringstream ss;
							ss << "Group - [You]: " << ct << "\r\n";
							
							strOut = ss.str();
							send(sock, strOut.c_str(), strOut.size() + 1, 0);
						}
						else {
							bool joined = false;
							for (int j = 0; j < countMember[index]; j++)
							{
								if (memberOfGroup[index][j] == to_string(sock)) {
									joined = true;
									break;
								}
							}

							if (!joined)
							{
								memberOfGroup[index][countMember[index]] = to_string(sock);
								countMember[index]++;

								for (int j = 0; j < countMember[index]; j++)
								{
									string strOut = "GC_ADD_USER|User" + to_string(sock) + " has joined this group chat.";
									send(stoi(memberOfGroup[index][j]), strOut.c_str(), strOut.size() + 1, 0);
									
										
									ostringstream ss;
									if (memberOfGroup[index][j] != to_string(sock))
									{
										ss << "Group - $[User" << sock << "]: " << ct << "\r\n";
									}else 
									{
										ss << "Group - [You]: " << ct << "\r\n";
									}
									strOut = ss.str();
									send(stoi(memberOfGroup[index][j]), strOut.c_str(), strOut.size() + 1, 0);
									
								}
							}
							else {
								for (int j = 0; j < countMember[index]; j++)
								{
									ostringstream ss;
									if (memberOfGroup[index][j] != to_string(sock))
									{
										ss << "Group - $[User" << sock << "]: " << ct << "\r\n";
									}
									else
									{
										ss << "Group - [You]: " << ct << "\r\n";
									}
									string strOut = ss.str();
									send(stoi(memberOfGroup[index][j]), strOut.c_str(), strOut.size() + 1, 0);

								}
							}
						}
					}
				}
			}
		}
	}

	// Remove the listening socket from the master file descriptor set and close it
	// to prevent anyone else trying to connect.
	FD_CLR(listening, &master);
	closesocket(listening);

	// Message to let users know what's happening.
	string msg = "SERVER:Server is shutting down. Goodbye\r\n";

	while (master.fd_count > 0)
	{
		// Get the socket number
		SOCKET sock = master.fd_array[0];

		// Send the goodbye message
		send(sock, msg.c_str(), msg.size() + 1, 0);

		// Remove it from the master file list and close the socket
		FD_CLR(sock, &master);
		closesocket(sock);
	}

	// Cleanup winsock
	WSACleanup();

	system("pause");
	return 0;
}