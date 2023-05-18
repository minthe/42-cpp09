/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfuhlenb <vfuhlenb@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 13:50:50 by vfuhlenb          #+#    #+#             */
/*   Updated: 2023/05/18 20:19:08 by vfuhlenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

void	BitcoinExchange(const char *argv) {
	std::map<std::size_t, float>	data;
	std::stringstream				input;
	
	fillMap(data);
	readInput(input, argv);
	checkInput(input);

	// std::cout << input.rdbuf() << argv << std::endl;
}


// DATA

void	fillMap(std::map<std::size_t, float> &data) {
	(void)data;
	// TODO fillMap
}

// INPUT

void	readInput(std::stringstream &input, const char *argv) {
	std::ifstream	buffer;
	buffer.open(argv);
	if ((buffer.rdstate() & std::ifstream::failbit) != 0 )
		throw std::runtime_error ("\x1b[31mError: could not open file.\x1b[0m");
	input << buffer.rdbuf();
	buffer.close();
}

void	checkInput(std::stringstream &input)
{
	std::string	line;
	while (std::getline(input, line, '\n'))
	{
		std::cout << "'" <<  line << "'" << std::endl;
	}
}