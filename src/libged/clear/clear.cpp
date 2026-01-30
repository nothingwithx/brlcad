/*                       C L E A R . C P P
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
/** @file libged/clear.cpp
 *
 * The clear command.
 *
 */

#include "common.h"

#include "../ged_private.h"

// clear is a no-op at the libged level - it's purpose is to support ged_exec
// callback hooks that call any application callback functions assigned to this
// command.
extern "C" int
ged_clear_core(struct ged *UNUSED(gedp), int UNUSED(argc), const char **UNUSED(argv))
{
    return BRLCAD_OK;
}

#include "../include/plugin.h"

struct ged_cmd_impl clear_impl = {"clear", ged_clear_core, GED_CMD_DEFAULT};
REGISTER_GED_COMMAND(clear);

#ifdef GED_PLUGIN
extern "C" {
    static bu_plugin_cmd pcommands[] = {
	{ "clear",          ged_clear_core }
    };
    static bu_plugin_manifest pinfo = {
	"libged_clear",
	1,
	(unsigned int)(sizeof(pcommands)/sizeof(pcommands[0])),
	pcommands,
	BU_PLUGIN_ABI_VERSION,
	sizeof(bu_plugin_manifest)
    };
    BU_PLUGIN_DECLARE_MANIFEST(pinfo)
}
#endif /* GED_PLUGIN */

// Local Variables:
// tab-width: 8
// mode: C++
// c-basic-offset: 4
// indent-tabs-mode: t
// c-file-style: "stroustrup"
// End:
// ex: shiftwidth=4 tabstop=8

