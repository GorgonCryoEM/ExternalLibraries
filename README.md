###Instructions for manually building Boost

- Download source from boost.org
- ./bootstrap.sh --prefix=${GORGON_SRC}/ExternalLibraries/boost/MacOSX --with-libraries=python
- ./b2
or
- ./b2 -jx
- ./b2 install
