

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.01.0622 */
/* at Mon Jan 18 20:14:07 2038
 */
/* Compiler settings for TypeLib.idl:
    Oicf, W1, Zp8, env=Win64 (32b run), target_arch=AMD64 8.01.0622 
    protocol : all , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */



/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 500
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif /* __RPCNDR_H_VERSION__ */


#ifndef __TypeLib_h_h__
#define __TypeLib_h_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __Plugin_FWD_DEFINED__
#define __Plugin_FWD_DEFINED__

#ifdef __cplusplus
typedef class Plugin Plugin;
#else
typedef struct Plugin Plugin;
#endif /* __cplusplus */

#endif 	/* __Plugin_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 



#ifndef __WebrelayControlPluginLib_LIBRARY_DEFINED__
#define __WebrelayControlPluginLib_LIBRARY_DEFINED__

/* library WebrelayControlPluginLib */
/* [version][uuid] */ 


EXTERN_C const IID LIBID_WebrelayControlPluginLib;

EXTERN_C const CLSID CLSID_Plugin;

#ifdef __cplusplus

class DECLSPEC_UUID("44283476-bcb3-4bee-9037-bb88ebde5734")
Plugin;
#endif
#endif /* __WebrelayControlPluginLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


