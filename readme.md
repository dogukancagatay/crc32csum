# COMPOSITE-CRC32 Checksum

Command line program that computes Composite CRC32 (CRC32C) checksum of a file. Which is particularly useful when working with HDFS and/or some object storage file systems where this type of checksum can be used.

Program uses [crc32c-hw](https://github.com/robertvazan/crc32c-hw) library which enables hardware assisted (using Intel SSE4.2 Instruction Set) (faster) computation of the checksum.

## Usage

Usage is simple.

```
./crc32csum file.txt
```

Result:
```
7c66d169        file.txt
```

## Building

### Windows

Regular cmake build commands.

```
mkdir build
cd build
cmake ../
```

Build generated solution file.

```
msbuild crc32csum.sln /p:Configuration=Release /p:Platform=x64
```

### Linux/Mac/Others

Regular cmake build commands.

```
mkdir build
cd build
cmake ../
make
```
