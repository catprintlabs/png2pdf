# Installation

## Dependencies

png2pdf uses [CMake](https://cmake.org/) for building and installation.

png2pdf has three runtime dependencies:

- [boost](https://www.boost.org/)
- [libpng](http://www.libpng.org/pub/png/libpng.html)
- [PoDoFo](http://podofo.sourceforge.net/)

Everything should be available through package managers:

#### Ubuntu

```shell-script
sudo apt install cmake libboost-system-dev libboost-filesystem-dev libboost-program-options-dev libpng-dev libpodofo-dev
```

#### macOS

```shell-script
brew install cmake boost libpng podofo
```

## Installing

checkinstall is recommend for installing, but it is only available on Linux.

```shell-script
mkdir build && cd build
cmake ../
make

# Linux
sudo checkinstall

# macOS
sudo make install
```
