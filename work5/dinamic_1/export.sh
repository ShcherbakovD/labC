#!/bin/bash
echo $LD_LIBRARY_PATH;
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:`pwd`
ldd wr5_2;
echo "";echo "Работа wr5_2 : ";echo "";
./wr5_2
