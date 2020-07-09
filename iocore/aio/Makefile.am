AM_CPPFLAGS += \
	-I$(abs_top_srcdir)/iocore/eventsystem \
	-I$(abs_top_srcdir)/include \
	-I$(abs_top_srcdir)/lib \
	$(TS_INCLUDES)

TESTS = test_AIO.sample

noinst_LIBRARIES = libinkaio.a
check_PROGRAMS = test_AIO

libinkaio_a_SOURCES = \
	AIO.cc \
	I_AIO.h \
	Inline.cc \
	P_AIO.h

test_AIO_LDFLAGS = \
	@AM_LDFLAGS@ \
	@OPENSSL_LDFLAGS@

test_AIO_SOURCES = \
	test_AIO.cc

test_AIO_CPPFLAGS = \
	$(AM_CPPFLAGS) \
	$(iocore_include_dirs) \
	-I$(abs_top_srcdir)/proxy \
	-I$(abs_top_srcdir)/proxy/hdrs \
	-I$(abs_top_srcdir)/proxy/http \
	-I$(abs_top_srcdir)/proxy/logging \
	-I$(abs_top_srcdir)/mgmt \
	-I$(abs_top_srcdir)/mgmt/utils \
	@OPENSSL_INCLUDES@

test_AIO_LDADD = \
	libinkaio.a \
	$(top_builddir)/lib/records/librecords_p.a \
	$(top_builddir)/mgmt/libmgmt_p.la \
	$(top_builddir)/iocore/eventsystem/libinkevent.a \
	$(top_builddir)/src/tscore/libtscore.la \
	$(top_builddir)/src/tscpp/util/libtscpputil.la \
	$(top_builddir)/proxy/shared/libUglyLogStubs.a \
	@LIBTCL@ @HWLOC_LIBS@

include $(top_srcdir)/build/tidy.mk

clang-tidy-local: $(DIST_SOURCES)
	$(CXX_Clang_Tidy)
