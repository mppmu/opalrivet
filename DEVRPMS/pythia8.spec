Name:		pythia8
Version:	8.1.80
Release:	1%{?dist}
Summary:	Pythia Event Generator for High Energy Physics
Group:		System Environment/Libraries

License:	GPLv2
URL:		http://home.thep.lu.se/~torbjorn/Pythia.html
Source0:	http://home.thep.lu.se/~torbjorn/pythia8/pythia8180.tgz
Patch0:		%{name}-fix-soname.patch
Patch1:		%{name}-hepmc-version.patch
Patch2:		%{name}-xmldir.patch

BuildRoot:	%{_tmppath}/%{name}-%{version}-%{release}-root-%(%{__id_u} -n)
BuildRequires:	lhapdf-devel
BuildRequires:	HepMC-devel
BuildRequires:	dos2unix
Requires:	%{name}-data = %{version}-%{release}

%description
PYTHIA is a program for the generation of high-energy physics events, i.e.
for the description of collisions at high energies between elementary
particles such as e⁺, e⁻, p and p̄ in various combinations. It contains
theory and models for a number of physics aspects, including hard and soft
interactions, parton distributions, initial and final-state parton showers,
multiple interactions, fragmentation and decay.

%package devel
Summary:	Pythia 8 Development Files
Group:		Development/Libraries
Requires:	%{name}%{?_isa} = %{version}-%{release}
Requires:	lhapdf-devel%{?_isa}

%description devel
This package provides development files for Pythia 8.

%package hepmcinterface
Summary:	Pythia 8 HepMC Interface
Group:		System Environment/Libraries
Requires:	%{name}%{?_isa} = %{version}-%{release}

%description hepmcinterface
This package provides the HepMC interface for Pythia 8.

%package hepmcinterface-devel
Summary:	Pythia 8 HepMC Interface Development Files
Group:		Development/Libraries
Requires:	%{name}-hepmcinterface%{?_isa} = %{version}-%{release}
Requires:	%{name}-devel%{?_isa} = %{version}-%{release}
Requires:	HepMC-devel%{?_isa}

%description hepmcinterface-devel
This package provides development files for the HepMC interface for
Pythia 8.

%package data
Summary:	Pythia 8 Data Files
Group:		Applications/Engineering
%if %{?fedora}%{!?fedora:0} >= 10 || %{?rhel}%{!?rhel:0} >= 6
BuildArch:	noarch
%endif

%description data
This package provides XML data files for Pythia 8.

%package examples
Summary:	Pythia 8 Example Source Files
Group:		Documentation
%if %{?fedora}%{!?fedora:0} >= 10 || %{?rhel}%{!?rhel:0} >= 6
BuildArch:	noarch
%endif

%description examples
This package provides example source files for Pythia 8.

%package doc
Summary:	Pythia 8 Documentation
Group:		Documentation
%if %{?fedora}%{!?fedora:0} >= 10 || %{?rhel}%{!?rhel:0} >= 6
BuildArch:	noarch
%endif

%description doc
This package provides documentation for Pythia 8.

%prep
%setup -q -n pythia8180
%patch0 -p1
%patch1 -p1
%patch2 -p1

# Use the real lhapdf library
rm -rf lhapdfdummy

# Remove DOS end-of-line
dos2unix examples/softsusy.spc xmldoc/mrstlostarstar.00.dat \
	 phpdoc/pythia.css htmldoc/pythia.css

%build
export USRCXXFLAGS="%{optflags}"
export USRLDFLAGSSHARED="%{?__global_ldflags} -Wl,-z,defs"
%configure --enable-shared --with-hepmc=/usr
make %{?_smp_mflags} SHAREDSUFFIX=so.%{version}

%install
rm -rf %{buildroot}

mkdir -p %{buildroot}%{_libdir}
install -m 755 lib/libpythia8.so.%{version} %{buildroot}%{_libdir}
ln -s libpythia8.so.%{version} %{buildroot}%{_libdir}/libpythia8.so
install -m 755 lib/libpythia8tohepmc.so.%{version} %{buildroot}%{_libdir}
ln -s libpythia8tohepmc.so.%{version} %{buildroot}%{_libdir}/libpythia8tohepmc.so

mkdir -p %{buildroot}%{_includedir}/Pythia8
install -m 644 -p include/Pythia8/* %{buildroot}%{_includedir}/Pythia8

mkdir -p %{buildroot}%{_datadir}/%{name}-data/xmldoc
install -m 644 -p xmldoc/*.xml %{buildroot}%{_datadir}/%{name}-data/xmldoc
install -m 644 -p xmldoc/*.dat %{buildroot}%{_datadir}/%{name}-data/xmldoc
install -m 644 -p xmldoc/*.data %{buildroot}%{_datadir}/%{name}-data/xmldoc
install -m 644 -p xmldoc/*.pds %{buildroot}%{_datadir}/%{name}-data/xmldoc
install -m 644 -p xmldoc/*.tbl %{buildroot}%{_datadir}/%{name}-data/xmldoc

%clean
rm -rf %{buildroot}

%post -p /sbin/ldconfig

%postun -p /sbin/ldconfig

%post hepmcinterface -p /sbin/ldconfig

%postun hepmcinterface -p /sbin/ldconfig

%files
%{_libdir}/libpythia8.so.*
%doc AUTHORS COPYING GUIDELINES

%files devel
%{_libdir}/libpythia8.so
%{_includedir}/Pythia8
%exclude %{_includedir}/Pythia8/Pythia8ToHepMC.h
%doc CODINGSTYLE

%files hepmcinterface
%{_libdir}/libpythia8tohepmc.so.*

%files hepmcinterface-devel
%{_libdir}/libpythia8tohepmc.so
%{_includedir}/Pythia8/Pythia8ToHepMC.h

%files data
%{_datadir}/%{name}-data
%doc COPYING

%files examples
%doc COPYING examples/*.cc examples/*.cmnd examples/*.lhe examples/*.spc examples/outref

%files doc
%doc COPYING htmldoc/*.html htmldoc/*.css htmldoc/*.gif htmldoc/*.pdf

%changelog
* Wed Oct 30 2013 Mattias Ellert <mattias.ellert@fysast.uu.se> - 8.1.80-1
- Update to version 8.1.80
- Use full version in soname

* Sun Aug 04 2013 Fedora Release Engineering <rel-eng@lists.fedoraproject.org> - 8.1.76-4
- Rebuilt for https://fedoraproject.org/wiki/Fedora_20_Mass_Rebuild

* Fri May 31 2013 Mattias Ellert <mattias.ellert@fysast.uu.se> - 8.1.76-3
- Remove DOS end-of-line

* Thu May 23 2013 Mattias Ellert <mattias.ellert@fysast.uu.se> - 8.1.76-2
- Fix race condition in Makefile
- Add isa to dependencies

* Sat May 18 2013 Mattias Ellert <mattias.ellert@fysast.uu.se> - 8.1.76-1
- New upstream release

* Wed Nov 14 2012 Mattias Ellert <mattias.ellert@fysast.uu.se> - 8.1.70-1
- Initial build
