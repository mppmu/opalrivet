%define major       0
%define libname     Herwig++
%define libnamedev  Herwig++-devel
%define develnamestatic  Rivet-static-devel




Name:         Herwig++
Version:      2.7.0
Release:      1

Summary:      Herwig++ is a C++ Monte Carlo event generator.
License:      GPL
Source0:	  http://www.hepforge.org/archive/rivet/%{name}-%{version}.tar.bz2
Group:		  Sciences/Physics
Url:	      http://projects.hepforge.org/herwig/
BuildRequires: gcc-c++  /usr/bin/g77 gsl-devel
#BuildRequires: ThePEG-devel


%description
The Rivet project (Robust Independent Validation of Experiment and Theory) 
is a toolkit for validation of Monte Carlo event generators. It provides a
large (and ever growi


%package -n     bazlib
Summary:        Libraries for %{name}
Group:          System/Libraries
Provides:       %{name} = %{version}-%{release}

%description -n     bazlib
Herwig

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
mkdir -p $(pwd)/tmp/usr
mkdir -p $(pwd)/tmp/%_lib
%configure --with-thepeg=%_prefix --prefix=$(pwd)/tmp/usr --libdir=$(pwd)/tmp/usr/%_lib
make %{?_smp_mflags}

%install
make install

mkdir -p $RPM_BUILD_ROOT/usr
cp -r $(pwd)/tmp/usr                              $RPM_BUILD_ROOT



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
