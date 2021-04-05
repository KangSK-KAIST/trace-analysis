# trace-analysis

An extremely basic trace analyzer written in C++.
Very crude, likely to be non-scalable, use at your own risk.


## Version 1.0

### v1.0

Stable program of byte-level mapping analysis.

### v1.1

Unstable program of byte-level mapping analysis.
Able to compress trace files.
*Very* crude, do not use if not mandatory.

## Version 2.0

Modified to page-level mapping analysis.
Much faster compared to version 1.0, as it now can map the whole memory as an array of pages.
This also means there is no need for considering fragmentation of bytes.
