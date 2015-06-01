###Instructions for manually building Boost

- Download source from boost.org
- ./bootstrap.sh --prefix=${GORGON_SRC}/ExternalLibraries/boost/ --with-libraries=python :TODO: Check paths
- ./b2
or
- ./b2 -jx
- ./b2 install
