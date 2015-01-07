/*
 * recanalyst_demo.c by biegleux modified by Prathamesh
 *
 * Simple program demonstrates the use of recanalyst library.
 *
 * Copyright (c) 2009, biegleux <biegleux@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published
 * by the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, see <http://www.gnu.org/licenses>.
 *
 * You must compile this program against gdi32. Example:
 * 	gcc -orecanalyst recanalyst_demo.c recanalyst.c -lgdi32
 */

#include <stdio.h>
#include <windows.h>
#include <wingdi.h>
#include "recanalyst.h"

BOOL enumPlayers(RECANALYST_PLAYER player, LPARAM lParam)
{
    printf("%lu%lu %s(%0.2s)\n", player.dwTeam, player.dwColorId, player.szName, player.lpCivilization);
    return TRUE;
}

int main(int argc, char **argv)
{
    HMODULE hModule;
    recanalyst* ra;
    RECANALYST_PARAMS params;
    RECANALYST_GAMESETTINGS gs;
    RECANALYST_VICTORY vict;

    int RET_CODE;

    /*
     * to support non-english language you can use following block of code:
     * char *mapstyles[] = { "Standard", "Real World", "Custom" };
     * printf("%s\n", mapstyles[gs.dwMapStyle]);
     */

    if (argc < 2)
    {
        printf("Input file was not specified.\n");
        return EXIT_FAILURE;
    }

    if (!(hModule = recanalystLoadLibrary()))
    {
        printf("Unable to load library.\n");
        return EXIT_FAILURE;
    }

    if ((ra = recanalyst_create()) == NULL)
    {
        printf("Unable to create recanalyst object instance.\n");
        return EXIT_FAILURE;
    }

    params.lpFileName = argv[1];
    params.bShowPositions = FALSE;

    if ((RET_CODE = recanalyst_setparams(ra, &params)) != RECANALYST_OK)
    {
        recanalyst_free(ra);
        printf("%s\n", recanalyst_errmsg(RET_CODE));
        return EXIT_FAILURE;
    }

    if ((RET_CODE = recanalyst_analyze(ra)) != RECANALYST_OK)
    {
        recanalyst_free(ra);
        printf("%s\n", recanalyst_errmsg(RET_CODE));
        return EXIT_FAILURE;
    }

    gs.lpVictory = &vict;

    if ((RET_CODE = recanalyst_getgamesettings(ra, &gs)) != RECANALYST_OK)
    {
        recanalyst_free(ra);
        printf("%s\n", recanalyst_errmsg(RET_CODE));
        return EXIT_FAILURE;
    }

    printf("%s\n", gs.szMap);

    if ((RET_CODE = recanalyst_enumplayers(ra, (EnumPlayersProc)enumPlayers, 0)) != RECANALYST_OK)
    {
        recanalyst_free(ra);
        printf("%s\n", recanalyst_errmsg(RET_CODE));
        return EXIT_FAILURE;
    }

    recanalyst_free(ra);

    return EXIT_SUCCESS;
}
