#ifndef GLOBUS_DONT_DOCUMENT_INTERNAL
/**
 * @file globus_gsi_system_config_error.c
 * Globus GSI System Config Library
 * @author Sam Lang, Sam Meder
 *
 * $RCSfile$
 * $Revision$
 * $Date$
 */
#endif

#include "globus_error_openssl.h"
#include "globus_i_gsi_system_config.h"
#include "globus_gsi_system_config_constants.h"

#ifndef GLOBUS_DONT_DOCUMENT_INTERNAL

static char * 
globus_l_gsi_sysconfig_error_strings[GLOBUS_GSI_SYSCONFIG_ERROR_LAST] =
{

/* 0 */   "Success",
};

/* ERROR FUNCTIONS */

globus_result_t
globus_i_gsi_sysconfig_openssl_error_result(
    int                                 error_type,
    const char *                        filename,
    const char *                        function_name,
    int                                 line_number,
    const char *                        long_desc)
{
    globus_object_t *                   error_object;
    globus_result_t                     result;

    static char *                       _function_name_ =
        "globus_i_gsi_sysconfig_openssl_error_result";
    
    GLOBUS_I_GSI_SYSCONFIG_DEBUG_ENTER;

    error_object = 
        globus_error_wrap_openssl_error(
            GLOBUS_GSI_SYSCONFIG_MODULE,
            error_type,
            "%s:%d: %s: %s",
            filename,
            line_number,
            function_name,
            globus_l_gsi_sysconfig_error_strings[error_type]);    

    globus_error_set_long_desc(error_object, long_desc);

    result = globus_error_put(error_object);
    
    GLOBUS_I_GSI_SYSCONFIG_DEBUG_EXIT;

    return result;
}

globus_result_t
globus_i_gsi_sysconfig_error_result(
    int                                 error_type,
    const char *                        filename,
    const char *                        function_name,
    int                                 line_number,
    const char *                        long_desc)
{
    globus_object_t *                   error_object;
    globus_result_t                     result;

    static char *                       _function_name_ =
        "globus_i_gsi_sysconfig_error_result";

    GLOBUS_I_GSI_SYSCONFIG_DEBUG_ENTER;

    error_object = globus_error_construct_error(
        GLOBUS_GSI_SYSCONFIG_MODULE,
        NULL,
        error_type,
        "%s:%d: %s: %s",
        filename, line_number, function_name, 
        globus_l_gsi_sysconfig_error_strings[error_type]);

    globus_error_set_long_desc(error_object, long_desc);

    result = globus_error_put(error_object);

    GLOBUS_I_GSI_SYSCONFIG_DEBUG_EXIT;

    return result;
}

globus_result_t
globus_i_gsi_sysconfig_error_chain_result(
    globus_result_t                     chain_result,
    int                                 error_type,
    const char *                        filename,
    const char *                        function_name,
    int                                 line_number,
    const char *                        long_desc)
{
    globus_object_t *                   error_object;
    globus_result_t                     result;

    static char *                       _function_name_ =
        "globus_i_gsi_sysconfig_error_chain_result";
    
    GLOBUS_I_GSI_SYSCONFIG_DEBUG_ENTER;
    
    error_object =
        globus_error_construct_error(
            GLOBUS_GSI_SYSCONFIG_MODULE,
            globus_error_get(chain_result),
            error_type,
            "%s:%d: %s: %s",
            filename, line_number, function_name, 
            globus_l_gsi_sysconfig_error_strings[error_type]);

    globus_error_set_long_desc(error_object, long_desc);

    result = globus_error_put(error_object);

    GLOBUS_I_GSI_SYSCONFIG_DEBUG_EXIT;

    return result;
}

#endif /* GLOBUS_DONT_DOCUMENT_INTERNAL */
