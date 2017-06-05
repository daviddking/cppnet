# C++ Networking TS Examples

## Get the example source code:

~~~
git clone git@github.com:daviddking/cppnet.git
~~~

## Build with Chris Kohlhoff's Networking TS implementation

~~~
git clone git@github.com:chriskohlhoff/networking-ts-impl.git
~~~

Modify cppnet/CMakeLists.txt

~~~
set(NETWORKING_TS_ROOT "your-path-here/networking-ts-impl")
~~~

## Build with the GCC 8.0 standard library

~~~
git clone https://github.com/daviddking/gcc
~~~

You then need to build gcc and the standard library:
* Download the pre-requisites:
    ~~~
    gcc/contrib/download_prerequisites
    ~~~
* Make a parallel directory named gccbuild:
    ~~~
    gcc/
    gccbuild/
    ~~~
* Build gcc (parameters below are for Linux x86 64 bit):
    ~~~
    cd gccbuild
    ../gcc/configure -v --build=x86_64-linux-gnu --host=x86_64-linux-gnu --target=x86_64-linux-gnu --prefix=/usr/local/gcc-8.0 --enable-checking=release --enable_languages=c++ --disable-multilib --program-suffix=-8.0   
    make -j  
    sudo make install
    ~~~

    More details and options are described here:
    
    https://gcc.gnu.org/wiki/InstallingGCC
    
* Modify cppnet/CMakeLists.txt. Comment out the below line:
    ~~~
    #set(NETWORKING_TS_ROOT "your-path-here/networking-ts-impl")
    ~~~

* Configure your system to use the g++-8.0 compiler, either using sudo update-alternativces --config c++, or settting CMAKE_CXX_COMPILER.




