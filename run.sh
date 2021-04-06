#!/bin/bash

# Snia traces
# build/main_snia /mnt/disk0/snia_refined/MSProduction/24Hour_RADIUS.total.csv.orig 16384 > results-16Gsn/24Hour_RADIUS &
# build/main_snia /mnt/disk0/snia_refined/MSProduction/MSNFS.total.csv.orig 16384 > results-16Gsn/MSNFS &
# build/main_snia /mnt/disk0/snia_refined/MSProduction/24Hour_RADIUS_SQL.total.csv.orig 16384 > results-16Gsn/24Hour_RADIUS_SQL &
# build/main_snia /mnt/disk0/snia_refined/MSProduction/BuildServer.total.csv.orig 16384 > results-16Gsn/BuildServer &
# build/main_snia /mnt/disk0/snia_refined/MSProduction/CFS.total.csv.orig 16384 > results-16Gsn/CFS &
# build/main_snia /mnt/disk0/snia_refined/MSProduction/DisplayAdsPayload.total.csv.orig 16384 > results-16Gsn/DisplayAdsPayload &
# build/main_snia /mnt/disk0/snia_refined/MSProduction/DevDivRelease.total.csv.orig 16384 > results-16Gsn/DevDivRelease &
# build/main_snia /mnt/disk0/snia_refined/MSEnterprise/Exchange.total.csv.orig 16384 > results-16Gsn/Exchange &
# build/main_snia /mnt/disk0/snia_refined/MSRCambridge/prn.total.csv.orig 16384 > results-16Gsn/prn &
# build/main_snia /mnt/disk0/snia_refined/MSRCambridge/src1.total.csv.orig 16384 > results-16Gsn/src1 &
# build/main_snia /mnt/disk0/snia_refined/MSRCambridge/src2.total.csv.orig 16384 > results-16Gsn/src2 &
# build/main_snia /mnt/disk0/snia_refined/MSRCambridge/ts.total.csv.orig 16384 > results-16Gsn/ts &
# build/main_snia /mnt/disk0/snia_refined/MSRCambridge/wdev.total.csv.orig 16384 > results-16Gsn/wdev &
# build/main_snia /mnt/disk0/snia_refined/FIU-srcmap/ikki.total.csv.orig 16384 > results-16Gsn/ikki &
# build/main_snia /mnt/disk0/snia_refined/FIU-srcmap/webmail+online.total.csv.orig 16384 > results-16Gsn/ikki &

# Best traces accrording to trace log
build/main_ali /mnt/disk0/alibaba_block_traces_2020/dev42/trace.csv 16384 > results-16Ga/dev42 &
build/main_ali /mnt/disk0/alibaba_block_traces_2020/dev49/trace.csv 16384 > results-16Ga/dev49 &
build/main_ali /mnt/disk0/alibaba_block_traces_2020/dev64/trace.csv 16384 > results-16Ga/dev64 &
build/main_ali /mnt/disk0/alibaba_block_traces_2020/dev143/trace.csv 16384 > results-16Ga/dev143 &
build/main_ali /mnt/disk0/alibaba_block_traces_2020/dev206/trace.csv 16384 > results-16Ga/dev206 &
build/main_ali /mnt/disk0/alibaba_block_traces_2020/dev271/trace.csv 16384 > results-16Ga/dev271 &
build/main_ali /mnt/disk0/alibaba_block_traces_2020/dev308/trace.csv 16384 > results-16Ga/dev308 &
build/main_ali /mnt/disk0/alibaba_block_traces_2020/dev351/trace.csv 16384 > results-16Ga/dev351 &
build/main_ali /mnt/disk0/alibaba_block_traces_2020/dev355/trace.csv 16384 > results-16Ga/dev355 &
build/main_ali /mnt/disk0/alibaba_block_traces_2020/dev373/trace.csv 16384 > results-16Ga/dev373 &
build/main_ali /mnt/disk0/alibaba_block_traces_2020/dev477/trace.csv 16384 > results-16Ga/dev477 &
build/main_ali /mnt/disk0/alibaba_block_traces_2020/dev667/trace.csv 16384 > results-16Ga/dev667 &
build/main_ali /mnt/disk0/alibaba_block_traces_2020/dev669/trace.csv 16384 > results-16Ga/dev669 &
build/main_ali /mnt/disk0/alibaba_block_traces_2020/dev770/trace.csv 16384 > results-16Ga/dev770 &
build/main_ali /mnt/disk0/alibaba_block_traces_2020/dev841/trace.csv 16384 > results-16Ga/dev841 &
build/main_ali /mnt/disk0/alibaba_block_traces_2020/dev857/trace.csv 16384 > results-16Ga/dev857 &
build/main_ali /mnt/disk0/alibaba_block_traces_2020/dev875/trace.csv 16384 > results-16Ga/dev875 &
build/main_ali /mnt/disk0/alibaba_block_traces_2020/dev881/trace.csv 16384 > results-16Ga/dev881 &
build/main_ali /mnt/disk0/alibaba_block_traces_2020/dev884/trace.csv 16384 > results-16Ga/dev884 &
build/main_ali /mnt/disk0/alibaba_block_traces_2020/dev994/trace.csv 16384 > results-16Ga/dev994 &
build/main_ali /mnt/disk0/alibaba_block_traces_2020/dev998/trace.csv 16384 > results-16Ga/dev998 &

# Longest traces
# build/main_ali /mnt/disk0/alibaba_block_traces_2020/dev10/trace.csv 16384 > results-16Gl/dev10 &
# build/main_ali /mnt/disk0/alibaba_block_traces_2020/dev4/trace.csv 16384 > results-16Gl/dev4 &
# build/main_ali /mnt/disk0/alibaba_block_traces_2020/dev38/trace.csv 16384 > results-16Gl/dev38 &
# build/main_ali /mnt/disk0/alibaba_block_traces_2020/dev225/trace.csv 16384 > results-16Gl/dev225 &
# build/main_ali /mnt/disk0/alibaba_block_traces_2020/dev679/trace.csv 16384 > results-16Gl/dev679 &
# build/main_ali /mnt/disk0/alibaba_block_traces_2020/dev277/trace.csv 16384 > results-16Gl/dev277 &
# build/main_ali /mnt/disk0/alibaba_block_traces_2020/dev124/trace.csv 16384 > results-16Gl/dev124 &
# build/main_ali /mnt/disk0/alibaba_block_traces_2020/dev740/trace.csv 16384 > results-16Gl/dev740 &
# build/main_ali /mnt/disk0/alibaba_block_traces_2020/dev206/trace.csv 16384 > results-16Gl/dev206
# build/main_ali /mnt/disk0/alibaba_block_traces_2020/dev144/trace.csv 16384 > results-16Gl/dev144 &
# build/main_ali /mnt/disk0/alibaba_block_traces_2020/dev58/trace.csv 16384 > results-16Gl/dev58 &
# build/main_ali /mnt/disk0/alibaba_block_traces_2020/dev79/trace.csv 16384 > results-16Gl/dev79 &
# build/main_ali /mnt/disk0/alibaba_block_traces_2020/dev177/trace.csv 16384 > results-16Gl/dev177 &
# build/main_ali /mnt/disk0/alibaba_block_traces_2020/dev141/trace.csv 16384 > results-16Gl/dev141 &
# build/main_ali /mnt/disk0/alibaba_block_traces_2020/dev107/trace.csv 16384 > results-16Gl/dev107 &
# build/main_ali /mnt/disk0/alibaba_block_traces_2020/dev178/trace.csv 16384 > results-16Gl/dev178 &
# build/main_ali /mnt/disk0/alibaba_block_traces_2020/dev804/trace.csv 16384 > results-16Gl/dev804
# build/main_ali /mnt/disk0/alibaba_block_traces_2020/dev52/trace.csv 16384 > results-16Gl/dev52 &
# build/main_ali /mnt/disk0/alibaba_block_traces_2020/dev40/trace.csv 16384 > results-16Gl/dev40 &
# build/main_ali /mnt/disk0/alibaba_block_traces_2020/dev7/trace.csv 16384 > results-16Gl/dev7 &
# build/main_ali /mnt/disk0/alibaba_block_traces_2020/dev121/trace.csv 16384 > results-16Gl/dev121 &
# build/main_ali /mnt/disk0/alibaba_block_traces_2020/dev810/trace.csv 16384 > results-16Gl/dev810 &
# build/main_ali /mnt/disk0/alibaba_block_traces_2020/dev32/trace.csv 16384 > results-16Gl/dev32 &
# build/main_ali /mnt/disk0/alibaba_block_traces_2020/dev188/trace.csv 16384 > results-16Gl/dev188 &
# build/main_ali /mnt/disk0/alibaba_block_traces_2020/dev228/trace.csv 16384 > results-16Gl/dev228 &
# build/main_ali /mnt/disk0/alibaba_block_traces_2020/dev256/trace.csv 16384 > results-16Gl/dev256 &
# build/main_ali /mnt/disk0/alibaba_block_traces_2020/dev148/trace.csv 16384 > results-16Gl/dev148
# build/main_ali /mnt/disk0/alibaba_block_traces_2020/dev293/trace.csv 16384 > results-16Gl/dev293 &
# build/main_ali /mnt/disk0/alibaba_block_traces_2020/dev262/trace.csv 16384 > results-16Gl/dev262 &
# build/main_ali /mnt/disk0/alibaba_block_traces_2020/dev181/trace.csv 16384 > results-16Gl/dev181 &
# build/main_ali /mnt/disk0/alibaba_block_traces_2020/dev68/trace.csv 16384 > results-16Gl/dev68 &
# build/main_ali /mnt/disk0/alibaba_block_traces_2020/dev631/trace.csv 16384 > results-16Gl/dev631 &
# build/main_ali /mnt/disk0/alibaba_block_traces_2020/dev336/trace.csv 16384 > results-16Gl/dev336 &
# build/main_ali /mnt/disk0/alibaba_block_traces_2020/dev207/trace.csv 16384 > results-16Gl/dev207 &
# build/main_ali /mnt/disk0/alibaba_block_traces_2020/dev276/trace.csv 16384 > results-16Gl/dev276 &
# build/main_ali /mnt/disk0/alibaba_block_traces_2020/dev12/trace.csv 16384 > results-16Gl/dev12