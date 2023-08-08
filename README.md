# EWPackageTools
A simple tool for browsing contents of Eastward `.g` packages.

## Build instructions

### Ubuntu 23.04

```bash 
# Install dependencies
apt install libgtk-3-dev

# Clone
git clone --recurse-submodules https://github.com/thirtque/EWPackageTools.git
cd EWPackageTools

# Build
mkdir build
cmake -B ./build
cd build
make

# Run
./EWPackageTools
```

## Screenshots
![ewtools](https://user-images.githubusercontent.com/90976311/143503141-a6ccfcb1-15f5-4c96-9fba-020e4113c424.png)