#include <linux/joystick.h>
struct player
{
	//SERVER INFO
	int id;
	int address;
	int playerNum;
	int teamName;
	int socket;
	bool isConnected;
	int teamColor;
	//JOYSTICK INFO
	char joyLoc[];
	int joy_fd, *axis, num_of_axis, num_of_buttons, x;
	char *button, name_of_joystick[80];
	struct js_event js;
	int varBut;
	struct player *nextPlayer;
	bool isReady;
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
