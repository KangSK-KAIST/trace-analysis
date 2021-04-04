#!/bin/bash

build/snia_compresser /home/kangsk/snia_refined/MSProduction/24Hour_RADIUS.total.csv.orig > /home/kangsk/snia_refined/MSProduction/24Hour_RADIUS.total.csv.compressed &
build/snia_compresser /home/kangsk/snia_refined/MSProduction/MSNFS.total.csv.orig > /home/kangsk/snia_refined/MSProduction/MSNFS.total.csv.compressed &
build/snia_compresser /home/kangsk/snia_refined/MSProduction/24Hour_RADIUS_SQL.total.csv.orig > /home/kangsk/snia_refined/MSProduction/24Hour_RADIUS_SQL.total.csv.compressed &
build/snia_compresser /home/kangsk/snia_refined/MSProduction/BuildServer.total.csv.orig > /home/kangsk/snia_refined/MSProduction/BuildServer.total.csv.compressed &
build/snia_compresser /home/kangsk/snia_refined/MSProduction/CFS.total.csv.orig > /home/kangsk/snia_refined/MSProduction/CFS.total.csv.compressed &
build/snia_compresser /home/kangsk/snia_refined/MSProduction/DisplayAdsPayload.total.csv.orig > /home/kangsk/snia_refined/MSProduction/DisplayAdsPayload.total.csv.compressed &
build/snia_compresser /home/kangsk/snia_refined/MSProduction/DevDivRelease.total.csv.orig > /home/kangsk/snia_refined/MSProduction/DevDivRelease.total.csv.compressed &
build/snia_compresser /home/kangsk/snia_refined/MSEnterprise/Exchange.total.csv.orig > /home/kangsk/snia_refined/MSEnterprise/Exchange.total.csv.compressed &
build/snia_compresser /home/kangsk/snia_refined/MSRCambridge/prn.total.csv.orig > /home/kangsk/snia_refined/MSRCambridge/prn.total.csv.compressed &
build/snia_compresser /home/kangsk/snia_refined/MSRCambridge/src1.total.csv.orig > /home/kangsk/snia_refined/MSRCambridge/src1.total.csv.compressed &
build/snia_compresser /home/kangsk/snia_refined/MSRCambridge/src2.total.csv.orig > /home/kangsk/snia_refined/MSRCambridge/src2.total.csv.compressed &
build/snia_compresser /home/kangsk/snia_refined/MSRCambridge/ts.total.csv.orig > /home/kangsk/snia_refined/MSRCambridge/ts.total.csv.compressed &
build/snia_compresser /home/kangsk/snia_refined/MSRCambridge/wdev.total.csv.orig > /home/kangsk/snia_refined/MSRCambridge/wdev.total.csv.compressed &
build/snia_compresser /home/kangsk/snia_refined/FIU-srcmap/ikki.total.csv.orig > /home/kangsk/snia_refined/FIU-srcmap/ikki.total.csv.compressed &
build/snia_compresser /home/kangsk/snia_refined/FIU-srcmap/webmail+online.total.csv.orig > /home/kangsk/snia_refined/FIU-srcmap/webmail+online.total.csv.compressed &

build/ali_compresser /home/kangsk/alibaba_block_traces_2020/dev49/trace.csv > /home/kangsk/alibaba_block_traces_2020/dev49/trace.csv.compressed &
build/ali_compresser /home/kangsk/alibaba_block_traces_2020/dev95/trace.csv > /home/kangsk/alibaba_block_traces_2020/dev95/trace.csv.compressed &
build/ali_compresser /home/kangsk/alibaba_block_traces_2020/dev125/trace.csv > /home/kangsk/alibaba_block_traces_2020/dev125/trace.csv.compressed &
build/ali_compresser /home/kangsk/alibaba_block_traces_2020/dev308/trace.csv > /home/kangsk/alibaba_block_traces_2020/dev308/trace.csv.compressed &
build/ali_compresser /home/kangsk/alibaba_block_traces_2020/dev355/trace.csv > /home/kangsk/alibaba_block_traces_2020/dev355/trace.csv.compressed &
build/ali_compresser /home/kangsk/alibaba_block_traces_2020/dev373/trace.csv > /home/kangsk/alibaba_block_traces_2020/dev373/trace.csv.compressed &
build/ali_compresser /home/kangsk/alibaba_block_traces_2020/dev454/trace.csv > /home/kangsk/alibaba_block_traces_2020/dev454/trace.csv.compressed &
build/ali_compresser /home/kangsk/alibaba_block_traces_2020/dev457/trace.csv > /home/kangsk/alibaba_block_traces_2020/dev457/trace.csv.compressed &
build/ali_compresser /home/kangsk/alibaba_block_traces_2020/dev467/trace.csv > /home/kangsk/alibaba_block_traces_2020/dev467/trace.csv.compressed &
build/ali_compresser /home/kangsk/alibaba_block_traces_2020/dev477/trace.csv > /home/kangsk/alibaba_block_traces_2020/dev477/trace.csv.compressed &
build/ali_compresser /home/kangsk/alibaba_block_traces_2020/dev550/trace.csv > /home/kangsk/alibaba_block_traces_2020/dev550/trace.csv.compressed &
build/ali_compresser /home/kangsk/alibaba_block_traces_2020/dev554/trace.csv > /home/kangsk/alibaba_block_traces_2020/dev554/trace.csv.compressed &
build/ali_compresser /home/kangsk/alibaba_block_traces_2020/dev618/trace.csv > /home/kangsk/alibaba_block_traces_2020/dev618/trace.csv.compressed &
build/ali_compresser /home/kangsk/alibaba_block_traces_2020/dev667/trace.csv > /home/kangsk/alibaba_block_traces_2020/dev667/trace.csv.compressed &
build/ali_compresser /home/kangsk/alibaba_block_traces_2020/dev767/trace.csv > /home/kangsk/alibaba_block_traces_2020/dev767/trace.csv.compressed &
build/ali_compresser /home/kangsk/alibaba_block_traces_2020/dev770/trace.csv > /home/kangsk/alibaba_block_traces_2020/dev770/trace.csv.compressed &


# {dev49,dev95,dev125,dev308,dev355,dev373,dev454,dev457,dev467,dev477,dev550,dev554,dev618,dev667,dev767,dev770}