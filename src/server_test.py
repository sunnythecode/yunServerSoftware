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

FLAG_ARDUINO_CONNECT = True
KEEP_ALIVE_TIMEOUT = 3
LOST_BROADCAST_CONNECTION = '127.0.0.1'
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
        sys.exit()
     
    while True:    
        data, sender =  bCastSock.recvfrom(1500) # buffer size is 1500 bytes
        if check4keepAlive(data, sender):
		lastKeepAlive = time.time()
		broadcastQueue.put(sender)
        elif time.time() - lastKeepAlive > KEEP_ALIVE_TIMEOUT:
		#broadcastQueue.put(LOST_BROADCAST_CONNECTION)
		print 'Lost Bcast'
	time.sleep(.1)

def arduinoCommRead():
    return ser.readLine()
def arduinoCommWrite(data):
    ser.write(data)

#start program
mainQueue = Queue()
broadcastQueue = Queue()

t1 = Thread(target=broadcastListener, args=())
t1.start()

UDP_IP = "192.168.1.9"
UDP_PORT = 5005
MESSAGE = "Hello, World!"
#set up socket for connection to host

while  True:
    print 'waiting for host broadcast.'
    host = broadcastQueue.get(True) #block until there is data from the broadcast thread
    validIp = True
    #setup arduino serial comm
    ser = serial.Serial('/dev/ttyATH0', 115200) # open serial port
    print ser.portstr
    ser.open()
    ser.flushInput()

    if validIp:
	
	sock = socket.socket(socket.AF_INET,socket.SOCK_DGRAM)
	try:
		sock.sendto(MESSAGE, (UDP_IP, UDP_PORT))
	except socket.error as msg:
		print 'could not send to ' + host[0] + 'error code: ' + str(msg[0])
		time.sleep(1000)
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
			sock.sendto("ROB:TEST_ROBOT",(host[0], PORT))
		except socket.error as msg:
			print ' could not send message 1 to ' + host[0] + ' error code: ' + msg[1]

		senderAddr =''
		ready = select.select([sock], [], [], .02)
		if ready[0]:
			bridgeData, senderAddr = sock.recv(1024)
		if(senderAddr == host[0]):
			arduinoCommWrite(bridgeData)

	sock.close()
        
        
        
        
    


    
