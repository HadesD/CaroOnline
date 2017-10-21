.PHONY: all run client server test

default: s
# default: client

c:
	cd Client && make && make run

s:
	cd Server && make && make run

test:
	cd tests && python pingudp.py
