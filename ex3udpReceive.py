import socket
import time

UDP_IP = "129.241.187.255"
UDP_PORT = 30000
 
sock = socket.socket(socket.AF_INET, # Internet
                     socket.SOCK_DGRAM) # UDP
sock.bind((UDP_IP, UDP_PORT))
 
while True:
  data, addr = sock.recvfrom(1024) # buffer size is 1024 bytes

  print "received message:", data
  time.sleep(2)
