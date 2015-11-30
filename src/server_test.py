import socket
import select
import serial
import sys
import time
from Queue import Queue
from threading import Thread
 
PORT = 2380 # Game host port
BROADCAST_PORT = 472 # Broadcast port
BROADCAST_IP = '' # Symbolic name, meaning all available interfaces
LOCAL_IP = ''

FLAG_ARDUINO_CONNECT = True
KEEP_ALIVE_TIMEOUT = 2

def check4keepAlive(dgram, source):
	if dgram == source[0]:	
		return True
	else:
		return False	

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

	while True:   
		readReady = select.select([bCastSock], [], [], .07)
		if readReady[0]: 
			data, sender =  bCastSock.recvfrom(1500) # buffer size is 1500 bytes
			if check4keepAlive(data, sender):
				lastKeepAlive = time.time()
				broadcastQueue.put(sender)

def arduinoCommRead():
    return ser.readLine()
def arduinoCommWrite(data):
    ser.write(data)

#start program
mainQueue = Queue()
broadcastQueue = Queue()

t1 = Thread(target=broadcastListener, args=())
t1.start()

#set up socket for connection to host

while  True:
	print 'waiting for host broadcast.'
	host = broadcastQueue.get(True) #block until there is data from the broadcast thread

	#setup arduino serial comm
	ser = serial.Serial('/dev/ttyATH0', 115200) # open serial port
	print ser.portstr
	ser.open()
	ser.flushInput()
	
	#send robot name to server
	fKeepAlive = True
	sock = socket.socket(socket.AF_INET,socket.SOCK_DGRAM)
	try:
		sock.bind((LOCAL_IP, PORT))
	except socket.error as msg:
		print 'Broadcast bind failed. Error Code : ' + str(msg[0]) + ' Message ' + msg[1]  
		sys.exit()
	try:
		sock.sendto("ROB:Laptop1",(host[0], PORT))
	except socket.error as msg:
		print ' Could not send robot name to ' + host[0] + ' error code: ' + msg[1]
		fKeepAlive = False
	keepAliveHolder = time.time()

	print "Alive"
	
	while fKeepAlive:
		if not broadcastQueue.empty():
			while not broadcastQueue.empty() :
				qPop = broadcastQueue.get()
				keepAliveHolder = time.time()

		if time.time() - keepAliveHolder > KEEP_ALIVE_TIMEOUT:
			fKeepAlive = False
			print "Connection Died"
			break

		#ardData = arduinoCommRead()
		ready = select.select([sock], [], [], .001)
		if ready[0]:
			bridgeData, senderAddr = sock.recvfrom(1024)
			if not bridgeData:
				continue
			else:
				if senderAddr[0] == host[0]:
					arduinoCommWrite(bridgeData)    
        
        
        
    


    
