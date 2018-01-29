# Balisc
- is an **_experiment_**, and
- detects **_SIMD extensions_** (SSE2/SSE4/AVX/...) and uses it (currently, just a little bit)
- improves **_run-time performance_** of various functions in `string`, `elementary_functions`, ... modules
- tries **_cleaning_** and **_simplification_** of code base (huge on-going task)
- _**dropped MSVC**_ support and will switch to _**MINGW/MSYS2**_ for Windows support (in the long run)
- currently runs on  _**Linux 64bit only**_, but is _**fully compatible**_ with current _**Scilab 6.x**_
- ...
## Is it for me?
We don't know, but you may try running this

```scilab
A=string(rand(1000,1000));
tic;B=strcat(A);toc
```

first, and then

```scilab
tic;strsubst(B,"3","X");toc
```

under current [**_Scilab 6.x_**](http://www.scilab.org/en/development/nightly_builds/master). In the meantime, you might think about compiling **_Balisc_** by yourself (cf. below) and executing the very same instuctions on your freshly built **_Balisc_**. This could confront you with a result like this.

```scilab
--> A=string(rand(1000,1000));
--> tic;B=strcat(A);toc
 ans  =

   0.063398
--> tic;strsubst(B,"3","X");toc
 ans  =

   0.095663
```

Please, don't take this example too seriously, it is just an extreme example chosen for pedagogic reasons. *Scilab is a very powerful and comprehensive tool*.

### Try some of Scilab's Benchmarks

Scilab 6.X is shipped with a sparse set of benchmarks only for some its modules. You may run them as follows:

```scilab
--> [n,t]=bench_run(<Benchmark>); sum(t)/1000
...
 ans  =
   <Time in s>
```
We have done that, and got the following results:

| Benchmark | Scilab 6.X | _Balisc_ | _Difference_ |
| ---------:| ----------:| --------:| ------------:|
| "ast" | 6.89 | 5.83 | _- 15 %_ |
| "core" | 39.14 | 30.49 | _- 22 %_ |
| "elementary_functions" | 41.41| 26.43 | _- 36 %_ |
| "fileio" | 44.98 | 5.89 | _- 87 %_ |
| "string" | 94.05 | 51.72 | _- 45 %_ |
| "time" | 94.65 | 40.79 | _- 56 %_ |

Please note, that the "**elementary_functions**" benchmark is not the same as that of Scilab 6.X (cf. `balisc/scilab/modules/elementary_functions/tests/benchmarks/`).

Furthermore, take these results just as an indicator, that **_Balisc might perform significantly better_** than Scilab 6.X.

**_Your mileage may vary!_** Things are currently **_really_** in an **_experimental_** and **_work-in-progress state!_**
 
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

## Issues and Pull Requests
Both are welcome! For the time being, we have the following focus
- improvement of run-time performance
- simplication of code base and maintainability
- compilation under Linux x86_64 GCC
- building of binary packages (Debian, Ubuntu, ...)
- ...
