/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfuhlenb <vfuhlenb@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 17:36:56 by vfuhlenb          #+#    #+#             */
/*   Updated: 2023/05/21 08:16:51 by vfuhlenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGE_ME_H
#define PMERGE_ME_H

#include <sys/_types/_time_t.h>
#define RED "\x1b[31m"
#define YELLOW "\x1b[33m"
#define RESET "\x1b[0m"

#include <iostream>
#include <vector>
#include <deque>
#include <time.h>



int		pmerge_me(char **argv);
void	validate(char **argv);

template<typename T>
time_t	sort(T& container)
{
	container.push_back(12);
	time_t	start = time(NULL);
	return start;
}

template<typename T>
double	run_sort(T& container)
{
	time_t	end = sort(container);
	std::cout << "time: " << end << std::endl;
	return end;
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