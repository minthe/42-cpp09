/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfuhlenb <vfuhlenb@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 17:36:56 by vfuhlenb          #+#    #+#             */
/*   Updated: 2023/05/21 10:02:49 by vfuhlenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGE_ME_H
#define PMERGE_ME_H

#include <chrono>
#include <sys/_types/_time_t.h>
#define RED "\x1b[31m"
#define YELLOW "\x1b[33m"
#define RESET "\x1b[0m"

#include <iostream>
#include <vector>
#include <deque>
#include <time.h>
#include <unistd.h>


int		pmerge_me(char **argv);
void	validate(char **argv);

template<typename T>
void	sort(T& container, char **argv)
{
	(void)argv;
	container.push_back(12);
	std::cout << "general exe..." << std::endl;
}

template<typename T> // TODO specialisation for vector containers
void	sort(std::vector<T>& container, char **argv)
{
	(void)argv;
	container.reserve(100);
	std::cout << "reserved 100 for vector" << std::endl;
	container.push_back(12);
}


template<typename T>
double	run_benchmark(T& container, char **argv)
{
	// unsigned int microsecond = 1000000;
	time_t	start = time(NULL);
	sort(container, argv);
	usleep(630000);
	time_t	end = time(NULL);
	return ((end - start));
}

template<typename T>
int		print_msg(const T& message, const int fd)
{
	fd == 0 ? (std::cout << std::boolalpha << YELLOW << message << RESET << std::endl) : (std::cerr << std::boolalpha << RED << message << RESET << std::endl);
	// if (fd == 0)
	// 	std::cout << std::boolalpha << YELLOW << message << RESET << std::endl;
	// else
	// 	std::cerr << std::boolalpha << RED << message << RESET << std::endl;
	return fd;
}

#endif