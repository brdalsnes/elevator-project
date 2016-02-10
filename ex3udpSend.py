import socket
import time

UDP_IP = "129.241.187.255"
UDP_PORT = 20022
MESSAGE = "msg from 22 \0"

print "UDP target IP:", UDP_IP
print "UDP target port:", UDP_PORT

sock = socket.socket(socket.AF_INET, # Internet
                     socket.SOCK_DGRAM) # UDP

sock.bind((UDP_IP, UDP_PORT))

sock.setsockopt(socket.SOL_SOCKET, socket.SO_BROADCAST, 1)

sock.sendto(MESSAGE, (UDP_IP, UDP_PORT))

while True:
  msg, addr = sock.recvfrom(2048)

  print msg
