import socket
import sys
 
HOST = ''   # Symbolic name, meaning all available interfaces
PORT = 8888 # Arbitrary non-privileged port
 
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
print 'Socket created'
 
#Bind socket to local host and port
try:
    s.bind((HOST, PORT))
except socket.error as msg:
    print 'Bind failed. Error Code : ' + str(msg[0]) + ' Message ' + msg[1]
    sys.exit()
     
print 'Socket bind complete'

#Start listening on socket
s.listen(10)
print 'Socket now listening'

#wait to accept a connection - this call is blocking
conn, addr= s.accept()                      
print 'Connected with ' + addr[0] + ':' + str(addr[1])
#now keep talking with the client
while 1:


	#loop back message from client	
        data = conn.recv(1024)

        conn.send(data)                               
s.close()
	
