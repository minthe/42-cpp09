/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfuhlenb <vfuhlenb@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 11:31:11 by vfuhlenb          #+#    #+#             */
/*   Updated: 2023/05/20 17:03:47 by vfuhlenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RPN_H
#define RPN_H

#define RED "\x1b[31m"
#define RESET "\x1b[0m"

#include <stack>
#include <iostream>
#include <iomanip>
#include <cmath>

void	rpn(const char *argv);
bool	check_arg(const char *argv);
bool	rpn_calc(const char *argv);

#endif
