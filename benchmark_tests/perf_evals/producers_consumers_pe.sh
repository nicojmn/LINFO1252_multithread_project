#!/usr/bin/bash
FILENAME=${1}

# Pick the number of physical threads and DON'T multiply by 2, because whe use the variable twice
CORENUMBER=$(grep "cpu cores" /proc/cpuinfo | uniq| awk '{print $4}')

#CSV HEADER
echo "nThread,iteration,time" >"${FILENAME}"

#Values
make -s -j CFLAGS+="-D_NOLOGS" producers_consumers_posix
for NTHREAD in $(eval echo "{1..$CORENUMBER}"); do
  #CSV DATA
  for i in {1..5}; do
    iTime=$(/usr/bin/time -f "%e" ./part1/producers_consumers/producers_consumers_posix.o "${NTHREAD}" "${NTHREAD}" 2>&1 | tail -n 1)
    echo $(("$NTHREAD" * 2)),"$i","$iTime" >>"$FILENAME"
  done
done

make -s -j clean #Clean Values
