#include "../inc/webserv.hpp"
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <fstream>

/* static int	check_element(t_s *list, std::string &line)
{
	if (!line.compare(0, 4, "\tip:"))

} */

int	parse_config(const std::string& file, t_data *data)
{
	std::ifstream in;
	std::string line;
	(void)		data;

	in.open(file.c_str(), std::ios::in);
	if (!in.is_open())
	{
		print_error("File could not be found or opened.\n");
		exit(EXIT_FAILURE);
	}
	while (in.good())
	{
		getline(in, line);
		if (!line.compare("server:"))
			s_back(&data->s_list, s_new());
/* 		if (line.at(0) == '\t')
		{
			if (check_element(s_last(data->s_list), line))
			{
				print_error("Wrong config file format.\n");
				exit(EXIT_FAILURE);
			}	
		} */
	}

	return (0);	
}