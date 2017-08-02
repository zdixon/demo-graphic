#!/bin/sh

make clean

if [ "$1" == "fm" ]; then
    echo "This is fm! Set up for Fumeng only."
    export MINVR_ROOT=/Users/fm/Documents/Github/MinVR
    # cmake .. -DMINVR_INSTALL_DIR=/Users/fm/Documents/Github/MinVR/build/install/
    cmake -G"Eclipse CDT4 - Unix Makefiles" -D CMAKE_BUILD_TYPE=Debug ../code/ -DMINVR_INSTALL_DIR=/Users/fm/Documents/Github/MinVR/build/install/
else
    cmake ../code/  -DMINVR_INSTALL_DIR=$1
fi

make


lowercase(){
    echo "$1" | sed "y/ABCDEFGHIJKLMNOPQRSTUVWXYZ/abcdefghijklmnopqrstuvwxyz/"
}

OS=`lowercase \`uname\``
KERNEL=`uname -r`
MACH=`uname -m`

if [ "{$OS}" == "windowsnt" ]; then
    OS=windows
    echo "This is windows"
    if [ ${MACH} == 'x86_64' ]; then
  		# 64-bit stuff here
  		echo "This is win64. Copy mysql libraies for win64"
    	cp "../code/external/mysql/win64/lib/mysqlcppconn.dll" "./mysqlcppconn.dll"

	else
  		# 32-bit stuff here
  		echo "This is win32. Copy mysql libraies for win64"
    	cp "../code/external/mysql/win32/lib/mysqlcppconn.dll" "./mysqlcppconn.dll"
	fi
elif [ "$OS" == "darwin" ]; then
    echo "This is Mac. Copy mysql libraies for macos"
    cp "../code/external/mysql/macos/lib/libmysqlcppconn.7.1.1.9.dylib" "./libmysqlcppconn.7.1.1.9.dylib"
else
    OS=`uname`
    if [ "${OS}" = "SunOS" ] ; then
        OS=Solaris
        ARCH=`uname -p`
        OSSTR="${OS} ${REV}(${ARCH} `uname -v`)"
    elif [ "${OS}" = "AIX" ] ; then
        OSSTR="${OS} `oslevel` (`oslevel -r`)"
    elif [ "${OS}" = "Linux" ] ; then
        if [ -f /etc/redhat-release ] ; then
            DistroBasedOn='RedHat'
            DIST=`cat /etc/redhat-release |sed s/\ release.*//`
            PSUEDONAME=`cat /etc/redhat-release | sed s/.*\(// | sed s/\)//`
            REV=`cat /etc/redhat-release | sed s/.*release\ // | sed s/\ .*//`
        elif [ -f /etc/SuSE-release ] ; then
            DistroBasedOn='SuSe'
            PSUEDONAME=`cat /etc/SuSE-release | tr "\n" ' '| sed s/VERSION.*//`
            REV=`cat /etc/SuSE-release | tr "\n" ' ' | sed s/.*=\ //`
        elif [ -f /etc/mandrake-release ] ; then
            DistroBasedOn='Mandrake'
            PSUEDONAME=`cat /etc/mandrake-release | sed s/.*\(// | sed s/\)//`
            REV=`cat /etc/mandrake-release | sed s/.*release\ // | sed s/\ .*//`
        elif [ -f /etc/debian_version ] ; then
            DistroBasedOn='Debian'
            DIST=`cat /etc/lsb-release | grep '^DISTRIB_ID' | awk -F=  '{ print $2 }'`
            PSUEDONAME=`cat /etc/lsb-release | grep '^DISTRIB_CODENAME' | awk -F=  '{ print $2 }'`
            REV=`cat /etc/lsb-release | grep '^DISTRIB_RELEASE' | awk -F=  '{ print $2 }'`
        fi
        if [ -f /etc/UnitedLinux-release ] ; then
            DIST="${DIST}[`cat /etc/UnitedLinux-release | tr "\n" ' ' | sed s/VERSION.*//`]"
        fi
        OS=`lowercase $OS`
        DistroBasedOn=`lowercase $DistroBasedOn`
        readonly OS
        readonly DIST
        readonly DistroBasedOn
        readonly PSUEDONAME
        readonly REV
        readonly KERNEL
        readonly MACH
    fi
fi

