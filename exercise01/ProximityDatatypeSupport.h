/*
WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

This file was generated from ProximityDatatype.idl using "rtiddsgen".
The rtiddsgen tool is part of the RTI Data Distribution Service distribution.
For more information, type 'rtiddsgen -help' at a command shell
or consult the RTI Data Distribution Service manual.
*/

#ifndef ProximityDatatypeSupport_1543506597_h
#define ProximityDatatypeSupport_1543506597_h

/* Uses */
#include "ProximityDatatype.h"
/* Requires */
#include "ProximityDatatypePlugin.h"

/* ========================================================================== */
/**
Uses:     T
Defines:  TTypeSupport, TDataWriter, TDataReader*/

#if (defined(RTI_WIN32) || defined(RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols. */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

#ifdef __cplusplus
extern "C" {
    #endif

    DDS_TYPESUPPORT_C(ProximityTypeTypeSupport, ProximityType);
    DDS_DATAWRITER_C(ProximityTypeDataWriter, ProximityType);

    DDS_DATAREADER_C(ProximityTypeDataReader, ProximityTypeSeq, ProximityType);

    #ifdef __cplusplus
} /* extern "C" */
#endif

#if (defined(RTI_WIN32) || defined(RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols. */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif

#endif  /* ProximityDatatypeSupport_1543506597_h */

