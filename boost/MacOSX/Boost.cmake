message("Dependency - Boost")

if( UNIX )
  set( Boost_Bootstrap_CMD ./bootstrap.sh )
  set( Boost_b2_CMD ./b2 )
else()
  if( WIN32 )
    set( Boost_Bootstrap_CMD bootstrap.bat )
    set( Boost_b2_CMD b2.exe )
  endif()
endif()

set(Source_Dir ${CMAKE_SOURCE_DIR}/ExternalLibraries/boost_src/bsrc)

#set(Boost_Bootstrap_CMD "${Boost_Bootstrap_CMD} --prefix=${CMAKE_SOURCE_DIR}/ExternalLibraries/boost_out --with-libraries=python")

#set( Boost_b2_CMD "${Boost_b2_CMD} install" )

#message(${Boost_Bootstrap_CMD})

include(ExternalProject)

ExternalProject_Add( Bust
	PREFIX ${CMAKE_SOURCE_DIR}/ExternalLibraries/boost_boost
 #--Download step--------------
 # # [DOWNLOAD_NAME fname]       # File name to store (if not end of URL)
 #  DOWNLOAD_DIR   ${CMAKE_SOURCE_DIR}/ExternalLibraries/boost_src        # Directory to store downloaded files
 #  DOWNLOAD_COMMAND ""   # Command to download source tree
 #   URL          http://downloads.sourceforge.net/project/boost/boost/1.58.0/boost_1_58_0.tar.gz # Full path or URL of source
 #   URL_HASH SHA1=a27b010b9d5de0c07df9dddc9c336767725b1e6b       # Hash of file at URL
 #   URL_MD5 5a5d5614d9a07672e1ab2a250b5defc5 # Equivalent to URL_HASH MD5=md5
 #   #[TLS_VERIFY bool]           # Should certificate for https be checked
 #   #[TLS_CAINFO file]           # Path to a certificate authority file
 #   #[TIMEOUT seconds]           # Time allowed for file download operations
 #--Configure step-------------
 SOURCE_DIR ${Source_Dir}            # Source dir to be used for build
 CONFIGURE_COMMAND   "${Source_Dir}/${Boost_Bootstrap_CMD} --prefix=${CMAKE_SOURCE_DIR}/ExternalLibraries/boost_out/" # Build tree configuration command
 #--Build step-----------------
 #[BINARY_DIR dir]            # Specify build dir location
 #[BUILD_COMMAND cmd...]      # Command to drive the native build
 #[BUILD_IN_SOURCE 1]         # Use source dir for build dir
 #--Install step---------------
 #[INSTALL_DIR dir]           # Installation prefix
 # INSTALL_COMMAND ${Boost_b2_CMD}    # Command to drive install after build
 #--Output logging-------------
  LOG_DOWNLOAD 1            # Wrap download in script to log output
  LOG_UPDATE 1              # Wrap update in script to log output
  LOG_CONFIGURE 1           # Wrap configure in script to log output
  LOG_BUILD 1               # Wrap build in script to log output
  LOG_TEST 1                # Wrap test in script to log output
  LOG_INSTALL 1             # Wrap install in script to log output
 #--Custom targets-------------
 # [STEP_TARGETS st1 st2 ...]  # Generate custom targets for these steps
  )
