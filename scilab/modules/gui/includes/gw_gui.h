/*
 * Scilab (http://www.scilab.org/ ) - This file is part of Scilab
 * Copyright (C) 2006 - INRIA - Allan CORNET
 * Copyright (C) 2008 - INRIA - Vincent COUVERT
 * Copyright (C) 2012 - 2016 - Scilab Enterprises
 * Copyright (C) 2017 - Dirk Reusch, Kybernetik Dr. Reusch
 *
 * This file is hereby licensed under the terms of the GNU GPL v2.0,
 * pursuant to article 5.3.4 of the CeCILL v.2.1.
 * This file was originally licensed under the terms of the CeCILL v2.1,
 * and continues to be available under such terms.
 * For more information, see the COPYING file which you should have received
 * along with this program.
 *
 */

#ifndef __GW_GUI__
#define __GW_GUI__

int sci_x_dialog(char* fname, void* pvApiCtx);
int sci_x_choose(char* fname, void* pvApiCtx);
int sci_x_mdialog(char* fname, void* pvApiCtx);
int sci_xchoicesi(char* fname, void* pvApiCtx);
int sci_delmenu(char* fname, void* pvApiCtx);
int sci_setmenu(char* fname, void* pvApiCtx);
int sci_unsetmenu(char* fname, void* pvApiCtx);
int sci_uigetdir(char* fname, void* pvApiCtx);
int sci_getlookandfeel(char* fname, void* pvApiCtx);
int sci_getinstalledlookandfeels(char* fname, void* pvApiCtx);
int sci_setlookandfeel(char* fname, void* pvApiCtx);
int sci_ClipBoard(char* fname, void* pvApiCtx);
int sci_toolbar(char* fname, void* pvApiCtx);
int sci_uicontrol(char* fname, void *pvApiCtx);
int sci_uimenu(char* fname, void *pvApiCtx);
int sci_x_choose_modeless(char* fname, void* pvApiCtx);
int sci_messagebox(char* fname, void* pvApiCtx);
int sci_waitbar(char* fname, void* pvApiCtx);
int sci_progressionbar(char* fname, void* pvApiCtx);
int sci_uigetfont(char* fname, void* pvApiCtx);
int sci_uigetcolor(char* fname, void* pvApiCtx);
int sci_getcallbackobject(char* fname, void* pvApiCtx);
int sci_uicontextmenu(char* fname, void* pvApiCtx);
int sci_uiwait(char* fname, void* pvApiCtx);
int sci_printfigure(char* fname, void* pvApiCtx);
int sci_exportUI(char* fname, void* pvApiCtx);
int sci_printsetupbox(char* fname, void* pvApiCtx);
int sci_toprint(char* fname, void* pvApiCtx);
int sci_uigetfile(char* fname, void* pvApiCtx);
int sci_usecanvas(char* fname, void* pvApiCtx);
int sci_uiputfile(char* fname, void* pvApiCtx);
int sci_raise_window (char* fname, void* pvApiCtx);

int sci_useeditor(char *fname, void* pvApiCtx);
int sci_openged(char *fname, void* pvApiCtx);
int sci_datatipcreate(char *fname, void* pvApiCtx);
int sci_datatipremove(char *fname, void* pvApiCtx);
int sci_plotbrowser(char *fname, void* pvApiCtx);
int sci_datatip_manager_mode(char *fname, void* pvApiCtx);
int sci_datatip_toggle(char *fname, void* pvApiCtx);
int sci_datatipmove(char *fname, void* pvApiCtx);
int sci_datatip_set_style(char *fname, void* pvApiCtx);
int sci_datatip_set_display(char *fname, void* pvApiCtx);
int sci_datatip_set_interp(char *fname, void* pvApiCtx);
int sci_datatip_set_orient(char *fname, void* pvApiCtx);

// Scilab 6
int sci_about(char* fname, void* pvApiCtx);
int sci_mpopup(char* fname, void* pvApiCtx);
int sci_fire_closing_finished (char* fname, void* pvApiCtx);

int sci_figure(char *fname, void* pvApiCtx);
int sci_saveGui(char *fname, void* pvApiCtx);
int sci_loadGui(char *fname, void* pvApiCtx);

#endif /*  __GW_GUI__ */
