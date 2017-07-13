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

#ifndef PJMSRP_CONFIG_H_
#define PJMSRP_CONFIG_H_

#ifdef __SYMBIAN32__
#undef _WIN32 /* Because of WINSCW */
#endif

// Windows (XP/Vista/7/CE and Windows Mobile) macro definition.
#if defined(WIN32)|| defined(_WIN32) || defined(_WIN32_WCE)
#	define PJMSRP_UNDER_WINDOWS	1
#	if defined(WINAPI_FAMILY) && (WINAPI_FAMILY == WINAPI_FAMILY_PHONE_APP || WINAPI_FAMILY == WINAPI_FAMILY_APP)
#		define PJMSRP_UNDER_WINDOWS_RT		1
#	endif
#endif

/* Used on Windows and Symbian systems to export/import public functions and global variables.
*/
#if !defined(__GNUC__) && defined(PJMSRP_EXPORTS)
# 	define PJMSRP_API		__declspec(dllexport)
#	define PJMSRP_GEXTERN	extern __declspec(dllexport)
#elif !defined(__GNUC__) && !defined(PJMSRP_IMPORTS_IGNORE)
# 	define PJMSRP_API		__declspec(dllimport)
#	define PJMSRP_GEXTERN	__declspec(dllimport)
#else
#	define PJMSRP_API
#	define PJMSRP_GEXTERN	extern
#endif

/* Guards against C++ name mangling
*/
#ifdef __cplusplus
#	define PJMSRP_BEGIN_DECLS extern "C" {
#	define PJMSRP_END_DECLS }
#else
#	define PJMSRP_BEGIN_DECLS
#	define PJMSRP_END_DECLS
#endif

/* Disable some well-known warnings
*/
#ifdef _MSC_VER
#	define _CRT_SECURE_NO_WARNINGS
#	pragma warning( disable : 4996 )
#endif

#include <stdint.h>
#include <stddef.h>


#if HAVE_CONFIG_H
#include <config.h>
#endif

//include header file of pjlib
#include <pjlib.h>
#include <inttypes.h>
/**
 * Specify maximum URL size.
 */
#ifndef PJSIP_MAX_URL_SIZE
#   define PJSIP_MAX_URL_SIZE		256
#endif

/**
 * Specify maximum URL size.
 */
#ifndef PJMSRP_MAX_STRING_SIZE
#   define PJMSRP_MAX_STRING_SIZE	10000//1M
#endif


#endif /* PJMSRP_CONFIG_H_ */
