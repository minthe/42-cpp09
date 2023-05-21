/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfuhlenb <vfuhlenb@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 17:36:56 by vfuhlenb          #+#    #+#             */
/*   Updated: 2023/05/21 09:44:26 by vfuhlenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

int	pmerge_me(char **argv)
{
	validate(argv);
	std::vector<int>	sort_vector;
	std::vector<int>	sort_vector_print;
	std::deque<int>		sort_deque;
	
	double				result_vector = run_benchmark<std::vector<int> >(sort_vector, argv);
	double				result_deque = run_benchmark<std::deque<int> >(sort_deque, argv);
	
	std::cout << "vector: " << std::fixed << result_vector << std::endl;
	std::cout << "deque: " << std::fixed << result_deque << std::endl;

	return 0;
}

void validate(char **argv)
{
	bool	sorted = true;
	for (int i = 1; argv[i] != 0; ++i)
	{
		double value = atof(argv[i]);
		if (value < 0)
			exit (print_msg("Error: negative value", 0));
		if (!isdigit(*argv[i]) || value > 2147483647)
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
