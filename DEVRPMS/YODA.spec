%define major       0
%define libname     YODA
%define libnamedev  YODA-devel
%define develnamestatic  YODA-static-devel



Name:           YODA
Version:        1.0.6
Release:        1
License:        GPLv3
Url:		http://www.YODA.fr
Source0:	http://www.hepforge.org/archive/yoda/%{name}-%{version}.tar.gz
#Patch0: patch0.txt
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
#%patch0 -p0

%build
autoreconf
#./configure  
#--prefix=%{_prefix} 
#--libdir=%{_libdir}
#mkdir -p $(pwd)/tmp/usr
#mkdir -p $(pwd)/tmp/%_lib
#./configure --prefix=$(pwd)/tmp/usr --libdir=$(pwd)/tmp/usr/%_lib --enable-root
%configure --enable-root
make  %{?_smp_mflags}

%install
make install  DESTDIR=$(pwd)/tmp
#sed -i s@$(pwd)/tmp/usr/%_lib@/usr/%_lib@g  $(pwd)/tmp/usr/%_lib/*.la
#sed -i s@$(pwd)/tmp/usr@/usr@g  $(pwd)/tmp/usr/bin/yoda-config

mkdir -p $RPM_BUILD_ROOT/usr
cp -r $(pwd)/tmp/usr                              $RPM_BUILD_ROOT

%files 
%doc AUTHORS README COPYING

%files -n %{libname}
/usr/%_lib/python2.6/site-packages/yoda/*
/usr/%_lib/python2.6/site-packages/yoda-*-info
/usr/%_lib/libYODA.la
/usr/%_lib/libYODA.so

/usr/share/YODA/yoda-completion

/usr/bin/*

%files -n %{libnamedev}

/usr/include/YODA/*.h
/usr/include/YODA/*.icc
/usr/include/YODA/Utils/*.h
/usr/include/YODA/Config/*.h


%changelog
* Fri Jan 20 2012 Alexander Khrukin <akhrukin@mandriva.org> 3.0.2-1
+ Revision: 763348
- imported package YODA

