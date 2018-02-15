Welcome to Scilab 6.1.X
=======================

This file details the changes between Scilab 6.1.X (this development branch), and the previous release 6.0.X.
For changelogs of earlier releases, please see [Scilab 6.0.0](https://help.scilab.org/docs/6.0.0/en_US/CHANGES.html).

This file is intended for the specific needs of advanced users, and describes:
- High-level new features,
- Changes in installation, compilation, and compatibility,
- Changes in the language,
- New and modified features, in each module,
- Changes in functions (removed/added/modified),
- Bug fixes.

This is an in-development version which might be unstable.
Please report any thing we could have missed, on the [mailing lists][1] or on the [bug tracker][2].

[1]: http://mailinglists.scilab.org
[2]: http://bugzilla.scilab.org


Main new features
-----------------

For a high-level description of the main new features of this release, please consult the [embedded help](modules/helptools/data/pages/homepage-en_US.html). It is also available as the "What's new" page of the help, by simply typing `help` in Scilab console.

In summary, the main new features are:
* Webtools utilities added for HTTP protocol, JSON data usage


Installation
------------


Compilation
-----------

* GNU autotools have been updated to :
   - automake 1.15
   - autoconf 2.69
   - libtool 2.4.6 (patched for Mac Os X)

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

    For more information, please consult: [What are the system requirements for Java?](http://java.com/en/download/help/sysreq.xml)

* [SSE2](https://en.wikipedia.org/wiki/SSE2), Streaming SIMD Extensions 2 support is now mandatory to run Scilab on Linux i686.


Feature changes and additions
-----------------------------

* Empty strings are used as the default values on String allocation
* HTTP get, post, put, upload, patch, delete functions added
* JSON encoding / decoding for Scilab datatypes added
* Memory invalid accesses have been greatly reduced thanks to :
  - PVS-Studio inspections blog report
  - Coverity scan weekly source analysis
* bitget() is upgraded:
  - It now accepts positive Signed encoded integers.
  - It now supports the new uint64 and int64 types of encoded integers.
  - For decimal numbers: bits with indices > 52 can now be retrieved (up to `log2(number_properties("huge"))` = 1024).
  - For decimal numbers `x > 2^52`, querried bits below `%eps` (indices < log2(x)-52) now return `Nan` instead of 0.
  - Several bits can now be retrieved from each component of an input array.


Help pages:
-----------

* overhauled / rewritten: `bitget`
* fixed / improved:  `bench_run` `M_SWITCH`


Xcos
----

* Default ending time reduced from 100000 to 30, to fit default scope block


API modification
----------------


Obsolete functions or features
------------------------------


Removed Functions
-----------------

* `hypermat` was obsolete and has been removed. Please use `matrix` instead.
* `square` was obsolete and has been removed.
* `xgetech` was obsolete and has been removed. Please use `gca` instead.


Known issues
------------

* This is one of the first releases of a completely rewritten interpreter engine. If you discover strange behaviors or unexpected results do not hesitate to [report](https://bugzilla.scilab.org) them.
* Toolboxes rebuild is in progress. Do not hesitate to submit patch or feature upgrade to the [development mailing list](dev@lists.scilab.org) for a particular toolbox.

### Bugs fixed in 6.0.2:
* [#7277](http://bugzilla.scilab.org/show_bug.cgi?id=7277): SciNotes `File>Open recent` menu was not updated after 5 items were added.
* [#7675](http://bugzilla.scilab.org/show_bug.cgi?id=7675): sparse() got a wrong result, when creation with many values in same position.
* [#8127](http://bugzilla.scilab.org/show_bug.cgi?id=8127): When using `ode()`, some internal errors messages were in french.
* [#9958](http://bugzilla.scilab.org/show_bug.cgi?id=9958): `mprintf("%d\r", 12345)` printed `" 345"`
* [#10190](http://bugzilla.scilab.org/show_bug.cgi?id=10190): Xcos blocks and labels positioning were not aligned to the grid on creation.
* [#11240](http://bugzilla.scilab.org/show_bug.cgi?id=11240): `A=[]; clear B; [A($+1),B]=1;` crashed Scilab.
* [#11916](http://bugzilla.scilab.org/show_bug.cgi?id=11916): Loading a graphic file containing several figures restored them by superimposing them in the same window.
* [#12109](http://bugzilla.scilab.org/show_bug.cgi?id=12109): `execstr(.,"errcatch")` calling a macro returning before setting the argout crashed Scilab.
* [#12566](http://bugzilla.scilab.org/show_bug.cgi?id=12566): `disp()` of a T-list with a single field set to an encoded integer value generated an error.
* [#14521](http://bugzilla.scilab.org/show_bug.cgi?id=14521): For the CONVERT Xcos block, types codes 2, 6, 7, and 8 were not documented.
* [#15423](http://bugzilla.scilab.org/show_bug.cgi?id=15423): `tbx_make(myModule,sections)` executed the existing builder (if any), instead of targeting only selected module sections. Otherwise, tbx_make(myModule, "help"|"macros") yielded an error, and tbx_make(myModule,"localization") never built it.
* [#15440](http://bugzilla.scilab.org/show_bug.cgi?id=15440): Scilab debug help page linked to Xcos debug.
* [#15422](http://bugzilla.scilab.org/show_bug.cgi?id=15422): `strsubst("ab", "", "cd")` crashed Scilab.
* [#15464](http://bugzilla.scilab.org/show_bug.cgi?id=15464): Xcos C-blocks could not link dlls on Windows.
* [#15495](http://bugzilla.scilab.org/show_bug.cgi?id=15495): SampleCLK simple demo failed to simulate.
* [#15496](http://bugzilla.scilab.org/show_bug.cgi?id=15496): Scinotes `File > Open recent` menu was not updated when it should.
* [#15499](http://bugzilla.scilab.org/show_bug.cgi?id=15499): Scinotes menus were inactive after session restore under OSX.
* [#15527](http://bugzilla.scilab.org/show_bug.cgi?id=15527): `ode` gave incorrect results with %ODEOPTIONS(1)=2.


### Bugs fixed in 6.0.1:
* [#2441](http://bugzilla.scilab.org/show_bug.cgi?id=2441): `%onprompt()` could be defined only at the top execution level.
* [#3256](http://bugzilla.scilab.org/show_bug.cgi?id=3256): The cursor of slider uicontrol is not displayed if the slider step is not an integer value.
* [#4276](http://bugzilla.scilab.org/show_bug.cgi?id=4276): `strsubst` replaced the first occurence in regex mode.
* [#5248](http://bugzilla.scilab.org/show_bug.cgi?id=5248): The graphical entity picker was out of work.
* [#5278](http://bugzilla.scilab.org/show_bug.cgi?id=5278): obsolete `xset()` was still used in scripts, macros, tests and help pages.
* [#5381](http://bugzilla.scilab.org/show_bug.cgi?id=5381): For UTF-8 inputs, `msprintf`, `mprintf` and `mfprintf` shortened the output.
* [#5567](http://bugzilla.scilab.org/show_bug.cgi?id=5567): `bar(.., colors)` used with grouped or stacked subsets, only a unique common meaningless color could be specified. Only a restricted list of 10 colors names could be used. Some arguments checking were wrong.
* [#5602](http://bugzilla.scilab.org/show_bug.cgi?id=5602): Assigning a component of a list in a cells array replaced the whole list.
* [#5611](http://bugzilla.scilab.org/show_bug.cgi?id=5611): It was not possible to delete the row or column of a cells array.
* [#6155](http://bugzilla.scilab.org/show_bug.cgi?id=6155): Pages of `param3d()` and `param3d1()` deserved being fixed, improved and merged in a single page.
* [#6607](http://bugzilla.scilab.org/show_bug.cgi?id=6607): `clear S; S(1:2,1:3).a = 1` yielded an error.
* [#6608](http://bugzilla.scilab.org/show_bug.cgi?id=6608): Field and data insertion in an array of structures might fail.
* [#6813](http://bugzilla.scilab.org/show_bug.cgi?id=6813): `makecell` used to create a N>2-D hyperarray yielded an error.
* [#6911](http://bugzilla.scilab.org/show_bug.cgi?id=6911): `help_from_sci` did not accept numerical HTML entities like `&#969;` in heading comments.
* [#6973](http://bugzilla.scilab.org/show_bug.cgi?id=6973): It was impossible to view figures of several demos in a stable docked panel.
* [#7652](http://bugzilla.scilab.org/show_bug.cgi?id=7652): Inserting `list("")` in a cells array could be erroneous.
* [#8140](http://bugzilla.scilab.org/show_bug.cgi?id=8140): Editing parameters of the EXPRESSION Xcos block changed Scilab's IEEE mode.
* [#8297](http://bugzilla.scilab.org/show_bug.cgi?id=8297): `cat` slowness was exponential, crippling, and made it useless.
* [#8629](http://bugzilla.scilab.org/show_bug.cgi?id=8629): On the help page of the Xcos Sinks palette, blocks screenshots were stacked and not hyperlinked to their page.
* [#8669](http://bugzilla.scilab.org/show_bug.cgi?id=8669): After `A=rand(3,3)`, some legal insertions in `A(*,*,:)` failed. Non regression tests added.
* [#8842](http://bugzilla.scilab.org/show_bug.cgi?id=8842): Assigning the pointer of a builtin function to a new structure failed.
* [#9297](http://bugzilla.scilab.org/show_bug.cgi?id=9297): Assigning a mlist to a structure's field failed.
* [#9519](http://bugzilla.scilab.org/show_bug.cgi?id=9519): The console menu `File -> Open a file` opened any file in Scinotes. Binary files like .zcos blocked Scinotes.
* [#9617](http://bugzilla.scilab.org/show_bug.cgi?id=9617): Xcos run-time version check was too conservative.
* [#9838](http://bugzilla.scilab.org/show_bug.cgi?id=9838): `evstr` poorly supported simple comments in input expressions.
* [#10270](http://bugzilla.scilab.org/show_bug.cgi?id=10270): `execstr(["%val=[int16(1)";"]"])` needed entering twice <enter> to be actually performed.
* [#10407](http://bugzilla.scilab.org/show_bug.cgi?id=10407): The macro `acf()` of the CACSD module was used nowhere and not documented. It is removed.
* [#10467](http://bugzilla.scilab.org/show_bug.cgi?id=10467): `execstr` inside a `try/end` with a `catch` killed the stack.
* [#11196](http://bugzilla.scilab.org/show_bug.cgi?id=11196): Some recursive extractions from a mlist failed.
* [#11251](http://bugzilla.scilab.org/show_bug.cgi?id=11251): `execstr` could kill the variables stack.
* [#11483](http://bugzilla.scilab.org/show_bug.cgi?id=11483): The `Graphics => Misc` demo had a hole, 2 duplicates, and other bugs.
* [#11530](http://bugzilla.scilab.org/show_bug.cgi?id=11530): Raise (help, scinotes, ...) windows when iconified ( recall or startup )
* [#11693](http://bugzilla.scilab.org/show_bug.cgi?id=11693): uicontrol edit fields needed <enter> after the input to actually record it.
* [#11756](http://bugzilla.scilab.org/show_bug.cgi?id=11756): In the categories of the ATOMS GUI, actually available modules might be not listed.
* [#11767](http://bugzilla.scilab.org/show_bug.cgi?id=11767): `execstr("A. 1","errcatch")` failed to catch the error.
* [#12195](http://bugzilla.scilab.org/show_bug.cgi?id=12195): `generateBlockImage` sometimes changed the current graphic driver.
* [#12356](http://bugzilla.scilab.org/show_bug.cgi?id=12356): `colordef` did not allow to reset colors to the default default ones.
* [#12372](http://bugzilla.scilab.org/show_bug.cgi?id=12372): The `mode` function was poorly documented.
* [#12586](http://bugzilla.scilab.org/show_bug.cgi?id=12586): An example showing how to get XML comments was missing in the `xmlXPath` help page.
* [#12771](http://bugzilla.scilab.org/show_bug.cgi?id=12771): xcosPalGenerateAllIcons help example was broken.
* [#12792](http://bugzilla.scilab.org/show_bug.cgi?id=12792): `save(filename, "undefinedVariable")` created an empty useless file.
* [#12862](http://bugzilla.scilab.org/show_bug.cgi?id=12862): `intsplin` no longer integrated the imaginary part of given ordinates.
* [#13014](http://bugzilla.scilab.org/show_bug.cgi?id=13014): `optim_ga`: update the Efficiency inner variable.
* [#13277](http://bugzilla.scilab.org/show_bug.cgi?id=13277): `execstr("clear")` did not clear any variables in the current scope.
* [#13581](http://bugzilla.scilab.org/show_bug.cgi?id=13581): The example of `inistate()` help page did not work on Windows 64bit.
* [#13592](http://bugzilla.scilab.org/show_bug.cgi?id=13592): In an axes in a uicontrol frame, setting a `legend` interactively might not follow the mouse accurately.
* [#13796](http://bugzilla.scilab.org/show_bug.cgi?id=13796): `tbx_generate_pofile` missed registering `_()` and `gettext()` references. In `en_US.po`, commented paths were absolute. Literal '' were copied in msgid without simplification.
* [#13900](http://bugzilla.scilab.org/show_bug.cgi?id=13900): `nanmin` and `nanmax` were useless duplicates of `min` and `max`
* [#13962](http://bugzilla.scilab.org/show_bug.cgi?id=13962): Preselecting a groupnamed radiobutton was impossible after having created it already once.
* [#13979](http://bugzilla.scilab.org/show_bug.cgi?id=13979): A variable whose name is longer than 24 characters could not be cleared.
* [#13984](http://bugzilla.scilab.org/show_bug.cgi?id=13984): For a set of curves, `plot(.., "color", colors..)` was not vectorized for colors specifications. Moreover, only 10 basic named colors were accepted, instead of the full list of predefined colors names.
* [#14221](http://bugzilla.scilab.org/show_bug.cgi?id=14221): `msprintf` and `mprintf` ignored row-wise processing with `%%`.
* [#14254](http://bugzilla.scilab.org/show_bug.cgi?id=14254): When installing an ATOMS module that is not locally registered and available, the error message was unclear.
* [#14305](http://bugzilla.scilab.org/show_bug.cgi?id=14305): unused `%i_d_i` was still distributed.
* [#14371](http://bugzilla.scilab.org/show_bug.cgi?id=14371): Scilab crashed when a block is edited.
* [#14376](http://bugzilla.scilab.org/show_bug.cgi?id=14376): `input()` was broken: \n was introduced before prompting; multiple prompts occurred; the output value could be missing; "%" "\n" "\t" were no longer supported in messages...
* [#14399](http://bugzilla.scilab.org/show_bug.cgi?id=14399): `whereami`: wrong information (line numbers).
* [#14424](http://bugzilla.scilab.org/show_bug.cgi?id=14424): There were some troubles with `input`.
* [#14490](http://bugzilla.scilab.org/show_bug.cgi?id=14490): `plot2d` crashed when leg parameter was a vector.
* [#14531](http://bugzilla.scilab.org/show_bug.cgi?id=14531): It was not possible to specify SCIHOME as a start-up option.
* [#14532](http://bugzilla.scilab.org/show_bug.cgi?id=14532): `test_run` failed for toolboxes that are not autoloaded.
* [#14544](http://bugzilla.scilab.org/show_bug.cgi?id=14544): `scatter` and `scatter3` canceled any upstream `drawlater` instruction.
* [#14551](http://bugzilla.scilab.org/show_bug.cgi?id=14551): In the icon of the Xcos CLR and DLR blocks, multichar exponents were badly rendered.
* [#14573](http://bugzilla.scilab.org/show_bug.cgi?id=14573): `varargout` misworked when it was used in addition to fixed output arguments.
* [#14588](http://bugzilla.scilab.org/show_bug.cgi?id=14588): Some cross usages of launching options `-nw` and `-nwni` with Wscilex.exe and Scilex.exe binaries were inconsistent.
* [#14584](http://bugzilla.scilab.org/show_bug.cgi?id=14584): The example of demo_choose help page was broken because of a wrong file path.
* [#14598](http://bugzilla.scilab.org/show_bug.cgi?id=14598): `fort` wasn't properly removed.
* [#14603](http://bugzilla.scilab.org/show_bug.cgi?id=14603): The icon of the PROD_f Xcos block was puzzled
* [#14623](http://bugzilla.scilab.org/show_bug.cgi?id=14623): Bad lhs in MList extraction overload.
* [#14629](http://bugzilla.scilab.org/show_bug.cgi?id=14629): In the Xcos EXPRESSION block, `<` could truncate the rendering of the expression in the icon.
* [#14636](http://bugzilla.scilab.org/show_bug.cgi?id=14636): Xcos model with modelica electrical blocks (created in 5.5.2) crashed Scilab 6.
* [#14637](http://bugzilla.scilab.org/show_bug.cgi?id=14367): Some Scilab 5.5.2 diagrams did not simulate properly in Xcos.
* [#14656](http://bugzilla.scilab.org/show_bug.cgi?id=14656): The `matrix` page missed a synopsis for hypermatrix and deserved some improvements.
* [#14680](http://bugzilla.scilab.org/show_bug.cgi?id=14680): The `<` char in expression was not rendered in the icon of Xcos EXPRESSION block.
* [#14703](http://bugzilla.scilab.org/show_bug.cgi?id=14703): `clear linspace, type(linspace)` returned 11 instead of 13.
* [#14749](http://bugzilla.scilab.org/show_bug.cgi?id=14749): The icon of the Xcos `POWBLK_f` and `EXPBLK_m` blocks displayed "u^a" and "a^u" instead of the actual a value.
* [#14883](http://bugzilla.scilab.org/show_bug.cgi?id=14883): `whereis` did not support builtin functions.
* [#14886](http://bugzilla.scilab.org/show_bug.cgi?id=14886): `Matplot` save/load failed.
* [#14896](http://bugzilla.scilab.org/show_bug.cgi?id=14896): Using `set` with multiple properties, only the first one was set.
* [#14901](http://bugzilla.scilab.org/show_bug.cgi?id=14901): WScilex.exe was stopped immediately when launched from Java.
* [#14903](http://bugzilla.scilab.org/show_bug.cgi?id=14903): `plot2d` crashed if a current figure has no axes.
* [#14910](http://bugzilla.scilab.org/show_bug.cgi?id=14910): The `plot()` example was displayed in overlay to the existing graphics.
* [#14922](http://bugzilla.scilab.org/show_bug.cgi?id=14922): The `%onprompt()` special function was not documented.
* [#14925](http://bugzilla.scilab.org/show_bug.cgi?id=14925): `jdeff`: `invoke_lu()` deleted/corrupted the called java method after an error occured.
* [#14981](http://bugzilla.scilab.org/show_bug.cgi?id=14981): Some vertical concatenations of cells and further cells extractions crash Scilab.
* [#14984](http://bugzilla.scilab.org/show_bug.cgi?id=14984): In palettes pages, blocks screenshots were not aligned nor hyperlinked.
* [#15006](http://bugzilla.scilab.org/show_bug.cgi?id=15006): `ode` help page still contained 'root' which has been replaced by 'roots'.
* [#15008](http://bugzilla.scilab.org/show_bug.cgi?id=15008): scilab crashed when using operator AND (&, &&) or OR (| ||) with a string.
* [#15010](http://bugzilla.scilab.org/show_bug.cgi?id=15010): Coselica did not simulate on Scilab 6.
* [#15015](http://bugzilla.scilab.org/show_bug.cgi?id=15015): Xcos blocks using the `ascii` didn't work
* [#15017](http://bugzilla.scilab.org/show_bug.cgi?id=15017): On numbers, `gcd` result was always of `int32` type instead of matching the input type.
* [#15018](http://bugzilla.scilab.org/show_bug.cgi?id=15018): `mfprintf`'\n' not working.
* [#15019](http://bugzilla.scilab.org/show_bug.cgi?id=15019): Add 'csci6' in the calling of ilib_build in 'Getting started with API_Scilab' help page.
* [#15020](http://bugzilla.scilab.org/show_bug.cgi?id=15020): Examples of ilib_build help page updated.
* [#15023](http://bugzilla.scilab.org/show_bug.cgi?id=15023): `clf()` wrongly reset `figure_id`.
* [#15024](http://bugzilla.scilab.org/show_bug.cgi?id=15024): Xcos labels were not preserved at diagram compilation.
* [#15028](http://bugzilla.scilab.org/show_bug.cgi?id=15028): `assert_checkalmostequal` could not work with polynomials.
* [#15034](http://bugzilla.scilab.org/show_bug.cgi?id=15034): It was no longer possible to create a structure through a mlist.
* [#15037](http://bugzilla.scilab.org/show_bug.cgi?id=15037): the `residu` function might crash Scilab.
* [#15039](http://bugzilla.scilab.org/show_bug.cgi?id=15039): New Xcos graphical features needed some demos.
* [#15046](http://bugzilla.scilab.org/show_bug.cgi?id=15046): `call` couldn't mix inputs and outputs.
* [#15052](http://bugzilla.scilab.org/show_bug.cgi?id=15052): `getpid` was no longer available.
* [#15053](http://bugzilla.scilab.org/show_bug.cgi?id=15053): `_str2code` was removed with no proper equivalence and made `mfile2sci` failing.
* [#15054](http://bugzilla.scilab.org/show_bug.cgi?id=15054): The callbacks of `wfir_gui()` were not prioritary.
* [#15057](http://bugzilla.scilab.org/show_bug.cgi?id=15057): `Matplot` `.data` assignation did not take care of >2 dimension
* [#15058](http://bugzilla.scilab.org/show_bug.cgi?id=15058): With integers, `gcd` and `lcm` could return a negative result, depending on the order of negative components.
* [#15060](http://bugzilla.scilab.org/show_bug.cgi?id=15060): `fplot3d` did not draw because of an addition with an empty matrix which now returns an empty matrix.
* [#15063](http://bugzilla.scilab.org/show_bug.cgi?id=15063): `fort` wasn't properly removed.
* [#15066](http://bugzilla.scilab.org/show_bug.cgi?id=15066): Undo did not update ports positions
* [#15070](http://bugzilla.scilab.org/show_bug.cgi?id=15070): `bitset` failed when the bit position is specified as encoded integer.
* [#15072](http://bugzilla.scilab.org/show_bug.cgi?id=15072): The context was stored as a root diagram attribute instead of being stored on each Superblock layer.
* [#15079](http://bugzilla.scilab.org/show_bug.cgi?id=15079): When all children of a graphic handle have not the same number of sub-children, any vectorized extraction or insertion in subchildren failed.
* [#15089](http://bugzilla.scilab.org/show_bug.cgi?id=15089): The `getcolor` GUI cleared and used the current figure.
* [#15106](http://bugzilla.scilab.org/show_bug.cgi?id=15106): Operation without operand crashed Scilab.
* [#15107](http://bugzilla.scilab.org/show_bug.cgi?id=15107): Scilab failed to build with ocaml 4.04.0.
* [#15111](http://bugzilla.scilab.org/show_bug.cgi?id=15111): Summation block symbol displayed minus sign instead of plus sign.
* [#15117](http://bugzilla.scilab.org/show_bug.cgi?id=15117): Imbricated calls to `optim` / `leastsq` / `lsqrsolve` / `fsolve` either crashed or returned errors.
* [#15119](http://bugzilla.scilab.org/show_bug.cgi?id=15119): Inequality comparisons between complex-encoded real numbers failed.
* [#15121](http://bugzilla.scilab.org/show_bug.cgi?id=15121): `getOptionals` fails to recognize some options.
* [#15137](http://bugzilla.scilab.org/show_bug.cgi?id=15137): `ilib_build` could not build a library with more than 999 function entries in Scilab 6
* [#15138](http://bugzilla.scilab.org/show_bug.cgi?id=15138): Scilab crashed at startup on Windows.
* [#15139](http://bugzilla.scilab.org/show_bug.cgi?id=15139): Fix return in `try` / `catch` expression
* [#15142](http://bugzilla.scilab.org/show_bug.cgi?id=15142): `mopen()` wrong err value
* [#15144](http://bugzilla.scilab.org/show_bug.cgi?id=15144): `mean` and `stdev` could not be overloaded.
* [#15146](http://bugzilla.scilab.org/show_bug.cgi?id=15146): `lasterror` crashed Scilab when last error message is empty.
* [#15148](http://bugzilla.scilab.org/show_bug.cgi?id=15148): `link` did not return any error for a wrong flag argument value.
* [#15149](http://bugzilla.scilab.org/show_bug.cgi?id=15149): Files saved as ZCOS were corrupted.
* [#15170](http://bugzilla.scilab.org/show_bug.cgi?id=15170): `getd` created and returned a variable `k` that could overwrite a loaded one.
* [#15183](http://bugzilla.scilab.org/show_bug.cgi?id=15183): `ndgrid(x)` with by default `y=x` was not accepted.
* [#15184](http://bugzilla.scilab.org/show_bug.cgi?id=15184): `(1+%i) < 2` crashed Scilab.
* [#15185](http://bugzilla.scilab.org/show_bug.cgi?id=15185): "Region to Superblock" did not restore broken links.
* [#15188](http://bugzilla.scilab.org/show_bug.cgi?id=15188): `sci_hdf5_is_file` was wrongly named in the hdf5 DLL.
* [#15199](http://bugzilla.scilab.org/show_bug.cgi?id=15199): Scilab crashed when using `fsolve` for functions containing other functions.
* [#15205](http://bugzilla.scilab.org/show_bug.cgi?id=15205): `get_scicos_version` returned the previous version.
* [#15207](http://bugzilla.scilab.org/show_bug.cgi?id=15207): `xcos(scs_m)` did not work for sub-systems.
* [#15215](http://bugzilla.scilab.org/show_bug.cgi?id=15215): `strcat` did not work correctly with empty strings.
* [#15223](http://bugzilla.scilab.org/show_bug.cgi?id=15223): `call` crashed in some cases.
* [#15228](http://bugzilla.scilab.org/show_bug.cgi?id=15228): `get` error message fixed.
* [#15236](http://bugzilla.scilab.org/show_bug.cgi?id=15236): The `isglobal` help page was inaccurate. Examples were erroneous.
* [#15239](http://bugzilla.scilab.org/show_bug.cgi?id=15239): The console properties `.tag` and `.userdata` were not displayed nor documented.
* [#15243](http://bugzilla.scilab.org/show_bug.cgi?id=15243): `grand(nr, nc, "uin", vmin)` crashed Scilab.
* [#15246](http://bugzilla.scilab.org/show_bug.cgi?id=15246): `chsolve` called a `blkslv` missing function.
* [#15249](http://bugzilla.scilab.org/show_bug.cgi?id=15249): `findobj("toto")` yielded an error instead of returning [].
* [#15260](http://bugzilla.scilab.org/show_bug.cgi?id=15260): `sci2exp` was broken for cells, structures, and all types of hypermatrix.
* [#15261](http://bugzilla.scilab.org/show_bug.cgi?id=15261): Insertion in struct felt with wrong default value.
* [#15266](http://bugzilla.scilab.org/show_bug.cgi?id=15266): Wrong default out_mode in `linear_interpn`.
* [#15273](http://bugzilla.scilab.org/show_bug.cgi?id=15273): The documented order of `eval_cshep2d` second derivatives was wrong.
* [#15278](http://bugzilla.scilab.org/show_bug.cgi?id=15278): Moving Xcos blocks reverted rotation and flip/mirror properties
* [#15282](http://bugzilla.scilab.org/show_bug.cgi?id=15282): `help_from_sci` could set an xml:id starting with the forbidden `%` character.
* [#15285](http://bugzilla.scilab.org/show_bug.cgi?id=15285): `resize_matrix` did not manage conversion into `int64` and `uint64`.
* [#15300](http://bugzilla.scilab.org/show_bug.cgi?id=15300): Distributive assignments like `a=(1,2)` crashed Scilab.
* [#15301](http://bugzilla.scilab.org/show_bug.cgi?id=15301): Sequence constructor `:` failed when a bound was an outputless funtion call.
* [#15302](http://bugzilla.scilab.org/show_bug.cgi?id=15302): `load` crashed when inputs arguments are not strings.
* [#15303](http://bugzilla.scilab.org/show_bug.cgi?id=15303): Some properties written in capital letter in set function crashed Scilab.
* [#15306](http://bugzilla.scilab.org/show_bug.cgi?id=15306): After the behavior of `||` was changed, its help page was not up to date.
* [#15308](http://bugzilla.scilab.org/show_bug.cgi?id=15308): Unlike `evstr(["1 2";"3 4"])`, `evstr(["1;2" "3;4"])` was not accepted.
* [#15328](http://bugzilla.scilab.org/show_bug.cgi?id=15328): OpenJDK 9 was not supported for custom builds.
* [#15337](http://bugzilla.scilab.org/show_bug.cgi?id=15337): There was a mistake in the definition of the l_p norm of a vector in the `norm` page.
* [#15339](http://bugzilla.scilab.org/show_bug.cgi?id=15339): `uigetfont()` returned garbage on user cancellation.
* [#15340](http://bugzilla.scilab.org/show_bug.cgi?id=15340): Scilab did not build against lucene 6.1.0.
* [#15342](http://bugzilla.scilab.org/show_bug.cgi?id=15342): `replot()` and `Reframe to contents` failed on graphics with xstring objects.
* [#15347](http://bugzilla.scilab.org/show_bug.cgi?id=15347): `toeplitz` failed with rationals.
* [#15354](http://bugzilla.scilab.org/show_bug.cgi?id=15354): `invr(%s^2)` returned 0 instead of `1/%s^2`. For any scalar number, polynomial or rational `a`, `coffg(a)` returned `0` instead of `1`. `coffg([])` yielded an error. `invr` and `coffg` had no unitary tests. The `coffg` help page was inaccurate and unclear.
* [#15360](http://bugzilla.scilab.org/show_bug.cgi?id=15360): `numer()` and `denom()` were almost useless, unused, and with more handy replacements. They are declared obsolete to be removed in Scilab 6.1.0.
* [#15363](http://bugzilla.scilab.org/show_bug.cgi?id=15363): `h2norm()` could no longer be applied to undefined time domain systems, and made the residu() right example failing.
* [#15368](http://bugzilla.scilab.org/show_bug.cgi?id=15368): `freson()` wrongly returned [] (no peak frequency detected) for some continuous time linear systems.
* [#15370](http://bugzilla.scilab.org/show_bug.cgi?id=15370): `bezout()` mishandled its output arguments.
* [#15375](http://bugzilla.scilab.org/show_bug.cgi?id=15375): A .zcos file opened as a palette was greyed out.
* [#15379](http://bugzilla.scilab.org/show_bug.cgi?id=15379): `zeros(A)` was not documented as equivalent to `mtlb_zeros(size(A))`.
* [#15380](http://bugzilla.scilab.org/show_bug.cgi?id=15380): `argn()` documentation was somewhat unclear and uncomplete.
* [#15388](http://bugzilla.scilab.org/show_bug.cgi?id=15388): Dynamic link did not work on MACOSX 10,12.
* [#15389](http://bugzilla.scilab.org/show_bug.cgi?id=15389): `Wscilex -nw` failed and created a ghost process.
* [#15390](http://bugzilla.scilab.org/show_bug.cgi?id=15390): In online help pages, tooltips showing the code on images were no longer displayed.
* [#15395](http://bugzilla.scilab.org/show_bug.cgi?id=15395): `ones(2,3,2) / %z` yielded an error..
* [#15396](http://bugzilla.scilab.org/show_bug.cgi?id=15396): `[m,n,p] = size(hr)` yielded an error with an hypermatrix hr of rationals.
* [#15402](http://bugzilla.scilab.org/show_bug.cgi?id=15402): The `range()` page was not fixed against the bug 1904 for the french and portuguese versions.
* [#15405](http://bugzilla.scilab.org/show_bug.cgi?id=15405): Accessing int64 hdf5 values crashed scilab.
* [#15413](http://bugzilla.scilab.org/show_bug.cgi?id=15413): Deleting some ranges (rows, columns, pages, ..) in a structures array failed.
* [#15418](http://bugzilla.scilab.org/show_bug.cgi?id=15418): With `colordef('black')` and `colordef('none')`, black title and labels were invisible on the black background.
* [#15419](http://bugzilla.scilab.org/show_bug.cgi?id=15419): `tbx_build_localization` did nothing and silently returned when no `~/locales` directory was detected. `tbx_generate_pofile()` was not run, and the user was not warned and guided.
* [#15420](http://bugzilla.scilab.org/show_bug.cgi?id=15420): insertion at negative index did not trigger an error.
* [#15456](http://bugzilla.scilab.org/show_bug.cgi?id=15456): Xcos 5.5.x files did not load properly.
* [#15459](http://bugzilla.scilab.org/show_bug.cgi?id=15459): Generating code from an Xcos superblock generated warnings.


### Bugs fixed in 6.0.0:
* [#592](http://bugzilla.scilab.org/show_bug.cgi?id=592): `linspace(a, b, n<=0)` returned `b` instead of `[]`
* [#2835](http://bugzilla.scilab.org/show_bug.cgi?id=2835): On negative "initial event", EVTDLY_c took no notice of the input.
* [#2919](http://bugzilla.scilab.org/show_bug.cgi?id=2919): The `fchamp` example and demo were unclear and badly rendered
* [#4327](http://bugzilla.scilab.org/show_bug.cgi?id=4327): Overloading did not support custom types names longer than 8 characters
* [#5278](http://bugzilla.scilab.org/show_bug.cgi?id=5278): Most of the references to `xset` and `xget` in scripts, macros, help pages and tests were obsolete.
* [#5723](http://bugzilla.scilab.org/show_bug.cgi?id=5723): Cross-references were missing between `axis_properties` and `axes_properties` help pages
* [#6307](http://bugzilla.scilab.org/show_bug.cgi?id=6307): There were no  easy versions of `lqr`, `lqe`, and `lqg`
* [#7192](http://bugzilla.scilab.org/show_bug.cgi?id=7192): From `S=[]`, `S($+1,:) = some_row` inserted it in row#2 after a parasitic row#1.
* [#7649](http://bugzilla.scilab.org/show_bug.cgi?id=7649): `isempty` returned `%F` on `struct()`, `{}` or `list(,)` and was not shortcut
* [#7696](http://bugzilla.scilab.org/show_bug.cgi?id=7696): The `parallel_run` help page was poorly formated
* [#7794](http://bugzilla.scilab.org/show_bug.cgi?id=7794): The example in the `findABCD` help page failed.
* [#7958](http://bugzilla.scilab.org/show_bug.cgi?id=7958): `mrfit`did not allow a fourth parameter as shown in the help page.
* [#8010](http://bugzilla.scilab.org/show_bug.cgi?id=8010): Permanent variables could be redefined through a syntax like `%i(1,1)=1`
* [#8190](http://bugzilla.scilab.org/show_bug.cgi?id=8190): Fixed ICSE demos of Optimization module.
* [#8356](http://bugzilla.scilab.org/show_bug.cgi?id=8356): `sci2exp` applied to lists, tlists or mlists having undefined fields yielded an error or a wrong result.
* [#8493](http://bugzilla.scilab.org/show_bug.cgi?id=8493): Some trivial simplifications of `p1./p2` with matrices of complex-encoded polynomials were not done.
* [#8841](http://bugzilla.scilab.org/show_bug.cgi?id=8841): After `s.a=list(4,7)`, `s.a` was not equal to `s(1).a`
* [#8938](http://bugzilla.scilab.org/show_bug.cgi?id=8938): In a boolean sparse matrix `sp`, distributive insertions like `sp(1,:)=%t`, `sp(1,1:$)=%t` or `sp(:,:)=%t` yielded an error.
* [#9008](http://bugzilla.scilab.org/show_bug.cgi?id=9008): `test_run` applied the `create_ref` option even for tests having the `<-- NO CHECK REF -->` flag.
* [#9153](http://bugzilla.scilab.org/show_bug.cgi?id=9153): The `isqualbitwise` help page was inaccurate and badly located
* [#9161](http://bugzilla.scilab.org/show_bug.cgi?id=9161): Multiple insertions at a repeated index in a sparse matrice wrongly updated it.
* [#9288](http://bugzilla.scilab.org/show_bug.cgi?id=9288): No palette dynamically built with the most used blocks was available
* [#9451](http://bugzilla.scilab.org/show_bug.cgi?id=9451): `test_run` output did not clearly distinguish heading lines of modules and tests lines
* [#9825](http://bugzilla.scilab.org/show_bug.cgi?id=9825): `assert_computedigits` returns too much digits
* [#9865](http://bugzilla.scilab.org/show_bug.cgi?id=9865): When making a plot with `point`(no line), no symbol was shown in the legend.
* [#9876](http://bugzilla.scilab.org/show_bug.cgi?id=9876): Creating a complex structure with multiple hierarchy level and size failed.
* [#9912](http://bugzilla.scilab.org/show_bug.cgi?id=9912): In case of missing translated help page, its default `en_US` version was sometimes ignored
* [#10116](http://bugzilla.scilab.org/show_bug.cgi?id=10116): `for h = H, .., end` could not be used when H is a vector of graphic handles
* [#10195](http://bugzilla.scilab.org/show_bug.cgi?id=10195): `execstr` interpreted ascii(0) to ascii(31) characters as the power `^` operator.
* [#10326](http://bugzilla.scilab.org/show_bug.cgi?id=10326): The palette browser didn't have any search engine.
* [#10981](http://bugzilla.scilab.org/show_bug.cgi?id=10981): It was possible to rotate a 2D axes, and hard to get it back to a 2D view.
* [#11375](http://bugzilla.scilab.org/show_bug.cgi?id=11375): When a localized help subdirectory has only a `CHAPTER` file specifying the section title, this one was ignored.
* [#11476](http://bugzilla.scilab.org/show_bug.cgi?id=11476): `clf("reset")` used on a docked figure resized and moved the whole docked block like the Scilab desktop.
* [#11692](http://bugzilla.scilab.org/show_bug.cgi?id=11692): The summary of a help section built from both default `en_US` and localized files was never sorted overall.
* [#11959](http://bugzilla.scilab.org/show_bug.cgi?id=11959): Selecting a zoom area starting on some axes borders was hard and tricky.
* [#12017](http://bugzilla.scilab.org/show_bug.cgi?id=12017): The on-screen rendering according to `figure.pixel_drawing_mode` was out of work since Scilab 5.4
* [#12110](http://bugzilla.scilab.org/show_bug.cgi?id=12110): Zooming multiple side-by-side or overlaying axes at once was out of work since Scilab 5.4
* [#12417](http://bugzilla.scilab.org/show_bug.cgi?id=12417): Set "All supported formats" as default selected on Xcos open.
* [#12431](http://bugzilla.scilab.org/show_bug.cgi?id=12431): The page describing the `%helps` variable needed clarification.
* [#12453](http://bugzilla.scilab.org/show_bug.cgi?id=12453): In the Xcos palette browser, enabling or disabling some category resized the left panel.
* [#12623](http://bugzilla.scilab.org/show_bug.cgi?id=12623): When `%onprompt()` is defined, variables defined in any callback of a console's menu were not accessible in the console.
* [#12897](http://bugzilla.scilab.org/show_bug.cgi?id=12897): Renamed `optim`'s `imp` argument to `"iprint"`.
* [#13217](http://bugzilla.scilab.org/show_bug.cgi?id=13217): `augment` was wrong when `flag2` was `"i"`
* [#13166](http://bugzilla.scilab.org/show_bug.cgi?id=13166): `l` and `b` endian flags used with `mget` and `mgeti` were sticky
* [#13375](http://bugzilla.scilab.org/show_bug.cgi?id=13375): For a uicontrol listbox, `.Max - .Min==1` prevented any multiple selection. The default value documented for uicontrol`.relief` was wrong.
* [#13401](http://bugzilla.scilab.org/show_bug.cgi?id=13401): Scilab became a ghost process when it was closed while an `input` or a `halt` instruction was being performed in a callback of an undockable figure.
* [#13583](http://bugzilla.scilab.org/show_bug.cgi?id=13583): `getd` loading a script including a `clear` instruction yielded an error.
* [#13597](http://bugzilla.scilab.org/show_bug.cgi?id=13597): `help format` claimed setting a number of digits instead of a number of characters.
* [#13613](http://bugzilla.scilab.org/show_bug.cgi?id=13613): `isdef(name, 'l')` produced wrong output.
* [#13620](http://bugzilla.scilab.org/show_bug.cgi?id=13620): `dos` called with a vector of OS instructions crashed Scilab.
* [#13651](http://bugzilla.scilab.org/show_bug.cgi?id=13651): It was not possible to `copy` an axes into an uicontrol frame.
* [#13757](http://bugzilla.scilab.org/show_bug.cgi?id=13757): The `Toolboxes` menu dit not load properly not autoloaded ATOMS modules.
* [#13759](http://bugzilla.scilab.org/show_bug.cgi?id=13759): At startup, sometimes autoloadable Atoms modules were not loaded, randomly.
* [#13794](http://bugzilla.scilab.org/show_bug.cgi?id=13794): It was not possible to toggle the display of a datatip just by clicking on its anchor or by overflying its anchor with the mouse pointer.
* [#13856](http://bugzilla.scilab.org/show_bug.cgi?id=13856): `messagebox` crashed under Windows in 5.5 Scilab version and updated in version 6.
* [#13877](http://bugzilla.scilab.org/show_bug.cgi?id=13877): In help pages, `<` characters included in `<screen>` areas were not rendered in the help browser.
* [#13878](http://bugzilla.scilab.org/show_bug.cgi?id=13878): `tokens([])` yielded an error instead of returning `[]`.
* [#13895](http://bugzilla.scilab.org/show_bug.cgi?id=13895): After `p.a.h = 1; p.b.h = 3;`, `p(:).h` crashed Scilab.
* [#13906](http://bugzilla.scilab.org/show_bug.cgi?id=13906): Arrows keys did not allow to navigate through the Palette browser.
* [#13990](http://bugzilla.scilab.org/show_bug.cgi?id=13990): `warning` with localization enabled some memory corruption.
* [#14171](http://bugzilla.scilab.org/show_bug.cgi?id=14171): Scinotes Favorite and most recently used directories could no be targeted through the console `File` menu.
* [#14192](http://bugzilla.scilab.org/show_bug.cgi?id=14192): `g_margin` error-ed for double integrator.
* [#14278](http://bugzilla.scilab.org/show_bug.cgi?id=14278): `ltitr` returned an incorrect xf output value.
* [#14306](http://bugzilla.scilab.org/show_bug.cgi?id=14306): `>` and `>=` operators could not be used to compare encoded integers of mismatching inttypes.
* [#14330](http://bugzilla.scilab.org/show_bug.cgi?id=14330): luget was really slow.
* [#14367](http://bugzilla.scilab.org/show_bug.cgi?id=14367): `edit_curv` failed opening due to a `[]+1` operation.
* [#14379](http://bugzilla.scilab.org/show_bug.cgi?id=14379): Problem with lists of functions having 2 arguments.
* [#14395](http://bugzilla.scilab.org/show_bug.cgi?id=14395): `dir` displayed a []+".." warning when no subdirectory exists.
* [#14405](http://bugzilla.scilab.org/show_bug.cgi?id=14405): `xcosPalAdd` did not work on Windows.
* [#14411](http://bugzilla.scilab.org/show_bug.cgi?id=14411): `abort` used in a `while`loop crashed Scilab.
* [#14437](http://bugzilla.scilab.org/show_bug.cgi?id=14437): Changing the field of a struct embedded in a list sometimes misworked.
* [#14448](http://bugzilla.scilab.org/show_bug.cgi?id=14448): `havewindow` is removed but was still documented.
* [#14461](http://bugzilla.scilab.org/show_bug.cgi?id=14461): Calling `grand(n, "markov", P, x0)` did not return all outputs.
* [#14470](http://bugzilla.scilab.org/show_bug.cgi?id=14470): `geomean` often overflowed for easily computable entries, and did not check input arguments.
* [#14483](http://bugzilla.scilab.org/show_bug.cgi?id=14483): The `figure.figure_name` property had no `figure.name` alias
* [#14513](http://bugzilla.scilab.org/show_bug.cgi?id=14513): `isqual` comparing two built-in functions yielded an error.
* [#14527](http://bugzilla.scilab.org/show_bug.cgi?id=14527): Calling `pathconvert` function without parameters crashed Scilab.
* [#14553](http://bugzilla.scilab.org/show_bug.cgi?id=14553): `find(a=b)` crashed Scilab.
* [#14557](http://bugzilla.scilab.org/show_bug.cgi?id=14557): `csim` failed when the system has no state.
* [#14558](http://bugzilla.scilab.org/show_bug.cgi?id=14558): `square` was poor, clumsy and too specific. It is tagged as obsolete.
* [#14564](http://bugzilla.scilab.org/show_bug.cgi?id=14564): `fieldnames` failed for empty structs.
* [#14571](http://bugzilla.scilab.org/show_bug.cgi?id=14571): The types of input arguments of `figure()` were not checked.
* [#14578](http://bugzilla.scilab.org/show_bug.cgi?id=14578): LaTeX string used for text uicontrol was not updated.
* [#14582](http://bugzilla.scilab.org/show_bug.cgi?id=14582): `gettext` or it alias `_()` were sometimes applied to broken literal strings
* [#14586](http://bugzilla.scilab.org/show_bug.cgi?id=14586): The Stop button of Xcos simulation did not work.
* [#14587](http://bugzilla.scilab.org/show_bug.cgi?id=14587): Datatip textbox wrong clipping when loaded from `*.scg` file.
* [#14590](http://bugzilla.scilab.org/show_bug.cgi?id=14590): Many help pages in `pt_BR` version had a wrong xml:lang="en" tag.
* [#14591](http://bugzilla.scilab.org/show_bug.cgi?id=14591): `<=` and `>=` elementwise operators comparing 2 hypermatrices of decimal numbers or encoded integers were inverted.
* [#14593](http://bugzilla.scilab.org/show_bug.cgi?id=14593): Signs were no longer drawn in BIGSOM and PRODUCT components.
* [#14602](http://bugzilla.scilab.org/show_bug.cgi?id=14602): WRITEC_f block didn't work for x86 machines.
* [#14604](http://bugzilla.scilab.org/show_bug.cgi?id=14604): `emptystr()` was 40x slower than Scilab 5
* [#14609](http://bugzilla.scilab.org/show_bug.cgi?id=14609): "msscanf" crashes Scilab when 'niter' parameter is out of range.
* [#14632](http://bugzilla.scilab.org/show_bug.cgi?id=14632): Zooming moved offscreen any drawn axis
* [#14640](http://bugzilla.scilab.org/show_bug.cgi?id=14640): `median(int8([10 60 80 100]))` returned -58 instead of 70 due to overflow when interpolating (60+80)>128
* [#14645](http://bugzilla.scilab.org/show_bug.cgi?id=14645): Xcos Demos -> Control Systems -> Lorenz Butterfly didn't end at the expected time (30)
* [#14648](http://bugzilla.scilab.org/show_bug.cgi?id=14648): `isinf` returned `%F` for complex numbers with both real and imag infinite parts.
* [#14649](http://bugzilla.scilab.org/show_bug.cgi?id=14649): `isnan(complex(%inf, %inf))` returned `%F` while the phase is `NaN`.
* [#14654](http://bugzilla.scilab.org/show_bug.cgi?id=14654): `bitor`, `bitxor` and `bitand` did not accept positive inputs of type `int8`, `int16`, `int32`, `int64` or `uint64`
* [#14659](http://bugzilla.scilab.org/show_bug.cgi?id=14659): number of I/O ports of the superblock was not updated when adding or deleting I/O blocks inside a superblock.
* [#14662](http://bugzilla.scilab.org/show_bug.cgi?id=14662): Matrix of strings concatenation with single quote led to a parser error.
* [#14664](http://bugzilla.scilab.org/show_bug.cgi?id=14664): Deleted obsolete WFILE_f block. Regenerated some Xcos demos to work with Scilab 6.
* [#14667](http://bugzilla.scilab.org/show_bug.cgi?id=14667): Multi line string without final quote generated a non terminal parser state.
* [#14681](http://bugzilla.scilab.org/show_bug.cgi?id=14681): Short-circuited AND operation was not possible with double matrices in if and while clauses
* [#14689](http://bugzilla.scilab.org/show_bug.cgi?id=14689): `resize_matrix(rand(2,3),[0 2])` did not return `[]`. Usage of new sizes <0 to keep them unchanged was not documented.
* [#14690](http://bugzilla.scilab.org/show_bug.cgi?id=14690): The user startup files set in the working directory were not executed. When `SCIHOME` is not the working directory, `SCIHOME\scilab.ini` was executed twice.
* [#14692](http://bugzilla.scilab.org/show_bug.cgi?id=14692): `isequal` always returned `%T` for builtin functions
* [#14694](http://bugzilla.scilab.org/show_bug.cgi?id=14694): The list of named colors was misaligned and poorly rendered in `help color_list`
* [#14710](http://bugzilla.scilab.org/show_bug.cgi?id=14710): `fullpath(TMPDIR+...)` was bugged on MacOS
* [#14711](http://bugzilla.scilab.org/show_bug.cgi?id=14711): When current axes is an uicontrol frame, `colorbar` did not display anything.
* [#14714](http://bugzilla.scilab.org/show_bug.cgi?id=14714): Deleting a datatip made Scilab leaking or crashed.
* [#14731](http://bugzilla.scilab.org/show_bug.cgi?id=14731): The demos `Graphics => Complex functions` opened an empty figure#0. Rotation of Im+Re parts were not synchronized
* [#14743](http://bugzilla.scilab.org/show_bug.cgi?id=14743): `test_run(.., "show_error")` did not document "failed: Slave Scilab exited with error code #" errors.
* [#14758](http://bugzilla.scilab.org/show_bug.cgi?id=14758): `xstringb` opened a default figure.
* [#14761](http://bugzilla.scilab.org/show_bug.cgi?id=14761): `||` misworked when LHS is %f or zeros. `&&` misworked when LHS is %t or non-zeros
* [#14779](http://bugzilla.scilab.org/show_bug.cgi?id=14779): `xsegs` used in logarithmic scale with coordinates `<= 0` crashed Scilab.
* [#14784](http://bugzilla.scilab.org/show_bug.cgi?id=14784): Setting field of graphics handle using children($) failed.
* [#14796](http://bugzilla.scilab.org/show_bug.cgi?id=14796): `ind2sub([4,2], [])` returned `[4 0]` instead of `[]`.
* [#14775](http://bugzilla.scilab.org/show_bug.cgi?id=14775): Loading an empty (0 bytes) `.sod` file crashed scilab
* [#14801](http://bugzilla.scilab.org/show_bug.cgi?id=14801): The horizontal concatenation of cells arrays wrongly puzzled components.
* [#14808](http://bugzilla.scilab.org/show_bug.cgi?id=14808): After `E=['A' 'B' 'C' 'D' 'E']`, `E(0:0)` crashed Scilab
* [#14821](http://bugzilla.scilab.org/show_bug.cgi?id=14821): `getio` function was missing. An error on the diary file opened has been corrected.
* [#14824](http://bugzilla.scilab.org/show_bug.cgi?id=14824): `mfprintf(fd, "%d", [])` yielded an incorrect error message.
* [#14835](http://bugzilla.scilab.org/show_bug.cgi?id=14835): `AFFICH_m` block was not rendered correctly.
* [#14839](http://bugzilla.scilab.org/show_bug.cgi?id=14839): `plot2d2` crashed Scilab.
* [#14885](http://bugzilla.scilab.org/show_bug.cgi?id=14885): The `tag` property was not documented in the `Matplot_properties` help page.
* [#14887](http://bugzilla.scilab.org/show_bug.cgi?id=14887): For many types of graphic handles, the display of the `.tag` value missed `".."` delimiters
* [#14909](http://bugzilla.scilab.org/show_bug.cgi?id=14909): On Windows, `getlongpathname` and `getshortpathname` did not force the file separator to `"\"`
* [#14911](http://bugzilla.scilab.org/show_bug.cgi?id=14911): The entry "Label => Title" was missing in the graphic context menu on a figure.
* [#14941](http://bugzilla.scilab.org/show_bug.cgi?id=14941): `find` did not accept encoded integers
* [#14942](http://bugzilla.scilab.org/show_bug.cgi?id=14942): Keep the Tkscale block label if block already has label.
* [#14956](http://bugzilla.scilab.org/show_bug.cgi?id=14956): `clf("reset")` forgot resetting the `immediate_drawing`, `resize`, `resizefcn`, `closerequestfcn`, `toolbar_visible`, `menubar_visible`, `infobar_visible`, `default_axes`, and `icon` figure properties.
* [#14965](http://bugzilla.scilab.org/show_bug.cgi?id=14965): `getPreferencesValue` could not read a tag having multiple occurrences and did not accept the path to the preferences file.
* [#14976](http://bugzilla.scilab.org/show_bug.cgi?id=14976): `asciimat(colNum)` concatenated rows when colNum has a single column of ascii codes. With UTF-8 chars, `asciimat(asciimat("àéïôù"))` yielded an error.
* [#14978](http://bugzilla.scilab.org/show_bug.cgi?id=14978): `input(message)` interpreted an entered `x` as a literal string, and exited with the new prompt on the same line.


### Bugs fixed in 6.0.0 beta-2 and earlier 6.0.0 pre-releases:

* [#2104](http://bugzilla.scilab.org/show_bug.cgi?id=2104): `iw(1:9)` and `w(1:10)` `ode` output parameters were not documented
* [#2517](http://bugzilla.scilab.org/show_bug.cgi?id=2517): `"position"` property format was not accepted by `figure` despite what was said in help
* [#6057](http://bugzilla.scilab.org/show_bug.cgi?id=6057): trailing space after minus sign has been removed from the display of values
* [#6064](http://bugzilla.scilab.org/show_bug.cgi?id=6064): `scatter` did not exist in Scilab.
* [#6314](http://bugzilla.scilab.org/show_bug.cgi?id=6314): The identical code of `%p_m_r` and `%r_m_p` was not factorized
* [#7378](http://bugzilla.scilab.org/show_bug.cgi?id=7378): `quart` used with only `NaN`s yielded an error instead of returning `NaN`.
* [#7646](http://bugzilla.scilab.org/show_bug.cgi?id=7646): Extractions `A'(1,2)` and `A.'(1,2)` from a transposed matrix were not possible
* [#7884](http://bugzilla.scilab.org/show_bug.cgi?id=7884): `typeof` help page was poor, puzzled, and not up-to-date to Scilab 6:
  - new typeof `uint64`, `int64`, `void`, `deletelist`, `implicitlist ` were missing
  - former `hypermat` and `size implicit` typeof weren't removed
  - typeof names longer than 8-char were not documented.
* [#8210](http://bugzilla.scilab.org/show_bug.cgi?id=8210): UMFPACK demos were not well packaged and not numerous enough.
* [#8310](http://bugzilla.scilab.org/show_bug.cgi?id=8310): Non-convex plane or unplane polygons could be wrongly triangulated and badly rendered with extra facets.
* [#8990](http://bugzilla.scilab.org/show_bug.cgi?id=8990): `Reframe to contents` feature was missing on the graphics toolbar and `Tools` menu.
* [#9456](http://bugzilla.scilab.org/show_bug.cgi?id=9456): `bench_run` did not work on a path or in a toolbox
* [#9560](http://bugzilla.scilab.org/show_bug.cgi?id=9560): `1./M` was parsed as `1. / M` instead of `1 ./ M`
* [#9621](http://bugzilla.scilab.org/show_bug.cgi?id=9621): A `tlist` with undefined fields can now be saved.
* [#10082](http://bugzilla.scilab.org/show_bug.cgi?id=10082): `string(complex)` with `real(complex)>0` did not remove the leading space replacing `"+"`
* [#11511](http://bugzilla.scilab.org/show_bug.cgi?id=11511): `error` did not accept string matrix (non regression test added).
* [#11625](http://bugzilla.scilab.org/show_bug.cgi?id=11625): Uicontrol table did not update `.string` when values were modified interactively in the table.
* [#12044](http://bugzilla.scilab.org/show_bug.cgi?id=12044): Adding or substracting the empty matrix now return an empty matrix.
* [#12202](http://bugzilla.scilab.org/show_bug.cgi?id=12202): Mixing int8 and doubles with colon operator led to wrong results.
* [#12419](http://bugzilla.scilab.org/show_bug.cgi?id=12419): objects were cleared before the `scilab.quit` was called
* [#12559](http://bugzilla.scilab.org/show_bug.cgi?id=12559): FFTW had some memory leaks
* [#12872](http://bugzilla.scilab.org/show_bug.cgi?id=12872): Help pages of `else`, `elseif`, `end`, `try`, `sciargs`, global, halt, empty and power were in wrong help sections
* [#12928](http://bugzilla.scilab.org/show_bug.cgi?id=12928): `intXX` functions with `%nan` and `%inf` return wrong values.
* [#13154](http://bugzilla.scilab.org/show_bug.cgi?id=13154): In shellmode, completion now separates Files from Directories.
* [#13289](http://bugzilla.scilab.org/show_bug.cgi?id=13289): Using non-integer indexes for mlists made Scilab crash.
* [#13298](http://bugzilla.scilab.org/show_bug.cgi?id=13298): Static analysis bugs detected by PVS-Studio fixed.
* [#13308](http://bugzilla.scilab.org/show_bug.cgi?id=13308): Xcos had no Crank-Nicolson solver.
* [#13465](http://bugzilla.scilab.org/show_bug.cgi?id=13465): The display of polyline `.display_function` and `.display_function` properties was not conventional
* [#13468](http://bugzilla.scilab.org/show_bug.cgi?id=13468): Scilab hanged when incorrect format was used for file reading using `mfscanf`.
* [#13490](http://bugzilla.scilab.org/show_bug.cgi?id=13490): `histc` help page fixed to match the macro (by default, normalize the result).
* [#13517](http://bugzilla.scilab.org/show_bug.cgi?id=13517): `isdef` crashed Scilab when called with a vector of strings as input in a function and after a declaration of variable.
* [#13709](http://bugzilla.scilab.org/show_bug.cgi?id=13709): `unique` sometimes returned wrong index values.
* [#13725](http://bugzilla.scilab.org/show_bug.cgi?id=13725): Sometimes `xfpoly` polygon filling failed.
* [#13748](http://bugzilla.scilab.org/show_bug.cgi?id=13748): `printf`, `sprintf` (en,ja): short descriptions and obsolete flags were missing.
* [#13750](http://bugzilla.scilab.org/show_bug.cgi?id=13750): Calling `ss2ss` with `flag = 2` returned an error.
* [#13751](http://bugzilla.scilab.org/show_bug.cgi?id=13751): `lqg2stan` returned wrong (inverted) values.
* [#13769](http://bugzilla.scilab.org/show_bug.cgi?id=13769): `t = "abc..//ghi"` was parsed as a continued + comment
* [#13780](http://bugzilla.scilab.org/show_bug.cgi?id=13780): `size` with two input and output arguments did not return an error.
* [#13795](http://bugzilla.scilab.org/show_bug.cgi?id=13795): `grep` with regexp option did not match the empty string properly
* [#13807](http://bugzilla.scilab.org/show_bug.cgi?id=13807): Invalid margins were computed when figure was not visible.
* [#13810](http://bugzilla.scilab.org/show_bug.cgi?id=13810): `householder(v, k*v)` returned column of `Nan`. Input parameters were not checked. The Householder matrix could not be returned. Help pages were inaccurate and without examples. There was no `householder` demo.
* [#13816](http://bugzilla.scilab.org/show_bug.cgi?id=13816): `show_margins` caused a scilab crash
* [#13829](http://bugzilla.scilab.org/show_bug.cgi?id=13829): `mean` and `sum` returned wrong results for hypermatrices.
* [#13831](http://bugzilla.scilab.org/show_bug.cgi?id=13831): `ss2ss` did not update the initial state
* [#13834](http://bugzilla.scilab.org/show_bug.cgi?id=13834): Drawing a high number of strings in a figure generated a Java exception.
* [#13838](http://bugzilla.scilab.org/show_bug.cgi?id=13838): Sparse and complex substraction made Scilab crash.
* [#13839](http://bugzilla.scilab.org/show_bug.cgi?id=13839): `sign` could not be used with sparse matrices
* [#13843](http://bugzilla.scilab.org/show_bug.cgi?id=13843): Scilab crashed when `polarplot` and `plot2d` were called with wrong `strf` value.
* [#13853](http://bugzilla.scilab.org/show_bug.cgi?id=13853): `plzr` returned wrong results for discrete-time systems with a numeric time step.
* [#13854](http://bugzilla.scilab.org/show_bug.cgi?id=13854): Under some operating systems, SciNotes did not initialize a new document at startup.
* [#13862](http://bugzilla.scilab.org/show_bug.cgi?id=13862): There was no lazy evaluation of `or` operands in `if` tests.
* [#13864](http://bugzilla.scilab.org/show_bug.cgi?id=13864): `%l_isequal` was useless in Scilab 6.
* [#13866](http://bugzilla.scilab.org/show_bug.cgi?id=13866): There were some issues with FFTW3 library.
* [#13869](http://bugzilla.scilab.org/show_bug.cgi?id=13869): `bench_run` with option `nb_run=10` did not override the NB RUN tags
* [#13872](http://bugzilla.scilab.org/show_bug.cgi?id=13872): Non regression test added for `unique` (the indices returned were wrong)
* [#13873](http://bugzilla.scilab.org/show_bug.cgi?id=13873): `%hm_stdev(H,idim>2)` returned `zeros(H)`
* [#13881](http://bugzilla.scilab.org/show_bug.cgi?id=13881): `datatipRemoveAll` did not work.
* [#13890](http://bugzilla.scilab.org/show_bug.cgi?id=13890): `getd` did not return loaded symbols in previous scope.
* [#13893](http://bugzilla.scilab.org/show_bug.cgi?id=13893): `simp` did not set a rational denominator at `1` when numerator was equal to zero.
* [#13894](http://bugzilla.scilab.org/show_bug.cgi?id=13894): Default working directory of the previous session did not work.
* [#13897](http://bugzilla.scilab.org/show_bug.cgi?id=13897): Concatenating structures with same fields in mismatching orders failed
* [#13899](http://bugzilla.scilab.org/show_bug.cgi?id=13899): Syntax coloring was off in `scinotes`
* [#13903](http://bugzilla.scilab.org/show_bug.cgi?id=13903): `get_function_path` returned a path with a missing file separator.
* [#13907](http://bugzilla.scilab.org/show_bug.cgi?id=13907): Avoids the gray background on the right panel of the palette Browser.
* [#13908](http://bugzilla.scilab.org/show_bug.cgi?id=13908): `part(text, n:$)` was very slow.
* [#13918](http://bugzilla.scilab.org/show_bug.cgi?id=13918): Unmanaged operations on hypermatrix did not call overload functions.
* [#13919](http://bugzilla.scilab.org/show_bug.cgi?id=13919): Scilab parsed `hidden` as a reserved keyword but it is not used.
* [#13920](http://bugzilla.scilab.org/show_bug.cgi?id=13920): `getscilabkeywords` help page should be in the "Scilab keywords" section.
* [#13923](http://bugzilla.scilab.org/show_bug.cgi?id=13923): Changes of `typeof(:)` and `typeof(n:$)` were not documented.
* [#13924](http://bugzilla.scilab.org/show_bug.cgi?id=13924): rationals `r1==r2` and `r1~=r2` might sometimes be wrong.
* [#13925](http://bugzilla.scilab.org/show_bug.cgi?id=13925): SciNotes used the wrong paired bracket highlight style.
* [#13931](http://bugzilla.scilab.org/show_bug.cgi?id=13931): handle `aarch64` processor for some Linux distribution.
* [#13939](http://bugzilla.scilab.org/show_bug.cgi?id=13939): In HTML help pages, itemizedlist `<ul>` were rendered as numbered ones
* [#13941](http://bugzilla.scilab.org/show_bug.cgi?id=13941): Internal timestamps of HDF5 files prevented having a fixed hash for an unvarying set of saved objects.
* [#13942](http://bugzilla.scilab.org/show_bug.cgi?id=13942): the palette browser tree was always resized when expanded/collapsed.
* [#13944](http://bugzilla.scilab.org/show_bug.cgi?id=13944): The menu "Toolboxes" was missing.
* [#13965](http://bugzilla.scilab.org/show_bug.cgi?id=13965): The rendering of histograms with `histplot` was poor
* [#13966](http://bugzilla.scilab.org/show_bug.cgi?id=13966): `twinkle` and `twinkle(n)` were not supported
* [#13971](http://bugzilla.scilab.org/show_bug.cgi?id=13971): A space has been added between Scilab prompt and cursor.
* [#13972](http://bugzilla.scilab.org/show_bug.cgi?id=13972): Wildcard `*` was not managed in `printf` expressions.
* [#13974](http://bugzilla.scilab.org/show_bug.cgi?id=13974): `isoview(xmin, xmax, ymin, ymax)` was unhandy.
* [#13983](http://bugzilla.scilab.org/show_bug.cgi?id=13983): `who_user` returned wrong values.
* [#13986](http://bugzilla.scilab.org/show_bug.cgi?id=13986): `setdefaultlanguage` did not set value correctly in Windows registry.
* [#13990](http://bugzilla.scilab.org/show_bug.cgi?id=13990): `gettext` did not manage the added `_W` macro.
* [#13999](http://bugzilla.scilab.org/show_bug.cgi?id=13999): `editor` was modal. It locked the console using an external editor.
* [#14012](http://bugzilla.scilab.org/show_bug.cgi?id=14012): Function `stripblanks` did not allow to remove only leading spaces of a set of strings, or only trailing one. An option to do so was added.
* [#14020](http://bugzilla.scilab.org/show_bug.cgi?id=14020): Incorrect carriage return ascii code.
* [#14022](http://bugzilla.scilab.org/show_bug.cgi?id=14022): `getscilabkeywords` was KO (+gateway what() added).
* [#14023](http://bugzilla.scilab.org/show_bug.cgi?id=14023): It was not possible to concatenate cells.
* [#14024](http://bugzilla.scilab.org/show_bug.cgi?id=14024): Print of `macrofile` display a debug message instead of macro prototype.
* [#14025](http://bugzilla.scilab.org/show_bug.cgi?id=14025): `head_comments` did not take into account compiled functions.
* [#14028](http://bugzilla.scilab.org/show_bug.cgi?id=14028): force flag of `genlib` did not rebuild bin file.
* [#14030](http://bugzilla.scilab.org/show_bug.cgi?id=14030): Linear algebra demo crashed due to a bad delete in `schur` implementation.
* [#14035](http://bugzilla.scilab.org/show_bug.cgi?id=14035): `ndgrid` did not manage all homogeneous data type (booleans, integers, polynomials, rationals, strings, `[]`)
* [#14036](http://bugzilla.scilab.org/show_bug.cgi?id=14036): `.tag` and `.user_data` properties were not displayed and not documented for light entity.
* [#14038](http://bugzilla.scilab.org/show_bug.cgi?id=14038): Encoded integers were no longer accepted for list extraction.
* [#14040](http://bugzilla.scilab.org/show_bug.cgi?id=14040): graphic property setting fails when using array of handles
* [#14041](http://bugzilla.scilab.org/show_bug.cgi?id=14041): `genlib` crashed when the file is locked by another program.
* [#14043](http://bugzilla.scilab.org/show_bug.cgi?id=14043): Examples of API Scilab help pages had to be updated (`pvApiCtx` in gateway prototypes).
* [#14044](http://bugzilla.scilab.org/show_bug.cgi?id=14044): `MALLOC.h` is now renamed to `sci_malloc.h`.
* [#14047](http://bugzilla.scilab.org/show_bug.cgi?id=14047): wrong behaviour of `break` ( `continue` ) in `if` and outside of loop fixed.
* [#14049](http://bugzilla.scilab.org/show_bug.cgi?id=14049): `genlib` hang if an unexpected `endfunction` occurs.
* [#14055](http://bugzilla.scilab.org/show_bug.cgi?id=14055): overload on matrix concatenation was not called with `[]`.
* [#14057](http://bugzilla.scilab.org/show_bug.cgi?id=14057): `grand(m,n)` returned a wrong error and `grand(m,n,p)` called an overloading function instead of returning an error.
* [#14058](http://bugzilla.scilab.org/show_bug.cgi?id=14058): Scilab crashed with `file("close", file())` instruction
* [#14059](http://bugzilla.scilab.org/show_bug.cgi?id=14059): Lack of performance on deletion of matrix elements.
* [#14065](http://bugzilla.scilab.org/show_bug.cgi?id=14065): Change "java size" in points in graphics font help page.
* [#14067](http://bugzilla.scilab.org/show_bug.cgi?id=14067): 3rd argument of `fsolve` became mandatory
* [#14082](http://bugzilla.scilab.org/show_bug.cgi?id=14082): `m=1; m()=1;` made Scilab crash.
* [#14093](http://bugzilla.scilab.org/show_bug.cgi?id=14093): `atanh` returns NaN for values with an absolute value greater than 1
* [#14095](http://bugzilla.scilab.org/show_bug.cgi?id=14095): Scilab crashed when a .fig file was loaded with `loadmatfile` function.
* [#14096](http://bugzilla.scilab.org/show_bug.cgi?id=14096): Issue with `mscanf`.
* [#14097](http://bugzilla.scilab.org/show_bug.cgi?id=14097): `genlib` no more adds a separator at the end of the lib path if it is not given in the directory path.
* [#14099](http://bugzilla.scilab.org/show_bug.cgi?id=14099): `sci2exp` macro was fixed to avoid "a+[] Warning". string(polynomials|rationals) had badly formated outputs and was not vectorized
* [#14105](http://bugzilla.scilab.org/show_bug.cgi?id=14105): New block comments `/*...*/` feature was not documented.
* [#14107](http://bugzilla.scilab.org/show_bug.cgi?id=14107): `lstcat` of a string and a list did not produce consistent results.
* [#14109](http://bugzilla.scilab.org/show_bug.cgi?id=14109): `lsq` crashed Scilab when Scilab version depended on MKL library.
* [#14111](http://bugzilla.scilab.org/show_bug.cgi?id=14111): In Scilab 6, `lib` loading a Scilab 5 library did not give a proper error message.
* [#14113](http://bugzilla.scilab.org/show_bug.cgi?id=14113): Scilab 6 did not detect infinite loop.
* [#14115](http://bugzilla.scilab.org/show_bug.cgi?id=14115): In Scinotes, the `switch` and `otherwise` keywords were no longer colorized.
* [#14116](http://bugzilla.scilab.org/show_bug.cgi?id=14116): Invalid exponent in case of complex exponents especially `0*%i`.
* [#14118](http://bugzilla.scilab.org/show_bug.cgi?id=14118): `real`, `imag`, `conj`, `isreal` did not accept rationals
* [#14135](http://bugzilla.scilab.org/show_bug.cgi?id=14135): crash when running "Graphics -> Matplot -> Java Image" demonstration.
* [#14141](http://bugzilla.scilab.org/show_bug.cgi?id=14141): `gcf().attribute=value` lead to "Wrong insertion: function or macro are not expected".
* [#14144](http://bugzilla.scilab.org/show_bug.cgi?id=14144): Scilab crashed with `int64(2^63)`.
* [#14149](http://bugzilla.scilab.org/show_bug.cgi?id=14149): HDF5 could not restore hypermatrix with good dimensions.
* [#14150](http://bugzilla.scilab.org/show_bug.cgi?id=14150): The Windows SDK was not found on Windows 8.1.
* [#14156](http://bugzilla.scilab.org/show_bug.cgi?id=14156): `mfscanf` returned an empty matrix when datafile contained a header.
* [#14157](http://bugzilla.scilab.org/show_bug.cgi?id=14157): Insert of big set in sparse was very slow.
* [#14159](http://bugzilla.scilab.org/show_bug.cgi?id=14159): `Matplot` crashed Scilab on boolean input.
* [#14178](http://bugzilla.scilab.org/show_bug.cgi?id=14178): Tcl/Tk unavailability on MacOS is now documented.
* [#14181](http://bugzilla.scilab.org/show_bug.cgi?id=14181): `intg` (or `integrate`) in a function that is being integrated failed.
* [#14187](http://bugzilla.scilab.org/show_bug.cgi?id=14187): `fscanfMat` failed to read format `%d`, `%i` and `%f`.
* [#14199](http://bugzilla.scilab.org/show_bug.cgi?id=14199): `sqrt` returned wrong dimension results on matrix with more than dimensions.
* [#14203](http://bugzilla.scilab.org/show_bug.cgi?id=14203): Improve some error messages, some help pages and some comments.
* [#14204](http://bugzilla.scilab.org/show_bug.cgi?id=14204): `dec2bin` ( `dec2base` ) must show a better error message for too large values.
* [#14205](http://bugzilla.scilab.org/show_bug.cgi?id=14205): Console crash when assigning uint32 numbers to double matrix.
* [#14209](http://bugzilla.scilab.org/show_bug.cgi?id=14209): `1:245` created infinite loop.
* [#14212](http://bugzilla.scilab.org/show_bug.cgi?id=14212): Scilab 6 did not load array of struct from Scilab 5.5 files correctly
* [#14219](http://bugzilla.scilab.org/show_bug.cgi?id=14219): As [bug #14203](http://bugzilla.scilab.org/show_bug.cgi?id=14203), improve some error messages, some help pages and some comments.
* [#14223](http://bugzilla.scilab.org/show_bug.cgi?id=14223): `det` returned an error when it is used with a singular matrix.
* [#14225](http://bugzilla.scilab.org/show_bug.cgi?id=14225): command-line option "-quit" should set the processs exit status
* [#14228](http://bugzilla.scilab.org/show_bug.cgi?id=14228): Setting `.rotation_angles` property to a matrix of any size did not return error message.
* [#14232](http://bugzilla.scilab.org/show_bug.cgi?id=14232): Typos fixed in Xcos.
* [#14245](http://bugzilla.scilab.org/show_bug.cgi?id=14245): Problem in recursive extraction using list with `struct`.
* [#14247](http://bugzilla.scilab.org/show_bug.cgi?id=14247): `sqrt` did not work on hypermatrices (non regression test added).
* [#14249](http://bugzilla.scilab.org/show_bug.cgi?id=14249): `Ctrl-C` can be used to stop writing control expression.
* [#14251](http://bugzilla.scilab.org/show_bug.cgi?id=14251): `spec` leaked some memory.
* [#14253](http://bugzilla.scilab.org/show_bug.cgi?id=14253): Insertion in a struct contained in a list fixed.
* [#14255](http://bugzilla.scilab.org/show_bug.cgi?id=14255): `fftw` without MKL leaked.
* [#14271](http://bugzilla.scilab.org/show_bug.cgi?id=14271): `conjgrad` displayed an incorrect error message about number of arguments.
* [#14297](http://bugzilla.scilab.org/show_bug.cgi?id=14297): `cumsum`'s output was badly documented.
* [#14300](http://bugzilla.scilab.org/show_bug.cgi?id=14300): Crash when playing with structures.
* [#14303](http://bugzilla.scilab.org/show_bug.cgi?id=14303): matrix display for large number was not correctly aligned
* [#14304](http://bugzilla.scilab.org/show_bug.cgi?id=14304): `find(x, nmax)` returned `[]` (non regression test added).
* [#14313](http://bugzilla.scilab.org/show_bug.cgi?id=14313): Parser did not create a column separator after spaces and `...` at the end of lines
* [#14316](http://bugzilla.scilab.org/show_bug.cgi?id=14316): Operation `scalar^matrix` was identical to `scalar.^matrix` instead of being `expm( log(scalar) * matrix )`
* [#14326](http://bugzilla.scilab.org/show_bug.cgi?id=14326): It was no longer possible to delete any part of a structure array with `[]`.
* [#14331](http://bugzilla.scilab.org/show_bug.cgi?id=14331): The third argument of `lsq` crashed Scilab.
* [#14347](http://bugzilla.scilab.org/show_bug.cgi?id=14347): `plot2d` crashed with multiple entries (non regression test added).
* [#14348](http://bugzilla.scilab.org/show_bug.cgi?id=14348): Scilab did not open sce/sci file from Windows explorer.
* [#14359](http://bugzilla.scilab.org/show_bug.cgi?id=14359): Black Hole demo updated. Stop and Clear buttons did not have priority tag set. `Callback_type` property has been added and set to `10`.
* [#14361](http://bugzilla.scilab.org/show_bug.cgi?id=14361): Parser did not manage -linebreak + blockcomment `... /* a comment */`
* [#14362](http://bugzilla.scilab.org/show_bug.cgi?id=14362): The `ode` Lotka demo had typo errors
* [#14366](http://bugzilla.scilab.org/show_bug.cgi?id=14366): `typeof(var,"overload")` was not documented
* [#14374](http://bugzilla.scilab.org/show_bug.cgi?id=14374): The parser did not manage comments properly in shellmode
* [#14375](http://bugzilla.scilab.org/show_bug.cgi?id=14375): Calling `input` with a argument of 64 characters or more crashed Scilab.
* [#14389](http://bugzilla.scilab.org/show_bug.cgi?id=14389): The new `int64` and `uint64` were not documented, and other help pages were not updated for them.
* [#14390](http://bugzilla.scilab.org/show_bug.cgi?id=14390): `double` help page had irrelevant syntaxes and was poor
* [#14396](http://bugzilla.scilab.org/show_bug.cgi?id=14396): Real number display was not proper for very wide decimal parts
* [#14398](http://bugzilla.scilab.org/show_bug.cgi?id=14398): Matrix extraction was mistakenly considered a function call in calling sequence
* [#14405](http://bugzilla.scilab.org/show_bug.cgi?id=14405): GetScilabVariableJNI symbol was not resolved on xcosPalAdd()
* [#14415](http://bugzilla.scilab.org/show_bug.cgi?id=14415): Some spelling errors were detected in ~20 help pages
* [#14416](http://bugzilla.scilab.org/show_bug.cgi?id=14416): The file extension filter in Scinotes "Save as" window did not re-used the active file's extension when applicable.
* [#14418](http://bugzilla.scilab.org/show_bug.cgi?id=14418): `saxon9he.jar` made scilab throw an XPathFactoryConfigurationException.
* [#14419](http://bugzilla.scilab.org/show_bug.cgi?id=14419): Scinotes's highlighting of the new `||` and `&&` operators was wrong.
* [#14423](http://bugzilla.scilab.org/show_bug.cgi?id=14423): `bench_run did` not have a return value, export file was not configurable
* [#14425](http://bugzilla.scilab.org/show_bug.cgi?id=14425): `xpause` was a duplicate of `sleep`. `sleep` did not propose "s" time unit.
* [#14429](http://bugzilla.scilab.org/show_bug.cgi?id=14429): Rationals `r+(-r)` and `r-r` did not simplify the denominator to 1 in `simp_mode(%t)`
* [#14432](http://bugzilla.scilab.org/show_bug.cgi?id=14432): Using an implicit list as scoped assignation to a variable in function call caused scilab to crash
* [#14433](http://bugzilla.scilab.org/show_bug.cgi?id=14433): `acoth` (which call `atanh`) crashed scilab
* [#14434](http://bugzilla.scilab.org/show_bug.cgi?id=14434): `PlotSparse` did not work anymore.
* [#14446](http://bugzilla.scilab.org/show_bug.cgi?id=14446): An error message generated by `save(..)` pointed a bad argument index.
* [#14450](http://bugzilla.scilab.org/show_bug.cgi?id=14450): `builder_help.sce` of a toolbox ignored some existing language directories
* [#14453](http://bugzilla.scilab.org/show_bug.cgi?id=14453): `strcat([])` returned an empty string instead of `[]`.
* [#14455](http://bugzilla.scilab.org/show_bug.cgi?id=14455): `macr2tree` crashed when passing a FieldExp.
* [#14468](http://bugzilla.scilab.org/show_bug.cgi?id=14468): Scinotes was unable to export to HTML.
* [#14471](http://bugzilla.scilab.org/show_bug.cgi?id=14471): `strange([])` returned `[]` instead of `Nan` as all other functions for statistical dispersion
* [#14476](http://bugzilla.scilab.org/show_bug.cgi?id=14476): Operation `.*` between polynomials and imaginary numbers was always returning `0`
* [#14493](http://bugzilla.scilab.org/show_bug.cgi?id=14493): `and` and `or` help pages were poor and inaccurate.
* [#14495](http://bugzilla.scilab.org/show_bug.cgi?id=14495): `consolebox` help page shew wrong syntaxes and was poor.
* [#14499](http://bugzilla.scilab.org/show_bug.cgi?id=14499): `getd` did not update already defined functions
* [#14500](http://bugzilla.scilab.org/show_bug.cgi?id=14500): Operator `.^` was broken for sparse matrices.
* [#14517](http://bugzilla.scilab.org/show_bug.cgi?id=14517): The second argument of part function accepted an index of 0 without exiting in error.
* [#14524](http://bugzilla.scilab.org/show_bug.cgi?id=14524): Numeric locales were not set to standard "C" by default at scilab startup
* [#14540](http://bugzilla.scilab.org/show_bug.cgi?id=14540): Datatips did not clip outside axes bounds
* [#14685](http://bugzilla.scilab.org/show_bug.cgi?id=14685): datavec produced an invalid index error.
* [#14980](http://bugzilla.scilab.org/show_bug.cgi?id=14980): The datatip display of the root locus arcs is broken.
* [#14992](http://bugzilla.scilab.org/show_bug.cgi?id=14992): `readgateway` has been removed, use `whereis` instead.

Bug Fixes
---------

### Bugs fixed in 6.1.0:
* [#2694](http://bugzilla.scilab.org/show_bug.cgi?id=2694): `bitget` did not accept positive integers of types int8, int16 or int32.
* [#8784](http://bugzilla.scilab.org/show_bug.cgi?id=8784): Automatic self-adjusting blocks `SCALE_CSCOPE` & `SCALE_CMSCOPE` in Xcos.
* [#14604](http://bugzilla.scilab.org/show_bug.cgi?id=14604): `emptystr()` is 40x slower with 6.0.0 wrt 5.5.2
* [#14605](http://bugzilla.scilab.org/show_bug.cgi?id=14605): fixed - `bench_run` was too strict about the specification of tests names.
* [#14812](http://bugzilla.scilab.org/show_bug.cgi?id=14812): Minor typos in messages.
* [#14863](http://bugzilla.scilab.org/show_bug.cgi?id=14863): In Xcos, the default ending time was unhandily high (100000), reduced it to 30.
* [#14982](http://bugzilla.scilab.org/show_bug.cgi?id=14982): `msprintf` segmentation fault was caught due to wrong size
* [#15269](http://bugzilla.scilab.org/show_bug.cgi?id=15269): `xgetech` was poor and stiff compared to any combination of `gca()` properties `.axes_bounds`, `.data_bounds`, `.log_flags`, and `.margins`. It is removed.
* [#15271](http://bugzilla.scilab.org/show_bug.cgi?id=15271): `bitget` needed to be upgraded.
* [#15425](http://bugzilla.scilab.org/show_bug.cgi?id=15425): The Kronecker product `a.*.b` failed when `a` or `b` or both are hypermatrices, with one or both being polynomials or rationals.
