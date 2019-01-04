Welcome to Scilab 6.1.X
=======================

This file details the changes between Scilab 6.1.X (this development branch), and the previous release 6.0.X.
For changelogs of earlier releases, please see [Scilab 6.0.0][1].

This file is intended for the specific needs of advanced users, and describes:
- High-level new features,
- Changes in installation, compilation, and compatibility,
- Changes in the language,
- New and modified features, in each module,
- Changes in functions (removed/added/modified),
- Bug fixes.

This is an in-development version which might be unstable.
Please report anything we could have missed, on the [mailing lists][2] or the [bug tracker][3].

[1]: https://help.scilab.org/docs/6.0.0/en_US/CHANGES.html
[2]: http://mailinglists.scilab.org
[3]: https://bugzilla.scilab.org


Main new features
-----------------

For a high-level description of the main new features of this release, please consult the [embedded help][4]. It is also available as the "What's new" page of the help, by simply typing `help` in Scilab console.

[4]: modules/helptools/data/pages/homepage-en_US.html

In summary, the main new features are:
* Webtools utilities added for HTTP protocol, JSON data usage
* Profiled values are available as Scilab values
* Values have a cleaner display:
   - they are displayed in order on assignment
   - strings are quoted
   - complex numbers are aligned for matrices
   - numbers (IEEE 754 double) are not rounded
   - polynomials and rationals display is more compact
   - In structures, nested lists or structures are now displayed recursively compactly and more explicitly.
* importgui function has been added to easily interface csvRead


Installation
------------


Compilation
-----------

* GNU autotools have been updated to :
   - automake 1.15
   - autoconf 2.69
   - libtool 2.4.6 (patched for macOS)

* Linux and macOS builds require a C++17 compiler. Toolboxes might also want to use this standard by specifying `-std=c++17` as a `CFLAGS`

* Migration to Microsoft Visual Studio 2017 and Intel Composer 2018


Dependencies
------------


Packaging & Supported Operating Systems
---------------------------------------

* Scilab embedded JVM is Java 8. To run or compile Scilab you need at least:
  - Windows:
     - Windows 10 (Desktop)
     - Windows 8 (Desktop)
     - Windows 7
     - Windows Vista SP2
     - Windows Server 2008 R2 SP1 (64-bit)
     - Windows Server 2012 (64-bit)
  - Mac OS X:
     - Intel-based Mac running Mac OS X 10.8.3+, 10.9+
  - Linux:
     - Red Hat Enterprise Linux 5.5+, 6.x (32-bit), 6.x (64-bit), 7.x (64-bit)
     - Oracle Linux 5.5+, 6.x (32-bit), 6.x (64-bit), 7.x (64-bit)
     - Ubuntu Linux 12.04 LTS, 13.x
     - Suse Linux Enterprise Server 10 SP2+, 11.x

    For more information, please consult: [What are the system requirements for Java?][5]

* [SSE2][6], Streaming SIMD Extensions 2 support is now mandatory to run Scilab on Linux i686.

[5]: http://java.com/en/download/help/sysreq.xml
[6]: https://en.wikipedia.org/wiki/SSE2

Feature changes and additions
-----------------------------

* `airy` has been added: Evaluation of Airy functions of the first and second kind, and their first derivative, possibly scaled.
* HTTP get, post, put, upload, patch, delete functions added
* JSON encoding / decoding for Scilab datatypes added
* Memory invalid accesses have been greatly reduced thanks to :
  - PVS-Studio inspections blog report
  - Coverity scan weekly source analysis
* `bitget` is upgraded:
  - It now accepts positive Signed encoded integers.
  - It now supports the new uint64 and int64 types of encoded integers.
  - For decimal numbers: bits with indices > 52 can now be retrieved (up to `log2(number_properties("huge"))` = 1024).
  - For decimal numbers `x > 2^52`, queried bits below `%eps` (indices < log2(x)-52) now return `Nan` instead of 0.
  - Several bits can now be retrieved from each component of an input array.
* `bitset` is upgraded:
  - It now accepts positive Signed encoded integers.
  - It now supports the new uint64 and int64 types of encoded integers.
  - For decimal numbers: bits with indices > 32 can now be set (up to #1024).
  - Several bits can now be set for each input component.
  - Distributive scalar inputs are now accepted.
* `edit` now accepts a line number as text (like "23").
* `profileEnable`, `profileDisable`, `profileGetInfo` could be used to instrument functions and gather execution information within Scilab.
* `prettyprint` is upgraded:
  - Integer and Text input are now actually supported.
  - Default input arguments can be skipped instead of still having to be provided.
  - The result string is better formatted to be easily wrappable and indented.
* `mesh2d` has been introduced to compute a 2d mesh from vectors (x,y) of points.
* `loadmatfile` is upgraded:
  - Octave native text data files can now be read.
  - Automatic detection of the input data format implemented.
  - `-toStruct` option added, to return results in a structure instead of in the calling environment.
* `jremove` is optional and `clear` could be used to release Java objects mapped to Scilab.
* `blockdiag` is introduced to improve, replace, and extend `sysdiag` to strings.
* `assert_checkequal` is upgraded:
  - support added for Nan and void in lists, Nan in sparses, implicit lists, graphic handles, macros, libraries, and built-in.
  - For arrays of matching typeof and sizes, and for lists of matching lengths, the failure message now indicates the index and values of the first mismatching elements.
* `diophant` is improved:
  - Encoded integers are accepted, in addition to decimal numbers. Only integer solutions are then searched.
  - When there is no solution, `[]` is returned.
  - When there is an infinite number of solutions, the err flag has a specific value.
  - The output size gets the input's one.
* `editvar()` GUI support copy-paste of strings removing quotes.
* calendar() can now display formated calendars.
* `xmlSetValues()` clones `setPreferencesValue` that is now obsolete.
* `unique()` is upgraded to:
  - return the number of occurences of distinct entities found in the input array.
  - return distinct entities in their initial order (rather than sorted), with the `"keepOrder"` option.
  - consider all `Nan` values as the same one, with the `"uniqueNan"` option.
* `ellipj` function introduced, to compute the `sn`, `cn`, `dn`, `ns`, `nc` and `nd` Jacobi elliptic functions.
* `riccati` is upgraded:
  - `riccati(H)` and `riccati(H,E)` syntaxes added, to describe the Riccati equation through its Hamiltonian H or (E,H) pencil.
  - The residual is returned as a new 3rd output argument.
  - When no solution is found, `X=[]` | `X1=[]` is returned instead of yielding an error.
* `hallchart` is upgraded:
  - The default set of modules is set automatically, according to data bounds.
  - Handles of the grids and labels are returned. Post-processing them becomes easy.
  - Named colors accepted; better default colors.
  - Improved placement of labels.
* `playsnd` is upgraded:
  - the name of a wav file can now be specified (instead of the sound data).
  - the input sound can now be repeated a given number of times.
  - the modal/non-modal processing is improved.
* `nicholschart` is improved: more neutral default frame color; improved labels positionning; colors can now be specified by their predefined name or "#RRGGBB" hexa code; a structure of handles is now returned to easily postprocess both subframes and the set of labels.
* `sciargs` returns a column instead of formerly a row.
* Booleans and encoded integers can now be concatenated together, as in `[%f int8(-5)]`.
* `gsort` can now perform multilevel sorting. This noticeably allows sorting completely complex numbers.
* `factorial` can be used now from n=171 up to n=10^14.
* `intersect` now supports complex numbers.
* `setdiff` now supports complex numbers.
* `twinkle` can now blink together several hierarchically independent objects, like a curve and its labels, etc.
* `repmat` has been rewritten. It is 7 times faster now.
* `plot` can now work in semi or bi-logarithmic mode with some input logflag.
* `plotimplicit` function added.
* The default smarter grid_style value is now 7 instead of 3.
* `weekday` accepts new date formats and new syntaxes. A language option applying to the day names is now available.
* `vectorfind` is upgraded:
  - vectorfind(m, []) now returns [] instead of an error.
  - A too long needle now returns [] instead of an error.
  - %nan values never matched. They are now regularly processed, as other values.
  - A needle shorter than the haystack size can now be used.
  - A wildcard value matching any value of the haystack can now be specified and used in the needle. Actual matching ranges can then be returned: Options `joker` and `matching` added.
  - Hypermatrices are now accepted as haystack.
  - The probing direction can now be numeric: 1, 2, ..
  - Returned indices can now be formatted with the new option `indType`.
  - There were no unit tests. More than 100 tests are added.
* `datafit` is now able to fit weighted data. It now supports any gap function vectorized for Data points, and so is much faster. It now accepts any matrix of parameters (not necessarily a colum). It now returns the average Mode-to-data distance, and the termination status for the quasi-Newton algo.
* `tree_show` is upgraded:
  - New `rootTitle` and `styles` optional inputs.
  - New `arrayByFields` option, to allow displaying each array component as an object in its whole.
  - Improved layout: detailled indices for 2D arrays, simplified symbols, etc.
  - The content of implicitlist objects, and information for Scilab functions and libraries of functions are now displayed.
* `nchoosek` is introduced, to compute the binomial coefficients.
* The left .\. and right ./. Kronecker divisions are now implemented, for arrays of decimal or complex numbers.


Help pages:
-----------

* overhauled / rewritten: `bitget`, `edit`, `factorial`, `vectorfind`, `datafit`
* fixed / improved:  `bench_run` `M_SWITCH`, `comet`, `comet3d`
* Rewritten: `weekday`
* Translations added:
  - (ru): `weekday`


User Interface improvements:
----------------------------

* The `ans` variable is editable as any other variable in Editvar.
* Commands history is saved before executing a command to have the correct history on a crash.
* Used memory per variable is displayed by BrowserVar to give the user numbers on memory usage repartition and let the user `clear` the big ones first.
* Autoscroll of console in GUI mode is disabled when the user scrolls up until he scrolls to the bottom.

Xcos
----

* Default ending time reduced from 100000 to 30, to fit default scope block.
* `CURVE_c` settings did not always display a window.
* Exporting all layers from a diagram will generate one unique file per layer.

API modification
----------------


Obsolete functions or features
------------------------------
* `frexp` becomes an internal. Please use `[m,e]=log2(x)` instead.
* `champ1` is obsolete. Please use `champ.colored` instead.
* `setPreferencesValue` is obsolete. Please use `xmlSetValues` instead.
* `%sn` is obsolete. Please use `ellipj` instead.
* `sysdiag` is obsolete. Please use `blockdiag` instead.
* `ric_desc` is obsolete and will be removed from Scilab 6.1.x. Please use `riccati` instead.
* `noisegen` will be removed from Scilab 6.1.x. Please use `grand` instead.
* `get_figure_handle(n)` is obsolete. Please use `findobj('figure_id',n)` instead.

Removed Functions
-----------------

* `eval` was obsolete and has been removed. Please use `evstr` instead.
* `hypermat` was obsolete and has been removed. Please use `matrix` instead.
* `lstsize` was obsolete and has been removed. Please use `size` instead.
* `denom` was obsolete and has been removed. Please use the `.den` rational field instead.
* `numer` was obsolete and has been removed. Please use the `.num` rational field instead.
* `square` was obsolete and has been removed.
* `strcmpi` was obsolete and has been removed. Please use `strcmp(,'i')` instead.
* `xgetech` was obsolete and has been removed. Please use `gca` instead.
* `fac3d` was obsolete since Scilab 4 and has been removed. Please use `plot3d` instead.
* `fac3d1` was obsolete since Scilab 4 and has been removed. Please use `plot3d1` instead.
* `xinfo` was obsolete and has been removed. Please use `gcf().info_message` instead.
* `with_tk` was obsolete and has been removed. Please use `with_module('tclsci')` instead.


Known issues
------------


Bug Fixes
---------

### Bugs fixed in 6.1.0:
* [#2694](http://bugzilla.scilab.org/show_bug.cgi?id=2694): `bitget` did not accept positive integers of types int8, int16 or int32.
* [#8784](http://bugzilla.scilab.org/show_bug.cgi?id=8784): Automatic self-adjusting blocks `SCALE_CSCOPE` & `SCALE_CMSCOPE` in Xcos.
* [#12013](http://bugzilla.scilab.org/show_bug.cgi?id=12013): `bitset` did not work for numbers greater than 2^32-1.
* [#14655](http://bugzilla.scilab.org/show_bug.cgi?id=14655): `bitset` worked only element-wise, without accepting mixed scalar and array inputs.
* [#14604](http://bugzilla.scilab.org/show_bug.cgi?id=14604): `emptystr()` is 40x slower with 6.0.0 wrt 5.5.2
* [#14605](http://bugzilla.scilab.org/show_bug.cgi?id=14605): fixed - `bench_run` was too strict about the specification of tests names.
* [#14812](http://bugzilla.scilab.org/show_bug.cgi?id=14812): Minor typos in messages.
* [#14863](http://bugzilla.scilab.org/show_bug.cgi?id=14863): In Xcos, the default ending time was unhandily high (100000), reduced it to 30.
* [#14982](http://bugzilla.scilab.org/show_bug.cgi?id=14982): `msprintf` segmentation fault was caught due to wrong size
* [#15269](http://bugzilla.scilab.org/show_bug.cgi?id=15269): `xgetech` was poor and stiff compared to any combination of `gca()` properties `.axes_bounds`, `.data_bounds`, `.log_flags`, and `.margins`. It is removed.
* [#15271](http://bugzilla.scilab.org/show_bug.cgi?id=15271): `bitget` needed to be upgraded.
* [#15425](http://bugzilla.scilab.org/show_bug.cgi?id=15425): The Kronecker product `a.*.b` failed when `a` or `b` or both are hypermatrices, with one or both being polynomials or rationals.
* [#15523](http://bugzilla.scilab.org/show_bug.cgi?id=15523): `%ODEOPTIONS(1)=2` didn't work with solvers 'rk' and 'rkf' 
* [#15577](http://bugzilla.scilab.org/show_bug.cgi?id=15577): `edit` did not accept a line number as text, as with `edit linspace 21`.
