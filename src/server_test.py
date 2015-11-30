import socket
import select
import serial
import sys
import time
from Queue import Queue
from threading import Thread
 
#network related variables
PORT = 2380 # Game host port
BROADCAST_PORT = 472 # Broadcast port
BROADCAST_IP = '' 
LOCAL_IP = ''

#timouts for respective interval timers
KEEP_ALIVE_TIMEOUT = 2
NAME_BROADCAST_TIMEOUT = 5

#change this to the relevant team name when the script is loaded to the yun
ROBOT_NAME = "ChangeThisToTheTeamName"

#deprecated function, left in case the keep alive packet becomes more complex in the future
def check4keepAlive(dgram, source):
	if dgram == source[0]:	
		return True
	else:
		return False	

#threaded function that listens for broadcasts from host.
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

#deprecated function. Will replace next version revision
def arduinoCommRead():
    return ser.readLine()

#deprecated function. Will replace next version revision	
def arduinoCommWrite(data):
    ser.write(data)

#start program
mainQueue = Queue()
broadcastQueue = Queue()
t1 = Thread(target=broadcastListener, args=())
t1.start()


#Main thread that handles bridging data from the host to the robots
while  True:
	print 'waiting for host broadcast.'
	host = broadcastQueue.get(True) #block until there is data from the broadcast thread
	fKeepAlive = True

	#setup arduino serial comm
	ser = serial.Serial('/dev/ttyATH0', 115200) # open serial port
	print ser.portstr
	ser.open()
	ser.flushInput()
	
	#create socket to recieve from host
	sock = socket.socket(socket.AF_INET,socket.SOCK_DGRAM)
	try:
		sock.bind((LOCAL_IP, PORT))
	except socket.error as msg:
		print 'Broadcast bind failed. Error Code : ' + str(msg[0]) + ' Message ' + msg[1]  
		sys.exit()
		
	#send robot name to host
	try:
		sock.sendto("ROB:" + ROBOT_NAME,(host[0], PORT))
	except socket.error as msg:
		print ' Could not send robot name to ' + host[0] + ' error code: ' + msg[1]
		fKeepAlive = False
	
	
	print "Alive"
	
	#reset timers for first run after the robot has connected to the host
	keepAliveHolder = time.time()
	nameBroadcastTimer = time.time()
	
	#bridge data until connection with host is lost
	while fKeepAlive:
		
		#Check that the host is sending broadcast packets, otherwise disconnect
		if not broadcastQueue.empty():
			while not broadcastQueue.empty() :
				qPop = broadcastQueue.get()
				keepAliveTimer = time.time()
		if time.time() - keepAliveTimer > KEEP_ALIVE_TIMEOUT:
			fKeepAlive = False
			print "Connection Died"
			break
		
		#Send robot name on interval
		if time.time() - nameBroadcastTimer > NAME_BROADCAST_TIMEOUT:
			nameBroadcastTimer = time.time()
			try:
				sock.sendto("ROB:" + ROBOT_NAME,(host[0], PORT))
			except socket.error as msg:
				print ' Could not send robot name to ' + host[0] + ' error code: ' + msg[1]
				fKeepAlive = False
				break
		
		#if controller data has come from the host send it to the arduino
		ready = select.select([sock], [], [], .001)
		if ready[0]:
			bridgeData, senderAddr = sock.recvfrom(1024)
			if not bridgeData:
				continue
			else:
				if senderAddr[0] == host[0]:
					arduinoCommWrite(bridgeData)    
        
        
        
    


    
