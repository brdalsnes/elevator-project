#!/usr/bin/env python
import socket

TCP_IP = "129.241.187.23"
TCP_PORT = 33546
BUFFER_SIZE = 2048
MESSAGE = "msg from 22 \0"

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect((TCP_IP, TCP_PORT))
s.send(MESSAGE)
data = s.recv(BUFFER_SIZE)
s.close()

print "Received data:", data
