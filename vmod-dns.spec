Summary: DNS VMOD for Varnish
Name: vmod-varnish-%{VARNISHVER}-dns
Version: 0.1
Release: 1%{?dist}
License: BSD
Group: System Environment/Daemons
Source0: libvmod-dns.tar.gz
BuildRoot: %{_tmppath}/%{name}-%{version}-%{release}-root-%(%{__id_u} -n)
Requires: varnish >= 4.0
BuildRequires: make, python-docutils

%description
DNS VMOD

%prep
%setup -n libvmod-dns

%build
./configure --prefix=/usr/
make

%install
make install DESTDIR=%{buildroot}
mkdir -p %{buildroot}/usr/share/doc/%{name}/
cp README.rst %{buildroot}/usr/share/doc/%{name}/
cp LICENSE %{buildroot}/usr/share/doc/%{name}/

%clean
rm -rf %{buildroot}

%files
%defattr(-,root,root,-)
%{_libdir}/varnish/vmods/
%doc /usr/share/doc/%{name}/*
%{_mandir}/man?/*

%changelog
* Mon Apr 01 2013 Kenneth Shaw <kenshaw@gmail.com> - 0.1-0.20130401
- Initial version.
