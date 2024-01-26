#include "../inc/Server.hpp"
#include "../inc/webserv.hpp"
#define _XOPEN_SOURCE_EXTENDED 1
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <cstdio>

Server::Server()
{
	ip = "127.0.0.1";
	port = "8888";
}

void	Server::start()
{
	get_addr_info(&s_addr, port.c_str());
	poll.fd = create_s(poll.fd, s_addr);
	bind_s(poll.fd, s_addr);
	listen_s(poll.fd);
	freeaddrinfo(s_addr);
}

void Server::loop()
{
	int	new_socket;
	struct sockaddr_in c_addr;
    socklen_t c_addr_size = sizeof (c_addr);

	while (true)
	{	
		new_socket = accept(poll.fd, (struct sockaddr *) &c_addr, &c_addr_size);
		if (new_socket < 0)
		{
            print_error(strerror(errno));
            exit(EXIT_FAILURE);
        }
		if (!fork())
		{	
			close(poll.fd);
			handle_client(new_socket);
			close(new_socket);
			exit(0);
		}
		close(new_socket);
	}	
}