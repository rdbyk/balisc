# Balisc
- is an **_experiment_**, and
- detects **_SIMD extensions_** (SSE2/SSE4/AVX/...) and uses it (currently, just a little bit)
- improves **_run-time performance_** of various functions in `string`, `elementary_functions`, ... modules
- tries **_cleaning_** and **_simplification_** of code base (huge on-going task)
- will drop MSVC support and switch to MINGW/MSYS2 (not finally decided, just thinking about it)
- ...
## Is it for me?
We don't know, but you may try running this

```scilab
A=string(rand(1000,1000));
tic;strcat(A);toc
```

under current [**_Scilab 6.x_**](http://www.scilab.org/en/development/nightly_builds/master). In the meantime, you might think about compiling **_Balisc_** by yourself (cf. below) and executing the very same instuctions on your freshly built **_Balisc_**. This could confront you with a result like this.

```scilab
--> A=string(rand(1000,1000));
--> tic;strcat(A);toc
 ans  =

   0.139977
```
Please, don't take this example too seriously, it is just an extreme example chosen for pedagogic reasons. *Scilab is a very powerful and comprehensive tool*.
## Compilation with GCC for Linux x86_64
You may want to follow the the instructions [Compilation of Scilab](https://wiki.scilab.org/Compilation%20of%20Scilab) (probably not up-to-date), or follow the **_procedure described below_**, which assumes, that you have installed all required non-Java stuff on your
system ([Dependencies of Scilab 5.X](https://wiki.scilab.org/Dependencies%20of%20Scilab%205.X), probably not up-to-date).

Please note, that **_Balisc_** additionally needs **_SLEEF (SIMD Library for Evaluating Elementary Functions)_**, under Ubuntu you may install the *SLEEF* library from this [PPA](https://launchpad.net/~shibatch/+archive/ubuntu/sleef).

**_What else is needed?_** For the time being, just run `configure` (cf. below), and see what is missing, install the missing libraries, and re-run `configure` ... and so on ...

- `cd <PATH>`
- `git clone -b master --depth=1 https://github.com/rdbyk/balic.git balisc_master`
- `cd balisc_master/scilab`
- `svn --force checkout https://github.com/scilab/scilab-prerequirements.git/trunk/linux_x64/ .`
- `mv usr usr_DEV`
- `mv lib lib_DEV`
- `mkdir -p lib/thirdparty`
- `cp lib_DEV/thirdparty/libjogl_*.so lib/thirdparty`
- `./configure --with-eigen-include=<PATH>/balisc_master/scilab/usr_DEV/include`
- `make`
