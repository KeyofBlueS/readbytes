# readbytes

A small utility that extracts a specified number of bytes from a binary file, starting at a given offset, and outputs them as a hexadecimal string.


# Build Instructions:

`g++ -static -o readbytes readbytes.cpp`


# Usage:

```sh
$ readbytes <input_file> [options]
```
```
Options:
  -s, --seek <offset>		Set the offset (default is 0)
  -l, --length <length>		Set the number of bytes to read (default is 4)
  -h, --help			Show this help message and exit
```
