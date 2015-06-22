Name:		HepMC
Version:	2.06.09
Release:	3%{?dist}
Summary:	C++ Event Record for Monte Carlo Generators
Group:		System Environment/Libraries

License:	GPLv2+
URL:		http://lcgapp.cern.ch/project/simu/HepMC/
Source0:	http://lcgapp.cern.ch/project/simu/HepMC/download/%{name}-%{version}.tar.gz
Patch0:		%{name}-fix-typo-hierachy-hierarchy.patch
Patch1:		%{name}-examples-makefile.patch
Patch2:		%{name}-examples-hwaend.patch
Patch3:		%{name}-linking.patch
Prefix: /usr

BuildRoot:	%{_tmppath}/%{name}-%{version}-%{release}-root-%(%{__id_u} -n)

%description
The HepMC package is an object oriented event record written in C++
for High Energy Physics Monte Carlo Generators. Many extensions from
HEPEVT, the Fortran HEP standard, are supported: the number of entries
is unlimited, spin density matrices can be stored with each vertex,
flow patterns (such as color) can be stored and traced, integers
representing random number generator states can be stored, and an
arbitrary number of event weights can be included. Particles and
vertices are kept separate in a graph structure, physically similar to
a physics event. The added information supports the modularization of
event generators. The package has been kept as simple as possible with
minimal internal/external dependencies. Event information is accessed
by means of iterators supplied with the package.

%package devel
Summary:	C++ Event Record for Monte Carlo Generators - development files
Group:		Development/Libraries
Requires:	%{name}%{?_isa} = %{version}-%{release}

%description devel
This package provides development files of HepMC.

%package doc
Summary:	C++ Event Record for Monte Carlo Generators - documentation
Group:		Documentation
%if %{?fedora}%{!?fedora:0} >= 10 || %{?rhel}%{!?rhel:0} >= 6
BuildArch:	noarch
%endif

%description doc
This package provides HepMC manuals and examples.

%prep
%setup -q
%patch0 -p1
%patch1 -p1
%patch2 -p1
%patch3 -p1

chmod 644 ChangeLog

%build
%configure --with-momentum=GEV --with-length=MM --disable-static
make %{?_smp_mflags}

%install
rm -rf %{buildroot}
make install DESTDIR=%{buildroot}

rm %{buildroot}%{_libdir}/libHepMC.la
rm %{buildroot}%{_libdir}/libHepMCfio.la

rm %{buildroot}%{_datadir}/%{name}/examples/pythia8/config.sh
rm %{buildroot}%{_datadir}/%{name}/examples/pythia8/config.csh
rm %{buildroot}%{_datadir}/%{name}/examples/pythia8/README

mkdir -p %{buildroot}%{_docdir}/%{name}-doc-%{version}
mv %{buildroot}%{_datadir}/%{name}/examples \
   %{buildroot}%{_docdir}/%{name}-doc-%{version}
mv %{buildroot}%{_datadir}/%{name}/doc/HepMC2_reference_manual.pdf \
   %{buildroot}%{_docdir}/%{name}-doc-%{version}/%{name}-reference-manual.pdf
mv %{buildroot}%{_datadir}/%{name}/doc/HepMC2_user_manual.pdf \
   %{buildroot}%{_docdir}/%{name}-doc-%{version}/%{name}-user-manual.pdf
install -p -m 644 COPYING %{buildroot}%{_docdir}/%{name}-doc-%{version}

%check
make check

%post -p /sbin/ldconfig

%postun -p /sbin/ldconfig

%files
%{_libdir}/libHepMC.so.*
%{_libdir}/libHepMCfio.so.*
%doc AUTHORS ChangeLog COPYING README

%files devel
%{_libdir}/libHepMC.so
%{_libdir}/libHepMCfio.so
%{_includedir}/%{name}

%files doc
%dir %{_docdir}/%{name}-doc-%{version}
%doc %{_docdir}/%{name}-doc-%{version}/examples
%doc %{_docdir}/%{name}-doc-%{version}/*.pdf
%doc %{_docdir}/%{name}-doc-%{version}/COPYING

%changelog
* Wed Jun 05 2013 Mattias Ellert <mattias.ellert@fysast.uu.se> - 2.06.09-3
- Make doc package independent

* Wed May 22 2013 Mattias Ellert <mattias.ellert@fysast.uu.se> - 2.06.09-2
- Add isa to dependencies

* Fri Nov 16 2012 Mattias Ellert <mattias.ellert@fysast.uu.se> - 2.06.09-1
- Initial build
