#!/usr/bin/bash
FILENAME=${1}

if [ -f "$FILENAME" ]; then
    echo "$FILENAME" found
else
  echo "$FILENAME" does not exist. Creating a blank csv
  mkdir -p "$(dirname "$FILENAME")"
  touch "$(dirname "$FILENAME")"/"$(basename "$FILENAME")"
fi

# Pick the number of physical threads and DON'T multiply by 2, because whe use the variable twice
CORENUMBER=$(grep "cpu cores" /proc/cpuinfo | uniq| awk '{print $4}')

#CSV HEADER
echo "nThread,iteration,time" >"${FILENAME}"

#Values
make -s -j CFLAGS+="-D_NOLOGS" readers_writers_posix
for NTHREAD in $(eval echo "{1..$CORENUMBER}"); do
  #CSV DATA
  for i in {1..5}; do
    iTime=$(/usr/bin/time -f "%e" ./part1/readers_writers/readers_writers_posix.o "${NTHREAD}" "${NTHREAD}" 2>&1 | tail -n 1)
    echo $(("$NTHREAD" * 2)),"$i","$iTime" >>"$FILENAME"
  done
done

make -s -j clean #Clean Values
