dnl $Id$
dnl ----------------------------------------------------------

echo Configuring GNUWorld...
echo

AC_REVISION($Revision$)
AC_INIT
AC_CONFIG_SRCDIR([auth.cc])
AM_INIT_AUTOMAKE(auth,1.0)

AC_PROG_INSTALL

dnl Substitute INCLTDL and LIBLTDL in the Makefiles
dnl For some reason, INCLTDL and LIBLTDL aren't set
dnl properly on OpenBSD
INCLTDL="-I../libltdl"
LIBLTDL="../libltdl/libltdlc.la"

AM_MAINTAINER_MODE
AC_ISC_POSIX

dnl Check for dlopen support
AC_LIBTOOL_DLOPEN

dnl Configure libtool
AM_PROG_LIBTOOL

CFLAGS="-W -Wall -pipe"
CXXFLAGS="-W -Wall -pipe"

AC_PREFIX_DEFAULT(`pwd`)
glibdir="`pwd`/libgnuworld"

AC_PROG_CC
AC_PROG_CXX
AC_PROG_CPP
AC_LANG([C++])

AC_PROG_MAKE_SET(gmake)

AC_HEADER_STDC
AC_HEADER_TIME
AC_TYPE_SIGNAL
AC_TYPE_MODE_T
AC_TYPE_PID_T
AC_TYPE_SIZE_T
AC_TYPE_UID_T


AC_ARG_WITH(debug,
	AC_HELP_STRING([--without-debug],
		       [Disable debugging in the executables]),
	[dummy=true],
	[CXXFLAGS="$CXXFLAGS -g"]
)

AC_ARG_WITH(pedantic,
	AC_HELP_STRING([--with-pedantic],
			[Add -pedantic to compile options]),
	[CXXFLAGS="$CXXFLAGS -pedantic"]
)

AC_ARG_WITH(optimization,
	AC_HELP_STRING([--with-optimization],
			[Optimize the executables]),
	[CXXFLAGS="$CXXFLAGS -O2"],
	[CXXFLAGS="$CXXFLAGS -O0"]
)

AC_ARG_WITH(prof,
	AC_HELP_STRING([--with-prof],
			[Generate profiling information]),
	[CXXFLAGS="$CXXFLAGS -pg"]
)

CXXFLAGS="$CXXFLAGS -I../include -I../libgnuworld"

dnl echo "CXXFLAGS: $CXXFLAGS"
dnl echo PGSQL_LIB: $PGSQL_LIB
dnl echo PGSQL_INCLUDE: $PGSQL_INCLUDE

AC_SUBST(CXXFLAGS)
AC_SUBST(INCLTDL)
AC_SUBST(LIBLTDL)
AC_SUBST(glibdir)
AC_SUBST(LIBTOOL_DEPS)

AC_CONFIG_FILES([Makefile])

AC_OUTPUT
