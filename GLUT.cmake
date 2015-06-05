
set(ext_dir ${CMAKE_SOURCE_DIR}/ExternalLibraries/GL/${folder_name}/GL)

#message("          VAL: ${ext_dir}")

FIND_PATH(
    GLUT_INCLUDE_DIR
    NAMES glut.h
    PATHS ${ext_dir}/include
    #NO_DEFAULT_PATH
)

FIND_LIBRARY(
    GLUT_glut_LIBRARY
    NAMES freeglut
    PATHS ${ext_dir}/lib
    #NO_DEFAULT_PATH
)


INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(GLUT DEFAULT_MSG GLUT_glut_LIBRARY GLUT_INCLUDE_DIR)
#MARK_AS_ADVANCED(FFTW3F_LIBRARIES FFTW3F_INCLUDE_DIRS FFTW3F_THREADS_LIBRARIES)