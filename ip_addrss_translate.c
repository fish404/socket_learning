#include <stdio.h>
#include <errno.h>
#include <arpa/inet.h>
#include <arpa/inet.h>

#define BUFFER_LEN 32 

#define 	ERR(...) 	 fprintf(stderr, __VA_ARGS__); fflush(stderr)



void print_ip(const void* src)
{

    if(src == NULL)
    {
        ERR("error! please input a valid in address \n");        
    }
    char data[BUFFER_LEN]={0};
    socklen_t size = BUFFER_LEN;
    const char* ret = inet_ntop(AF_INET,src,data, size);
    if( ret )
    {
        ERR("\t%d  ----->  %s\n",*(int*)src, data);
        return ;
    }
    else
    {
        ERR("transfer ip failed\n");
        strerror(errno);
        return ;
    }
    return ;
}

int main()
{
    int ip = 0;
    int process_ip = 0;
    while( scanf("%d",&ip ) != EOF )
    {
        process_ip = ntohl(ip);
        print_ip(&process_ip);
    }
    
    return 0;
    
    
}
