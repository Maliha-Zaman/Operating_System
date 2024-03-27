#!/bin/bash

read -p "Enter your password: " user_password

length_valid=0
alphabet_valid=0
number_valid=0
uppercase_valid=0
lowercase_valid=0

if [ ${#user_password} -ge 8 ]; then
    length_valid=1
fi

if [[ "$user_password" =~ [A-Za-z] && "$user_password" =~ [0-9] ]]; then
    alphabet_valid=1
    number_valid=1
fi

if [[ "$user_password" =~ [A-Z] && "$user_password" =~ [a-z] ]]; then
    uppercase_valid=1
    lowercase_valid=1
fi

if [ $length_valid -eq 0 ]; then
    echo "Weak Password -> Password length should have at least 8 characters."
fi

if [ $number_valid -eq 0 ]; then
    echo "Weak Password -> Should use a number."
fi

if [ $uppercase_valid -eq 0 ]; then
    echo "Weak Password -> Should include an upper-case letter."
fi

if [ $lowercase_valid -eq 0 ]; then
    echo "Weak Password -> Should include a lower-case letter."
fi

if [ $length_valid -eq 1 ] && [ $alphabet_valid -eq 1 ] && [ $number_valid -eq 1 ] && [ $uppercase_valid -eq 1 ] && [ $lowercase_valid -eq 1 ]; then
    echo "Strong Password."
fi

