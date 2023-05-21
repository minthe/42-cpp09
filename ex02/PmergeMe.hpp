/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfuhlenb <vfuhlenb@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 17:36:56 by vfuhlenb          #+#    #+#             */
/*   Updated: 2023/05/21 11:53:19 by vfuhlenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGE_ME_H
#define PMERGE_ME_H

#include <chrono>
#include <iterator>
#include <sys/_types/_time_t.h>
#define RED "\x1b[31m"
#define YELLOW "\x1b[33m"
#define RESET "\x1b[0m"

#include <iostream>
#include <vector>
#include <list>
#include <deque>
#include <time.h>
#include <unistd.h>


int		pmerge_me(char **argv);
void	validate(char **argv);

template<typename T>
void	sort(T& container, char **argv)
{
	for (++argv ; *argv; ++argv)
		container.push_back(atoi(*argv));
	// std::cout << "sorting..." << std::endl;
}

// template<typename T> // TODO specialisation for vector containers
// void	sort(std::vector<T>& container, char **argv)
// {
// 	(void)argv;
// 	container.reserve(100);
// 	std::cout << "reserved 100 for vector" << std::endl;
// 	container.push_back(12);
// }

template<typename T>
double	run_benchmark(T container, char **argv)
{
	// unsigned int microsecond = 1000000;
	time_t	start = time(NULL);
	sort(container, argv);
	usleep(630000);
	time_t	end = time(NULL);
	return ((end - start));
}

template<typename T>
void print_container(const T& container)
{
	T temp_container = container;
	typename T::iterator it = temp_container.begin();
	for (; it != temp_container.end(); ++it)
		std::cout << *it << " ";
	std::cout << std::endl;
}

template<typename T>
int		print_msg(const T& message, const int fd)
{
	fd == 0 ? (std::cout << std::boolalpha << YELLOW << message << RESET << std::endl) \
	: (std::cerr << std::boolalpha << RED << message << RESET << std::endl);
	return fd;
}

#endif
