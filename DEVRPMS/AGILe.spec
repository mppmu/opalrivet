%define major       0
%define libname     AGILe
%define libnamedev  AGILe-devel
%define develnamestatic  AGILe-static-devel



Name:           AGILe
Version:        1.4.1
Release:        1
License:        GPLv3
Url:		    http://rivet.hepforge.org/
Source0:	    http://www.hepforge.org/archive/rivet/%{name}-%{version}.tar.gz
#Patch0:         patch-AGILe-0.txt
Group:		    Sciences/Physics
Summary:        Robust Independent Validation of Experiment and Theory
BuildRequires:	gcc-gfortran gcc-c++ YODA YODA-devel boost-devel

%description
The AGILe project (Robust Independent Validation of Experiment and Theory) 
is a toolkit for validation of Monte Carlo event generators. It provides a
large (and ever growing) set of experimental analyses useful for MC generator 
development, validation, and tuning, as well as a convenient infrastructure for
 adding your own analyses. AGILe is the most widespread way by which analysis code 
 from the LHC and other high-energy collider experiments is preserved for comparison 
 to and development of future theory models. 

%package -n     bazlib
Summary:        Libraries for %{name}
Group:          System/Libraries
#Requires:       %{name}-common
Provides:       %{name} = %{version}-%{release}

%description -n     bazlib
The AGILe project (Robust Independent Validation of Experiment and Theory) 
is a toolkit for validation of Monte Carlo event generators. It provides a
large (and ever growing) set of experimental analyses useful for MC generator 
development, validation, and tuning, as well as a convenient infrastructure for
 adding your own analyses. AGILe is the most widespread way by which analysis code 
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


%build
mkdir -p $(pwd)/tmp/usr
mkdir -p $(pwd)/tmp/%_lib
./configure  --prefix=$(pwd)/tmp/usr --libdir=$(pwd)/tmp/usr/%_lib --with-hepmc-libpath=/usr/%_lib
make %{?_smp_mflags}

%install
make install
sed -i s@$(pwd)/tmp/usr/%_lib@/usr/%_lib@g  $(pwd)/tmp/usr/%_lib/*.la
sed -i s@$(pwd)/tmp/usr/%_lib@/usr/%_lib@g  $(pwd)/tmp/usr/%_lib/*.la
sed -i s@$(pwd)/tmp/usr@/usr@g  $(pwd)/tmp/usr/bin/agile-*
mkdir -p $RPM_BUILD_ROOT/usr
cp -r $(pwd)/tmp/usr                              $RPM_BUILD_ROOT

%files 
%doc AUTHORS README COPYING

%files -n %{libname}

%{_bindir}/*
/usr/%_lib/*

%files -n %{libnamedev}
%{_includedir}/AGILe/*h
/usr/share/AGILe/*
%{_includedir}/AGILe/AlpGen/*hh
%{_includedir}/AGILe/Ariadne/*hh
%{_includedir}/AGILe/Cascade/*hh
%{_includedir}/AGILe/Charybdis/*hh
%{_includedir}/AGILe/FHerwig/*hh
%{_includedir}/AGILe/FPythia/*hh
%{_includedir}/AGILe/Phojet/*hh
%{_includedir}/AGILe/Rapgap/*hh
%{_includedir}/AGILe/Tools/*hh




%changelog
* Mon Feb 3 2014 Andrii Verbytskyi 1.0.4
+ Initial spec file

