struct player
{
	//SERVER INFO
	int id;
	int address;
	int playerNum;
	int teamName;
	int socket;
	bool isConnected = false;
	int teamColor;
	//JOYSTICK INFO
	char joyLoc[];
	int joy_fd, *axis = NULL, num_of_axis = 0, num_of_buttons = 0, x;
	char *button = NULL, name_of_joystick[80];
	struct js_event js;
	int varBut;
};

struct client
{
	int id;
	int socket;
	bool isConnected;
	struct *nextClient;
};
