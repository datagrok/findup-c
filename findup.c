/* findup: locate a given file in the nearest ancestor directory
 *
 * Copyright (C) 2017 Michael F. Lamb <http://datagrok.org>
 * 
 * This program is free software: you can redistribute it and/or modify it
 * under the terms of the GNU Affero General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License
 * for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program. If not, see http://www.gnu.org/licenses/.
 *
 * */

#define version "0.1"

#include <fcntl.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

void usage() {
    fputs("Usage: findup [OPTION]... FILENAME\n", stdout);
    fputs("find the nearest ancestor directory containing FILENAME\n", stdout);
    fputs("\
    -h              display this help and exit\n\
    -V              display version and license information\n\
    -C DIRECTORY    begin search in DIRECTORY (default: current directory)\n\
    -q              suppress all normal output\n\
    -a              print paths to FILENAME found in all ancestor directories\n\
    -x              skip directories on different file systems than default\n\
\n\
Exit status is 0 if FILENAME is found, 1 if not, 2 upon error.\n", stdout);
}

void license() {
    printf("findup %s\n", version);
    fputs("Copyright (C) 2017  Michael F. Lamb\n\
License: AGPLv3+ (GNU AGPL version 3 or later) <http://gnu.org/licenses/agpl.html>.\n\
Web: https://github.com/datagrok/findup\n\
\n\
This is free software, distributed under the terms of the GNU Affero General\n\
Public License, version 3, or (at your option) any later version. You are\n\
entitled to a copy of its complete and corresponding source source code, and\n\
you may modify and share it under certain conditions.\n\
\n\
There is no warranty.\n\
\n\
See the source code or license text for details.\n\\n\
\n\
", stdout);
}


int findup(char *dir, char *filename, int quiet, int all, int onefs) {
    int dirlen, i;
    struct stat sb, root_sb;
    if (stat("/", &root_sb) != 0) {
       fputs("can't stat root!\n", stdout);
       return 2;
    }
    dirlen = strlen(dir);

    for (i=0; i<9; i++) {
        strncpy(&dir[dirlen], filename, PATH_MAX - dirlen);
        printf("checking %s\n", dir);
        if (stat(dir, &sb) == 0) {
            printf("found: %s\n", dir);
            return 0;
        }
        strncpy(&dir[dirlen], "../", 4);
        dirlen += 3;
    }
    
    return 0;
}


int main(int argc, char **argv) {
    int optc;
    int quiet, all, onefs = 0;
    int dirfd = AT_FDCWD;
    char dir[PATH_MAX] = "";

    while ((optc = getopt(argc, argv, "hVC:qax")) != -1) {
        switch (optc) {
            case 'h': usage();      return EXIT_SUCCESS;
            case 'V': license();    return EXIT_SUCCESS;
            case 'C': 
                strncpy(dir, optarg, PATH_MAX);
                break;
            case 'q': quiet = 1;    break;
            case 'a': all = 1;      break;
            case 'x': onefs = 1;    break;
            default:  usage();      return 2;
        }
    }
    if (optind >= argc) {
        fputs("No FILENAME was specified.\n", stderr);
        usage();
        return EXIT_FAILURE;
    }
    return findup(dir, argv[optind], quiet, all, onefs);
}
