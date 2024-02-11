#include <webserv.hpp>

Request::Request()
{
	//status_line = "HTTP/1.1 200 OK\r\n";
	//headers.setHeader("Content-Length: 2");//\r\n");
	//body = "Hi";
}

Request::~Request()
{
}

std::string Request::makeRequest()
{
	return (this->status_line + this->headers.makeHeader()
			+ "\r\n" + this->body);
}

void	Request::setStatusLine(std::string _status_line)
{
	this->status_line = _status_line + "\r\n";
}

void	Request::setHeader(std::string _header)
{
	this->headers.setHeader(_header);
}

void	Request::setBody(std::string _body)
{
	this->body = _body;
}
