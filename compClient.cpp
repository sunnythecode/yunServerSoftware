#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/joystick.h>
#include <time.h>
#include <sys/socket.h>
#include <arpa/inet.h> //inet_addr
#include <string.h>
#include <sys/types.h>
#include <ifaddrs.h>
#include <netinet/in.h> 
//STATES

#define S_ENTRY 9001
#define S_GAME_CONTROL 9002
#define S_NO_CONNECT 9003
#define S_SCAN 9004
#define S_AUTO 9005
#define S_TELEOP 9006

using namespace std;

int state;
char address[12];
int port;

//PLAYER


struct player{
	//SERVER INFO
	int id;
	char address[];
	int port;
	int playerNum;
	int teamName;
	int socket;
	//JOYSTICK INFO
	char joyLoc[];
	int joy_fd, *axis=NULL, num_of_axis=0, num_of_buttons=0, x;
	char *button=NULL, name_of_joystick[80];
	struct js_event js;
	int varBut;
};

struct client{
	int id;
	int socket;
};

//FUNCTION DECLARATIONS

int initiliaze();
int connectToServer(char address[50], int port);

int main()
{	
	clock_t timer = clock();
	while(1)
	{
		if(state==S_ENTRY)
		{
			//initialize all players
			struct player player1;
			struct player player2;
			struct player player3;
			struct player player4;
			struct player player5;
			struct player player6;
			struct client client1
			struct client client2;
			struct client client3;
			struct client client4;
			struct client client5;
			
			//create all sockets
			createSocket(player1);
			createSocket(player2);
			createSocket(player3);
			createSocket(player4);
			createSocket(player5);
			createSocket(player6);
			createSocket(client1);
			createSocket(client2);
			createSocket(client3);
			createSocket(client4);
			createSocket(client5);
			
			
		}
		if(state==S_GAME_CONTROL)
		{

		}
		if(state==S_NO_CONNECT)
		{
			//if(connectToServer(player.address[],player.port))initialize();
			//else state=S_ENTRY;
			sock = socket(AF_INET , SOCK_STREAM , 0);
			if (sock == -1)
			{
				printf("Could not create socket");
			}
		}
		if(state==S_SCAN)
		{
			//GET LOCAL IP
			int fd;
			struct ifreq ifr;
			fd = socket(AF_INET, SOCK_DGRAM, 0);
			/* I want to get an IPv4 IP address */
			ifr.ifr_addr.sa_family = AF_INET;

			/* I want IP address attached to "wlan0" */
			strncpy(ifr.ifr_name, "wlan0", IFNAMSIZ-1);

			ioctl(fd, SIOCGIFADDR, &ifr);

			close(fd);

			/* display result */
			char currAddress[] = inet_ntoa(((struct sockaddr_in *)&ifr.ifr_addr)->sin_addr);
			int ip1,ip2,ip3,ip4;
			sscanf(currAddress,"%d.%d.%d.%d",ip1,ip2,ip3,ip4);
			struct sockaddr_in scanServer;
			//Create socket
			bool connectAddresses[256];
			char scanServerAddress[];
			for(char i=0,i<256,i++)
			{
				sprintf(scanServerAddress,"%d.%d.%d.%d",ip1.ip2.ip3.i);
				scanServer.sin_addr.s_addr = inet_addr(scanServerAddress);
				scanServer.sin_family = AF_INET;
				scanServer.sin_port = htons( 8888 );
				
				if (connect(sock , (struct sockaddr *)&scanServer , sizeof(scanServer)) < 0)
				{
					connectAddresses[i] = true;
				}
				else connectAddresses[i] = false;
			}
		}
		if(state==S_AUTO)
		{

		}
		if(state==S_TELEOP)
		{
		
		}

	}
}

int initialize()
{
	return 1;
}
int connectToServer(char address[], int port)
{
	struct sockaddr_in server;
	char message[1000] , server_reply[2000];
     	//Create socket
	sock = socket(AF_INET , SOCK_STREAM , 0);
	if (sock == -1)
	{
		printf("Could not create socket");
	}
	puts("Socket created");
     
	server.sin_addr.s_addr = inet_addr(address);
	server.sin_family = AF_INET;
	server.sin_port = htons( port );
 
	//Connect to remote server
	if (connect(sock , (struct sockaddr *)&server , sizeof(server)) < 0)
	{
		perror("connect failed. Error");
 		return 0;
	}	
	puts("Connected\n");
	return 1;
}
int initializeJoystick(struct player play)
{
	if( ( play.joy_fd = open( play.joyLoc , O_RDONLY)) == -1 )
	{
		printf( "Couldn't open joystick\n" );
		return -1;
	}
	ioctl( play.joy_fd, JSIOCGAXES, &play.num_of_axis );
	ioctl( play.joy_fd, JSIOCGBUTTONS, &play.num_of_buttons );
	ioctl( play.joy_fd, JSIOCGNAME(80), &play.name_of_joystick );

	play.axis = (int *) calloc( play.num_of_axis, sizeof( int ) );
	play.button = (char *) calloc( play.num_of_buttons, sizeof( char ) );

	printf("Joystick detected: %s\n\t%d axis\n\t%d buttons\n\n"
		, play.name_of_joystick
		, play.num_of_axis
		, play.num_of_buttons );

	fcntl( play.joy_fd, F_SETFL, O_NONBLOCK );	/* use non-blocking mode */
	return 1;
}
int getJoyValues(struct player play)
{
	read(play.joy_fd, &play.js, sizeof(struct js_event));

	/* see what to do with the event */
	switch (play.js.type & ~JS_EVENT_INIT)
	{
	case JS_EVENT_AXIS:
		play.axis   [ play.js.number ] = play.js.value;
		break;
	case JS_EVENT_BUTTON:
		play.button [ play.js.number ] = play.js.value;
		break;
	}
	for(int x=0; x<6; x++)
	{
		if(play.button[x])play.varBut=play.varBut|(1<<x);
	}
	if(play.button[9])play.varBut=play.varBut|(1<<9);
	if(play.button[10])play.varBut=play.varBut|(1<<10);
	return 1;
}
int sendJoyValues(struct player play)
{
	char message[1000];
	sprintf(message, "%d,%d,%d,%d,%d,%d,%d,%d,%c",play.axis[0],play.axis[1],play.axis[2],play.axis[3],play.axis[4],play.axis[5],play.axis[6],play.axis[7],play.varBut);
	if( send(play.socket , message , strlen(message) , 0) < 0)
      	{
		puts("Send failed");
		return 0;
	}
	return 1;
}
int createSocket(struct player play)
{
	play.socket = socket(AF_INET , SOCK_STREAM , 0);
	if(play.socket == -1)
	{
		printf("Player%d Socket creation failed",play.id);
		return 0;
	}
	return 1;
}
int createSocket(struct client cli)
{
	cli.socket = socket(AF_INET , SOCK_STREAM , 0);
	if(cli.socket == -1)
	{
		printf("Client%d Socket creation failed",cli.id);
		return 0;
	}
	return 1;
}
int handshake(struct player play)
{	
	if(send(play.socket, "1",strlen("1"),0))<0) return 0;
	char returnMessage[20];
	recv(play.socket, returnMessage, 20, 0);
	if(returnMessage == "lancer") return 1;
	return 0;
}