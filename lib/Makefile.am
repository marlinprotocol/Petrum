SUBDIRS = . records tsconfig

if BUILD_PERL_LIB
SUBDIRS += perl
endif

# to prevent Clang Analyzer warning
LOCAL =

if BUILD_YAML_CPP
LOCAL += yamlcpp
endif

all-local:	$(LOCAL)
	$(MAKE) -C yamlcpp

clean-local:
	$(MAKE) -C yamlcpp clean
