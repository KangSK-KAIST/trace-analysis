import copy
import os
import pickle
import sys

import pandas as pd
import numpy as np

rawFileName = "snia_refined/MSEnterprise/Enterprise1.total.csv.orig"
pickleFileName = "trace.bin"

pdTrace = []
lTraceRead = []
lTraceWrite = []
lTraceReadCentric = []
lTraceWriteCentric = []

# Read raw trace
def read_trace():
    global pdTrace
    print_line()
    print("#1 Reading file...")
    pdTrace = pd.read_csv(rawFileName, delim_whitespace=True, names=["time","op", "address", "size"])
    print(pdTrace)
    print("Finished reading file")
    print_line()

# Parse raw trace into R/W centric, respectively
def parse_trace():
    global lTraceRaw, lTraceRead, lTraceWrite
    lTraceRead = copy.deepcopy(lTraceRaw)
    lTraceWrite = copy.deepcopy(lTraceRaw)
    print(lTraceRead, lTraceWrite)

# Group traces into R/W centric data
def group_trace():
    global lTraceRaw, lTraceReadCentric, lTraceWriteCentric
    lTraceReadCentric = copy.deepcopy(lTraceRaw)
    lTraceWriteCentric = copy.deepcopy(lTraceRaw)
    print(lTraceReadCentric, lTraceWriteCentric)

# Save R/W centric data
def save_pickle():
    global lTraceReadCentric, lTraceWriteCentric
    with open(pickleFileName, "wb") as fPickleOut:
        pickle.dump(lTraceReadCentric, fPickleOut)
        pickle.dump(lTraceWriteCentric, fPickleOut)

# Read from pickle, R/W centric data
def read_pickle():
    global lTraceReadCentric, lTraceWriteCentric
    with open(pickleFileName, "rb") as fPickleIn:
        lTraceReadCentric = pickle.load(fPickleIn)
        lTraceWriteCentric = pickle.load(fPickleIn)

# Analyze the trace
def analyze_trace():
    global lTraceReadCentric, lTraceWriteCentric
    print(lTraceReadCentric)
    print(lTraceWriteCentric)

if (__name__ == "__main__"):
    if not os.path.exists(pickleFileName):
        read_trace()
        parse_trace()
        group_trace()
        save_pickle()
    else:
        read_pickle()
    analyze_trace()