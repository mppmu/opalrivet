%define major       0
%define libname     SHERPA-MC
%define libnamedev  SHERPA-MC-devel
%define develnamestatic  SHERPA-MC-static-devel



Name:           SHERPA-MC
Version:        2.1.0
Release:        1
License:        GPLv3
Url:		    https://sherpa.hepforge.org
Source0:	    http://www.hepforge.org/archive/sherpa/%{name}-%{version}.tar.gz
#Patch0:         patch-SHERPA-0.txt
Group:		    Sciences/Physics
Summary:        Sherpa is a Monte Carlo event generator
BuildRequires:	gcc-gfortran gcc-c++ root HepMC-devel 


%description
Sherpa is a Monte Carlo event generator for the Simulation of High-Energy 
Reactions of PArticles in lepton-lepton, lepton-photon, photon-photon, 
lepton-hadron and hadron-hadron collisions. Simulation programs - also 
dubbed event generators - like Sherpa are indispensable work horses for 
current particle physics phenomenology and are (at) the interface between 
theory and experiment.  

%package -n     bazlib
Summary:        Libraries for %{name}
Group:          System/Libraries
#Requires:       %{name}-common
Provides:       %{name} = %{version}-%{release}


%description -n     bazlib
Sherpa is a Monte Carlo event generator for the Simulation of High-Energy 
Reactions of PArticles in lepton-lepton, lepton-photon, photon-photon, 
lepton-hadron and hadron-hadron collisions. Simulation programs - also 
dubbed event generators - like Sherpa are indispensable work horses for 
current particle physics phenomenology and are (at) the interface between 
theory and experiment. 

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
mkdir -p $(pwd)/tmp/usr
mkdir -p $(pwd)/tmp/%_lib
./configure --enable-hepmc2=/usr --enable-rivet --enable-root  --enable-binreloc --prefix=$(pwd)/tmp/usr --libdir=$(pwd)/tmp/usr/%_lib
make  %{?_smp_mflags}

%install
make install
sed -i s@$(pwd)/tmp/usr@/usr@g  $(pwd)/tmp/usr/bin/Sherpa-*
#sed -i s@$(pwd)/tmp/usr@/usr@g  $(pwd)/tmp/usr/%_lib/SHERPA-MC/*a
sed -i s@$(pwd)/tmp/usr@/usr@g  $(pwd)/tmp/usr/include/SHERPA-MC/ATOOLS/*/*H
mkdir -p $RPM_BUILD_ROOT/usr
cp -r $(pwd)/tmp/usr                              $RPM_BUILD_ROOT
rm -rf $RPM_BUILD_ROOT/usr/share/info/dir
%files 
%doc AUTHORS README COPYING






%files -n %{libname}
/usr/%_lib/SHERPA-MC/*.so*
/usr/%_lib/SHERPA-MC/*a
/usr/bin/*

%files -n %{libnamedev}

/usr/share/SHERPA-MC/*
/usr/share/man/man1
/usr/share/man/man1/*
/usr/share/doc/*
/usr/share/info/*
/usr/include/SHERPA-MC/*




%changelog
* Mon Feb 3 2014 Andrii Verbytskyi 1.0.4
+ Initial spec file

