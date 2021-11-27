#!/usr/bin/bash
FILENAME=${1}

#CSV HEADER
echo "nthread, time" > "${FILENAME}"

#Values
make -s -j CFLAGS+="-D_NOLOGS" producers_consumers
for NTHREAD in 1 2 4 7 8
do
  #CSV DATA
  /usr/bin/time -f "$((NTHREAD+NTHREAD)), %e" ./producers_consumers/producers_consumers.o ${NTHREAD} ${NTHREAD} 2>& 1|tail -n 1 >> "${FILENAME}"
done

make -s -j clean #Clean Values