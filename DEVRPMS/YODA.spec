%define major       0
%define libname     YODA
%define libnamedev  YODA-devel
%define develnamestatic  YODA-static-devel



Name:           YODA
Version: 1.3.0
Release:        1
License:        GPLv3
Url:		http://www.YODA.fr
Source0:	http://www.hepforge.org/archive/yoda/%{name}-%{version}.tar.gz
Patch0:     patch-YODA-0.txt
Group:		Sciences/Physics
Summary:        Fast implementation of several recombination jet algorithms
BuildRequires:	gcc-gfortran gcc-c++


%description
A software package for jet finding in pp and e+e- collisions.
It includes fast native implementations of many sequential 
recombination clustering algorithms, plugins for access 
to a range of cone jet finders and tools for advanced jet manipulation. 

%package -n     bazlib
Summary:        Libraries for %{name}
Group:          System/Libraries
#Requires:       %{name}-common
Provides:       %{name} = %{version}-%{release}


%description -n     bazlib
A software package for jet finding in pp and e+e- collisions.
It includes fast native implementations of many sequential 
recombination clustering algorithms, plugins for access 
to a range of cone jet finders and tools for advanced jet manipulation. 


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
autoreconf
#./configure --prefix=$(pwd)/tmp/usr --libdir=$(pwd)/tmp/usr/%_lib --enable-root
%configure --enable-root --disable-pyext
make  %{?_smp_mflags}

%install
make install  DESTDIR=$(pwd)/tmp

mkdir -p $RPM_BUILD_ROOT/usr
cp -r $(pwd)/tmp/usr                              $RPM_BUILD_ROOT

%files 
%doc AUTHORS README COPYING

%files -n %{libname}
/usr/%_lib/*
/usr/*

/usr/bin/*

%files -n %{libnamedev}

/usr/include/YODA/*.h
/usr/include/YODA/*.icc
/usr/include/YODA/Utils/*.h
/usr/include/YODA/Config/*.h


%changelog
* Fri Jan 20 2012 FAKEAlexander Khrukin <akhrukin@mandriva.org> 3.0.2-1
+ Revision: 763348
- imported package YODA

