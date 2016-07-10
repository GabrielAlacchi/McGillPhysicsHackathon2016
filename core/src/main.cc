
#include "simulation.hpp"

#include <pthread.h>
#include <thread>
#include <string>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <time.h> 

void runSocket(Simulation& ref) {
	int listenfd = 0, connfd = 0;
    struct sockaddr_in serv_addr; 

    char sendBuff[1025];
    time_t ticks; 

    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    memset(&serv_addr, '0', sizeof(serv_addr));
    memset(sendBuff, '0', sizeof(sendBuff)); 

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    serv_addr.sin_port = htons(5000); 

    bind(listenfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)); 

    listen(listenfd, 10); 

    while(1)
    {
        connfd = accept(listenfd, (struct sockaddr*)NULL, NULL); 

        write(connfd, sendBuff, strlen(sendBuff)); 
		
		vec3 pos, vel;
		long double mass;
		
		scanf(sendBuff, "%d_%d_%d_%d_%d_%d_%d", 
			pos.x,
			pos.y,
			pos.z,
			vel.x,
			vel.y,
			vel.z,
			mass);		

		ref.addBody(pos, vel, mass);

        close(connfd);
        sleep(1);
     }
}

int main(int argc, char **argv) {
	
	Simulation sim(0.3, 1);
	
	vec3 pos1, vel1;

	pos1 = {0.0, 0.0, 0.0};
	vel1 = {0.0, 0.0, 0.0};

	sim.addBody(pos1, vel1, 1e6);

	std::thread t(&runSocket, std::ref(sim));

	while (true) {
		sim.tick();
	}
    	
	return 0;
}
