#!/bin/bash

if [[ $1 == "-h" ]]; then
  echo "$0 prints the string rerpresentation of the floating point quotient of 2 numbers that are not divisible by one another, up to n-significant digits. -syntax: $0 <number_1> <number_2> <number_3>
  -- parameter 1 <number_1>: Dividend
  -- parameter 2<number2>: Divisor(must be greater than 0)
  -- parameter 3 <numbner_3> number of significant digits after the decimal points"
  exit 1
fi

if [ $# -ne 3 ]; then
  echo "Syntax Error!! Syntax: $0 <number_1> <number_2> <number_3> for more info type: $0 -h"
  exit 1
fi

Dividend="$1"
Divisor="$2"
significant_digits="$3"

if [ "$Divisor" -eq 0 ]; then
  echo "Division by zero error for more info type $0 -h."
  exit 1
fi

result=$(echo "scale=$significant_digits; $Dividend / $Divisor" | bc -l)

echo "Result of $Dividend / $Divisor with $significant_digits significant digits:"
echo "$result"

