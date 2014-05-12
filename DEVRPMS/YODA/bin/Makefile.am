dist_bin_SCRIPTS = yoda-config  yodamerge

bin_PROGRAMS = yodaconvert
yodaconvert_SOURCES = yodaconvert.cc
yodaconvert_CXXFLAGS=-std=c++0x
yodaconvert_LDADD= $(SUBLIBS) $(AM_LDFLAGS) $(top_builddir)/src/libYODA.la 

if  ENABLE_ROOT
yodaconvert_LDADD+=$(ROOT_LIBS)
yodaconvert_CPPFLAGS = $(ROOT_CXXFLAGS) -Wno-long-long 
endif

## bash completion
if ENABLE_PYEXT
dist_pkgdata_DATA = yoda-completion
bashcomp_dir = $(prefix)/etc/bash_completion.d
install-data-local:
	if [[ -d "$(bashcomp_dir)" && -w "$(bashcomp_dir)" ]]; then \
      install --mode 644 yoda-completion $(bashcomp_dir)/; fi
uninstall-local:
	rm -f $(bashcomp_dir)/yoda-completion
else
EXTRA_DIST = yoda-completion
endif




