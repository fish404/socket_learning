

#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>

#define BUFFER_SIZE 512 


typedef struct config
{
	short port;


}Config;

int main(int argc, char* argv[])
{
    Config conf;
	int op;
		
	/* parse input parameters */
	while ((op = getopt(argc, argv, "D:")) != -1) 
	{
		switch (op) 
		{
			//case 's': inet_aton(optarg, &opts.pkt.ip.ip_src); break;
			//case 'd': inet_aton(optarg, &opts.pkt.ip.ip_dst); break;
			//case 'S': opts.pkt.udp.uh_sport = htons(atoi(optarg)); break;
			case 'D':  conf.port = atoi(optarg); break;
			//case 'l': opts.pkt.udp.uh_ulen = atoi(optarg); break;
			//case 'c': strcpy(opts.pkt.data, optarg); break;
			//case 'p': opts.pps = atoi(optarg); break;
			//case 'B': opts.bufsize = atoi(optarg); break;
			//case 'v': opts.debug = 1; break;


		}
	}
	

	int sockfd = socket(AF_INET, SOCK_DGRAM,0);
    if( sockfd == -1 )
    {
        perror("can't create udp socket: ");
        return -1;      
        
    }
    struct sockaddr_in sock_addr;
	char dst_ip[24]="192.168.56.102";
	char tmp[sizeof(struct in_addr)]={0};
    memset(&sock_addr, 0, sizeof( struct sockaddr_in));
	if( inet_pton(AF_INET, dst_ip, tmp) != 1)
	{
		perror("inet_pton failed:");
		return -1;
	}
    memcpy(&sock_addr.sin_addr.s_addr ,tmp,sizeof(struct in_addr));
    sock_addr.sin_port = htons(conf.port);
    sock_addr.sin_family = AF_INET; 
    
	char buf[BUFFER_SIZE]={0};

    
    if ( -1 == bind( sockfd, (struct sockaddr*)&sock_addr,sizeof(struct sockaddr_in) ) ) 
    {
        perror("bind socket failed:");
        return -1;
    }

    struct sockaddr_in src;
	int addr_len = 0;
    memset(&src, 0, sizeof(struct sockaddr_in ));
    
    while(  1 )
    {
        if( recvfrom(sockfd,buf,BUFFER_SIZE,0,(struct sockaddr *)&src,&addr_len ) == -1)
        {
            perror("recvfrom failed :");
            return -1;
        }
        char src_ip[24]={0};
        inet_ntop(AF_INET, &src.sin_addr.s_addr,src_ip, 24);
        printf("recv from %s message is %s\n",src_ip, buf);

    }
    return 0;

}
