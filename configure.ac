#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.
AC_PREREQ(2.61)
AC_INIT(EVIE, 2.4, BUG-REPORT-ADDRESS)
AM_INIT_AUTOMAKE
AC_CONFIG_SRCDIR([src/animal.h])
AC_CONFIG_HEADER([config.h])

AM_MAINTAINER_MODE

# Checks for programs.
AC_PROG_CXX
AC_PROG_CC


AC_SUBST([AUTO_DEPS])


# Checks for libraries.
AC_CHECK_LIB(g2,g2_clear , ,
  AC_MSG_ERROR([Could not find g2 library.]), )
AC_CHECK_LIB(X11,XOpenDisplay , ,
  AC_MSG_ERROR([Could not find X11 library.]), )
AC_CHECK_LIB(z,gzclose , ,
  AC_MSG_ERROR([Could notfind z library.]), )

# Checks for header files.
AC_HEADER_STDC
AC_CHECK_HEADERS([stdlib.h string.h unistd.h time.h] , ,
  AC_MSG_ERROR([Could not find development headers]),)
AC_CHECK_HEADERS([g2.h g2_X11.h] , , 
  AC_MSG_ERROR([Could not find g2 development headers]))
AC_CHECK_HEADERS([zlib.h] , ,
  AC_MSG_ERROR([Could not find zlib development headers]))


# Checks for typedefs, structures, and compiler characteristics.
AC_HEADER_STDBOOL
AC_C_CONST
AC_C_INLINE
AC_HEADER_TIME
AC_STRUCT_TM
AC_TYPE_SIZE_T

# Checks for library functions.
AC_FUNC_MALLOC
AC_CHECK_FUNCS([floor pow sqrt])


AC_CONFIG_FILES([Makefile
		src/Makefile])

AC_OUTPUT
