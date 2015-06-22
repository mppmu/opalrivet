%define major       0
%define libname     YODA
%define libnamedev  YODA-devel
%define develnamestatic  YODA-static-devel

Name:           YODA
Version: 1.3.1
Release:        1
License:        GPLv3
Url:		http://www.YODA.fr
Source0:	http://www.hepforge.org/archive/yoda/%{name}-%{version}.tar.gz
Group:		Sciences/Physics
Prefix: /usr
Summary:        Fast implementation of several recombination jet algorithms
BuildRequires:	 /usr/bin/g++ /usr/bin/Cython


%description
Junk software inspired by NIH syndrom, needed for Rivet.

%package -n     bazlib
Summary:        Libraries for %{name}
Group:          System/Libraries
#Requires:       %{name}-common
Provides:       %{name} = %{version}-%{release}


%description -n     bazlib
Junk software inspired by NIH syndrom, needed for Rivet.

%package  devel
Summary:        Libraries and headers for %{name}
Group:          Development/C
Provides:       %{name}-devel = %{version}-%{release}

%description devel
%{libnamedev} contains the libraries and header files needed to
develop programs which make use of %{name}.

%prep
%setup -q

%build
%configure --disable-pyext
make

%install
make install  DESTDIR=$RPM_BUILD_ROOT

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
* Mon Jun 22 2015 Andrii Verbytskyi <andrii.verbytskyi@desy.de> 1.3.1-1
- imported package YODA

