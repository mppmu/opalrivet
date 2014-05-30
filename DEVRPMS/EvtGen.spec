%define major       0
%define libname     EvtGen
%define libnamedev  EvtGen-devel
%define develnamestatic  EvtGen-static-devel



Name:           EvtGen
Version:        1.3.0
Release:        1
License:        GPLv3
Url:		    http://rivet.hepforge.org/
Source0:	    http://evtgen.warwick.ac.uk/static/srcrep/R01-03-00/EvtGen.R01-03-00.tar.gz/%{name}-%{version}.tar.gz
Patch0:         patch-EvtGen-0.txt
Group:		    Sciences/Physics
Summary:        Robust Independent Validation of Experiment and Theory
BuildRequires:	gcc-gfortran gcc-c++ YODA YODA-devel boost-devel

%description
The EvtGen project (Robust Independent Validation of Experiment and Theory) 
is a toolkit for validation of Monte Carlo event generators. It provides a
large (and ever growing) set of experimental analyses useful for MC generator 
development, validation, and tuning, as well as a convenient infrastructure for
 adding your own analyses. EvtGen is the most widespread way by which analysis code 
 from the LHC and other high-energy collider experiments is preserved for comparison 
 to and development of future theory models. 

%package -n     bazlib
Summary:        Libraries for %{name}
Group:          System/Libraries
Provides:       %{name} = %{version}-%{release}

%description -n     bazlib
The EvtGen project (Robust Independent Validation of Experiment and Theory) 
is a toolkit for validation of Monte Carlo event generators. It provides a
large (and ever growing) set of experimental analyses useful for MC generator 
development, validation, and tuning, as well as a convenient infrastructure for
 adding your own analyses. EvtGen is the most widespread way by which analysis code 
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
#%patch0 -p0
%patch0 -p1

%build
mkdir -p $(pwd)/tmp/usr
mkdir -p $(pwd)/tmp/%_lib
#autoreconf
./configure  --prefix=/usr --libdir=/usr/%_lib --hepmcdir=/usr --pythiadir=/usr --photosdir=/usr --tauoladir=/usr 
make 

%install
make install DESTDIR=$(pwd)/tmp 
mkdir -p $RPM_BUILD_ROOT/usr
cp -r $(pwd)/tmp/usr                              $RPM_BUILD_ROOT

%files 
%doc AUTHORS README COPYING

%files -n %{libname}
/usr/%_lib/*

%files -n %{libnamedev}
/usr/share/*
%{_includedir}/*




%changelog
* Mon Feb 3 2014 Andrii Verbytskyi 1.0.4
+ Initial spec file

