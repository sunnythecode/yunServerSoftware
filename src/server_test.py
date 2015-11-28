import socket
import select
import sys
import time
from Queue import Queue
from threading import Thread
 
PORT = 2380 # Game host port
BROADCAST_PORT = 472 # Broadcast port
BROADCAST_IP = '' # Symbolic name, meaning all available interfaces

FLAG_ARDUINO_CONNECT = True
KEEP_ALIVE_TIMEOUT = 0.5
LOST_BROADCAST_CONNECTION = '127.0.0.1'
def check4keepAlive(dgram):
	a = dgram.split('.')
	if len(a) != 4:          #check that the dgram is not too small
		return False
	for x in a:              #check that each member is a number less than 255
		if not x.isdigit():
			return False
		i = int(x)
		if i< -1 or i > 255:
			return False
	if a[0] != 192:
		return False
	return True

def broadcastListener():
    lastKeepAlive = time.time()

    bCastSock =socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    bCastSock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    bCastSock.setsockopt(socket.SOL_SOCKET, socket.SO_BROADCAST, 1)
    try:
        bCastSock.bind((BROADCAST_IP, BROADCAST_PORT))
    except socket.error as msg:
        bCastSock.close()
        print 'Broadcast bind failed. Error Code : ' + str(msg[0]) + ' Message ' + msg[1]  
        sys.exit()
     
    while True:    
        data =  bCastSock.recv(1500) # buffer size is 1500 bytes
        if check4keepAlive(data) == True:
            lastKeepAlive = time.time()
            broadcastQueue.put(data)
        elif time.time() - lastKeepAlive > KEEP_ALIVE_TIMEOUT:
            #broadcastQueue.put(LOST_BROADCAST_CONNECTION)
	    print 'wow'
        time.sleep(.1)

def arduinoCommRead():
    return "data" #add serial code later
def arduinoCommWrite(data):
    pass #add serial code later

#start program
mainQueue = Queue()
broadcastQueue = Queue()

t1 = Thread(target=broadcastListener, args=())
t1.start()

#set up socket for connection to host

while  True:
    print 'waiting for host broadcast.'
    host = broadcastQueue.get(True) #block until there is data from the broadcast thread
    validIp = True
    print 'got data for host: ' + host

    try:
        socket.inet_aton(host)
    except socket.error:
        validIp = False
        
    if validIp:
	
	sock = socket.socket(socket.AF_INET,socket.SOCK_DGRAM)
	try:
		sock.bind(('127.0.0.1', PORT))
        except socket.error as msg:
		print 'Bind failed. Error Code : ' + str(msg[0]) + ' Message ' + msg[1]
		print 'tried to connect to:' + host
        else:
		try:
			sock.sendto("ROB:TEST_ROBOT",('192.168.1.9', PORT))
		except socket.error as msg:
			print 'could not send to ' + host + 'error code: ' + str(msg[0])
		fKeepAlive = True
		keepAliveHolder = time.time()
		while fKeepAlive:
			print "alive"
			if not broadcastQueue.empty():
				qPop = broadcastQueue.get()
				keepAliveHolder = time.time()

			if time.time() - keepAliveHolder > KEEP_ALIVE_TIMEOUT:
				fKeepAlive = False
				print "connection died"
				break

			ardData = arduinoCommRead()
			print host
			MESSAGE = "gotta go fast"
			try:
				sock.sendto(MESSAGE,(host,PORT))
			except socket.error as msg:
				print ' could not send message 1 to ' + host + ' error code: ' + msg[1]

			senderAddr =''
			ready = select.select([sock], [], [], .02)
			if ready[0]:
				bridgeData, senderAddr = sock.recv(1024)
			if(senderAddr == host):
				arduinoCommWrite(bridgeData)
			else:
				print senderAddr + ' - did not match - ' + host
	        
	        
	        
                
            
    
        
    
