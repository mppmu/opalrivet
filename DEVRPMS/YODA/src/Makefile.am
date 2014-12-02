SUBDIRS = tinyxml .

lib_LTLIBRARIES = libYODA.la

## Compile ReaderYODA and ReaderFLAT first: they take longest so this speeds up -jN compilation!
libYODA_la_SOURCES = \
    Reader.cc \
    ReaderYODA.cc \
    ReaderFLAT.cc \
    ReaderAIDA.cc \
    Writer.cc \
    WriterYODA.cc \
    WriterAIDA.cc \
    WriterFLAT.cc \
    Dbn0D.cc \
    Dbn1D.cc \
    Counter.cc \
    Histo1D.cc \
    Histo2D.cc \
    Profile1D.cc \
    Profile2D.cc \
    Scatter1D.cc \
    Scatter2D.cc \
    Scatter3D.cc


libYODA_la_LDFLAGS = -avoid-version 
libYODA_la_LIBADD = tinyxml/libtinyxml.la
libYODA_la_CPPFLAGS = $(AM_CPPFLAGS) -DTIXML_USE_STL 

if  ENABLE_ROOT
libYODA_la_SOURCES += ROOTConvert.cc 
libYODA_la_SOURCES += ReaderROOT.cc 
libYODA_la_SOURCES += WriterROOT.cc 
libYODA_la_LDFLAGS += $(ROOT_LDFLAGS) $(ROOT_LIBS)
libYODA_la_CPPFLAGS += $(ROOT_CXXFLAGS) -Wno-long-long 
#libYODA_la_CXXFLAGS += $(ROOT_CXXFLAGS) -Wno-long-long 

endif
