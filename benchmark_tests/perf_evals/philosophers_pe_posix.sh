#!/usr/bin/bash
FILENAME=${1}

if [ -f "$FILENAME" ]; then
    echo "$FILENAME" found
else
  echo "$FILENAME" does not exist. Creating a blank csv
  mkdir -p "$(dirname "$FILENAME")"
  touch "$(dirname "$FILENAME")"/"$(basename "$FILENAME")"
fi

# Pick the number of physical threads and multiply by 2
CORENUMBER=$(grep "cpu cores" /proc/cpuinfo | uniq| awk '{print $4}')
MAXTHREAD=$(("$CORENUMBER" * 2))

#CSV HEADER
echo "nThread,iteration,time" >"${FILENAME}"

#Values
make -s -j CFLAGS+="-D_NOLOGS" philosophers_posix
for PHILOSOPHERS in $(eval echo "{2..$MAXTHREAD}"); do
  #CSV DATA
  for i in {1..5}; do
    iTime=$(/usr/bin/time -f "%e" ./part1/philosophers/philosophers_posix.o "$PHILOSOPHERS" 2>&1 | tail -n 1)
    echo "$PHILOSOPHERS","$i","$iTime" >>"$FILENAME"
  done
done

make -s -j clean #Clean Values