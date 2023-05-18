/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfuhlenb <vfuhlenb@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 13:50:50 by vfuhlenb          #+#    #+#             */
/*   Updated: 2023/05/18 19:17:06 by vfuhlenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"
#include <exception>
#include <sstream>
#include <stdexcept>

void	BitcoinExchange(const char *input)
{
	std::map<std::size_t, float> data;
	fillMap(data, input);
	std::cout << "running exchange on " << input << std::endl;
}

void	fillMap(std::map<std::size_t, float> &data, const char *argv)
{
	// check input file
	std::ifstream		input_txt;
	std::stringstream	buffer;
	(void)data;
	input_txt.open(argv);
	if ((input_txt.rdstate() & std::ifstream::failbit) != 0 )
		throw std::runtime_error ("\x1b[31mError: could not open file.\x1b[0m");
	buffer << input_txt.rdbuf();
	std::cout << buffer.str() << std::endl;
	input_txt.close();
}
