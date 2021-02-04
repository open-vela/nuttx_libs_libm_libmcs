#!/bin/bash
while IFS= read -r line; do
	A="$(cut -d' ' -f2 <<< $line)"
	B="$(cut -d' ' -f3 <<< $line)"
	echo "$A $B"
	head -n $B $A | tail -1 >> "$1.code"
done < "$1"