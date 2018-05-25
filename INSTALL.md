 libILUStateMachine

## Requirements

You need the following software installed for the build process:

    autoconf 2.60  (or later)
    automake 1.15  (or later)
    libtool  2.4.6 (or later)
    GNU m4 (required by autoconf)

This library depends on the following libraries:
    boost 1.67.0  (or later)

## Build from git

Building from git is made in the following steps:

    autoreconf -i
    ./configure
    make
    make test (optional)
    make install

You probably need to be root when doing the last command.

If you want to install libILUStateMachine in a different file hierarchy
than `/usr/local`, specify that when running configure:

    ./configure --prefix=/path/to/libILUStateMachine/tree

If you have write permission in that directory, you can do 'make install'
without being root. An example of this would be to make a local install in
your own home directory:

    autoreconf -i
    ./configure --prefix=$HOME
    make
    make install