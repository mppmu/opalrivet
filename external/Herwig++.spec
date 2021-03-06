%define major       0
%define libname     Herwig++
%define libnamedev  Herwig++-devel
%define develnamestatic  Rivet-static-devel




Name:         Herwig++
Version:      2.7.0
Release:      1

Summary:      Herwig++ is a C++ Monte Carlo event generator.
License:      GPL
Source0:	  http://www.hepforge.org/archive/herwig/%{name}-%{version}.tar.bz2
Patch0:         patch-Herwig++-0.txt
Group:		  Sciences/Physics
Url:	      http://projects.hepforge.org/herwig/
BuildRequires: gcc-c++   gsl-devel
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
%patch0 -p1

%build
autoreconf -fisv
mkdir -p $(pwd)/tmp/usr
mkdir -p $(pwd)/tmp/%_lib
%configure --with-thepeg=%_prefix --prefix=/usr --libdir=/usr/%_lib --with-hepmc
make %{?_smp_mflags} 

%install
make install DESTDIR=$(pwd)/tmp 
#sed -i s@$(pwd)/tmp/usr/@/usr/@g  $(pwd)/tmp/usr/%_lib/Herwig++/*rpo
#sed -i s@$(pwd)/tmp/usr/@/usr/@g  $(pwd)/tmp/usr/%_lib/defaults/PDF.in
#sed -i s@$(pwd)/tmp/usr/@/usr/@g  $(pwd)/tmp/usr/share/Herwig++/*rpo
#sed -i s@$(pwd)/tmp/usr/@/usr/@g  $(pwd)/tmp/usr/share/Herwig++/defaults/PDF.in

#--with-thepeg=%_prefix --prefix=/usr --libdir=/usr/%_lib

mkdir -p $RPM_BUILD_ROOT/usr
cp -r $(pwd)/tmp/usr                              $RPM_BUILD_ROOT



%files 
%doc AUTHORS README COPYING

%files -n %{libname}
%_bindir/*
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
