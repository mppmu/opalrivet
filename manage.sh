#!/bin/bash
build_package()
{
set -x
PACKAGE=$1
TOPDIR=$(pwd)
VERSION=$(grep Version: $TOPDIR/$PACKAGE.spec | sed s'/Version://g' | tr -d ' ' )
RELEASE=$(head -n 1 $TOPDIR/$PACKAGE/VERSION  | grep evision| cut -f 2 -d\ )
if [ "x"$VERSION == "x" ]; then
VERSION=0.$(head -n 1 $TOPDIR/$PACKAGE/VERSION  | grep evision| cut -f 2 -d\ )
fi
if [ "x"$RELEASE == "x" ]; then
RELEASE=1
fi
RPM_BUILD_ROOT=$TOPDIR/temp/rpmbuild

date >> $TOPDIR/$PACKAGE/VERSION
if  [ -f $TOPDIR/$PACKAGE/share/doc/header.tex ]; then 
echo "%"$(date) >> $TOPDIR/$PACKAGE/share/doc/header.tex
fi

rm    -rf  $TOPDIR/temp/$PACKAGE
mkdir -p   $TOPDIR/temp
svn export $PACKAGE $TOPDIR/temp/$PACKAGE

cd $TOPDIR/temp
rm -rf $TOPDIR/temp/$PACKAGE.tar
tar -cf $TOPDIR/temp/$PACKAGE.tar $PACKAGE/*
rm -rf  $TOPDIR/temp/$PACKAGE.tar.gz
gzip  $TOPDIR/temp/$PACKAGE.tar
#not all systems have -k
tar -cf $TOPDIR/temp/$PACKAGE.tar $PACKAGE/*
cd $TOPDIR

mkdir -p $RPM_BUILD_ROOT/{BUILD,RPMS,SOURCES,SPECS,SRPMS}
cp $TOPDIR/temp/$PACKAGE.tar    $RPM_BUILD_ROOT/SOURCES/$PACKAGE.tar
cp $TOPDIR/temp/$PACKAGE.tar.gz $RPM_BUILD_ROOT/SOURCES/$PACKAGE.tar.gz
cp $TOPDIR/temp/$PACKAGE.tar.gz $RPM_BUILD_ROOT/SOURCES/$PACKAGE-$VERSION.tar.gz

cp $TOPDIR/$PACKAGE.spec  $RPM_BUILD_ROOT/SPECS/$PACKAGE.spec
sed -i  's/^Version.*/Version:\ '$(echo $VERSION)'/g'  $RPM_BUILD_ROOT/SPECS/$PACKAGE.spec
sed -i  's/^Release.*/Release:\ '$(echo $RELEASE)'%{?dist}/g'  $RPM_BUILD_ROOT/SPECS/$PACKAGE.spec
sed -i  's/Name.*/Name:\ '$PACKAGE'/g' $RPM_BUILD_ROOT/SPECS/$PACKAGE.spec
if [ -f /etc/debian_version ]; then
echo "Running on Debian or Ubuntu, I have to disable dependancies in spec files to build binaries"
rpmbuild -D '%_topdir '$RPM_BUILD_ROOT  -bs $RPM_BUILD_ROOT/SPECS/$PACKAGE.spec
sed -i  's/BuildRequires:/#BuildRequires:/g'  $RPM_BUILD_ROOT/SPECS/$PACKAGE.spec
sed -i  's/Requires:/#Requires:/g'       $RPM_BUILD_ROOT/SPECS/$PACKAGE.spec
rpmbuild -D '%_topdir '$RPM_BUILD_ROOT  -D '%dist .ubuntu' -bb $RPM_BUILD_ROOT/SPECS/$PACKAGE.spec
else
rpmbuild -D '%_topdir '$RPM_BUILD_ROOT   -ba $RPM_BUILD_ROOT/SPECS/$PACKAGE.spec
fi
mkdir -p $TOPDIR/temp/RPMS
mkdir -p $TOPDIR/temp/SRPMS
cp 	$RPM_BUILD_ROOT/RPMS/*/$PACKAGE*-$VERSION*.rpm $TOPDIR/temp/RPMS
cp 	$RPM_BUILD_ROOT/SRPMS/$PACKAGE*-$VERSION*src.rpm $TOPDIR/temp/SRPMS
cd $TOPDIR
}	

build_package zbestlib
