/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfuhlenb <vfuhlenb@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 17:36:56 by vfuhlenb          #+#    #+#             */
/*   Updated: 2023/05/20 20:23:23 by vfuhlenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGE_ME_H
#define PMERGE_ME_H

#define RED "\x1b[31m"
#define YELLOW "\x1b[33m"
#define RESET "\x1b[0m"

#include <iostream>
#include <vector>

int		pmerge_me(char **argv);
void	validate(char **argv);

template<typename T>
void	sort(T& container)
{
	
}

template<typename T>
int		print_msg(const T& message, const int fd)
{
	if (fd == 0)
		std::cout << std::boolalpha << YELLOW << message << RESET << std::endl;
	else
		std::cerr << std::boolalpha << RED << message << RESET << std::endl;
	return fd;
}

#endif