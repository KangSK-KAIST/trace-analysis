#!/bin/bash

build/main_snia /mnt/disk0/snia_refined/MSProduction/24Hour_RADIUS.total.csv.orig 16384 > results-16G/24Hour_RADIUS &
build/main_snia /mnt/disk0/snia_refined/MSProduction/MSNFS.total.csv.orig 16384 > results-16G/MSNFS &
build/main_snia /mnt/disk0/snia_refined/MSProduction/24Hour_RADIUS_SQL.total.csv.orig 16384 > results-16G/24Hour_RADIUS_SQL &
build/main_snia /mnt/disk0/snia_refined/MSProduction/BuildServer.total.csv.orig 16384 > results-16G/BuildServer &
build/main_snia /mnt/disk0/snia_refined/MSProduction/CFS.total.csv.orig 16384 > results-16G/CFS &
build/main_snia /mnt/disk0/snia_refined/MSProduction/DisplayAdsPayload.total.csv.orig 16384 > results-16G/DisplayAdsPayload &
build/main_snia /mnt/disk0/snia_refined/MSProduction/DevDivRelease.total.csv.orig 16384 > results-16G/DevDivRelease &
build/main_snia /mnt/disk0/snia_refined/MSEnterprise/Exchange.total.csv.orig 16384 > results-16G/Exchange &
build/main_snia /mnt/disk0/snia_refined/MSRCambridge/prn.total.csv.orig 16384 > results-16G/prn &
build/main_snia /mnt/disk0/snia_refined/MSRCambridge/src1.total.csv.orig 16384 > results-16G/src1 &
build/main_snia /mnt/disk0/snia_refined/MSRCambridge/src2.total.csv.orig 16384 > results-16G/src2 &
build/main_snia /mnt/disk0/snia_refined/MSRCambridge/ts.total.csv.orig 16384 > results-16G/ts &
build/main_snia /mnt/disk0/snia_refined/MSRCambridge/wdev.total.csv.orig 16384 > results-16G/wdev &
build/main_snia /mnt/disk0/snia_refined/FIU-srcmap/ikki.total.csv.orig 16384 > results-16G/ikki &
build/main_snia /mnt/disk0/snia_refined/FIU-srcmap/webmail+online.total.csv.orig 16384 > results-16G/ikki &

build/main_ali /mnt/disk0/alibaba_block_traces_2020/dev49/trace.csv 16384 > results-16G/dev49 &
build/main_ali /mnt/disk0/alibaba_block_traces_2020/dev95/trace.csv 16384 > results-16G/dev95 &
build/main_ali /mnt/disk0/alibaba_block_traces_2020/dev125/trace.csv 16384 > results-16G/dev125 &
build/main_ali /mnt/disk0/alibaba_block_traces_2020/dev308/trace.csv 16384 > results-16G/dev308 &
build/main_ali /mnt/disk0/alibaba_block_traces_2020/dev355/trace.csv 16384 > results-16G/dev355 &
build/main_ali /mnt/disk0/alibaba_block_traces_2020/dev373/trace.csv 16384 > results-16G/dev373 &
build/main_ali /mnt/disk0/alibaba_block_traces_2020/dev454/trace.csv 16384 > results-16G/dev454 &
build/main_ali /mnt/disk0/alibaba_block_traces_2020/dev457/trace.csv 16384 > results-16G/dev457 &
build/main_ali /mnt/disk0/alibaba_block_traces_2020/dev467/trace.csv 16384 > results-16G/dev467 &
build/main_ali /mnt/disk0/alibaba_block_traces_2020/dev477/trace.csv 16384 > results-16G/dev477 &
build/main_ali /mnt/disk0/alibaba_block_traces_2020/dev550/trace.csv 16384 > results-16G/dev550 &
build/main_ali /mnt/disk0/alibaba_block_traces_2020/dev554/trace.csv 16384 > results-16G/dev554 &
build/main_ali /mnt/disk0/alibaba_block_traces_2020/dev618/trace.csv 16384 > results-16G/dev618 &
build/main_ali /mnt/disk0/alibaba_block_traces_2020/dev667/trace.csv 16384 > results-16G/dev667 &
build/main_ali /mnt/disk0/alibaba_block_traces_2020/dev767/trace.csv 16384 > results-16G/dev767 &
build/main_ali /mnt/disk0/alibaba_block_traces_2020/dev770/trace.csv 16384 > results-16G/dev770 &
