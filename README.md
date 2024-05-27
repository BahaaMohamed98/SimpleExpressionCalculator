# Simple Expression Calculator

This is a simple expression calculator that supports floating-point numbers and basic arithmetic operations. It converts infix expressions to postfix notation and then evaluates them. The calculator currently supports the following operators:

- `^` (exponentiation)
- `*` (multiplication)
- `/` (division)
- `+` (addition)
- `-` (subtraction)

## Features

- **Supports Floating-point Numbers**: The calculator can handle numbers with decimal points.
- **Basic Arithmetic Operations**: You can perform exponentiation, multiplication, division, addition, and subtraction.
- **Infix to Postfix Conversion**: Converts infix expressions (human-readable form) to postfix notation (for easier evaluation).
- **Simple and Extensible**: Designed to be easy to understand and modify. Future plans include adding support for negative numbers and brackets.

## Usage

1. Clone the repository to your local machine.
2. Compile the code using a C++ compiler.
3. Run the executable and enter an expression to calculate.

### Example

Valid operators: [^, *, /, +, -]

Enter an expression to calculate: 3.5 + 2.1 * 4 - 1.2 / 3

`3.5 + 2.1 * 4 - 1.2 / 3 = 11.5`
