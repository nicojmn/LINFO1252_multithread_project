#!/usr/bin/bash
#Variables
NVALUES=${1}
FILENAME=${2}

#Titles
echo "nthread, time" > "${FILENAME}"

#Values
for NTHREAD in 1 2 4 8
do
	for ((i=0 ; ${NVALUES} - $i ; i++))
	do
		/usr/bin/time -f "${NTHREAD}, %e" make -s -j ${NTHREAD} 2>& 1|tail -n 1  >>  "${FILENAME}"
		make -s clean #Clean Values
	done
done
	