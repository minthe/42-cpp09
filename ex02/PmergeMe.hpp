/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfuhlenb <vfuhlenb@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 17:36:56 by vfuhlenb          #+#    #+#             */
/*   Updated: 2023/05/21 15:29:34 by vfuhlenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGE_ME_H
#define PMERGE_ME_H

#include <iostream>
#include <vector>
#include <list>
#include <deque>
#include <unistd.h>
#include <iterator>
#include <typeinfo>
#include <sys/time.h>
#include <iomanip>

#define RED "\x1b[31m"
#define YELLOW "\x1b[33m"
#define RESET "\x1b[0m"

// #define VECTOR_INT typeid(std::vector<int>).name()
// #define DEQUE_INT typeid(std::deque<int>).name()
// #define LIST_INT typeid(std::list<int>).name()

int		pmerge_me(char **argv);
void	validate(char **argv);

template<typename T>
double print_container(const T& container)
{
	struct timeval start, end;
	gettimeofday(&start, NULL);
	T temp_container = container;
	typename T::iterator it = temp_container.begin();
	for (; it != temp_container.end(); ++it)
		std::cout << *it << " ";
	std::cout << std::endl;
	gettimeofday(&end, NULL);
	long time_us= (end.tv_sec- start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec);
	double time_s = static_cast<double>(time_us);
    return time_s;
}

template<typename T>
void	sort(T& container, char **argv)
{
	// FILLING CONTAINER
	// if (strcmp(typeid(container).name(),VECTOR_INT) == 0)
	// {
	// 	char **temp = argv;
	// 	int count = 0;
	// 	for (++temp; *temp; ++temp)
	// 		count++;
	// 	container.reserve(count);
	// 	// std::cout << "reserving for vector: " << count << std::endl; // DEBUG
	// }
	for (++argv ; *argv; ++argv)
		container.push_back(atoi(*argv));
	
	// MERGE
	typename T::iterator l_first = container.begin();
	typename T::iterator l_last = container.begin() + (container.size() / 2);
	T subcontainer(l_first, l_last);
	typename T::iterator r_first = container.begin() + (container.size() / 2);
	typename T::iterator r_last = container.end();
	T subcontainer2(r_first, r_last);
	subcontainer.swap(subcontainer2);
	container = subcontainer;
	container.insert(container.end(), subcontainer2.begin(), subcontainer2.end());
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
	struct timeval start, end;
	gettimeofday(&start, NULL);
	sort(container, argv);
	gettimeofday(&end, NULL);
	long time_us= (end.tv_sec- start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec);
	double time_s = static_cast<double>(time_us);
    return time_s;
}

template<typename T>
int		print_msg(const T& message, const int fd)
{
	fd == 0 ? (std::cout << std::boolalpha << YELLOW << message << RESET << std::endl) \
	: (std::cerr << std::boolalpha << RED << message << RESET << std::endl);
	return fd;
}

#endif
