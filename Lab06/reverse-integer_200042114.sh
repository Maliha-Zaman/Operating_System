if [[ $1 == "-h" ]]; then
  echo "$0 prints number in reverse order,each in a new line.
  -Syntax: $0 <num_1> <num_2>..<num_n>
  --parameter 1 <num_1>: First number to be printed in reverse
  --parameter 2 <num_2>: Second number to be printed in reverse
  --"
  exit 1
fi
if [[ $# -eq 0 ]]; then
    echo "please providecorrect input in the below format- usage: $0 number"
    exit 1
fi

for num in "$@"; do
    reversed=""
    length=${#num}

    for (( i=$length-1; i>=0; i-- )); do
        reversed="$reversed${num:i:1}"
    done

    echo "Reverse of $num is $reversed"
done
