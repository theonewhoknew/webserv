#include<webserv.hpp>

int	parse_listen(t_sock **list, std::string &line) // extraemos el puerto, que debe estar en el archivo precedido de un espacio de separación con la instrucción y seguido de un punto y coma que delimite la instrucción
{
	size_t space_pos = line.find(' ');
	size_t semicolon_pos = line.find(';');
	std::string port = line.substr(space_pos + 1, semicolon_pos - space_pos - 1);
	if (port.find_first_not_of("0123456789") == std::string::npos)
	{
		sock_back(list, sock_new(port));
		return (0);
	}
	return (1);
}

/* int	parse_server_name(t_s *list, std::string &line)
{	
	(void) list;
	size_t space_pos = line.find(' ');
	size_t semicolon_pos = line.find(';');
	std::string port = line.substr(space_pos + 1, semicolon_pos - space_pos - 1);
	if (port.find_first_not_of("0123456789") == std::string::npos)
	{
		list->s->port = port;
		return (0);
	}
	return (1);
} */