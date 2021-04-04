#!/bin/bash

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
build/main_snia /mnt/disk0/snia_refined/MSRCambridge/wdev.total.csv.orig 4096 > results/wdev