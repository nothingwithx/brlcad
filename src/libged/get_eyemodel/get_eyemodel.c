/*                         G E T _ E Y E M O D E L . C
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
/** @file libged/get_eyemodel.c
 *
 * The get_eyemodel command.
 *
 */

#include "common.h"


#include "../ged_private.h"


/*
 * Returns the views eyemodel
 *
 * Usage:
 * get_eyemodel
 *
 */
int
ged_get_eyemodel_core(struct ged *gedp, int argc, const char *argv[])
{
    quat_t quat;
    vect_t eye_model;

    GED_CHECK_DRAWABLE(gedp, BRLCAD_ERROR);
    GED_CHECK_VIEW(gedp, BRLCAD_ERROR);
    GED_CHECK_ARGC_GT_0(gedp, argc, BRLCAD_ERROR);

    /* initialize result */
    bu_vls_trunc(gedp->ged_result_str, 0);

    if (argc != 1) {
	bu_vls_printf(gedp->ged_result_str, "Usage: %s", argv[0]);
	return BRLCAD_ERROR;
    }

    _ged_rt_set_eye_model(gedp, eye_model);
    quat_mat2quat(quat, gedp->ged_gvp->gv_rotation);

    bu_vls_printf(gedp->ged_result_str, "viewsize %.15e;\n", gedp->ged_gvp->gv_size);
    bu_vls_printf(gedp->ged_result_str, "orientation %.15e %.15e %.15e %.15e;\n",
		  V4ARGS(quat));
    bu_vls_printf(gedp->ged_result_str, "eye_pt %.15e %.15e %.15e;\n",
		  eye_model[X], eye_model[Y], eye_model[Z]);

    return BRLCAD_OK;
}

#include "../include/plugin.h"

struct ged_cmd_impl get_eyemodel_impl = {"get_eyemodel", ged_get_eyemodel_core, GED_CMD_DEFAULT};
REGISTER_GED_COMMAND(get_eyemodel);

#ifdef GED_PLUGIN
static bu_plugin_cmd pcommands[] = {
    { "get_eyemodel",            ged_get_eyemodel_core }
};
static bu_plugin_manifest pinfo = {
    "libged_get_eyemodel",
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
