/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfuhlenb <vfuhlenb@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 17:36:56 by vfuhlenb          #+#    #+#             */
/*   Updated: 2023/05/21 20:49:21 by vfuhlenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

static void print_unsorted(char **argv)
{
	int counter = 0;
	for (++argv ; *argv; ++argv)
	{
		if (counter > AMOUNT)
		{
			std::cout << " [...]" << std::endl;
			return ;
		}	
		std::cout << " " << *argv;
		counter++;
	}
	std::cout << std::endl;
}

int	pmerge_me(char **argv)
{
	validate(argv);
	std::vector<int>	sort_vector;
	std::deque<int>		sort_deque;
	std::vector<int>	sort_vector_print;
	
	// vector vs. deque
	std::cout << "Before:";
	print_unsorted(argv);
	sort(sort_vector_print, argv);
	std::cout << "After:";
	print_container(sort_vector_print, AMOUNT);
	// std::cout << std::endl;
	double		result_vector = run_benchmark<std::vector<int> >(sort_vector, argv);
	double		result_deque = run_benchmark<std::deque<int> >(sort_deque, argv);

	std::cout << "Time to process a range of " << sort_vector_print.size() << " elements with std::vector<int> : " << result_vector << " us" << std::endl;
	std::cout << "Time to process a range of " << sort_vector_print.size() << " elements with std::deque<int> : " << result_deque << " us" << std::endl;

	return 0;
}

static bool only_digits(const char* token) {
	while (*token) {
		if (!std::isdigit(*token))
			return false;
		token++; }
	return true;
}

void validate(char **argv)
{
	bool	sorted = true;
	for (int i = 1; argv[i] != 0; ++i)
	{
		double value = atof(argv[i]);
		if (value < 0)
			exit (print_msg("Error: negative value", 0));
		if (!only_digits(argv[i]) || value > 2147483647)
			exit (print_msg("Error: non-integer value", 0));
		if (argv[i + 1] && atof(argv[i]) > atof(argv[i + 1]))
			sorted = false;
		// print_msg(argv[i], 0); // DEBUG
	}
	if (sorted)
		exit (print_msg("Execution stopped: input already sorted", 0));
	// print_msg(sorted, 0); // DEBUG
	return ;
}
