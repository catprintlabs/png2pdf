# Installation

## Dependencies

png2pdf uses [CMake](https://cmake.org/) for building and installation.

png2pdf has three runtime dependencies:

- [boost](https://www.boost.org/)
- [png++](https://www.nongnu.org/pngpp/)
- [libpng](http://www.libpng.org/pub/png/libpng.html) (required by png++)
- [PoDoFo](http://podofo.sourceforge.net/)

Mostly everything should be available through package managers:

#### Ubuntu

```shell-script
sudo apt install cmake libboost-system-dev libboost-filesystem-dev libboost-program-options-dev libpng-dev libpodofo-dev
```

#### macOS

```shell-script
brew install cmake boost libpng podofo png++
```

on Ubuntu png++ needs to be installed manually:

```shell-script
cd /usr/local/src # Or wherever you compile code
wget http://download.savannah.nongnu.org/releases/pngpp/png++-0.2.9.tar.gz
tar zxf png++-0.2.9.tar.gz
cd png++-0.2.9
make
sudo make install
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
