

#ifndef LOCATIONS_HPP
#define LOCATIONS_HPP

#include <iostream>
#include <vector>
#include <string>
#include <map>

class Locations {
	private:
		bool autoindex;
		std::string location;
//		std::string index;
		int methods[3]; //[0] = GET, [1] = POST, [2] = DELETE. Si es 0 no permitido si es 1 permitido.
		std::string redirection;
		std::string root;
		std::string allurl;
		std::map<std::string, std::string> cgi;
		std::vector<std::string> index;
	public:
		Locations();
		~Locations();
		void setAutoindex(bool autoin);
		void setVIndex(std::vector<std::string> idx);
		void setMethods(int met[3]);
		void setLocation(std::string loc);
		void setRedirection(std::string red);
		void setRoot(std::string rt);
		void setAllUrl(std::string url);
		void setCGI(std::string ext, std::string path);
		std::map<std::string, std::string> getCGI() const;
		bool getAutoindex() const;
		std::vector<std::string> getIndex() const;
		const int *getMethods() const;
		const std::string getLocation() const;
		const std::string getRedirection() const;
		const std::string getRoot() const;
		std::string getAllUrl();
};

#endif
