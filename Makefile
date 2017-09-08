.PHONY: all run client server

default: server

client:
	cd Client && make && make run

server:
	cd Server && make && make run
