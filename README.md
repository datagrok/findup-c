# findup-c

_An implementation of [findup](https://github.com/datagrok/findup-sh) in C, based on GnuLib.
My hope is to offer the finished program for inclusion into [GNU Core Utilities](https://www.gnu.org/software/coreutils/).
This is currently incomplete;
it mostly-works but I'm still learning how to use the GNU toolchain and GnuLib properly._

**findup** ("find up") locates a given filename in the nearest ancestor directory.

```
Usage: findup [-C DIRECTORY] FILENAME

Look for FILENAME in the current or given DIRECTORY and all of its
ancestors until found. Return the full path of the closest match on
standard output.
```

## Compiling from source

You'll need the GNU toolchain, including `autoreconf`.

This program is built with the GNU Portability Library, [Gnulib](https://www.gnu.org/software/gnulib/). On Debian systems, you can get it with `apt-get install gnulib`. You could instead just clone gnulib somewhere with `git clone git://git.savannah.gnu.org/gnulib.git`; the only change to the script below will be that you will have to provide the full path to your clone's copy of `gnulib-tool`.

    git clone git@github.com:datagrok/findup.git
    cd findup
    gnulib-tool --add-import
    autoreconf -i
    # Now, the standard compile + install step
    ./configure && make && make install

## License: AGPL-3.0+

All of the code herein is copyright 2017 [Michael F. Lamb](http://datagrok.org) and released under the terms of the [GNU Affero General Public License, version 3][AGPL-3.0+] (or, at your option, any later version.)

[AGPL-3.0+]: http://www.gnu.org/licenses/agpl.html
