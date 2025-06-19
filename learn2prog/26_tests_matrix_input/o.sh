#!/bin/bash
FILENAME="ff.txt"
{
    for i in {1..9}; do
	echo "0123456789"
    done

    printf '01234\xff6789\n'
} > "ff.txt"
