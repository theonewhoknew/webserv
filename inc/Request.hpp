#ifndef REQUEST_HPP
# define REQUEST_HPP

#include<HeaderHTTP.hpp>
#include "lib.hpp"

class Socket;
class Server;
class Location;

class Request
{	
	private:
		/*request elements*/	
		std::string			method;
		std::string 		target;
		std::string			version;
		std::string			request_line;
		HeaderHTTP			headers;
		std::string 		body;

		std::string			path;
		std::string			extension;

		std::string 		ip;
		std::string 		host;
		std::string 		port;

		std::string			cgiExtension;
		std::string			cgiBinary;

		bool				keepAlive;
		const Server		*serv;
		const Location		*loc;

		int					trailSlashRedir;

	public:
		Request(std::string buff, const std::vector<class Server> &server, Socket &listener, Socket &client);
		~Request();
			
		void				setRequestLine(std::string _request_line);
		void				setHeader(std::string _header);
		void				setHeaders(HeaderHTTP headers);
		void				setBody(std::string _body);

		void				splitRequest(std::string buff);
		
		std::string 		getMethod();
		std::string 		getTarget();
		std::string 		getVersion();
		std::string			getRequestLine();
		std::string			getHeader(std::string header);
		HeaderHTTP			getHeaders();
		std::string 		getBody();

		std::string			getIp();
		std::string			getHost();
		std::string			getPort();

		std::string 		getCgiExtension();
		std::string 		getCgiBinary();
		const Server		*getServer();
		const Location		*getLocation();
		bool				getTrailSlashRedir();

		std::string			getPath();
		std::string			getExtension();

		void				setCgiExtension(std::string &extension);
		void				setCgiBinary(std::string &binary);

		void 				setIpPortHost(Socket &listener);
		void				setTrailSlashRedir(bool redir);

		void				setServer(const std::vector<class Server> &server);
		void				setLocation(const Server *serv);

		void				setIp(std::string &ip);
		void				setHost(std::string &host);
		void				setPort(std::string &port);

		void				setPath(std::string path);
		void				setExtension(std::string path);

		bool				getKeepAlive();

		bool				good;

		void				printRequest();
		std::string 		makeRequest(); // devuelve el texto con el formato completo
};

#endif