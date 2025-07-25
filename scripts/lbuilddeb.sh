if [ $# -lt 1 ]; then
    echo ""
    echo "    --build-d    Build for /usr/local/lib"
    echo "    --build-t    Build for /data/data/com.termux/files/usr/lib"
    exit 1
fi


TMP_BUILDDEB=./build/deb
GENTMP=$TMP_BUILDDEB/libbigdecimal
mkdir ./build 2>/dev/null
mkdir ./build/deb/ 2>/dev/null

rm -r $GENTMP
mkdir $GENTMP
mkdir $GENTMP/DEBIAN
if [ $1 = "--build-t" ]; then
mkdir $GENTMP/data
mkdir $GENTMP/data/data
mkdir $GENTMP/data/data/com.termux
mkdir $GENTMP/data/data/com.termux/files
mkdir $GENTMP/data/data/com.termux/files/usr/
LIBPREFIX=$GENTMP/data/data/com.termux/files/usr/lib
fi
if [ $1 = "--build-d" ]; then
mkdir $GENTMP/usr
mkdir $GENTMP/usr/local
mkdir $GENTMP/usr/local/lib
LIBPREFIX=$GENTMP/usr/local/lib
fi
if [ -z "$LIBPREFIX" ]; then
exit 1
else
mkdir $LIBPREFIX
cp ./build/libbigdecimal.so $LIBPREFIX
echo "Package: libbigdecimal
Version: 0.1.2
Section: utils
Priority: optional
Architecture: $(uname -m)
Maintainer: VeryrrDefine <1308061599@qq.com>
Description: A big decimal library" > $GENTMP/DEBIAN/control
chmod 755 $GENTMP/DEBIAN/

cd $TMP_BUILDDEB
dpkg-deb --build libbigdecimal
fi
