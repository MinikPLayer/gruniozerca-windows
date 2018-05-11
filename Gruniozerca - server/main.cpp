#include <iostream>
#include <fstream>
#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <vector>
#include <algorithm>
#include <ctime>
#include <list>

using namespace sf;
using namespace std;

int main()
{
	Clock zegar;
	Time czas;
	int grX[2];
	std::cout << "Uruchomiono" << endl;
	srand(time(NULL));
	sf::UdpSocket socket[2];
	unsigned short porttcp = 12345;
	unsigned short portudpupload[2] = { 12348, 12348 + 1 };
	unsigned short portudpdownload[2] = { 12346, 12346 + 1 };
	TcpListener listener;
	listener.listen(porttcp);
	// Create a list to store the future clients
	IpAddress IPKlientow[2];
	short iloscklientow = 0;
	// Create a selector
	sf::SocketSelector selector;
	// Add the listener to the selector
	selector.add(listener);
	// Endless loop that waits for new connections
	short timeoutklientow[2] = { 0, 0 };
	short poilutimeoutachwywala = 25;		// Po jakim czasie wyrzuci nie odpowiadaj¹cego u¿ytkownika w sekundach
	// Co jaki czas wysy³aæ pakiety
	short tickratetime = 15;
	poilutimeoutachwywala = poilutimeoutachwywala * (1000.f / tickratetime);
	socket[0].bind(portudpdownload[0]);
	socket[1].bind(portudpdownload[1]);
	socket[0].setBlocking(false);
	socket[1].setBlocking(false);

	int ktorysierozlaczyl = 0;
	while (true)
	{
		if (iloscklientow < 2)
		{
			// Make the selector wait for data on any socket
			if (selector.wait(sf::milliseconds(50)))
			{
				// Test the listener
				if (selector.isReady(listener))
				{
					// The listener is ready: there is a pending connection
					sf::TcpSocket* client = new sf::TcpSocket;
					if (listener.accept(*client) == sf::Socket::Done)
					{
						if (ktorysierozlaczyl == 0)
						{
							IPKlientow[iloscklientow] = client->getRemoteAddress();
							Packet packet;
							unsigned short porttupl = portudpdownload[iloscklientow];// Port na który klient ma wysy³aæ dane
							unsigned short porttdwn = portudpupload[iloscklientow];	// Port na który klient ma wysy³aæ dane
							std::cout << "UserID: " << iloscklientow << endl;
							packet << porttupl << porttdwn << iloscklientow;
							client->send(packet);
							iloscklientow++;
							delete client;
						}
						else
						{
							IPKlientow[ktorysierozlaczyl] = client->getRemoteAddress();
							Packet packet;
							unsigned short porttupl = portudpdownload[ktorysierozlaczyl];// Port na który klient ma wysy³aæ dane
							unsigned short porttdwn = portudpupload[ktorysierozlaczyl];	// Port na który klient ma wysy³aæ dane
							std::cout << "UserID: " << ktorysierozlaczyl << endl;
							packet << porttupl << porttdwn << ktorysierozlaczyl;
							client->send(packet);
							iloscklientow++;
							delete client;
						}
						
					}
					else
					{
						// Error, we won't get a new connection, delete the socket
						delete client;
					}
				}
			}
		}
		else
		{
			timeoutklientow[0] = 0;
			timeoutklientow[1] = 0;
			// The listener socket is not ready, test all other sockets (the clients)
			czas = zegar.getElapsedTime();
			if (czas.asMilliseconds() >= tickratetime)
			{
				for (int i = 0; i < iloscklientow; ++i)
				{
					Packet packet;
					unsigned short portudpdownloadi = portudpdownload[i];
					if (socket[i].receive(packet, IPKlientow[i], portudpdownloadi) == Socket::Disconnected || !Socket::Done)
					{
						timeoutklientow[i]++;
					}
					else
						timeoutklientow[i] = 0;
					packet >> grX[i];
					//std::cout << "GrX [" << i << "]: " << grX[i] << endl;
				}
				for (int i = 0; i < iloscklientow; ++i)
				{
					Packet packet;
					bool czyjestwgrze = 1;
					bool przeciwnikjestwgrze = 1;
					packet << przeciwnikjestwgrze << czyjestwgrze << grX[0] << grX[1];
					unsigned short portudpuploadi = portudpupload[i];
					if(socket[i].send(packet, IPKlientow[i], portudpuploadi) == Socket::Disconnected || !Socket::Done)
					{
						timeoutklientow[i]++;
					}
					else
						timeoutklientow[i] = 0;
					//std::cout << "Wyslano na " << IPKlientow[i] << " na porcie: " << portudpuploadi << endl;
					if (timeoutklientow[i] >= poilutimeoutachwywala)
					{
						IPKlientow[i] = "0.0.0.0";
						iloscklientow--;
						ktorysierozlaczyl = i+1;
						cout << "Rozlaczono" << endl;
						timeoutklientow[i] = 0;
					}
					cout << "Timeout: " << timeoutklientow[i] << endl;
				}
				cout << endl;
				zegar.restart();
			}
		}
		if (iloscklientow == 1)
		{
			czas = zegar.getElapsedTime();
			if (czas.asMilliseconds() >= tickratetime)
			{
				Packet packet;
				if (ktorysierozlaczyl == 1)
				{
					socket[1].receive(packet, IPKlientow[1], portudpdownload[1]);
				}
				else
				{
					socket[0].receive(packet, IPKlientow[0], portudpdownload[0]);
				}
				packet.clear();
				bool zero = 0;
				int int_zero = 0;
				packet << zero << zero << int_zero << int_zero;
				if (ktorysierozlaczyl == 1)
				{
					if (socket[1].send(packet, IPKlientow[1], portudpdownload[1]) != Socket::Done)
					{
						timeoutklientow[1]++;
					}
					else
						timeoutklientow[1] = 0;
				}
				else
				{
					if (socket[0].send(packet, IPKlientow[0], portudpdownload[0]))
					{
						timeoutklientow[0]++;
					}
					else
						timeoutklientow[0] = 0;
				}
				zegar.restart();
				cout << "Timeoutklientow: " << timeoutklientow[ktorysierozlaczyl] << endl;

				if (timeoutklientow[0] >= poilutimeoutachwywala || timeoutklientow[1] >= poilutimeoutachwywala)
				{
					iloscklientow--;
				}
			}
		}
	}
}