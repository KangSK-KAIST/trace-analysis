#!/bin/bash

rm -r results

build/main_snia /mnt/disk0/snia_refined/MSProduction/24Hour_RADIUS_SQL.total.csv.orig 4096 > results/24Hour_RADIUS_SQL &
build/main_snia /mnt/disk0/snia_refined/MSProduction/BuildServer.total.csv.orig 4096 > results/BuildServer &
build/main_snia /mnt/disk0/snia_refined/MSProduction/CFS.total.csv.orig 4096 > results/CFS &
build/main_snia /mnt/disk0/snia_refined/MSProduction/DisplayAdsPayload.total.csv.orig 4096 > results/DisplayAdsPayload &
build/main_snia /mnt/disk0/snia_refined/MSProduction/DevDivRelease.total.csv.orig 4096 > results/DevDivRelease &
build/main_snia /mnt/disk0/snia_refined/MSEnterprise/Exchange.total.csv.orig 4096 > results/Exchange &
build/main_snia /mnt/disk0/snia_refined/MSProduction/MSNFS.total.csv.orig 4096 > results/MSNFS &
build/main_snia /mnt/disk0/snia_refined/MSRCambridge/prn.total.csv.orig 4096 > results/prn &
build/main_snia /mnt/disk0/snia_refined/MSRCambridge/src1.total.csv.orig 4096 > results/src1 &
build/main_snia /mnt/disk0/snia_refined/MSRCambridge/src2.total.csv.orig 4096 > results/src2 &
build/main_snia /mnt/disk0/snia_refined/MSRCambridge/ts.total.csv.orig 4096 > results/ts &
build/main_snia /mnt/disk0/snia_refined/MSRCambridge/wdev.total.csv.orig 4096 > results/wdev &

build/main_ali /mnt/disk0/alibaba_block_traces_2020/dev3/trace.csv 4096 > results/dev3 &
build/main_ali /mnt/disk0/alibaba_block_traces_2020/dev64/trace.csv 4096 > results/dev64 &
build/main_ali /mnt/disk0/alibaba_block_traces_2020/dev125/trace.csv 4096 > results/dev125 &
build/main_ali /mnt/disk0/alibaba_block_traces_2020/dev550/trace.csv 4096 > results/dev550 &
build/main_ali /mnt/disk0/alibaba_block_traces_2020/dev667/trace.csv 4096 > results/dev667 &
build/main_ali /mnt/disk0/alibaba_block_traces_2020/dev669/trace.csv 4096 > results/dev669 &
build/main_ali /mnt/disk0/alibaba_block_traces_2020/dev726/trace.csv 4096 > results/dev726 &
build/main_ali /mnt/disk0/alibaba_block_traces_2020/dev743/trace.csv 4096 > results/dev743 &
build/main_ali /mnt/disk0/alibaba_block_traces_2020/dev767/trace.csv 4096 > results/dev767 &
build/main_ali /mnt/disk0/alibaba_block_traces_2020/dev852/trace.csv 4096 > results/dev852 &
build/main_ali /mnt/disk0/alibaba_block_traces_2020/dev907/trace.csv 4096 > results/dev907 &
build/main_ali /mnt/disk0/alibaba_block_traces_2020/dev972/trace.csv 4096 > results/dev972