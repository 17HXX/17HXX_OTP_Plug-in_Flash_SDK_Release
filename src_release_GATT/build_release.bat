rem ===========================================================================
rem Copyright 2009-2015  Co., LTD.
rem
rem All rights reserved. Distribution, copying, modification, compilation
rem or any other use whatsoever of this material is strictly prohibited
rem except in accordance with a Non Disclosure Agreement and Software License
rem Agreement with  Semiconductor Co. LTD.
rem ===========================================================================
rm python_to_gen_ble_libnsdk/*.pyc;sh getver.sh
rem Build BLE projects, project list is defined in python_to_gen_ble_libnsdk/ble_projects.py
python -u python_to_gen_ble_libnsdk/build_projects.py

rem Check trtor bug
python -u python_to_gen_ble_libnsdk/check_trotrs.py

rem Create release sdk package.
python -u python_to_gen_ble_libnsdk/gen_sdk.py

rem Generate sdk eclipse .cproject file.
python python_to_gen_ble_libnsdk/gen_sdk_cproject.py
mv -f out.cproject ../sdk/.cproject

rem Generate doxygen documentation
rem doxygen doxy.conf

rem Build generated sdk package to verify correctness.
cd ../sdk
python python_to_gen_ble_libnsdk/build_sdk_projects.py
cd ../ble_lt

rem Release customer release according to python_to_gen_ble_libnsdk/customer_projects.py
python python_to_gen_ble_libnsdk/gen_customer_projects.py
python python_to_gen_ble_libnsdk/gen_customer_cproject.py