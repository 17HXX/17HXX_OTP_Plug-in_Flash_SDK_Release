#record sdk version
SDK_VERSION=10.1
echo "Telink BLE SDK_VERSION = $SDK_VERSION" > ./sdk_version.txt

dir_release="BLE_SDK_V"${SDK_VERSION}

rm -rf ../$dir_release
mkdir ../$dir_release
cp -rf proj proj_lib vendor ../$dir_release
cp * .project .cproject ../$dir_release
find ../$dir_release/proj_lib -name *.c |xargs rm -rf
rm -rf ../$dir_release/release_sdk_for_17H26_ble.sh
rm -rf ../$dir_release/release_sdk_for_lenze.sh
rm -rf ../$dir_release/readme.git.txt
rm -rf ../$dir_release/readme.txt
rm -rf ../$dir_release/ven_release.bat
rm -rf ../$dir_release/build_release.bat


cp lib_17H26_l/liblt_17H26.a ../$dir_release/proj_lib

sed -i -e "3c	<name>${dir_release}</name>" ../$dir_release/.project



