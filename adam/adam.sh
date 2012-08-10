#/bin/bash
gcc -g -Wall -Wextra -pedantic adam.c -o adam
./adam | while read line; do
  echo -n "Testing '$line == 24'... "
  if [ $(echo "$line == 24" | bc -l) -eq 1 ];
    then echo "SUCCESS" && exit
    else echo "FAILURE"
  fi
done
rm adam
