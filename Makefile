.PHONY: all run client server test

default: server
# default: client

client:
	cd Client && make && make run

server:
	cd Server && make && make run

test:
	cd tests && python pingudp.py
