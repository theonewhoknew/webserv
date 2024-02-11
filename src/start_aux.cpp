#include<webserv.hpp>

void	get_addr_info(struct addrinfo **s_addr, const char *port)
{	
	int				status;
	struct addrinfo hints;

	memset(&hints, 0, sizeof (hints)); // damos valor NULL a todo para luego inicializar
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;
	status = getaddrinfo(NULL, port, &hints, s_addr);
	if (status != 0)
	{
		print_error(gai_strerror(status));
    	exit(1);
	}
}

int create_s(int server_fd, struct addrinfo *s_addr)
{
	server_fd = socket(s_addr->ai_family, s_addr->ai_socktype, s_addr->ai_protocol);
	if (server_fd < 0)
	{
		print_error(strerror(errno));
        close(server_fd);
        exit(EXIT_FAILURE);
	}
	if (fcntl(server_fd, F_SETFL, O_NONBLOCK, FD_CLOEXEC) == -1)
	{
		print_error(strerror(errno));
        close(server_fd);
        exit(EXIT_FAILURE);
	}
	return (server_fd);
}

int bind_s(int server_fd, struct addrinfo *s_addr)
{	
	int	yes = 1;

	if (bind(server_fd, s_addr->ai_addr, s_addr->ai_addrlen) < 0) // hacemos bind
	{
		print_error(strerror(errno));
        close(server_fd);
        exit(EXIT_FAILURE);
	}
	if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof (yes)) == -1) 
	{
    	print_error(strerror(errno));
   		exit(1);
	}
	return (server_fd);
}

int listen_s(int server_fd)
{
	if (listen(server_fd, 10) < 0)
	{
		print_error(strerror(errno));
        close(server_fd);
        exit(EXIT_FAILURE);
	}
	return (server_fd);
}
