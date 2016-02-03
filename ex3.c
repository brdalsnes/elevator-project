#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/uio.h>
#include <stdio.h>
#include "util/Datagram.h"

//char IP = "129.241.187.32";
//char BROADCAST_IP = "129.241.187.255";

int main(void){
	const char* hostname=0; /* wildcard */
	const char* portname= "30000";
	struct addrinfo hints;
	memset(&hints,0,sizeof(hints));
	hints.ai_family=AF_UNSPEC;
	hints.ai_socktype=SOCK_DGRAM;
	hints.ai_protocol=0;
	hints.ai_flags=AI_PASSIVE|AI_ADDRCONFIG;
	struct addrinfo* res=0;

	getaddrinfo(hostname,portname,&hints,&res);

	int fd=socket(res->ai_family,res->ai_socktype,res->ai_protocol);

	bind(fd,res->ai_addr,res->ai_addrlen);

	freeaddrinfo(res);

	char buffer[548];
	struct sockaddr_storage src_addr;

	struct iovec iov[1];
	iov[0].iov_base=buffer;
	iov[0].iov_len=sizeof(buffer);

	struct msghdr message;
	message.msg_name=&src_addr;
	message.msg_namelen=sizeof(src_addr);
	message.msg_iov=iov;
	message.msg_iovlen=1;
	message.msg_control=0;
	message.msg_controllen=0;

	ssize_t count=recvmsg(fd,&message,0);
	if (count==-1) {
    //die("%s",strerror(errno));
	} else if (message.msg_flags&MSG_TRUNC) {
    	//warn("datagram too large for buffer: truncated");
	} else {
    	//handle_datagram(buffer,count);
    	printf("%s\n", buffer);
	}

	return 0;
}
