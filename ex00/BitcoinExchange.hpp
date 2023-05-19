/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfuhlenb <vfuhlenb@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 13:53:05 by vfuhlenb          #+#    #+#             */
/*   Updated: 2023/05/19 16:17:42 by vfuhlenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOIN_EXCHANGE_HPP
#define BITCOIN_EXCHANGE_HPP

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <map>
#include <exception>
#include <cctype>
#include <cmath>
#include <sys/_types/_size_t.h>

#define DATABASE "data.csv"
#define RED "\x1b[31m"
#define RESET "\x1b[0m"

std::size_t		BitcoinExchange(const char *argv);
bool			check_input_line(std::string line);
std::size_t		serialize_date(const std::string line);

#endif
