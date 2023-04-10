#!/bin/bash

# Copyright Hash-LSH Authors. All Rights Reserved.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#    http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.


###########################################################################
#
# Author: Adan Hirales Carbajal
# Email : adan.hirales@cetys.mx
#
###########################################################################


# Evaluate if arguments are given
[ $# -eq 0 ] && { echo "Usage: $0 path"; exit 1; }

# Evaluate if the argument corresponds to a directory
if [ -d "$1" ]; then
	# Scan the corpora subdirectories and concatenate all TXT files
	for k in $(ls -l $1 | grep '^d' | awk  '{OFS=" "; print $9; }'); do
		
		source_file=$1$k/*.txt
		target_file=$k'_corpora.txt'
		
		if [ -f /tmp/$target_file ]; then
			echo "Removing ${target_file} from /tmp"
			rm /tmp/$target_file
		fi

		echo "Concatenating ${k} files"
		cat $source_file | tr [:upper:] [:lower:] | \
		grep -oE '[[:alnum:],[:punct:]]{1,}' | sort --dictionary-order | \
		uniq -i > /tmp/$target_file
	done
fi
