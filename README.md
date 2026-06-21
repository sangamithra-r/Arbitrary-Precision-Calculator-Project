# Arbitrary Precision Calculator (APC)

The Arbitrary Precision Calculator (APC) is a C-based command-line application that performs arithmetic operations on integers of arbitrary length. Unlike standard C data types such as int, long, and long long, which have fixed storage limits, APC can handle numbers of virtually unlimited size using a Doubly Linked List representation.
Each digit of a number is stored in a separate node, allowing calculations to be performed digit-by-digit without overflow.

## Supported Operations 
✅ Addition (+)
✅ Subtraction (-)
✅ Multiplication (x / X)
✅ Division (/)
✅ Modulus (%)
✅ Power (^)

## Problem Statement
Standard data types in C have limited storage capacity and cannot accurately represent very large numbers. Overflow occurs when the value exceeds the maximum range supported by the data type.
This project overcomes that limitation by storing each digit of a number in a Doubly Linked List and performing arithmetic operations digit-by-digit, similar to manual calculations.

## Data Structure Used

### Doubly Linked List

Each digit of a number is stored in a separate node.

Example :
 Number : 1 2 3 4 5
 NULL <-- [1] <--> [2] <--> [3] <--> [4] <--> [5] --> NULL
          ^                                    ^
          head                                tail

* head points to the Most Significant Digit.
* tail points to the Least Significant Digit.
* Arithmetic operations begin from the tail.

Command : ./a.out operand1 operator operand2


## Project Structure

APC/ 
│ 
├── main.c 
├── apc.c 
├── add.c 
├── sub.c 
├── mul.c 
├── div.c 
├── mod.c 
├── pow.c 
├── apc.h 
├── Makefile 
├── README.md 


## Compilation

### Using Makefile
make

### Manual Compilation
gcc *.c -o a.out


## Sample Executions

### Addition

$ ./a.out 123 + 456 
579

### Subtraction

$ ./a.out 1000 - 1 
999

### Multiplication

$ ./a.out 123 x 456 
56088

### Division

$ ./a.out 12345 / 123 
100

### Modulus

$ ./a.out 123 % 12 
3

### Power

$ ./a.out 2 ^ 10 
1024


## Skills Demonstrated

* C Programming
* Data Structures
* Doubly Linked Lists
* Dynamic Memory Allocation
* Pointer Manipulation
* Command Line Argument Processing
* Modular Programming
* Algorithm Design
* Big Integer Arithmetic


## Author
Sangamithra R
Electronics & Communication Engineering Graduate

Interested in Embedded Systems, Firmware Development, C Programming, and Data Structures.

GitHub: https://github.com/sangamithra-r
