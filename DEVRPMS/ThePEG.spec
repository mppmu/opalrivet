%define major       0
%define libname     ThePEG
%define libnamedev  ThePEG-devel
%define develnamestatic  ThePEG-static-devel



Name:           ThePEG
Version:        1.9.0
Release:        1
License:        GPLv3
Url:		    http://rivet.hepforge.org/
Source0:	    http://www.hepforge.org/archive/thepeg/%{name}-%{version}.tar.bz2
Patch0:         patch-ThePEG-0.txt
Group:		    Sciences/Physics
Summary:        Robust Independent Validation of Experiment and Theory
BuildRequires:	gcc-gfortran gcc-c++ YODA YODA-devel boost-devel

%description
The ThePEG project (Robust Independent Validation of Experiment and Theory) 
is a toolkit for validation of Monte Carlo event generators. It provides a
large (and ever growing) set of experimental analyses useful for MC generator 
development, validation, and tuning, as well as a convenient infrastructure for
 adding your own analyses. ThePEG is the most widespread way by which analysis code 
 from the LHC and other high-energy collider experiments is preserved for comparison 
 to and development of future theory models. 

%package -n     bazlib
Summary:        Libraries for %{name}
Group:          System/Libraries
Provides:       %{name} = %{version}-%{release}

%description -n     bazlib
The ThePEG project (Robust Independent Validation of Experiment and Theory) 
is a toolkit for validation of Monte Carlo event generators. It provides a
large (and ever growing) set of experimental analyses useful for MC generator 
development, validation, and tuning, as well as a convenient infrastructure for
 adding your own analyses. ThePEG is the most widespread way by which analysis code 
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

%build
mkdir -p $(pwd)/tmp/usr
mkdir -p $(pwd)/tmp/%_lib
autoreconf
./configure  --prefix=$(pwd)/tmp/usr --libdir=$(pwd)/tmp/usr/%_lib 
make %{?_smp_mflags}

%install
make install
sed -i s@$(pwd)/tmp/usr/@/usr/@g  $(pwd)/tmp/usr/bin/thepeg
sed -i s@$(pwd)/tmp/usr/@/usr/@g  $(pwd)/tmp/usr/%_lib/ThePEG/*la
mkdir -p $RPM_BUILD_ROOT/usr
cp -r $(pwd)/tmp/usr                              $RPM_BUILD_ROOT


%files 
%doc AUTHORS README COPYING

%files -n %{libname}
%_bindir/*
%_datadir/ThePEG/*
%_libdir/ThePEG/*


%files -n %{libnamedev}
%_includedir/ThePEG




%changelog
* Mon Feb 3 2014 Andrii Verbytskyi 1.0.4
+ Initial spec file

