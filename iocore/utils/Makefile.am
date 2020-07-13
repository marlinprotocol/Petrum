AM_CPPFLAGS += \
	-I$(abs_top_srcdir)/include \
	-I$(abs_top_srcdir)/lib \
	-I$(abs_top_srcdir)/iocore/eventsystem \
	$(TS_INCLUDES)

noinst_LIBRARIES = libinkutils.a

libinkutils_a_SOURCES = \
	I_Machine.h \
	I_OneWayMultiTunnel.h \
	I_OneWayTunnel.h \
	Machine.cc \
	OneWayMultiTunnel.cc \
	OneWayTunnel.cc

include $(top_srcdir)/build/tidy.mk

clang-tidy-local: $(DIST_SOURCES)
	$(CXX_Clang_Tidy)
