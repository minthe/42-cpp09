/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfuhlenb <vfuhlenb@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 13:54:46 by vfuhlenb          #+#    #+#             */
/*   Updated: 2023/05/19 16:17:38 by vfuhlenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"
#include <exception>
#include <iostream>
#include <stdexcept>

int	main(int argc, char **argv)
{
	if (argc != 2) {
		std::cerr << RED << "Error: could not open file." << RESET << std::endl;
		return 1;
	}
	try
	{
		if (!BitcoinExchange(argv[1]))
			std::cerr << RED << "no lines to process" << RESET << std::endl;
	}
	catch (std::exception& e)
	{
		// throw std::runtime_error ("\x1b[31mError: could not open file.\x1b[0m");
		std::cerr << "Exception caught: " << e.what() << std::endl;
	}
	return 0;
}
