/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfuhlenb <vfuhlenb@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 13:50:50 by vfuhlenb          #+#    #+#             */
/*   Updated: 2023/05/19 02:24:07 by vfuhlenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

void	BitcoinExchange(const char *argv) {
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

// parse input and calculate result
	if (std::getline(input, line, '\n') && line != "date | value")
		throw std::runtime_error ("\x1b[31mError: invalid input on line 1.\x1b[0m");
	while (std::getline(input, line, '\n')) {
		if (checkInputLine(line))
		{
			// TODO case 0: if no previous date is found... <2009
			// TODO calculation
			std::cout << "'" <<  line << "' -> value: " << atof(line.substr(13,(line.length()-13)).c_str()) << std::endl; // DEBUG print
		}
	}
}

static bool only_digits(const char* token) {
	while (*token) {
		if (!std::isdigit(*token))
			return false;
		token++; }
	return true;
}

static bool no_whitespace(const char* token) {
	while (*token) {
		if (std::isspace(*token))
			return false;
		token++; }
	return true;
}

static bool is_float_literal(const char* token) {
	size_t dots = 0;
	while (*token) {
		if (*token == '.')
			dots++;
		if ((!std::isdigit(*token) && *token != '.') || dots > 1)
			return false;
		token++; }
	return true;
}

static bool is_valid_number(const std::string token) {
	double value;
	value = atof(token.c_str());
	if (value > 1000) {
		std::cout << "Error: too large number." << std::endl; // Error case 3
		return false; }
	return true;
}

static bool is_valid_line(const std::string line) {
	if (line.length() < 14)
		return false;
	if (!only_digits(line.substr(0,4).c_str()) || !only_digits(line.substr(5,2).c_str()) \
		|| !only_digits(line.substr(8,2).c_str())) // Date values
		return false;
	if (line.at(4) != '-' || line.at(7) != '-' || \
		line.at(10) != ' ' || line.at(11) != '|' || \
		line.at(12) != ' ') // delimiters
		return false;
	if (!no_whitespace(line.substr(13,(line.length()-13)).c_str()))
		std::cout << "Error: bad input => " << line << std::endl; // Error case 3
	if (!is_float_literal(line.substr(13,(line.length()-13)).c_str()))
		std::cout << "Error: bad input => " << line << std::endl; // Error case 3
	return true;
}

bool	checkInputLine(const std::string line) {
	if (line.empty())
		return false;
	else if (!is_valid_line(line)) {
		std::cout << "Error: bad input => " << line << std::endl; // Error case 3
		return false; }
	else if (line.at(13) == '-') {
		std::cout << "Error: not a positive number." << std::endl; // Error case 2
		return false; }
	else if (!is_valid_number(line.substr(13,(line.length()-13))))
		return false;
	// TODO check for valid date
	return true;
}
