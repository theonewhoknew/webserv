#include "../inc/Server.hpp"

Server::Server()
{
	sock_list	= NULL;
	active = 1;
	ip = "";
	server_name = "";
	error_page = "";
	methods = "";
}

void	Server::start()
{
	for(t_sock *ptr = sock_list; ptr != NULL; ptr = ptr->next)
	{
		ptr->sock->start(); //inicializamos los datos del socket
	}
}

std::string Server::getPort()
{
	return (this->port);
}

std::string Server::getIp()
{
	return (this->ip);
}

std::string Server::getServerName()
{
	return (this->server_name);
}

std::string Server::getErrorPage()
{
	return (this->error_page);
}

std::string Server::getAllowMethods()
{
	return (this->methods);
}

void	Server::setPort(std::string port)
{
	this->port = port;
}

void	Server::setIp(std::string ip)
{
	this->ip = ip;
}

void	Server::setServerName(std::string serverName)
{
	this->server_name = serverName;
}

void	Server::setErrorPage(std::string errorPage)
{
	this->error_page = errorPage;
}

void	Server::setAllowMethods(std::string allow)
{
	this->methods = allow;
}

void	Server::addVServerName(std::string str)
{
	vserver_name.push_back(str);
}

std::vector<std::string>& Server::getVServerName()
{
	return (vserver_name);
}

void	Server::addVPort(std::string str)
{
	vports.push_back(str);
}

std::vector<std::string>& Server::getVPort()
{
	return (vports);
}
