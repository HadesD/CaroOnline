.PHONY: all run client

default: client

client:
	cd Client && make && make run

server:
	cd Server && make && run
