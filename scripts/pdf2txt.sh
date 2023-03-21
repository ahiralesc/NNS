#/bin/bash

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
# Author: Anthony Hirales Ahuatzin
# Email : anthony.hirales@cetys.edu.mx
#
###########################################################################

# Get the file names from the source path

source_dir=$1  	# Source directory with PDFs
target_dir=$2		# Target directory where TXT files are to be stored

# If the target directory does not exist, create it.
if [ ! -f $target_dir ];
then
	mkdir $target_dir  # create the target directory
fi


for fname in $(ls -AS $source_dir); do
	if [[ $fname == *.pdf  ||  $fname = *.PDF ]];
	then
		source_fname=${source_dir:0:-1}/$fname
		target_fname=${target_dir:0:-1}/${fname:0:-4}.txt
		pdftotext -eol unix $source_fname $target_fname
		echo $target_fname
	fi
done
