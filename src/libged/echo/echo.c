/*                         E C H O . C
 * BRL-CAD
 *
 * Copyright (c) 2008-2025 United States Government as represented by
 * the U.S. Army Research Laboratory.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public License
 * version 2.1 as published by the Free Software Foundation.
 *
 * This library is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this file; see the file named COPYING for more
 * information.
 */
/** @file libged/echo.c
 *
 * The echo command.
 *
 */

#include "common.h"

#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "../ged_private.h"


int
ged_echo_core(struct ged *gedp, int argc, const char *argv[])
{
    int i;

    GED_CHECK_ARGC_GT_0(gedp, argc, BRLCAD_ERROR);

    /* initialize result */
    bu_vls_trunc(gedp->ged_result_str, 0);

    for (i = 1; i < argc; i++) {
	bu_vls_printf(gedp->ged_result_str, "%s%s", i == 1 ? "" : " ", argv[i]);
    }

    bu_vls_printf(gedp->ged_result_str, "\n");

    return BRLCAD_OK;
}


#include "../include/plugin.h"

#ifdef GED_PLUGIN
static bu_plugin_cmd pcommands[] = {
    { "echo",            ged_echo_core }
};
static bu_plugin_manifest pinfo = {
    "libged_echo",
    1,
    (unsigned int)(sizeof(pcommands)/sizeof(pcommands[0])),
    pcommands,
    BU_PLUGIN_ABI_VERSION,
    sizeof(bu_plugin_manifest)
};
BU_PLUGIN_DECLARE_MANIFEST(pinfo)
#endif /* GED_PLUGIN */

/*
 * Local Variables:
 * mode: C
 * tab-width: 8
 * indent-tabs-mode: t
 * c-file-style: "stroustrup"
 * End:
 * ex: shiftwidth=4 tabstop=8
 */
