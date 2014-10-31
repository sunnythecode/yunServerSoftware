#ifndef STRUCT_SERV_CLIENT_H
#define STRUCT_SERV_CLIENT_H

#include <xinput.h>
#include <winsock2.h>
#include <ws2tcpip.h>

struct player
{
	//SERVER INFO
	int id;
	char address[128];
	int port;
	int playerNum;
	int teamName;
	int socket;
	bool isConnected;
	int teamColor;

	//JOYSTICK INFO
	char joyLoc[15];
	int joy_fd, *axis, num_of_axis, num_of_buttons, x;
    char *button, name_of_joystick[80];
	int varBut;
	struct player *nextPlayer;
	bool isReady;
	char buffer[512];
	bool buffFull;
	struct sockaddr_in server;
    XINPUT_STATE controller;
    SOCKET comLine;
};

struct client
{
	float mainTime, startTime, autoEndTime, teleEndTime;
	int id;
	int socket;
	bool isConnected;
	char buffer[512];
	bool buffFull;
	bool isReady;
	struct client *nextClient;
	struct player player;

};

#endif
