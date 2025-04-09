#!/bin/bash

amount=(2 3 4 5 6 7 8 9 10 11 14 15 16 17 18 19 20 21 22 23 25 26 27 28 29 30 31 32 33)
comparison_limit=(1 3 5 7 10 13 16 19 22 26 38 42 46 50 54 58 62 66 71 76 86 91 96 101 106 111 116 121 126)

# Linux_command: shuf -i 1-10000 -n "${amount[$i]}" | tr "\n" " "
# OS_command: jot -r "${amount[$i]}" 1 10000 | tr '\n' ' '


i=0
while (($i < 29))
do
	echo -n "Testing for ${amount[$i]} numbers -> "
	limit_loop=100
	while (($limit_loop > 0))
	do
		generated_nums=$(shuf -i 1-10000 -n "${amount[$i]}" | tr "\n" " ")
		# generated_nums=$(jot -r "${amount[$i]}" 1 10000 | tr '\n' ' ')
		output=$(./PmergeMe $generated_nums)
		comparisons=$(echo "$output" | awk '/Comparisons:/ {for(i=1;i<=NF;i++) if ($i ~ /^[0-9]+$/) {print $i; exit}}')
		after_sequence=$(echo "$output" | awk '/After:/ {for(i=1;i<=NF;i++) if ($i ~ /^[0-9]+$/) printf $i" "; print ""}')
		sorted=$(echo $generated_nums | tr ' ' '\n' | sort -n | tr '\n' ' ')
		# if [ "$after_sequence" != "$sorted" ];
		# then
		# 	size_after=$(echo "$after_sequence" | wc -w)
		# 	size_sorted=$(echo "$sorted" | wc -w)
		# 	if [ "$size_after" -ne "$size_sorted" ];
		# 	then
		# 		echo "Error: The size of 'After' does not match initial input"
		# 		echo "After: "
		# 		echo "$after_sequence"
		# 		echo "Input: "
		# 		echo "$generated_nums"
		# 		exit 1
		# 	fi
		# 	echo "Error: Array not sorted"
		# 	exit 1
		# fi
		if [ "$comparisons" -gt "${comparison_limit[$i]}" ];
		then
			echo "Error: comparison number above the limit"
			echo "Max limit for ${amount[$i]} numbers: ${comparison_limit[$i]}"
			echo "Your comparison number: $comparisons"
			echo "Tested sequence: "
			echo "$generated_nums"
			exit 1
		fi
		((limit_loop--))
	done
	echo "OK"
	((i++))
done



# i=400
# while (($i <= 5000))
# do
# 	echo -n "Testing for $i numbers -> "
# 	limit_loop=10
# 	while (($limit_loop > 0))
# 	do
# 		generated_nums=$(shuf -i 1-10000 -n "$i" | tr "\n" " ")
# 		# generated_nums=$(jot -r "$i" 1 10000 | tr '\n' ' ')
# 		output=$(./PmergeMe $generated_nums)
# 		after_sequence=$(echo "$output" | awk '/After:/ {for(i=1;i<=NF;i++) if ($i ~ /^[0-9]+$/) printf $i" "; print ""}')
# 		sorted=$(echo $generated_nums | tr ' ' '\n' | sort -n | tr '\n' ' ')
# 		if [ "$after_sequence" != "$sorted" ];
# 		then
# 			size_after=$(echo "$after_sequence" | wc -w)
# 			size_sorted=$(echo "$sorted" | wc -w)
# 			if [ "$size_after" -ne "$size_sorted" ];
# 			then
# 				echo "Error: The size of 'After' does not match initial input"
# 				echo "After: "
# 				echo "$after_sequence"
# 				echo "Input: "
# 				echo "$generated_nums"
# 				exit 1
# 			fi
# 			echo "Error: Array not sorted"
# 			exit 1
# 		fi
# 		((limit_loop--))
# 	done
# 	echo "OK"
# 	((i++))
# done
