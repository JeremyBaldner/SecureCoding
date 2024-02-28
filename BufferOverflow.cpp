// BufferOverflow.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iomanip>
#include <iostream>

/*
<summay>
Function that checks if correct parameter lengths are met
<param> name="size"> size requirement of the char array </param>
Returns a correct size string
*/
std::string getUserInput(int size)
{
	std::string temp;
	std::cin >> temp;

	// loop while the size is not coorect or the input has failed
	while ((temp.size() >= size) || (!std::cin))
	{
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << "Enter a value less than 20 characters" << std::endl;
		std::cin >> temp;
	}

	return temp;
}

int main()
{
	std::cout << "Buffer Overflow Example" << std::endl;

	const std::string account_number = "CharlieBrown42";
	char user_input[20];
	std::cout << "Enter a value: ";
	strcpy_s(user_input, 20, getUserInput(sizeof(user_input)).c_str()); // <-- replaces std::cin >> user_input;

	std::cout << "You entered: " << user_input << std::endl;
	std::cout << "Account Number = " << account_number << std::endl;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu