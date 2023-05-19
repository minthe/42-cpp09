/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfuhlenb <vfuhlenb@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 13:50:50 by vfuhlenb          #+#    #+#             */
/*   Updated: 2023/05/19 20:21:46 by vfuhlenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

std::size_t	BitcoinExchange(const char *argv) {
	std::map<std::size_t, double>	data;
	std::ifstream					buffer;
	std::stringstream				input;
	std::stringstream				input_db;
	std::string						line;
	std::string						line_db;
	std::size_t						counter = 0;
	
// open input
	buffer.open(argv);
	if ((buffer.rdstate() & std::ifstream::failbit) != 0 )
		throw std::runtime_error ("\x1b[31mError: could not open file.\x1b[0m");
	input << buffer.rdbuf();
	buffer.close();
	if (input.rdbuf()->str().empty())
		throw std::runtime_error ("\x1b[31mError: empty input file.\x1b[0m");
	
// fill the map with data
	buffer.open(DATABASE);
	if ((buffer.rdstate() & std::ifstream::failbit) != 0 )
		throw std::runtime_error ("\x1b[31mError: could not open database.\x1b[0m");
	input_db << buffer.rdbuf();
	buffer.close();
	if (input_db.rdbuf()->str().empty())
		throw std::runtime_error ("\x1b[31mError: empty database file.\x1b[0m");
	std::getline(input_db, line_db);
	if (line_db != "date,exchange_rate")
		throw std::runtime_error ("\x1b[31mError: invalid database file.\x1b[0m");
	while (std::getline(input_db, line_db, '\n'))
	{
		std::string	token1, token2;
		std::stringstream line_temp(line_db);

		std::getline(line_temp, token1, ',');
		std::getline(line_temp, token2, ',');
		data.insert(std::make_pair(serialize_date(token1), atof(token2.c_str()))); // https://en.cppreference.com/w/cpp/utility/pair/make_pair
	}

// parse input and calculate result
	if (std::getline(input, line, '\n') && line != "date | value")
		throw std::runtime_error ("\x1b[31mError: invalid input on line 1.\x1b[0m");
	while (std::getline(input, line, '\n')) {
		if (check_input_line(line))
		{
			size_t	date = serialize_date(line.substr(0,10));
			double	value = atof(line.substr(13,(line.length()-13)).c_str());
			std::map<size_t, double>::iterator it = data.lower_bound(date);
			if (it->first != date && it != data.begin())
				--it;
			double	result = it->second * value;
			double threshold = 1.0e6;
			if (std::abs(result) >= threshold)
			{
				std::cout << line.substr(0,10) << " => " << value << " = ";
				if (std::floor(result) == result)
					std::cout << std::fixed << std::setprecision(0) << result << std::endl;
				else
					std::cout << std::fixed << std::setprecision(2) << result << std::endl;
			}
			else
				std::cout << line.substr(0,10) << " => " << value << " = " << result << std::endl;
		}
		counter++;
	}
	return counter;
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
	if (*token == '-')
		token++;
	while (*token) {
		if (*token == '.')
			dots++;
		if ((!std::isdigit(*token) && *token != '.') || dots > 1)
			return false;
		token++; }
	if (*--token == '.')
		return false;
	return true;
}

static bool is_valid_number(const std::string token) {
	double	value;
	value = atof(token.c_str());
	// if (value == 0) { // optional
	// 	std::cout << "Error: not a positive number." << std::endl; // Error case 2
	// 	return false; }
	if (value > 1000) {
		std::cout << RED << "Error: too large a number." << RESET << std::endl; // Error case 3
		return false; }
	return true;
}

static bool is_gap_year(const size_t y)
{
	if ((y % 4 == 0 && y % 100 != 0) || y % 400 == 0) // https://www.kalenderpedia.de/schaltjahre.html
		return true;
	return false;
}

static bool	check_date(const std::string line)
{
	const size_t	y = atoi(line.substr(0,4).c_str());
	const size_t	m = atoi(line.substr(5,2).c_str());
	const size_t	d = atoi(line.substr(8,2).c_str());

	if (y < 2009 || m < 1 || m > 12 || d < 1 || d > 31) // bounds
		return false;
	if (m == 2 && (!is_gap_year(y) && d > 28))  // Gap Years
		return false;
	if ((m == 4 || m == 6 || m == 9 || m == 11) && d > 30) // month with 31 days
		return false;
	if (serialize_date(line) < (size_t)20090102) // bitcoin start date
		return false;
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
		return false;
	if (!is_float_literal(line.substr(13,(line.length()-13)).c_str()))
		return false;
	if (!check_date(line))
		return false;
	return true;
}

bool	check_input_line(const std::string line) {
	if (line.empty())
		return false;
	else if (!is_valid_line(line)) {
		std::cout << RED <<  "Error: bad input => " << line << RESET << std::endl; // Error case 3
		return false; }
	else if (line.c_str()[13] == '-') {
		std::cout << RED << "Error: not a positive number." << RESET << std::endl; // Error case 2
		return false; }
	else if (!is_valid_number(line.substr(13,(line.length()-13))))
		return false;
	return true;
}

size_t	serialize_date(const std::string line) {
	std::string _line = line;
	_line.erase(4, 1);
	_line.erase(6, 1);
	const size_t date = atoi(_line.c_str());
	return date;
}
