/*
    Copyright (C) 2012 Modelon AB

    This program is free software: you can redistribute it and/or modify
    it under the terms of the BSD style license.

     This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    FMILIB_License.txt file for more details.

    You should have received a copy of the FMILIB_License.txt file
    along with this program. If not, contact Modelon AB <http://www.modelon.com>.
*/

#include <string.h>
#include "JM/jm_callbacks.h"
#include "JM/jm_named_ptr.h"

jm_named_ptr jm_named_alloc(const char* name, size_t size, size_t nameoffset, jm_callbacks* c) {
    jm_named_ptr out;
    size_t namelen = strlen(name);
    size_t sizefull = size + namelen;
    out.ptr = c->malloc(sizefull);
	out.name = 0;
    if(out.ptr) {
        char* outname;
        outname = out.ptr;
        outname += nameoffset;
        if(namelen)
            memcpy(outname, name, namelen);
        outname[namelen] = 0;
        out.name = outname;
    }
    return out;
}

/*
 * Returns a named_ptr where the content of the pointer has been allocated.
 * Calling function needs to verify that the allocated pointer
 * is not NULL.
 * 
 * size: how much to allocate (just like for malloc)
 * nameoffset: write the name at offset from the start of the requested 'size' (TODO: I have no idea why this has to be done here instead; caller can just do it after <named_ptr> has been returned?)
 */
jm_named_ptr jm_named_alloc_v(jm_vector(char)* name, size_t size, size_t nameoffset, jm_callbacks* c) {
    jm_named_ptr out;
    size_t namelen = jm_vector_get_size(char)(name);
    size_t sizefull = size + namelen;
    out.ptr = c->malloc(sizefull); /* Optimization: malloc once instead of twice */
	out.name = 0;
    if (out.ptr) {
        char* outname = out.ptr;
        outname += nameoffset;
        if (namelen) {
            memcpy(outname, jm_vector_get_itemp(char)(name, 0), namelen);
        }
        outname[namelen] = 0;
        out.name = outname;
    }
    return out; /* this is the same as out.ptr */
}

#define JM_TEMPLATE_INSTANCE_TYPE jm_named_ptr
#include "JM/jm_vector_template.h"
