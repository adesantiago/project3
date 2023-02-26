//
//  main.cpp
//  proj3_905327084
//
//  Created by Alex De Santiago on 7/11/21.
//

#include <iostream>
#include <string>
#include <cassert>

using namespace std;

int extractNumber(string elevatorstring, size_t& index)
{
    // track the integer value found
    int quantity(0);
    bool foundADigit = false;
    while (index < elevatorstring.size())
    {
        char c = elevatorstring.at(index);
        // we are only interested in digit characters 0-9
        if (c >= '0' && c <= '9')
        {
            foundADigit = true;
            // extract one digit and add it to the cumulative
            // value held in quantity
            int digit = c - '0';
            quantity = quantity * 10 + digit;
            index = index + 1;
        }
        else
        {
            break;
        }
    }
    if (!foundADigit)
    {
        quantity = -1;
    }
    return quantity;
}

bool isValidElevatorString(string elevatorstring)
{
    if (elevatorstring == "" || elevatorstring[0] != 'M' || elevatorstring == "M")
        return false;
    
    int open_count = 0;
    int close_count = 1;
    int population = 0;
    int incr = 0;
    char letter;
    for (size_t k = 1; k < elevatorstring.size(); k++) //if there are only m and integer values for floors
    {
        letter = elevatorstring[k];
        //takes care of open/close variable counters
        if(letter == 'O')
        {
            open_count++;
        }
        else if (letter == 'C')
        {
            close_count++;
        }
        //takes care of passenger processing
        incr = 0;
        if (elevatorstring[k-1] == '+')
        {
            if (elevatorstring[k] == '-')
                return false;
            int num = extractNumber(elevatorstring, k);
            if (num != -1)
            {
                incr += num;
            }
        }
        else if(elevatorstring[k-1] == '-')
        {
            if (elevatorstring[k] == '+')
                return false;
            int num = extractNumber(elevatorstring, k);
            if (num != -1)
            {
                incr -= num;
            }
        }
        population += incr;
        if(population<0)
        {
            cerr<<"pop negative \n";
            return false;
        }
        
        //check validity
        if (!isdigit(letter) && letter != 'O' && letter != 'C' && letter != '+' && letter != '-' && letter != 'M')
        {
            // first part of string must be m to be valid and it allows integers and an opening of doors
            // and closing of the doors and the addition and subtraction of passengers and another m in the string
            cerr<<"char invalid: "<< letter <<"\n";
            return false;
        }
        else if (elevatorstring[k-1] == 'M' && !isdigit(letter))
        {
            cerr<<"M has no floor num \n";
            return false; // if the first part of the string isnt m & followed by a number it is false ##1
        }
        else if(abs(close_count-open_count)>1) // (open_count>close_count)
        {
            cerr<<"close/open too many times in a row \n";
            return false;
        } //prevents open close mult times in succession
        else if(letter == 'M'){
            if(open_count == close_count){
                return true;
            }
        }
    }
    if (open_count > close_count)
    {
        return false;
    }
    
    return true;
}

bool doorsOpen(string elevatorstring)
{
    if (!isValidElevatorString(elevatorstring))
        return false;
    int open_count = 0;
    int close_count = 1;
    for (int k = 0; k < elevatorstring.size(); k++)
    {
        if (elevatorstring[k] == 'C')
        {
            close_count++;
        }
        else if(elevatorstring[k] == 'O')
        {
            open_count++;
        }
    }
    if (open_count == close_count)
        return true;
    return false;
}

int endingPassengers(string elevatorstring)
{
    if (!isValidElevatorString(elevatorstring))
        return -1;
    int population = 0;
        for (size_t k = 0; k < elevatorstring.size(); k++)
        {
            int incr = 0;
            if (elevatorstring[k-1] == '+')
    {
        int num = extractNumber(elevatorstring, k);
        if (num != -1)
        {
            incr += num; ///replace to pop
        }
    }
    else if(elevatorstring[k-1] == '-')
    {
        int num = extractNumber(elevatorstring, k);
        if (num != -1)
        {
            incr -= num;
        }
    }
    population += incr;
    if(population<0)
    {
        cerr<<"pop negative \n";
        return -1;
    }
        }
    return population;
}

int mostPassengers(string elevatorstring)
{
    if (!isValidElevatorString(elevatorstring))
            return -1;
        int population = 0;
    int maxpassengers = 0;
            for (size_t k = 0; k < elevatorstring.size(); k++)
            {
                int incr = 0;
                if (elevatorstring[k-1] == '+')
        {
            int num = extractNumber(elevatorstring, k);
            if (num != -1)
            {
                incr += num; ///replace to pop
            }
        }
        else if(elevatorstring[k-1] == '-')
        {
            int num = extractNumber(elevatorstring, k);
            if (num != -1)
            {
                incr -= num;
            }
        }
                
        population += incr;
                if (population > maxpassengers)
                    maxpassengers = population;
        if(population<0)
        {
            cerr<<"pop negative \n";
            return -1;
        }
            }
        return maxpassengers;
}

int endingFloor(string elevatorstring)
{
    if (!isValidElevatorString(elevatorstring))
            return -1;
    int floornumber = 0;
    for (size_t k = 1; k < elevatorstring.size(); k++)
    {
        if (elevatorstring[k-1] == 'M')
        {
            floornumber = extractNumber(elevatorstring, k);
        }
    }
    return floornumber;
}

int highestFloor(string elevatorstring)
{
    if (!isValidElevatorString(elevatorstring))
            return -1;
    int floornumber = 0;
    int highestfloor = 0;
    for (size_t k = 1; k < elevatorstring.size(); k++)
    {
        if (elevatorstring[k-1] == 'M')
        floornumber = extractNumber(elevatorstring, k);
        if (floornumber > highestfloor)
            highestfloor = floornumber;
    }
    return highestfloor;
}






int main()
{
    //valid strings
    string str = "M2O";
    assert(isValidElevatorString(str));
    assert(doorsOpen(str));
    str = "M12";
    assert(isValidElevatorString(str));
    str = "M12O+1-0C";
    assert(isValidElevatorString(str));
    assert(endingPassengers(str) == 1);
    str = "M12O+1CM3";
    assert(isValidElevatorString(str));
    str = "M1O+0004C";
    assert(isValidElevatorString(str));
    str = "M10M8M9";
    assert(isValidElevatorString(str));
    assert(endingFloor(str) == 9);
    assert(highestFloor(str) == 10);
    str = "M3O+3COCOCM2";
    assert(isValidElevatorString(str));
    assert(endingFloor(str) == 2);
    assert(endingPassengers(str) == 3);
    str = "M2OO+2";
    assert(!isValidElevatorString(str));
    str = "M2OO+2";
    assert(!isValidElevatorString(str));
    str = "M2OO+2";
    assert(!isValidElevatorString(str));
    str = "M3O+4CM2O-1C";
    assert(isValidElevatorString(str));
    assert(mostPassengers(str) == 4);
    assert(highestFloor(str) == 3);
    
    cout << "All Tests Passed Thottie :*" << endl;
}
