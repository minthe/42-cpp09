/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfuhlenb <vfuhlenb@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 13:50:50 by vfuhlenb          #+#    #+#             */
/*   Updated: 2023/05/19 00:11:58 by vfuhlenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

void		BitcoinExchange(const char *argv) {

	std::map<std::size_t, float>	data;
	std::ifstream					buffer;
	std::stringstream				input;
	std::string						line;
	
	// open input
	buffer.open(argv);
	if ((buffer.rdstate() & std::ifstream::failbit) != 0 )
		throw std::runtime_error ("\x1b[31mError: could not open file.\x1b[0m");
	input << buffer.rdbuf();
	buffer.close();
	if (input.rdbuf()->str().empty())
		throw std::runtime_error ("\x1b[31mError: empty input file.\x1b[0m");

	// fill the map with data
	// TODO fill map

	// read, check and calculate value
	if (std::getline(input, line, '\n') && line != "date | value")
		throw std::runtime_error ("\x1b[31mError: invalid input on line 1.\x1b[0m");
	while (std::getline(input, line, '\n')) {
		if (checkInputLine(line))
		{
			// TODO calculation
			std::cout << "'" <<  line << "' -> calculation..." << std::endl; // DEBUG print
		}
	}

	// std::cout << input.rdbuf() << argv << std::endl;
}

static bool is_valid_line(const std::string line)
{
	if (line.at(0) != '2')
		return false;
	return true;
}

bool		checkInputLine(const std::string line)
{
	if (line.empty())
		return false;
	if (!is_valid_line(line))
		std::cout << "Error: bad input => " << line << std::endl; // Error case 3
	return true;
}
