#!/bin/sh

#
# findup: locate a given filename in the nearest ancestor directory. 
#
# Copyright 2017 Michael F. Lamb <http://datagrok.org>
#
# This program is free software: you can redistribute it and/or modify it under
# the terms of the GNU Affero General Public License as published by the Free
# Software Foundation, either version 3 of the License, or (at your option) any
# later version.
#
# License: AGPLv3+ http://www.gnu.org/licenses/agpl.html
#

usage(){ cat <<- USAGE >&2
	Usage: $0 [-C DIRECTORY] FILENAME

	Look for FILENAME in the current or given DIRECTORY and all of its
	ancestors until found. Return the full path of the closest match on
	standard output.

	Example:

	    Run 'make' from deep within your source heiarchy, like 'ant -find':
	        make -f \`findup Makefile\`
	USAGE
}

if [ "$1" = "-C" ]; then
	cwd="$2"
	shift 2
else
	cwd="$(pwd)"
fi
cwd="$(readlink -f "$cwd")"

target="$1"

if [ ! "$1" ]; then
	usage
	exit 1
fi

while [ "$cwd" ]; do
	if [ -e "$cwd/$target" ]; then
		[ "$cwd" = "/" ] && readlink -f "/$1" || readlink -f "$cwd/$1"
		exit 0
	fi
	cwd="${cwd%/*}"
done
 
exit 1
