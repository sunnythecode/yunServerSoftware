#include "networkCom.hpp"

int sendString(char message[], struct client *clients)
{
	char* nullPos;
	if(!(nullPos = strchr(message,'\0'))) return FORMATING_ERROR;
	
	while(clients!=NULL)
	{
		int sendRet = send(clients->socket, message, strlen(message),0);
		clients = client->nextClient;
		if(sendRet == nullPos - message) printf("Send successful\n");
		if(sendRet == EACCESS) printf("Access Denied\n");
	}
	return nullPos - message;
}
void recvString(struct client *client)
{
	recv(client->socket, client->buffer, MAX_BUFFER, 0);
}

