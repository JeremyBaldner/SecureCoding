// Exceptions.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include <stdexcept>

bool do_even_more_custom_application_logic()
{
    // Throw standard exception
    int* array = new int[99999999999999999];

    std::cout << "Running Even More Custom Application Logic." << std::endl;

    return true;
}
void do_custom_application_logic()
{
    std::cout << "Running Custom Application Logic." << std::endl;
    try
    {
        if (do_even_more_custom_application_logic())
        {
            std::cout << "Even More Custom Application Logic Succeeded." << std::endl;
        }
    }
    catch (std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }

    // Throw a custom exception derived from std::exception and catch it explictly in main
    throw std::runtime_error("Runtime Error");

    std::cout << "Leaving Custom Application Logic." << std::endl;

}

float divide(float num, float den)
{
    // Throw custom exception.
    if (den == 0) 
    {
        throw 0;
    }
    return (num / den);
}

void do_division() noexcept
{
    float numerator = 10.0f;
    float denominator = 0;

    try
    {
        auto result = divide(numerator, denominator);
        std::cout << "divide(" << numerator << ", " << denominator << ") = " << result << std::endl;
    }
    catch (int e)
    {
        std::cout << "Custom divide by " << e << " error" << std::endl;
    }
}

// Exception handlers that catch (in this order):
//  1. your custom exception,
//  2. std::exception,
//  3. uncaught exception that wraps the whole main function, and displays a message to the console.

int main()
{
    try
    {
    std::cout << "Exceptions Tests!" << std::endl;

        do_division();
        do_custom_application_logic();
    }
    catch (...)
    {
        std::cout << "All exceptions caught" << std::endl;
    }
}
