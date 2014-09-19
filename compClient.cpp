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

//STATES

#define S_ENTRY 9001
#define S_GAME_CONTROL 9002
#define S_NO_CONNECT 9003
#define S_SCAN 9004
#define S_AUTO 9005
#define S_TELEOP 9006

int state;
String address;
int port;

//PLAYER

struct player{
	//SERVER INFO
	String address;
	int port;
	int playerNum;
	int teamName;
	//JOYSTICK INFO
	String joyLoc;
	int joy_fd, *axis=NULL, num_of_axis=0, num_of_buttons=0, x;
	char *button=NULL, name_of_joystick[80];
	struct js_event js;
	int varBut;
};

//FUNCTION DECLARATIONS

int initiliaze();
int connectToServer(String address, int port)

int main()
{	
	clock_t timer = clock();
	while(1)
	{
		if(state==S_ENTRY)
		{

		}
		if(state==S_GAME_CONTROL)
		{

		}
		if(state==S_NO_CONNECT)
		{
			if(connectToServer(player.address,player.port))initialize();
			else state=S_ENTRY;
		}
		if(state==S_SCAN)
		{
			
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
int connectToServer(String address, int port)
{
	int sock;
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

	play.axis = (int *) calloc( num_of_axis, sizeof( int ) );
	play.button = (char *) calloc( num_of_buttons, sizeof( char ) );

	printf("Joystick detected: %s\n\t%d axis\n\t%d buttons\n\n"
		, play.name_of_joystick
		, play.num_of_axis
		, play.num_of_buttons );

	fcntl( play.joy_fd, F_SETFL, O_NONBLOCK );	/* use non-blocking mode */
	return 1;
}
int getJoyValues(struct player play)
	{
		read(joy_fd, &js, sizeof(struct js_event));
		
		/* see what to do with the event */
		switch (js.type & ~JS_EVENT_INIT)
		{
		case JS_EVENT_AXIS:
			play.axis   [ js.number ] = js.value;
			break;
		case JS_EVENT_BUTTON:
			play.button [ js.number ] = js.value;
			break;
		}
				char varBut = 0;
		for(int x=0; x<6; x++)
		{
			if(button[x])play.varBut=play.varBut|(1<<x);
		}
		if(button[9])play.varBut=play.varBut|(1<<9);
		if(button[10])play.varBut=play.varBut|(1<<10);
	}
