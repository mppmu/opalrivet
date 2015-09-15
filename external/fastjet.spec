%define major       0
%define libname     fastjet
%define libnamedev  fastjet-devel
%define develnamestatic  fastjet-static-devel



Name:           fastjet
Version:        3.1.2
Release:        1
License:        GPLv3
Url:		http://www.fastjet.fr
Source0:	http://www.fastjet.fr/repo/%{name}-%{version}.tar.gz
Group:		Sciences/Physics
Prefix: /usr
Summary:        Fast implementation of several recombination jet algorithms
#BuildRequires:	gcc-gfortran gcc-c++

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



%package 	static-devel
License:	BSD-like
Summary:	Library for accessing files in FITS format for C and Fortran
Group:		System/Libraries
#Requires:	%{libnamedev} = %version
#Requires:	%libname = %version

%description static-devel
This package contains the headers required for compiling software that uses
the %{name} library


%prep
%setup -q

%build
mkdir -p $(pwd)/tmp/usr
mkdir -p $(pwd)/tmp/%_lib
./configure --enable-allplugins --prefix=$(pwd)/tmp/usr --libdir=$(pwd)/tmp/usr/%_lib
#./configure --enable-allplugins --prefix=%{buildroot}%{_prefix} --libdir=%{buildroot}%{_libdir}
make

%install
make install
sed -i s@$(pwd)/tmp/usr/%_lib@/usr/%_lib@g  $(pwd)/tmp/usr/%_lib/*.la
sed -i s@$(pwd)/tmp/usr@/usr@g  $(pwd)/tmp/usr/bin/fastjet-config

mkdir -p $RPM_BUILD_ROOT/usr
cp -r $(pwd)/tmp/usr                              $RPM_BUILD_ROOT
find $RPM_BUILD_ROOT -type f -name '*.la' -exec rm -f {} \;

%files 
%doc AUTHORS README COPYING

%files -n %{libname}
%{_bindir}/%{name}-config
%{_libdir}/libfastjet.so
%{_libdir}/libfastjet.so.0
%{_libdir}/libfastjet.so.0.0.0
%{_libdir}/libfastjetplugins.so*
%{_libdir}/libfastjettools.so*
%{_libdir}/libsiscone.so*
%{_libdir}/libsiscone_spherical.so*

%files -n %{libnamedev}

#/usr/lib64/libfastjet.so.0
#/usr/lib64/libfastjettools.so
#/usr/lib64/libfastjet.so.0.0.0
#/usr/lib64/libfastjetplugins.la
#/usr/lib64/libfastjet.so
#/usr/lib64/
#/usr/lib64/libfastjettools.a
#/usr/lib64/libfastjetplugins.so.0
#/usr/lib64/libfastjetplugins.a
#/usr/lib64/libfastjet.la
#/usr/lib64/libfastjettools.la
#/usr/lib64/libfastjetplugins.so.0.0.0
#/usr/lib64/libfastjetplugins.so
#/usr/lib64/libfastjettools.so.0
#/usr/lib64/libfastjettools.so.0.0.0



%{_libdir}/libfastjet.so
%{_libdir}/libfastjettools.so
%{_libdir}/libsiscone.so
%{_libdir}/libsiscone_spherical.so
%{_libdir}/libfastjetplugins.so
#%{_includedir}/*.h
%{_includedir}/siscone/*.h
%{_includedir}/siscone/spherical/*.h
%{_includedir}/fastjet/*.h
%{_includedir}/fastjet/*.hh
%{_includedir}/fastjet/tools/*.hh
%{_includedir}/fastjet/internal/*.hh


%files -n %{develnamestatic}
%{_libdir}/*.a



%changelog
* Fri Jan 20 2012 Alexander Khrukin <akhrukin@mandriva.org> 3.0.2-1
+ Revision: 763348
- imported package fastjet


