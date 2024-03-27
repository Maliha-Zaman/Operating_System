#!/bin/bash
if [ "$#" -ne 2 ]; then
    echo "Usage: $0 <lower_range> <upper_range>"
    exit 1
fi

lower_range="$1"
upper_range="$2"

is_prime() {
    local num=$1
    if [ "$num" -le 1 ]; then
        return 1
    fi
    for ((i = 2; i * i <= num; i++)); do
        if [ "$((num % i))" -eq 0 ]; then
            return 1
        fi
    done
    return 0
}


if ! [[ "$lower_range" =~ ^-?[0-9]+$ && "$upper_range" =~ ^-?[0-9]+$ && "$lower_range" -le "$upper_range" ]]; then
    echo "Invalid inputs"
    exit 1
fi


echo "LIst of prime numbers"
for ((num = lower_range; num <= upper_range; num++)); do
    if is_prime "$num"; then
        echo "$num"
    fi
done

echo "List of non-prime numbers"
for ((num = lower_range; num <= upper_range; num++)); do
    if ! is_prime "$num"; then
        echo "$num"
    fi
done
