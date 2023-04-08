#!/bin/bash

# Evaluate if arguments are given
[ $# -eq 0 ] && { echo "Usage: $0 path"; exit 1; }

# Evaluate if the argument corresponds to a directory
if [ -d "$1" ]
then
	# Concatenated file exists in /tmp, then delete it
	if [ -f /tmp/concatenated_txt.txt ] 
	then
		echo "Deleting /tmp_concant.txt"
		rm /tmp/concatenated_txt.txt
	fi

	# Scan the corpora subdirectories and concatenate all TXT files
	for k in $(ls -l $1 | grep '^d' | awk  '{OFS=" "; print $9; }'); do
		source_path=$1$k/*.txt
		target_file=$k"_concat.txt"
		cat $source_path >> /tmp/$target_file
	done
fi


#cat /tmp/concatenated_txt.txt | \
#	tr [[:upper:]] [[:lower]] | \
#	grep -oE '[[:alnum:],[:punct:]]{1,}' | \
#	uniq -i | sort --dictionary-order
