/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmouaike <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 08:49:34 by jmouaike          #+#    #+#             */
/*   Updated: 2023/04/27 08:49:37 by jmouaike         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/RPN.hpp"

/* *********************** */
/*  Ex01  RPN              */
/* *********************** */

int					main(int argc, char **argv)
{
	switch (argc)
	{
	case 2:
		{
			std::string 	input_operation = static_cast <std::string>(argv[1]);
			RPN				to_stack(input_operation);

			try
			{
				to_stack.calculator();
			}
			catch(const std::exception &e)
			{
				std::cerr << COL_BRED << e.what() << COL_RES << std::endl;
				
			}
		}
		break;
	default:
		std::cout << COL_AUB << "./RNP   \"operation\" " << COL_RES << std::endl;
		break;
	}
	return 0;
}

/*
Issues :
1- constructor by copy and copy assignement operator=

2- necessary space before operator ? unecessary befor digit ?
"En fait RPN est censé fonctionner sans espace en ayant les opérandes et les opérateurs collés, du coup ça implique qu'on n'a pas à gérer les négatifs"
Ben si le - est collé au chiffre c’est négatif, si il y a un espace c’est opérande
Je viens de me faire corriger sur le CPP09 et j'ai fail car sur un test de la correction, je refusais pour faute de syntaxte  ./RPN "12 * 2 / 5 + 46 * 6 / 8 * 2 / + 2 *2" 
On est sense l'accepter avec le / et le + qui se suivent a la fin ?

3- static ? static class ? whichInputChar 

4- const

5- handle multiple exceptions : explicit error messages
			throw std::runtime_error("Error opening output file");

6- int overflow => switch to double ? throw exception ?

7- change stack to deque to use iterators
"et techniquement stack n'est pas un container mais un adaptateur de container ; )
ds les prerequis des containers il faut des iterators"


8- implicit cast char to int :  this->_mstack->push((this->_input[i]) - '0');

9- negative numbers "-9 5 +" should be result -4 ?


https://wisdomsky.github.io/reverse-polish-notation-js-parser/

"8 9 * 9 - 9 - 9 - 4 - 1 +"  ===> 42
"  1 "    ====> 1 ?
"7 6 3 *-" ====> -11
"  6 2 / 2 4 + 5 - +" ==> 4
"z 3 3 +"      ===>invalid
"   3 5 + 4-"  ===> 4
"5 1 1 1---"   ===> 3 
"5    2 +7/"   ===> 1
"5 2 + 1 3 * +" ====> 10
"5 2 + 1 3 * *"  ===> 21
5 2 1 3 + * + === 13
./RPN "9 9 * 9 * 9 * 9* 9* 9* 9* 9* 9* 8* 3 * "
./RPN "12 * 2 / 5 + 46 * 6 / 8 * 2 / + 2 *2" 
*/
