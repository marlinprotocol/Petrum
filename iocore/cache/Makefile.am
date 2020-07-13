AM_CPPFLAGS += \
	$(iocore_include_dirs) \
	-I$(abs_top_srcdir)/include \
	-I$(abs_top_srcdir)/lib \
	-I$(abs_top_srcdir)/proxy \
	-I$(abs_top_srcdir)/proxy/hdrs \
	-I$(abs_top_srcdir)/proxy/http \
	-I$(abs_top_srcdir)/proxy/shared \
	-I$(abs_top_srcdir)/proxy/http/remap \
	-I$(abs_top_srcdir)/mgmt \
	-I$(abs_top_srcdir)/mgmt/utils \
	$(TS_INCLUDES)

noinst_LIBRARIES = libinkcache.a

libinkcache_a_SOURCES = \
	Cache.cc \
	CacheDir.cc \
	CacheDisk.cc \
	CacheHosting.cc \
	CacheHttp.cc \
	CacheLink.cc \
	CachePages.cc \
	CachePagesInternal.cc \
	CacheRead.cc \
	CacheVol.cc \
	CacheWrite.cc \
	I_Cache.h \
	I_CacheDefs.h \
	I_Store.h \
	Inline.cc \
	P_Cache.h \
	P_CacheArray.h \
	P_CacheDir.h \
	P_CacheDisk.h \
	P_CacheHosting.h \
	P_CacheHttp.h \
	P_CacheInternal.h \
	P_CacheVol.h \
	P_RamCache.h \
	RamCacheCLFUS.cc \
	RamCacheLRU.cc \
	Store.cc

if BUILD_TESTS
libinkcache_a_SOURCES += \
	CacheTest.cc \
	P_CacheTest.h
endif

include $(top_srcdir)/build/tidy.mk

clang-tidy-local: $(DIST_SOURCES)
	$(CXX_Clang_Tidy)
