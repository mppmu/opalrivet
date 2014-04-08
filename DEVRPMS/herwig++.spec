%define major       0
%define libname     Herwig++
%define libnamedev  Herwig++-devel
%define develnamestatic  Rivet-static-devel




Name:         Herwig++
Version:      2.7.0
Release:      1

Summary:      Herwig++ is a C++ Monte Carlo event generator.
License:      GPL
Url:		  http://rivet.hepforge.org/
Source0:	  http://www.hepforge.org/archive/rivet/%{name}-%{version}.tar.gz
Group:		  Sciences/Physics
Url:	      http://projects.hepforge.org/herwig/
BuildRequires: gcc-c++ gcc-g77 gsl-devel
BuildRequires: ThePEG-devel

%package -n     bazlib
Summary:        Libraries for %{name}
Group:          System/Libraries
Provides:       %{name} = %{version}-%{release}



%description
%summary

%package devel
Summary: Herwig++ the C++ Monte Carlo event generator development files.
Group:   Development/C++
Requires: %name = %version-%release

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
autoreconf -fisv
%configure --with-thepeg=%_prefix
%make 

%install
export LD_LIBRARY_PATH=%_libdir/ThePEG
%makeinstall



%files 
%doc AUTHORS README COPYING

%files -n %{libname}
%_bindir/Herwig++
%_datadir/Herwig++
%_libdir/Herwig++



%files -n %{libnamedev}
%_bindir/herwig-config
%_includedir/Herwig++
%_libdir/Herwig++/*.so
%_libdir/Herwig++/*.la

%changelog
* Thu Oct 22 2009 Igor Vlasenko <viy@altlinux.ru> 2.4.0-alt1
- first build for Sisyphus
