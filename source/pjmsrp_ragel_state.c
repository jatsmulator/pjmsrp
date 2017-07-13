/*
* Copyright (C) 2016 John Li.
*
* Contact: John Li <jatsmulator(at)gmail.com>
*
* PJRCS is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation; either version 2 of the License, or
* (at your option) any later version.
*
* PJRCS is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with PJRCS; if not, write to the Free Software
* Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

#include "pjmsrp/pjmsrp_ragel_state.h"

PJ_DECL(void) pjmsrp_ragel_state_init(pjmsrp_ragel_state_t *state, const pj_char_t *data, pj_size_t size){
    state->cs = 0;
    state->tag_start = state->p = data;
    state->eoh = state->eof = state->tag_end = state->pe = state->p + size;
}
