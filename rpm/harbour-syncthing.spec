Name:       harbour-syncthing

# >> macros
%global _missing_build_ids_terminate_build 0
%define syncthing_version 1.27.7
# << macros

%{!?qtc_qmake:%define qtc_qmake %qmake}
%{!?qtc_qmake5:%define qtc_qmake5 %qmake5}
%{!?qtc_make:%define qtc_make make}
%{?qtc_builddir:%define _builddir %qtc_builddir}
Summary:    Syncthing
Version:    0.0.2
Release:    1
Group:      Qt/Qt
License:    GPLv3
URL:        https://scarpino.dev
Source0:    %{name}-%{version}.tar.bz2
%ifarch %arm
Source1: syncthing-linux-arm-v%{syncthing_version}.tar.gz
%endif
%ifarch aarch64
Source1: syncthing-linux-arm64-v%{syncthing_version}.tar.gz
%endif
%ifarch %ix86
Source1: syncthing-linux-386-v%{syncthing_version}.tar.gz
%endif
Source2:    syncthing.service
Requires:   sailfishsilica-qt5 >= 0.10.9
BuildRequires:  pkgconfig(sailfishapp) >= 1.0.2
BuildRequires:  pkgconfig(Qt5Core)
BuildRequires:  pkgconfig(Qt5Qml)
BuildRequires:  pkgconfig(Qt5Quick)
BuildRequires:  pkgconfig(Qt5Xml)
BuildRequires:  desktop-file-utils

%ifarch %arm
%define syncthing_dir syncthing-linux-arm-v%{syncthing_version}
%endif
%ifarch aarch64
%define syncthing_dir syncthing-linux-arm64-v%{syncthing_version}
%endif
%ifarch %ix86
%define syncthing_dir syncthing-linux-386-v%{syncthing_version}
%endif

%description
Open Source Continuous Replication / Cluster Synchronization Thing.

%prep
%setup -q -n %{name}-%{version}

#%setup -a 1 doesn't work in mb2
if [ ! -d %{_sourcedir}/%{syncthing_dir} ]; then
  tar xf %{SOURCE1} -C %{_sourcedir}
fi

# >> setup
# << setup

%build
# >> build pre
# << build pre

%qtc_qmake5

%qtc_make %{?_smp_mflags}

# >> build post
# << build post

%install
rm -rf %{buildroot}
# >> install pre
# << install pre
%qmake5_install

# >> install post
install -d %{buildroot}%{_userunitdir}
install -m644 %{SOURCE2} %{buildroot}%{_userunitdir}

install -m755 %{_sourcedir}/%{syncthing_dir}/syncthing %{buildroot}%{_bindir}
# << install post

desktop-file-install --delete-original       \
  --dir %{buildroot}%{_datadir}/applications             \
   %{buildroot}%{_datadir}/applications/*.desktop

%files
%defattr(-,root,root,-)
%{_bindir}/syncthing
%{_bindir}/%{name}
%{_datadir}/%{name}
%{_userunitdir}/syncthing.service
%{_datadir}/applications/%{name}.desktop
%{_datadir}/icons/hicolor/*/apps/%{name}.png
# >> files
# << files

%post
systemctl-user daemon-reload

%preun
if [ $1 -eq 0 ]; then
  systemctl-user stop syncthing.service
fi

%postun
systemctl-user daemon-reload
