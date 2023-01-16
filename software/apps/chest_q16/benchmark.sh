# Copyright 2022 ETH Zurich and University of Bologna.
# Licensed under the Apache License, Version 2.0, see LICENSE for details.
# SPDX-License-Identifier: Apache-2.0

# Author: Marco Bertuletti, ETH Zurich

#!/bin/bash
# Benchmark shell script

axis=0

APP="chest_q16"
DIR=$(dirname $(realpath “${BASH_SOURCE:-$0}”))
APP_DIR="$DIR/.."
HW_DIR="$DIR/../../../hardware"

echo $APP_DIR
echo $HW_DIR

for n_rx in 4 #8 16 32
do
    for n_tx in 32 #4 8 16 32
    do
        for n_sc in 512 1024 2048 4096 #4 8 16 32
        do
            echo "n_rx = $n_rx"
            echo "n_tx = $n_tx"
            #result_dir="$result_path/sc_${n_rx}_${n_tx}"

            echo "./data_chest_q16.py" -b $n_tx -l $n_rx -s $n_s
            "./data_chest_q16.py" -b $n_tx -l $n_rx -s $n_sc
            make $APP -C $APP_DIR
            app=$APP make simcvcs -C $HW_DIR
            make resultpath=results_che_sc trace -C $HW_DIR
        done
    done
done
