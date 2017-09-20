#!/usr/bin/env python

import socket

host = "0.0.0.0"
port = 8889
udp_sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
for i in range(0, 100):
  udp_sock.sendto(str(i), (host, port))
