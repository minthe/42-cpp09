/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfuhlenb <vfuhlenb@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 11:31:12 by vfuhlenb          #+#    #+#             */
/*   Updated: 2023/05/20 17:03:43 by vfuhlenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

const std::string		set_operators = "+-/*", set_allowed = " +-/*0123456789";

void	rpn(const char *argv)
{
	if (check_arg(argv) && rpn_calc(argv))
		return ;
	std::cout << RED << "error: not a valid RPN expression" << RESET << std::endl;
	return ;
}

// validates expression
bool	check_arg(const char *argv)
{
	std::string				str(argv);
	int						operands = 0, operators = 0;

	for (std::string::iterator it = str.begin(); it != str.end(); ++it)
	{
		if (set_allowed.find(*it) == std::string::npos)
			return false;
		if (std::isdigit(*it))
			operands++;
		else if (set_operators.find(*it) != std::string::npos)
			operators++;
	}
	if (operators != (operands - 1))
		return false;
	return true;
}

static double	calculation(double a, double b, char c)
{
	switch (c) {
		case '+':
			return (a + b);
		case '-':
			return (a - b);
		case '/':
			return (a / b);
		case '*':
			return (a * b);
		default:
			return 0;
	}
}

// calculates expression
bool	rpn_calc(const char *argv)
{
	std::stack<double>		stack;
	std::string				str(argv);
	std::string::iterator	it(str.begin());

	while (it != str.end())
	{
		if (std::isdigit(*it))
			stack.push(*it - '0');
		else if (set_operators.find(*it) != std::string::npos)
		{
			if (stack.size() < 2)
				return false;
			double a = stack.top();
			stack.pop();
			double b = stack.top();
			stack.pop();
			stack.push(calculation(b, a, *it));
		}
		it++;
	}
	double threshold = 1.0e6;
	if (std::abs(stack.top()) >= threshold)
	{
		if (std::floor(stack.top()) == stack.top())
			std::cout << stack.top() << std::endl;
		else
			std::cout << std::fixed << std::setprecision(2) << stack.top() << std::endl;
	}
	else
		std::cout << stack.top() << std::endl;
	return true;
}
