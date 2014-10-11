void sendString(char message[], struct client *clients)
{
	
	while(clients!=NULL)
	{
		send(clients->socket, message, strlen(message),0);
		clients = client->nextClient;
	}
}
