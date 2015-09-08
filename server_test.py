import socket
import sys
import time
from Queue import Queue
from threading import Thread
 
HOST = ''   # Symbolic name, meaning all available interfaces
PORT = 8888 # Arbitrary non-privileged port
data =' '
BROADCAST_PORT = 400
BROADCAST_IP = "127.0.0.1"

def broadcastListener():
    while True:
        bCastSock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        bCastSock.bind((BROADCAST_IP, BROADCAST_PORT))
        mainQueue.put("data")
        
        

while  True:
    mainQueue = Queue()
    broadcastQueue = Queue()

    t1 = Thread(target=broadcastListener, args=())
    t1.start()
    
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    print 'New Socket created'
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
    matchState = 0;
    connState = True
    while connState:
            #loop back message from client
            try:
                data = conn.recv(1024)
            except socket.error, (value,message):
                if value == 10054: #if connection was reset remotely
                    connState = False
            try:
                    delmPos = data.index('!')
            except ValueError:
                    print "could not find delim"
                    connState = False
            if len(data) > 1 :
                    if data[0] == '1' :
                            sendCnt =conn.send("lancer")
                            print "number of chars sent: " + repr(sendCnt)   
                    if data[0] == '6':
                            matchState = 1 #matchstate 1 is match start, auto
                            print "matchStart"
                    if data[0] == '7':
                            matchState = 2 #matchstate 2 is teleop
                            print "teleop start"
                    if data[0] == '8':
                            matchState = 0 #matchstate 0 is matchEnd
                            print "match over"
