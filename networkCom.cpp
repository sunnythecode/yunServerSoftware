#include "networkCom.hpp"
int sendString(char *message, struct client *clients)
{
	char* nullPos;
	if(!(nullPos = strchr(message,'\0'))) return FORMATING_ERROR;
	
	while(clients!=NULL)
	{
		int sendRet = send(clients->socket, message, strlen(message),0);
		
		if(sendRet == nullPos - message) printf("Send successful\n");
		else{
			printf("Error :%d ",sendRet);
			if(sendRet == EACCES) 
			{
				printf("Access Denied: Try running as root\n");
				return EACCES;
			}
			else if(sendRet == EAGAIN || sendRet == EWOULDBLOCK)
			{
				printf("Message too long\n");
				return EWOULDBLOCK;
			}
			else if(sendRet == ECONNRESET)
			{
				printf("Connecting reset by peer\n");
				return ECONNRESET;
			}
			
		}
		clients = clients->nextClient;
	}
	return nullPos - message;
}
int recvString(struct client *client)
{
	if(!client->buffFull)
	{
		int recvRet = recv(client->socket, client->buffer, MAX_BUFF, 0);
		if(recvRet == EAGAIN || recvRet == EWOULDBLOCK)
		{
			printf("Message too long\n");
			return EWOULDBLOCK;
		}
		else if(ECONNREFUSED)
		{
			printf("Connection refused\n");
			return ECONNREFUSED;
		}
		client->buffFull = true;
	}
	else return BUFFER_FULL;
}
int getConnectionType(struct client *client)
{
	int connectType;	
	scanf(client->buffer, "%d!",&connectType);
	return connectType;
}
int readyUp(struct client *client)
{
	int numReadyPlayers = 0;
	for(struct client *mover = client; mover->nextClient; mover= mover->nextClient)
	{
		numReadyPlayers +=mover->isReady;
		recvString(client);
		if(client->buffFull)
		{
			if(getConnectionType(client)==READYING)
			{
				client->isReady=true;
				client->buffFull = false;
			}
			else if(getConnectionType(client)==UN_READYING)
			{
				client->isReady=false;
				client->buffFull = false;
			}
		}	
	}
	if(numReadyPlayers == MAX_CLIENTS)
	{
		char message[20];
		float time= (float)clock();
		client->startTime =time+5;
		sprintf(message,"4! %f %f",time,time+5);
		return TIME_SET;
	}
	else
	{
		for(struct client *mover = client; mover->nextClient; mover= mover->nextClient)
		{
			char message[] = "2!";
			sendString(message, mover);
		}
	}

}
void setTime(struct client *client)
{
	char message[50];
	recvString(client);
	int temp;
	char temp2;
	if(getConnectionType(client)==TIME) sscanf(message, "%d%c %f %f",&temp,&temp2,&client->mainTime,&client->startTime);
	client->autoEndTime = client->startTime + AUTO_LEN;
	client->teleEndTime = client->startTime + MATCH_LEN;
}
void 

int main()
{
	return 1;
}
