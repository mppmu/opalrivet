%define major       0
%define libname     Rivet
%define libnamedev  Rivet-devel
%define develnamestatic  Rivet-static-devel



Name:           Rivet
Version: 2.2.0
Release:        1
License:        GPLv3
Url:		    http://rivet.hepforge.org/
Source0:	    http://www.hepforge.org/archive/rivet/%{name}-%{version}.tar.gz
Patch0:         patch-Rivet-0.txt
#Patch1:         patch-Rivet-1.txt
Group:		    Sciences/Physics
Summary:        Robust Independent Validation of Experiment and Theory
#Ubuntu is crap
BuildRequires:	gcc-gfortran gcc-c++ YODA YODA-devel boost-devel

%description
The Rivet project (Robust Independent Validation of Experiment and Theory) 
is a toolkit for validation of Monte Carlo event generators. It provides a
large (and ever growing) set of experimental analyses useful for MC generator 
development, validation, and tuning, as well as a convenient infrastructure for
 adding your own analyses. Rivet is the most widespread way by which analysis code 
 from the LHC and other high-energy collider experiments is preserved for comparison 
 to and development of future theory models. 

%package -n     bazlib
Summary:        Libraries for %{name}
Group:          System/Libraries
Provides:       %{name} = %{version}-%{release}

%description -n     bazlib
The Rivet project (Robust Independent Validation of Experiment and Theory) 
is a toolkit for validation of Monte Carlo event generators. It provides a
large (and ever growing) set of experimental analyses useful for MC generator 
development, validation, and tuning, as well as a convenient infrastructure for
 adding your own analyses. Rivet is the most widespread way by which analysis code 
 from the LHC and other high-energy collider experiments is preserved for comparison 
 to and development of future theory models. 


%package  devel
Summary:        Libraries and headers for %{name}
Group:          Development/C
#Requires:       %{libname} = %{version}
Provides:       %{name}-devel = %{version}-%{release}

%description devel
%{libnamedev} contains the libraries and header files needed to
develop programs which make use of %{name}.
The library documentation is available on header files.




%prep
%setup -q
%patch0 -p0
#%patch0 -p1

%build
mkdir -p $(pwd)/tmp/usr
mkdir -p $(pwd)/tmp/%_lib
autoreconf
#./configure  --prefix=$(pwd)/tmp/usr --libdir=$(pwd)/tmp/usr/%_lib --disable-analyses
%configure --disable-analyses
make %{?_smp_mflags}

%install
#make install
#install -c -m 644 src/Analyses/*.cc  $(pwd)/tmp/usr/share/Rivet
#sed -i s@$(pwd)/tmp/usr/%_lib@/usr/%_lib@g  $(pwd)/tmp/usr/%_lib/*.la
#sed -i s@$(pwd)/tmp/usr@/usr@g  $(pwd)/tmp/usr/bin/rivet*
#mkdir -p $RPM_BUILD_ROOT/usr
#cp -r $(pwd)/tmp/usr                              $RPM_BUILD_ROOT
#rm -rf $RPM_BUILD_ROOT/usr/share/Rivet/texmf
make install  DESTDIR=$(pwd)/tmp
mkdir -p $RPM_BUILD_ROOT/usr
cp -r $(pwd)/tmp/usr                              $RPM_BUILD_ROOT

%files 
%doc AUTHORS README COPYING

%files -n %{libname}

%{_bindir}/rivet-which
%{_bindir}/rivet-mkanalysis
%{_bindir}/rivet-config
%{_bindir}/rivet-findid
%{_bindir}/make-plots
%{_bindir}/rivet-buildplugin
%{_bindir}/rivet-cmphistos
%{_bindir}/rivet-mkhtml
%{_bindir}/rivet

/usr/%_lib/python2.6/site-packages/*
/usr/%_lib/*.so
/usr/%_lib/*.la
/usr/%_lib/*/*.pc

%files -n %{libnamedev}


%{_includedir}/Rivet/*hh
%{_includedir}/Rivet/Math/*.hh
%{_includedir}/Rivet/Math/eigen/*.h
%{_includedir}/Rivet/Projections/*.hh
%{_includedir}/Rivet/Tools/*.hh
%{_includedir}/Rivet/Analyses/*.hh
%{_includedir}/Rivet/Config/*.hh
/usr/share/Rivet/*
%{_includedir}/Rivet/*.fhh




%changelog
* Mon Feb 3 2014 Andrii Verbytskyi 1.0.4
+ Initial spec file

