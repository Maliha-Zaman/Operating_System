#!/bin/bash

read -p "First Name: " first_name
read -p "Middle Name: " middle_name
read -p "Last Name: " last_name

read -p "Hi $last_name, do you want me to display your full name? [y|n] " choice

if [[ "$choice" == "y" || "$choice" == "Y" ]]; then
    echo "Your Full Name is $first_name $middle_name $last_name."
else
    echo "Thank you, $last_name, for your time."
fi

