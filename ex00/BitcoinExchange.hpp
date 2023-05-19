/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfuhlenb <vfuhlenb@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 13:53:05 by vfuhlenb          #+#    #+#             */
/*   Updated: 2023/05/19 14:25:30 by vfuhlenb         ###   ########.fr       */
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

void		BitcoinExchange(const char *argv);
bool		check_input_line(std::string line);
size_t		serialize_date(const std::string line);

#endif
