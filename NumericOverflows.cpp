// NumericOverflows.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>     // std::cout
#include <limits>       // std::numeric_limits

/*
<summary>
Template function to abstract away the logic of:
start + (increment * steps)

<typeparam name="T">A type that with basic math functions</typeparam>
<param name="start">The number to start with</param>
<param name="increment">How much to add each step</param>
<param name="steps">The number of steps to iterate</param>
<param name="verify">The boolean to determine proper return value - JB
<returns>start + (increment * steps)</returns>
*/

template <typename T>
T add_numbers(T const& start, T const& increment, unsigned long int const& steps, bool* verify)
{
    T result = start;
    long double check = std::numeric_limits<T>::max() / increment;
    *verify = false;

    // if statement that compares max steps to planned steps to pre-check for overflow -JB
    // If precheck is failed: return max, else: return result
    if (check < steps)
    {
        return std::numeric_limits<T>::max();
    }
    else
    {
        *verify = true;
        for (unsigned long int i = 0; i < steps; ++i)
        {
            result += increment;
        }
    }

    return result;
}

/*
<summary>
Template function to abstract away the logic of:
start - (increment * steps)

<typeparam name="T">A type that with basic math functions</typeparam>
<param name="start">The number to start with</param>
<param name="increment">How much to subtract each step</param>
<param name="steps">The number of steps to iterate</param>
<param name="verify">The boolean to determine proper return value - JB
<returns>start - (increment * steps)</returns>
*/

template <typename T>
T subtract_numbers(T const& start, T const& decrement, unsigned long int const& steps, bool* verify)
{
    T result = start;
    long double check = std::numeric_limits<T>::max() / decrement; // Find the max steps possible
    *verify = false; // initialize verification method

    // if statement that compares max steps to planned steps to pre-check for underflow -JB
    // If precheck is failed: return min, else: return result
    if (check < steps)
    {
        return std::numeric_limits<T>::min();
    }
    else
    {
        *verify = true;
        for (unsigned long int i = 0; i < steps; ++i)
        {
            result -= decrement;
        }
    }

    return result;
}

/*
<summary> -JB
Function to output the proper values or provide an error message.
<param name="verify">A boolean that determines if error message should be released
<parm name="opperation">Specifies the opperation performed to output the correct under/over flow message
<parm name="results">results that were returned from the opperation
*/
void get_output(bool verify, char opperation, long double results)
{
    char addition = 'add';
    if (opperation == addition) {
        // Detect failed calculations. Inform user of overflow -JB
        if (!verify)
        {
            std::cout << "Error: Overflow calculation occured. Maximum value is " << +results << std::endl;
        }
        else {
            std::cout << +results << std::endl;
        }
    }
    else {
        // Detect failed calculations. Inform user of overflow -JB
        if (!verify)
        {
            std::cout << "Error: Underflow calculation occured. Minimum value is " << +results << std::endl;
        }
        else {
            std::cout << +results << std::endl;
        }
    }
}


//  NOTE:
//    You will see the unary ('+') operator used in front of the variables in the test_XXX methods.
//    This forces the output to be a number for cases where cout would assume it is a character. 

template <typename T>
void test_overflow()
{
    // START DO NOT CHANGE
    //  how many times will we iterate
    const unsigned long int steps = 5;
    // how much will we add each step (result should be: start + (increment * steps))
    const T increment = std::numeric_limits<T>::max() / steps;
    // whats our starting point
    const T start = 0;

    std::cout << "Overflow Test of Type = " << typeid(T).name() << std::endl;
    // END DO NOT CHANGE

    // variable used to determine unexpected output -JB
    bool verification;

    std::cout << "\tAdding Numbers Without Overflow (" << +start << ", " << +increment << ", " << steps << ") = ";
    T result = add_numbers<T>(start, increment, steps, &verification);
    get_output(verification, 'add', +result);

    std::cout << "\tAdding Numbers With Overflow (" << +start << ", " << +increment << ", " << (steps + 1) << ") = ";
    result = add_numbers<T>(start, increment, steps + 1, &verification);
    get_output(verification, 'add', +result);
}

template <typename T>
void test_underflow()
{
    // START DO NOT CHANGE
    //  how many times will we iterate
    const unsigned long int steps = 5;
    // how much will we subtract each step (result should be: start - (increment * steps))
    const T decrement = std::numeric_limits<T>::max() / steps;
    // whats our starting point
    const T start = std::numeric_limits<T>::max();

    std::cout << "Underflow Test of Type = " << typeid(T).name() << std::endl;
    // END DO NOT CHANGE

    // variable used to determine unexpected output -JB
    bool verification;

    std::cout << "\tSubtracting Numbers Without Overflow (" << +start << ", " << +decrement << ", " << steps << ") = ";
    auto result = subtract_numbers<T>(start, decrement, steps, &verification);
    get_output(verification, 'sub', +result);

    std::cout << "\tSubtracting Numbers With Overflow (" << +start << ", " << +decrement << ", " << (steps + 1) << ") = ";
    result = subtract_numbers<T>(start, decrement, steps + 1, &verification);
    get_output(verification, 'sub', +result);
}

void do_overflow_tests(const std::string& star_line)
{
    std::cout << std::endl << star_line << std::endl;
    std::cout << "*** Running Overflow Tests ***" << std::endl;
    std::cout << star_line << std::endl;

    // Testing C++ primative times see: https://www.geeksforgeeks.org/c-data-types/
    // signed integers
    test_overflow<char>();
    test_overflow<wchar_t>();
    test_overflow<short int>();
    test_overflow<int>();
    test_overflow<long>();
    test_overflow<long long>();

    // unsigned integers
    test_overflow<unsigned char>();
    test_overflow<unsigned short int>();
    test_overflow<unsigned int>();
    test_overflow<unsigned long>();
    test_overflow<unsigned long long>();

    // real numbers
    test_overflow<float>();
    test_overflow<double>();
    test_overflow<long double>();
}

void do_underflow_tests(const std::string& star_line)
{
    std::cout << std::endl << star_line << std::endl;
    std::cout << "*** Running Undeflow Tests ***" << std::endl;
    std::cout << star_line << std::endl;

    // Testing C++ primative times see: https://www.geeksforgeeks.org/c-data-types/
    // signed integers
    test_underflow<char>();
    test_underflow<wchar_t>();
    test_underflow<short int>();
    test_underflow<int>();
    test_underflow<long>();
    test_underflow<long long>();

    // unsigned integers
    test_underflow<unsigned char>();
    test_underflow<unsigned short int>();
    test_underflow<unsigned int>();
    test_underflow<unsigned long>();
    test_underflow<unsigned long long>();

    // real numbers
    test_underflow<float>();
    test_underflow<double>();
    test_underflow<long double>();
}

// <summary>
// Entry point into the application
// <returns>0 when complete</returns>
int main()
{
    //  create a string of "*" to use in the console
    const std::string star_line = std::string(50, '*');

    std::cout << "Starting Numeric Underflow / Overflow Tests!" << std::endl;

    // run the overflow tests
    do_overflow_tests(star_line);

    // run the underflow tests
    do_underflow_tests(star_line);

    std::cout << std::endl << "All Numeric Underflow / Overflow Tests Complete!" << std::endl;

    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu
