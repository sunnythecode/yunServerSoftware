import socket
import sys
import time
from Queue import Queue
from threading import Thread
 
HOST = ''   # Symbolic name, meaning all available interfaces
PORT = 2367 # Arbitrary non-privileged port
data =' '
BROADCAST_PORT = 400
BROADCAST_IP = '' # Symbolic name, meaning all available interfaces

FLAG_ARDUINO_CONNECT = True
KEEP_ALIVE_TIMEOUT = 3
LOST_BROADCAST_CONNECTION = "1"

def check4keepAlive(dgram):
    a = dgram.split('.')
    if len(a) != 4:           #check that the dgram is not too small
        return False
    for x in a:              #check that each member is a number less than 255
        if not x.isdigit():
            return False
        i = int(x)
        if i< -1 or i > 255:
                return False
    return True

def broadcastListener():
    fKeepAlive = True
    lastKeepAlive = time.time()
    
    
    while True:
        bCastSock =socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        bCastSock.setsockopt(socket.SOL_SOCKET, socket.SO_BROADCAST, 1)
        bCastSock.bind((BROADCAST_IP, BROADCAST_PORT))

        while fKeepAlive:
            data =  bCastSock.recv(1500) # buffer size is 1500 bytes
            if check4keepAlive(data) == True:
                lastKeepAlive = time.time()
                broadcastQueue.put(data)
            elif time.time() - lastKeepAlive > KEEP_ALIVE_TIMEOUT:
                fKeepAlive = False
                broadcastQueue.put(LOST_BROADCAST_CONNECTION)
                
            time.sleep(.1)
        bCastSock.close()


#start program
mainQueue = Queue()
broadcastQueue = Queue()

t1 = Thread(target=broadcastListener, args=())
t1.start()

while  True:
    s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    print 'New Socket created'
    #Bind socket to local host and port
    try:
        s.bind((HOST, PORT))
    except socket.error as msg:
        print 'Bind failed. Error Code : ' + str(msg[0]) + ' Message ' + msg[1]
        
         
    print 'Socket bind complete'
    
