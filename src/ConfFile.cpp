#include<webserv.hpp>
#include <poll.h>

ConfFile::ConfFile(std::string _file)
{
	file = _file;
}

ConfFile::~ConfFile()
{
}

void	ConfFile::parse_config()
{
	std::ifstream in;
	std::string line;
	int find;
	
	find = 0;
	in.open(file.c_str(), std::ios::in); //abrimos archivo de configuración (nginx)
	if (!in.is_open())
	{
		print_error("File could not be found or opened.\n");
		exit(EXIT_FAILURE);
	}
	while (in.good()) // leemos por lineas el archivo de configuración
	{
		if (!getline(in, line))
			return ;
		if (!line.find("server"))
		{
			Server	S;
			this->serv_vec.push_back(S); // añadimos nuevo server creado
			find = 1;
		}
		int pos = line.find("listen");
		if (pos != -1 && find == 1)
		{
			if (parse_element(line)) //parseamos la instrucción
			{
				print_error("Wrong config file format.\n");
				exit(EXIT_FAILURE);
			}
		}
	}
}

//Encuentra ip y server
int		ConfFile::parse_element(std::string &line)
{
	int listenPos = line.find("listen");
	int	semicolonPos = line.find(";");
	int	ipfound = line.find(":");
	std::size_t firstNonSpace;
	std::size_t lastNonSpace;
	std::string port;
	Socket S;

	if (ipfound > -1)
	{
		std::string ip = line.substr(listenPos + 6, ipfound - (listenPos + 6));
		firstNonSpace = ip.find_first_not_of(" \t\n\r");
		lastNonSpace = ip.find_last_not_of(" \t\n\r;");
		ip = ip.substr(firstNonSpace, lastNonSpace - firstNonSpace + 1);
		if (port.find_first_not_of("0123456789.") != std::string::npos)
			return (1);
		S.ip = ip;
	}
	if (ipfound == -1)
		port = line.substr(listenPos + 6, semicolonPos);
	else
		port = line.substr(ipfound + 1, semicolonPos);
	firstNonSpace = port.find_first_not_of(" \t\n\r");
    lastNonSpace = port.find_last_not_of(" \t\n\r;");
	port = port.substr(firstNonSpace, lastNonSpace - firstNonSpace + 1);
	if (port.find_first_not_of("0123456789") != std::string::npos)
		return (1);
	S.port = port;
	this->serv_vec.back().sock_vec.push_back(S);
	return (0);
}

void	ConfFile::print_servers()
{
	for (size_t i = 0; i < this->serv_vec.size(); i++)
	{
		std::cout << "server " << i + 1 << ":" << std::endl;
		for (size_t j = 0; j < this->serv_vec[i].sock_vec.size(); j++)
		{
			std::cout << "Socket info:" << std::endl;
			std::cout << "Port: " << this->serv_vec[i].sock_vec[j].port << std::endl;
			std::cout << "IP: ";
			if (!this->serv_vec[i].sock_vec[j].ip.empty())
			   std::cout << this->serv_vec[i].sock_vec[j].ip << std::endl;
			else
				std::cout << "empty" << std::endl;
		}
		std::cout << std::endl;
	}
}

void	ConfFile::init_serv()
{
	for (size_t i = 0; i < this->serv_vec.size(); i++)
	{
		for (size_t j = 0; j < this->serv_vec[i].sock_vec.size(); j++)
		{
			this->serv_vec[i].sock_vec[j].start();
		}
	}
}

void	ConfFile::init_poll()
{
	size_t x = 0;
	int i = 0;
	for (x = 0; x < this->serv_vec.size(); x++) // recorremos todos los servers
	{
		i += (int)this->serv_vec[x].sock_vec.size(); // contamos todos los sockets de todos los servers
	}
 	this->poll_ptr = new struct pollfd[i]; // reservamos tantos polls como sockets haya
	this->fd_size = i;
	this->fd_count = i;
	i = 0;
	for (x = 0; x < this->serv_vec.size(); x++) // recorremos todos los servers
	{
		for (size_t j = 0; j < this->serv_vec[x].sock_vec.size(); j++) // recorremos todos los sockets de cada server
		{
			this->poll_ptr[i].fd = this->serv_vec[x].sock_vec[j].s_fd; // asignamos el fd de cada socket a un poll
			this->poll_ptr[i].events = POLLIN; // ?
			i++;
		}
	}
}


/* 
void	ConfFile::poll_loop()
{
	//datos para nueva conexion//
	int c_fd;
    struct sockaddr_in c_addr;
    socklen_t addrlen;
	//datos para nueva conexion//

	while (1)
	{
		//this->poll_ptr = NULL;
		print_poll(poll_ptr, fd_size);
		int poll_count = poll(this->poll_ptr, this->fd_size, -1); // ?
		if (poll_count == -1)
		{
			print_error("poll error");
			exit(EXIT_FAILURE);
		}
		for (int i = 0; i < this->fd_size; i++) // buscamos que socket esta listo para recibir cliente
		{
			if (this->poll_ptr[i].revents & POLLIN) // hay alguien listo para leer = hay un intento de conexion
			{
				//if (check_if_listener(this->poll[i].fd, list)) // comentamos de momento
				//{
					//aceptamos nueva conexion, y gestionamos inmediatamente peticion cliente, ya que subject
					//especifica solo UN POLL, para I/O entre cliente y servidor
				addrlen = sizeof (c_addr);
				c_fd = accept(this->poll_ptr[i].fd, (struct sockaddr *) &c_addr, &addrlen); // el cliente acepta el socket
				
				if (c_fd == -1)
					print_error("client accept error");
				else
				{
					handle_client(c_fd); // gestionamos cliente inmediatamente, efectuando I/O entre cliente y servidor en un poll
					close(c_fd);
				//	add_pollfd(&this->poll_ptr, c_fd, &this->fd_count, &this->fd_size);
				//	cout << "pollserver: new connection" << endl;
				}
			}
				//else //si no es listener, es peticion de cliente
				//{
				//	if (handle_client(this->poll_ptr[i].fd))
				//	{	//devuelve uno, conexion terminada o error en recv
				//		close(this->poll_ptr[i].fd);   //cerramos fd y eliminamos de array pollfd
				//		remove_pollfd(&this->poll_ptr, i, &this->fd_count); 
				//	}
					//si ha devuelto cero, peticion ha sido resuelta y la conexion sigue abierta
				//}
		}
	}
} */
