#!/usr/bin/bash
FILENAME=${1}

#CSV HEADER
echo "nThread,iteration,time" > "${FILENAME}"

#Values
make -s -j CFLAGS+="-D_NOLOGS" philosophers
for PHILOSOPHERS in 2 4 6 8 16
do
  #CSV DATA
  for i in {1..5}
  do
    iTime=$(/usr/bin/time -f "%e" ./philosophers/philosophers.o "$PHILOSOPHERS" 2>&1 | tail -n 1)
    echo "$PHILOSOPHERS","$i","$iTime" >> "$FILENAME"
  done
done

make -s -j clean #Clean Values