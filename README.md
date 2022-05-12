# simple-eb
These files are extracted from libeb, a epwing library parser.   
To make build on windows easier.

# how to build 

## windows
```
vcpkg install zlib:x64-windows
```

```
cmake .  -DCMAKE=xxx (output from the previous `vcpkg` command)
cmake --build .
```
