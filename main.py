import os
import pickle
import copy

rawFileName = "snia_refined/MSEnterprise/Enterpr"

lTraceRaw = []
lTraceRead = []
lTraceWrite = []
lTraceReadCentric = []
lTraceWriteCentric = []

# Read raw trace
def read_trace():
    global lTraceRaw
    with open("trace.txt", "r") as fTraceIn:
        lines = fTraceIn.readlines()
    lTraceRaw = [line.strip() for line in lines]
    print(lTraceRaw[0])

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
    with open("trace.bin", "wb") as fPickleOut:
        pickle.dump(lTraceReadCentric, fPickleOut)
        pickle.dump(lTraceWriteCentric, fPickleOut)

# Read from pickle, R/W centric data
def read_pickle():
    global lTraceReadCentric, lTraceWriteCentric
    with open("trace.bin", "rb") as fPickleIn:
        lTraceReadCentric = pickle.load(fPickleIn)
        lTraceWriteCentric = pickle.load(fPickleIn)

# Analyze the trace
def analyze_trace():
    global lTraceReadCentric, lTraceWriteCentric
    print(lTraceReadCentric)
    print(lTraceWriteCentric)

if (__name__ == "__main__"):
    if not os.path.exists("trace.bin"):
        read_trace()
        parse_trace()
        group_trace()
        save_pickle()
    else:
        read_pickle()
    analyze_trace()