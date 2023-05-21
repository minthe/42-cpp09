/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfuhlenb <vfuhlenb@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 17:36:56 by vfuhlenb          #+#    #+#             */
/*   Updated: 2023/05/21 18:36:49 by vfuhlenb         ###   ########.fr       */
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
#include <stdlib.h>

#define RED "\x1b[31m"
#define YELLOW "\x1b[33m"
#define RESET "\x1b[0m"
#define AMOUNT 15
#define THRESHOLD 4

// #define VECTOR_INT typeid(std::vector<int>).name() // TODO Not working on osx
// #define DEQUE_INT typeid(std::deque<int>).name()
// #define LIST_INT typeid(std::list<int>).name()

int		pmerge_me(char **argv);
void	validate(char **argv);

template<typename T>
void print_container(const T& container, const int amount)
{
	int counter = 0;
	T temp_container = container;
	typename T::iterator it = temp_container.begin();
	for (; it != temp_container.end(); ++it)
	{
		if (counter > amount)
		{
			std::cout << " [...]" << std::endl;
			return ;
		}
		std::cout << " " << *it;
		counter++;
	}
	std::cout << std::endl;
}

/*
	- left, mid_point, and right are the boundaries that defines the subarrays
	- creates two new containers for each side.
	- then compares the values and assigns the smaller/equal value to container_iter -> original container.
	- if there are remaining elements it copies it to container_iter
*/
template<typename T>
void merge(T& container, int left, int mid_point, int right)
{
	T left_container(container.begin() + left, container.begin() + mid_point + 1);
	T right_container(container.begin() + mid_point + 1, container.begin() + right + 1);

	typename T::iterator left_iter = left_container.begin();
	typename T::iterator right_iter = right_container.begin();
	typename T::iterator container_iter = container.begin() + left; // iterator that points to the original container

	while (left_iter != left_container.end() && right_iter != right_container.end())
	{
		if (*left_iter <= *right_iter) // if value is smaller or equal then copy value to container
		{
			*container_iter = *left_iter;
			++left_iter;
		}
		else // if bigger then use it from the other half
		{
			*container_iter = *right_iter;
			++right_iter;
		}
		++container_iter;
	}

	while (left_iter != left_container.end()) // leftovers from left_temp container
	{
		*container_iter = *left_iter;
		++left_iter;
		++container_iter;
	}

	while (right_iter != right_container.end()) // leftovers from right_temp container
	{
		*container_iter = *right_iter;
		++right_iter;
		++container_iter;
	}
}

/*
	- it iterates to the right within the left and right boundaries on the container array
	- if current element is smaller than previous iterate to the left and place it until the previous is smaller than the current element.
	- or its the first element after the operation.
	
*/
template<typename T>
void insertionSort(T& container, int left, int right) {
	for (int i = left + 1; i <= right; ++i)
	{
		int current_element = container[i]; // initialize current_element to compare against range
		int j = i - 1; // sets j to previous element
		while (j >= left && container[j] > current_element) // compares value against current element
		{
			container[j + 1] = container[j]; // swaps the bigger previous with current pos.
			--j; // repeat until previous is smaller
		}
		container[j + 1] = current_element; // inserts the swapped value
	}
}

/*
	- starting with container and begin() and end().
	- first step is to run MergeSort in recursion until the threshold is reached.
	   it divides the container into chunks.
	- then the insertion sort will be applied to the smallest chunks.
	- merge combines these sorted chunks in the right order until it
	   reaches the end of the recursion.
*/
template<typename T>
void	mergeSort(T& container, int left, int right)
{
	if (left < right) { // checks if there is more than one element in the subarray
		if (right - left + 1 <= THRESHOLD) {
			insertionSort(container, left, right); // run this on small chunck
		}
		else {
			int mid = left + (right - left) / 2;
			
			mergeSort(container, left, mid);
			mergeSort(container, mid + 1, right);

			merge(container, left, mid, right);
		}
	}
}

template<typename T>
void	sort(std::deque<T>& container, char **argv)
{
	// filling the container
	for (++argv ; *argv; ++argv)
		container.push_back(atoi(*argv));
	// sorting
	mergeSort(container, 0, container.size() - 1); // - 1 because we want to point to the last array value
	// std::cout << "sorting..." << std::endl;
}

template<typename T>
void	sort(std::vector<T>& container, char **argv)
{
	// Reserving space for vector container
	// if (strcmp(typeid(container).name(),VECTOR_INT) == 0)
	{
		char **temp = argv;
		int count = 0;
		for (++temp; *temp; ++temp)
			count++;
		container.reserve(count);
		// std::cout << "reserving for vector: " << count << std::endl; // DEBUG
	}
	// Filling the container
	for (++argv ; *argv; ++argv)
		container.push_back(atoi(*argv));
	
	// MERGE
	mergeSort(container, 0, container.size() - 1);
}

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
