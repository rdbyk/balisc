# Balisc
- provides a **_fresh (experimental)_** look at **_Scilab 6.x_**, i.e. it
- detects **_SIMD extensions_** (SSE2/SSE4/AVX/...) and uses it (currently, just a little bit)
- improves **_run-time performance_** of various functions in `string`, `elementary_functions`, ... modules
- tries **_cleaning_** and **_simplification_** of code base (huge on-going task)
- will try to **_get rid of legacy redundancies_** and **_inconsistencies_** at a faster pace
- _**dropped MSVC**_ support and will switch to _**MINGW/MSYS2**_ for Windows support (in the long run)
- currently runs on  _**Linux 64bit only**_, but is _**fully compatible**_ with _**Scilab 6.x**_ (at least at the language level)
- ...
## Is it for me?
We don't know, but you may try running this

```scilab
A=string(rand(1000,1000));
tic;B=strcat(A);toc
tic;strsubst(B,"3","X");toc
S=sprand(5000,5000,0.001);
tic;S==0.5;toc
```

under current [**_Scilab 6.x_**](http://www.scilab.org/en/development/nightly_builds/master). In the meantime, you might think about compiling **_Balisc_** by yourself (cf. below) and executing the very same instuctions on your freshly built **_Balisc_**. This could confront you with results like this.

```scilab
--> A=string(rand(1000,1000));
--> tic;B=strcat(A);toc
 ans  =
   0.063398
--> tic;strsubst(B,"3","X");toc
 ans  =
   0.095663
--> a=sprand(5000,5000,0.001);
--> tic;a==0.5;toc
 ans  =
   0.233446
```

Please, don't take these examples too seriously, they are just extremes chosen for pedagogic reasons. *Scilab is a very powerful and comprehensive tool*.

#### You want to Protect Just One Variable?
With the unique functions `protect`, `unprotect`, and `isprotected` of **_Balisc_**, you might do this 
```scilab
--> x=123;y=456;
--> protect x
--> x=0
Redefining permanent variable.
--> y=1
 y  = 
   1.
--> isprotected(["x" "y"])
 ans  =
  T F
--> unprotect x
--> x=0
 x  = 
   0.
```
Please note, these functions have been added very recently (cf. [#366](https://github.com/rdbyk/balisc/pull/366) [#420](https://github.com/rdbyk/balisc/pull/420)), thus they are not tested very well and might need some polishing. However, can you do the same thing using `predef` in current Scilab 6.x?

#### You are working with Complex Numbers and Expect Consistent Results?
With **_Balisc_** your calculations will yield _complex infinity_ and _undefined_ results consistently with respect to the
complex plane. Therefore, a result with a `Nan` real _and_ a `Nan` imaginary part is _undefined_ and a result with at least one `Inf` part corresponds to _complex infinity_.
```scilab
--> 0/(0+0*%i)
 ans  =
   Nan + Nani
--> (0+0*%i)/(0+0*%i)
 ans  =
   Nan + Nani
--> 1/(0+0*%i)
 ans  =
   Inf + Nani
--> (1+0*%i)/(0+0*%i)
 ans  =
   Inf + Nani
```
Please note, this is just how nowadays the complex arithmetics, provided by a decent C/C++ compiler, works. These rectifications have been added very recently (cf. [#390](https://github.com/rdbyk/balisc/pull/390) [#402](https://github.com/rdbyk/balisc/pull/402)).

#### You Expect (Vectorized) Code to be Executed Faster?
Heavily inspired by this simple [benchmark](https://github.com/antoine-levitt/benchmark_heat), we have assembled the following two functions `heat_loop` and `heat_vect`. 

```scilab
// naive (not vectorized)
function u = heat_loop(nx, nt, dx, dt, D, v)
    u=42*zeros(nx,1);
    u_next=u;
    for it=1:nt
        for ix=2:nx-1
            u_next(ix)=u(ix)+D*dt/(dx*dx)*(u(ix+1)-2*u(ix)+u(ix-1))-v*dt/dx*(u(ix+1)-u(ix));
        end
        u=u_next;
    end
endfunction

// vectorized
function u = heat_vect(nx, nt, dx, dt, D, v)
    u=42*zeros(nx, 1);
    u_next=u;
    for it=1:nt
        u_next(2:nx-1)=u(2:nx-1)+D*dt/(dx*dx)*(u(3:nx)-2*u(2:nx-1)+u(1:nx-2))-v*dt/dx*(u(3:nx)-u(2:nx-1));
        u=u_next;
    end
endfunction
```
We have run them under Scilab 6.0.1 and current *__Balisc__* and got the following timing results.
##### Scilab 6.0.1
```scilab
--> tic();heat_loop(1e3,1e4,1e-1,1e-8,1,1);t_loop=toc()
 t_loop  = 
   101.15152
--> tic();heat_vect(1e3,1e4,1e-1,1e-8,1,1);t_vect=toc()
 t_vect  = 
   0.97665
--> t_loop/t_vect
 ans  =
   103.56988
```
##### Balisc ([current](https://github.com/rdbyk/balisc/tree/b9641ac26a28efe78a55bd9b280c927546704130))
```scilab
--> tic();heat_loop(1e3,1e4,1e-1,1e-8,1,1);t_loop=toc()
 t_loop  = 
   80.622409
--> tic();heat_vect(1e3,1e4,1e-1,1e-8,1,1);t_vect=toc()
 t_vect  = 
   0.491977
--> t_loop/t_vect
 ans  =
   163.87435
```
The vectorized code `heat_vect` was executed 100 times faster under Scilab 6.0.1 and even __160 times faster under__ *__Balisc__* in comparison to `vect_loop`. Furthermore, `heat_vect` was executed __two times faster under__ *__Balisc__* in direct comparison to Scilab 6.0.1.

Please don't expect to achieve this speed-up for every piece of code you can think of!
This is just a motivating little spot light!.

### Try some of Scilab's Benchmarks

Scilab 6.X is shipped with a sparse set of benchmarks only for some its modules. You may run them as follows:

```scilab
--> [n,t]=bench_run(<Benchmark>); sum(t)/1000
...
 ans  =
   <Time in s>
```
We have done that, and got the following results:

| Benchmark | Scilab 6.0.1 | _Balisc 0_ | _Difference_ | Scilab 6.0.2 | _Balisc 1_ | _Difference_ |
| ---------:| ------------:| ----------:| ------------:| ------------:| ----------:| ------------:|
| "ast" | -- | -- | -- | 6.91 | 5.79 | _- 16 %_ |
| "core" | 35.16 | 30.82 | _- 12 %_ | 36.01 | 28.87 | _- 20 %_ |
| "elementary_functions" | 41.49 | 26.90 | _- 35 %_ | 43.02 | 25.91 | _- 40 %_ |
| "fileio" | 47.19 | 6.25 | _- 86 %_ | 5.74 | 5.38 | _- 6 %_ |
| "string" | 140.89 | 51.06 | _- 63 %_ | 144.69 | 52.19 | _- 64 %_ |
| "time" | 91.76 | 24.51 | _- 73 %_ | 66.53 | 20.44 | _- 69 %_ |

Please note, that the "**elementary_functions**" benchmark is not the same as that of Scilab 6.X (cf. `balisc/scilab/modules/elementary_functions/tests/benchmarks/`).

Furthermore, take these results just as an indicator, that **_Balisc might perform significantly better_** than Scilab 6.X.

**_Your mileage may vary!_** Things are currently **_really_** in an **_experimental_** and **_work-in-progress state!_**
 
## Compilation with GCC for Linux x86_64
You may want to follow the the instructions [Compilation of Scilab](https://wiki.scilab.org/Compilation%20of%20Scilab) (probably not up-to-date), or follow the **_procedure described below_**, which assumes, that you have installed all required non-Java stuff on your
system ([Dependencies of Scilab 5.X](https://wiki.scilab.org/Dependencies%20of%20Scilab%205.X), probably not up-to-date).

Please note, that **_Balisc_** additionally needs **_SLEEF (SIMD Library for Evaluating Elementary Functions)_**, under Ubuntu you may install the *SLEEF* library from this [PPA](https://launchpad.net/~shibatch/+archive/ubuntu/sleef).

**_What else is needed?_** For the time being, just run `configure` (cf. below), and see what is missing, install the missing libraries, and re-run `configure` ... and so on ...

- `cd <PATH>`
- `git clone https://github.com/rdbyk/balisc.git balisc`
- `cd balisc/scilab`
- `svn --force checkout https://github.com/scilab/scilab-prerequirements.git/trunk/linux_x64/ .`
- `mv usr usr_DEV`
- `mv lib lib_DEV`
- `mkdir -p lib/thirdparty`
- `cp lib_DEV/thirdparty/libjogl_*.so lib/thirdparty`
- `./configure --with-eigen-include=<PATH>/balisc/scilab/usr_DEV/include`
- `make`

## Issues and Pull Requests
Both are welcome! For the time being, we have the following focus
- improvement of run-time performance and maintainability
- simplification of code base
- compilation under Linux x86_64 GCC
- building of binary packages (Debian, Ubuntu, ...)
- ...
