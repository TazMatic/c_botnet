#ifndef NETWORK_H
#define NETWORK_H

#include <stdint.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <netinet/udp.h>
#include <netinet/ip.h>

#define PORT 80
#define DATAGRAM_SIZE 1024
#define MAX_HOST 128
#define HOST_DISCONNECT_TIMER 15 //seconds

#define HOST_STATE_DISCONNECTED 0
#define HOST_STATE_PINGING 1
#define HOST_STATE_WORK_SENT 2

/*
 *	'send_data' & 'recv_data' are identical structs. Throughout development
 *	this has not been the case the majority of the time. In the future,
 *	they can be combined into a single struct.
 */


//Conn struct, written by build_conn().
struct send_data {

	char packet_send[DATAGRAM_SIZE];
	char * packet_send_body;
	struct udphdr * udp_header;
};

struct host_data {

	struct sockaddr_in addr;
	struct timeval ack_time;	
	uint8_t state; //0 - disconnected, 1 - pinging, 2 - work sent
};

struct recv_data {

	char packet_recv[DATAGRAM_SIZE];
	char * packet_recv_body; //stores body
	struct udphdr * udp_header; //struct version, points to same thing.
	struct sockaddr_in addr;

};


void build_sock(int * sock);
void build_send(struct send_data * send_data_srct);
void update_send(struct send_data * send_data_srct, struct host_data * host_data_srct,
				 uint16_t num_to_check);
void build_recv(struct recv_data * recv_data_srct);

int try_send(struct send_data * send_data_srct, struct host_data * host_data_srct,
			 int * sock, uint16_t num_to_check);
int try_recv(struct recv_data * recv_data_srct, int * sock);

void set_ack_time(struct host_data * host);
int check_outdated_ack_time(struct host_data * host, struct timeval * time);

int api_get_input();
int api_send_output(uint16_t in_fibonacci);

#endif
