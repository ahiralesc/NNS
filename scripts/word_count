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
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied    .
# See the License for the specific language governing permissions and
# limitations under the License.


#########################################################################    ##
#
# Author: GOMEZ BEUTELSPACHER ROCCO and KUANG ZENG FIONA
# Email : rocco.gomez@cetys.edu.mx and fiona.kuang@cetys.edu.mx
#
#########################################################################    ##

if [ -f count.txt ];
then
	rm count.txt
fi

for fname in $(ls -AS $1); do
	if [[ $fname == *.txt  ||  $fname = *.TXT ]];
	then
		wc -c $1$fname >> count.txt
	fi
done

# sort and extract the maximum value
sort count.txt | head -1 | awk '{print $1}'

# rm the temporary file
rm count.txt

