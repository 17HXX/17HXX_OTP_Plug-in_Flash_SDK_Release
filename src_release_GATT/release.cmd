cd..
mkdir src_release
xcopy src src_release
cd src_release
mkdir vendor
xcopy ..\src\vendor\* vendor /s
mkdir proj
xcopy ..\src\proj\* proj /s
mkdir proj_lib
xcopy ..\src\proj_lib\*.h proj_lib /s
xcopy ..\src\proj_lib\*.a proj_lib /s
xcopy ..\src\proj_lib\ble_l2cap\ble_ll_ota.c proj_lib\ble_l2cap

pause