AM_CPPFLAGS += \
	$(iocore_include_dirs) \
	-I$(abs_top_srcdir)/include \
	-I$(abs_top_srcdir)/lib \
	-I$(abs_top_srcdir)/proxy \
	-I$(abs_top_srcdir)/proxy/http \
	-I$(abs_top_srcdir)/proxy/hdrs \
	-I$(abs_top_srcdir)/mgmt \
	-I$(abs_top_srcdir)/mgmt/utils \
	$(TS_INCLUDES)

noinst_LIBRARIES = libinkdns.a

libinkdns_a_SOURCES = \
	DNS.cc \
	DNSConnection.cc \
	I_DNS.h \
	I_DNSProcessor.h \
	I_SplitDNS.h \
	I_SplitDNSProcessor.h \
	Inline.cc \
	P_DNS.h \
	P_DNSConnection.h \
	P_DNSProcessor.h \
	P_SplitDNS.h \
	P_SplitDNSProcessor.h \
	SRV.h \
	SplitDNS.cc

#test_UNUSED_SOURCES = \
#  test_I_DNS.cc \
#  test_P_DNS.cc

include $(top_srcdir)/build/tidy.mk

clang-tidy-local: $(DIST_SOURCES)
	$(CXX_Clang_Tidy)
