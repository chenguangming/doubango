/*
* Copyright (C) 2009 Mamadou Diop.
*
* Contact: Mamadou Diop <diopmamadou@yahoo.fr>
*	
* This file is part of Open Source Doubango Framework.
*
* DOUBANGO is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*	
* DOUBANGO is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*	
* You should have received a copy of the GNU General Public License
* along with DOUBANGO.
*
*/

/**@file tsdp_header_M.h
 * @brief SDP "m=" header (Media Descriptions).
 *
 * @author Mamadou Diop <diopmamadou(at)yahoo.fr>
 *
 * @date Created: Iat Nov 8 16:54:58 2009 mdiop
 */
#ifndef _TSDP_HEADER_M_H_
#define _TSDP_HEADER_M_H_

#include "tinySDP_config.h"
#include "tinySDP/headers/tsdp_header.h"

#include "tinySDP/headers/tsdp_header_A.h"
#include "tinySDP/headers/tsdp_header_B.h"
#include "tinySDP/headers/tsdp_header_C.h"
#include "tinySDP/headers/tsdp_header_I.h"
#include "tinySDP/headers/tsdp_header_K.h"

#include "tsk_string.h"

TSDP_BEGIN_DECLS

/**@def TSDP_HEADER_M_CREATE
* Creates new sdp M header.  You must call @ref TSK_OBJECT_SAFE_FREE to free the header.
* @sa TSK_OBJECT_SAFE_FREE.
*/
#define TSDP_HEADER_M_VA_ARGS(media, port, proto)		tsdp_header_M_def_t, (const char*)media, (uint32_t)port, (const char*)proto
#define TSDP_HEADER_M_CREATE(media, port, proto)			tsk_object_new(TSDP_HEADER_M_VA_ARGS(media, port, proto))
#define TSDP_HEADER_M_CREATE_NULL()			TSDP_HEADER_M_CREATE(TSDP_NULL, TSDP_NULL, TSDP_NULL)

////////////////////////////////////////////////////////////////////////////////////////////////////
/// @struct	
///
/// @brief	SDP "m=" header (Media Descriptions).
///
/// @par ABNF :  m=*(media-field
/// information-field
/// *connection-field
/// bandwidth-fields
/// key-field
/// attribute-fields)
///
/// media-field	=  	%x6d "=" media SP port ["/" integer] SP proto 1*(SP fmt) CRLF 
/// media	=  	token 
/// port	=  	1*DIGIT
/// proto	=  	token *("/" token) 
/// fmt	=  	token 
/// 	
////////////////////////////////////////////////////////////////////////////////////////////////////
typedef struct tsdp_header_M_s
{	
	TSDP_DECLARE_HEADER;
	
	char* media;
	uint32_t port;
	uint32_t nports; /**< <number of ports> */
	char* proto;
	tsk_strings_L_t* FMTs;
	
	// Fields below will be set by the message parser.
	tsdp_header_I_t* I;
	tsdp_header_C_t* C;
	tsdp_headers_B_L_t* Bandwidths; // (zero or more bandwidth information lines)
	tsdp_header_K_t* K; // (encryption key)
	tsdp_headers_A_L_t* Attributes; // (zero or more media attribute lines)
}
tsdp_header_M_t;

typedef tsk_list_t tsdp_headers_M_L_t;

tsdp_header_M_t *tsdp_header_M_parse(const char *data, size_t size);

TINYSDP_GEXTERN const void *tsdp_header_M_def_t;

TSDP_END_DECLS

#endif /* _TSDP_HEADER_M_H_ */
