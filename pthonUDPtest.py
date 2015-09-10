import time
import socket
UDP_IP = "192.168.0.9"
UDP_PORT = 2480

MESSAGE = "Hello, World!"
print "UDP target IP:", UDP_IP
print "UDP target port:", UDP_PORT
print "message:", MESSAGE
sock = socket.socket(socket.AF_INET,socket.SOCK_DGRAM)
while 1:
     
    sock.sendto(MESSAGE, (UDP_IP, UDP_PORT))
    print 'sent'
    time.sleep(.5)
