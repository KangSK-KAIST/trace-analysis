import copy
import os
import pickle
import sys

import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

rawFileName = "snia_refined/MSEnterprise/Enterprise1.total.csv.orig"
pickleFileName = "trace.bin"

pdTrace = []
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

# Parse raw trace into R/W centric, respectively
def parse_trace():
    global pdTrace
    print_line()
    print("#2 Parsing file...")
    pdTrace.sort_values(by=["op", "address", "time"], inplace=True)
    print(pdTrace.head())
    print(pdTrace.tail())

# Group traces into R/W centric data
def group_trace():
    global pdTrace, lTraceReadCentric, lTraceWriteCentric
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

# Helper functions
def print_line():
    for i in range(os.get_terminal_size().columns):
        print('=', end='')

if (__name__ == "__main__"):
    if not os.path.exists(pickleFileName):
        read_trace()
        parse_trace()
        group_trace()
        save_pickle()
    else:
        read_pickle()
    analyze_trace()