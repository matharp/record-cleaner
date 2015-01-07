/*
 * recanalyst.c
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
 */

#include <windows.h>
#include "recanalyst.h"

/* function pointers */

RECANALYST_CREATE_FN			recanalyst_create			= NULL;
RECANALYST_FREE_FN				recanalyst_free				= NULL;
RECANALYST_SETPARAMS_FN			recanalyst_setparams		= NULL;
RECANALYST_RESET_FN				recanalyst_reset			= NULL;
RECANALYST_ANALYZE_FN			recanalyst_analyze			= NULL;
RECANALYST_GETGAMESETTINGS_FN	recanalyst_getgamesettings	= NULL;
RECANALYST_ENUMPLAYERS_FN		recanalyst_enumplayers		= NULL;
RECANALYST_GETPREGAMECHAT_FN	recanalyst_getpregamechat	= NULL;
RECANALYST_GETINGAMECHAT_FN		recanalyst_getingamechat	= NULL;
RECANALYST_GETOBJECTIVES_FN		recanalyst_getobjectives	= NULL;
RECANALYST_ENUMTRIBUTES_FN		recanalyst_enumtributes		= NULL;
RECANALYST_SETCOMMENT_FN		recanalyst_setcomment		= NULL;
RECANALYST_GETCOMMENT_FN		recanalyst_getcomment		= NULL;
RECANALYST_GENERATEMAP_FN		recanalyst_generatemap		= NULL;
RECANALYST_ANALYZETIME_FN		recanalyst_analyzetime		= NULL;
RECANALYST_TIMETOSTRING_FN		recanalyst_timetostring		= NULL;
RECANALYST_ERRMSG_FN			recanalyst_errmsg			= NULL;
RECANALYST_LIBVERSION_FN		recanalyst_libversion		= NULL;

HMODULE recanalystLoadLibrary()
{
    HMODULE hModule;
    BOOL ok = TRUE;

    if (!(hModule = LoadLibrary(RECANALYST_DLL)))
        return NULL;

    ok = ok && (recanalyst_create			= (RECANALYST_CREATE_FN)GetProcAddress(hModule, "recanalyst_create"));
    ok = ok && (recanalyst_free				= (RECANALYST_FREE_FN)GetProcAddress(hModule, "recanalyst_free"));
    ok = ok && (recanalyst_setparams		= (RECANALYST_SETPARAMS_FN)GetProcAddress(hModule, "recanalyst_setparams"));
    ok = ok && (recanalyst_reset			= (RECANALYST_RESET_FN)GetProcAddress(hModule, "recanalyst_reset"));
    ok = ok && (recanalyst_analyze			= (RECANALYST_ANALYZE_FN)GetProcAddress(hModule, "recanalyst_analyze"));
    ok = ok && (recanalyst_getgamesettings	= (RECANALYST_GETGAMESETTINGS_FN)GetProcAddress(hModule, "recanalyst_getgamesettings"));
    ok = ok && (recanalyst_enumplayers		= (RECANALYST_ENUMPLAYERS_FN)GetProcAddress(hModule, "recanalyst_enumplayers"));
    ok = ok && (recanalyst_getpregamechat	= (RECANALYST_GETPREGAMECHAT_FN)GetProcAddress(hModule, "recanalyst_getpregamechat"));
    ok = ok && (recanalyst_getingamechat	= (RECANALYST_GETINGAMECHAT_FN)GetProcAddress(hModule, "recanalyst_getingamechat"));
    ok = ok && (recanalyst_getobjectives	= (RECANALYST_GETOBJECTIVES_FN)GetProcAddress(hModule, "recanalyst_getobjectives"));
    ok = ok && (recanalyst_enumtributes		= (RECANALYST_ENUMTRIBUTES_FN)GetProcAddress(hModule, "recanalyst_enumtributes"));
    ok = ok && (recanalyst_setcomment		= (RECANALYST_SETCOMMENT_FN)GetProcAddress(hModule, "recanalyst_setcomment"));
    ok = ok && (recanalyst_getcomment		= (RECANALYST_GETCOMMENT_FN)GetProcAddress(hModule, "recanalyst_getcomment"));
    ok = ok && (recanalyst_generatemap		= (RECANALYST_GENERATEMAP_FN)GetProcAddress(hModule, "recanalyst_generatemap"));
    ok = ok && (recanalyst_analyzetime		= (RECANALYST_ANALYZETIME_FN)GetProcAddress(hModule, "recanalyst_analyzetime"));
    ok = ok && (recanalyst_timetostring		= (RECANALYST_TIMETOSTRING_FN)GetProcAddress(hModule, "recanalyst_timetostring"));
    ok = ok && (recanalyst_errmsg			= (RECANALYST_ERRMSG_FN)GetProcAddress(hModule, "recanalyst_errmsg"));
    ok = ok && (recanalyst_libversion		= (RECANALYST_LIBVERSION_FN)GetProcAddress(hModule, "recanalyst_libversion"));

    if (!ok) {
        recanalystUnloadLibrary(hModule);
        hModule = NULL;
    }

    return hModule;
}

void recanalystClearPointers(void)
{
    recanalyst_create			= NULL;
    recanalyst_free				= NULL;
    recanalyst_setparams		= NULL;
    recanalyst_reset			= NULL;
    recanalyst_analyze			= NULL;
    recanalyst_getgamesettings	= NULL;
    recanalyst_enumplayers		= NULL;
    recanalyst_getpregamechat	= NULL;
    recanalyst_getingamechat	= NULL;
    recanalyst_getobjectives	= NULL;
    recanalyst_enumtributes		= NULL;
    recanalyst_setcomment		= NULL;
    recanalyst_getcomment		= NULL;
    recanalyst_generatemap		= NULL;
    recanalyst_analyzetime		= NULL;
    recanalyst_timetostring		= NULL;
    recanalyst_errmsg			= NULL;
    recanalyst_libversion		= NULL;
}

void recanalystUnloadLibrary(HMODULE hModule)
{
    if (hModule)
        FreeLibrary(hModule);

    recanalystClearPointers();
}
