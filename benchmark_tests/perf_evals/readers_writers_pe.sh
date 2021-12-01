#!/usr/bin/bash
FILENAME=${1}

#CSV HEADER
echo "nThread,iteration,time" >"${FILENAME}"

#Values
make -s -j CFLAGS+="-D_NOLOGS" readers_writers
for NTHREAD in 1 2 4 7 8; do
  #CSV DATA
  for i in {1..5}; do
    iTime=$(/usr/bin/time -f "%e" ./readers_writers/readers_writers.o ${NTHREAD} ${NTHREAD} 2>&1 | tail -n 1)
    echo $((NTHREAD * 2)),"$i","$iTime" >>"$FILENAME"
  done
done

make -s -j clean #Clean Values
