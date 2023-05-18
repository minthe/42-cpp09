/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfuhlenb <vfuhlenb@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 13:50:50 by vfuhlenb          #+#    #+#             */
/*   Updated: 2023/05/18 20:14:25 by vfuhlenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"
#include <cstdio>
#include <exception>
#include <sstream>
#include <stdexcept>

void	BitcoinExchange(const char *argv) {
	std::map<std::size_t, float>	data;
	std::stringstream				input;
	
	readInput(input, argv);
	checkInput(input);
	fillMap(data);

	// std::cout << input.rdbuf() << argv << std::endl;
}

// PARSING

void	fillMap(std::map<std::size_t, float> &data) {
	(void)data;
	// TODO fillMap
}

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
