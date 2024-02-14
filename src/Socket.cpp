#include<webserv.hpp>


Socket::Socket()
{
//	port = "8888";
}

Socket::~Socket()
{
}

void	Socket::start()
{
	get_addr_info(&s_addr, port.c_str()); // obtenemos datos
	s_fd = create_s(s_fd, s_addr); //creamos el fd del socket
	bind_s(s_fd, s_addr);
	listen_s(s_fd);
	freeaddrinfo(s_addr);
}

/* void Socket::loop()
{
	int	new_socket;
	struct sockaddr_in c_addr;
    socklen_t c_addr_size = sizeof (c_addr);

	while (true)
	{	
		new_socket = accept(s_fd, (struct sockaddr *) &c_addr, &c_addr_size);
		if (new_socket < 0)
		{
            print_error(strerror(errno));
            exit(EXIT_FAILURE);
        }
		if (!fork())
		{	
			close(s_fd);
			handle_client(new_socket);
			close(new_socket);
			exit(0);
		}
		close(new_socket);
	}	
} */

std::string Socket::getPort()
{
	return (this->port);
}

std::string Socket::getIp()
{
	return (this->ip);
}

std::string Socket::getServerName()
{
	return (this->server_name);
}

std::string Socket::getErrorPage()
{
	return (this->error_page);
}

std::string Socket::getAllowMethods()
{
	return (this->methods);
}

void	Socket::setPort(std::string port)
{
	this->port = port;
}

void	Socket::setIp(std::string ip)
{
	this->ip = ip;
}

void	Socket::setServerName(std::string serverName)
{
	this->server_name = serverName;
}

void	Socket::setErrorPage(std::string errorPage)
{
	this->error_page = errorPage;
}

void	Socket::setAllowMethods(std::string allow)
{
	this->methods = allow;
}
