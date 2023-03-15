all : appclient_tcp appserver_tcp
.PHONY : all
appclient_tcp : appclient_tcp.c transfer.h utils.h
	gcc -g -Wall -O2 -pthread appclient_tcp.c utils.c  -o appclient_tcp
appserver_tcp : appserver_tcp.c transfer.h utils.h
	gcc -g -Wall -O2 appserver_tcp.c utils.c -o appserver_tcp	
clean :
	rm appclient_tcp appserver_tcp