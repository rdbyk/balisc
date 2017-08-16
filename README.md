# Compilation for Linux x86_64
- `git clone -b master --depth=1 https://github.com/rdbyk/balic.git balisc_master`
- `cd balisc_master/scilab`
- `svn --force checkout https://github.com/scilab/scilab-prerequirements.git/trunk/linux_x64/ .`
- `mv usr usr_DEV`
- `mv lib lib_DEV`
- `mkdir -p lib/thirdpary`
- `cp lib_DEV/thirdparty/libjogl_*.so lib/thirdpary`
- `./configure --with-eigen-include=./usr_DEV/include`
- `make`
