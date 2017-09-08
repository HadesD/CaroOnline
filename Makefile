.PHONY: all run client server

default: server
# default: client

client:
	cd Client && make && make run

server:
	cd Server && make && make run
