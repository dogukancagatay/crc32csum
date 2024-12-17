# COMPOSITE-CRC32 Checksum

A command-line program computes a Composite CRC32 (CRC32C) file checksum. It is particularly useful when checking quickly for file equality or working with HDFS and/or some object storage file systems, where this type of checksum can be used. Beware that CRC32C is not a cryptographic checksum.

Program uses ~~[crc32c-hw](https://github.com/robertvazan/crc32c-hw)~~ [crc32c](https://github.com/google/crc32c.git) library, enables hardware assisted computation of the checksum.

## Usage

Usage is simple.

```sh
./crc32csum file.txt
```

Result:

```sh
7c66d169        file.txt
```

## Building

The library dependencies are bundled with the library.

```sh
git submodule update --init --recursive
```

### Linux/Mac/Others

Regular cmake build commands.

```sh
mkdir build
cd build
cmake ../
make
```

### Windows

!! Windows build is not tested yet, may not be running right now. !!

Regular cmake build commands.

```sh
mkdir build
cd build
cmake ../
```

Build generated solution file.

```sh
msbuild crc32csum.sln /p:Configuration=Release /p:Platform=x64
```
