#ifndef GLOBUS_INCLUDE_GLOBUS_GSI_PROXY_H
#define GLOBUS_INCLUDE_GLOBUS_GSI_PROXY_H

/**
 * @anchor globus_gsi_proxy_api   
 * @mainpage Globus GSI Proxy API
 *
 * The globus_gsi_proxy library is motivated by the desire to provide
 * a abstraction layer for the proxy creation and delegation
 * process. For background on this process please refer to the proxy
 * certificate profile draft.
 *
 * Any program that uses Globus GSI Proxy functions must include
 * "globus_gsi_proxy.h". 
 *
 * We envision the API to be used in the following manner:
 *
 * Delegator:                           Delegatee:
 *                                      set desired cert info
 *                                      extension by usinf the handle
 *                                      set functions.
 *                                      globus_gsi_proxy_create_req
 * globus_gsi_proxy_inquire_req
 * modify cert info extension by using
 * handle set/get/clear functions.
 * globus_gsi_proxy_sign_req
 *                                      globus_gsi_proxy_assemble_cred
 *
 * @htmlonly
 * <a href="main.html" target="_top">View documentation without frames</a><br>
 * <a href="index.html" target="_top">View documentation with frames</a><br>
 * @endhtmlonly
 */


#ifndef EXTERN_C_BEGIN
#    ifdef __cplusplus
#        define EXTERN_C_BEGIN extern "C" {
#        define EXTERN_C_END }
#    else
#        define EXTERN_C_BEGIN
#        define EXTERN_C_END
#    endif
#endif

EXTERN_C_BEGIN

#ifndef GLOBUS_DONT_DOCUMENT_INTERNAL
#include "globus_gsi_credential.h"
#endif


/**
 * @defgroup globus_gsi_proxy_activation Activation
 *
 * Globus GSI Proxy uses standard Globus module activation and
 * deactivation. Before any Globus GSI Proxy functions are called, the
 * following function must be called:
 *
 * @code
 *      globus_module_activate(GLOBUS_GSI_PROXY_MODULE)
 * @endcode
 *
 *
 * This function returns GLOBUS_SUCCESS if Globus GSI Proxy was
 * successfully initialized, and you are therefore allowed to
 * subsequently call Globus GSI Proxy functions.  Otherwise, an error
 * code is returned, and Globus GSI Proxy functions should not be
 * subsequently called. This function may be called multiple times.
 *
 * To deactivate Globus GSI Proxy, the following function must be called:
 *
 * @code
 *    globus_module_deactivate(GLOBUS_GSI_PROXY_MODULE)
 * @endcode
 *
 * This function should be called once for each time Globus GSI Proxy
 * was activated. 
 *
 */

/** Module descriptor
 * @ingroup globus_gsi_proxy_activation
 * @hideinitializer
 */
#define GLOBUS_GSI_PROXY_MODULE (&globus_i_gsi_proxy_module)

extern
globus_module_descriptor_t		globus_i_gsi_proxy_module;


/**
 * GSI Proxy Handle.
 * @ingroup globus_gsi_proxy_handle
 *
 * An GSI Proxy handle is used to associate state with a group of
 * operations. Handles can have
 * @ref globus_gsi_proxy_handleattr_t "attributes"
 * associated with them. All proxy @link
 * globus_gsi_proxy_operations operations @endlink take a handle pointer
 * as a parameter.
 *
 * @see globus_gsi_proxy_handle_init(),
 * globus_gsi_proxy_handle_destroy(), globus_gsi_proxy_handle_attrs_t
 */

typedef struct globus_l_gsi_proxy_handle_s * globus_gsi_proxy_handle_t

/**
 * Handle Attributes.
 * @ingroup globus_gsi_proxy_handle_attrs
 *
 * Handle attributes are currently not used, but are provided for
 * extensibility.
 *
 * @see globus_gsi_proxy_handle_t, @ref globus_gsi_proxy_handle_attrs
 */

typedef struct globus_l_gsi_proxy_handle_attrs_s * globus_gsi_proxy_handle_attrs_t

/**
 * @defgroup globus_gsi_proxy_handle Handle Management
 *
 * Create/Destroy/Modify a GSI Proxy Handle.
 *
 * Within the Globus GSI Proxy Libary, all proxy operations require a
 * handle parameter. Currently, only one proxy operation may be in
 * progress at once per proxy handle.
 *
 * This section defines operations to create, modify and destroy GSI
 * Proxy handles.
 */

#ifndef DOXYGEN

globus_result_t
globus_gsi_proxy_handle_init(
    globus_gsi_proxy_handle_t *         handle,
    globus_gsi_proxy_handle_attrs_t     handle_attrs);

globus_result_t
globus_gsi_proxy_handle_destroy(
    globus_gsi_proxy_handle_t *         handle);

globus_result_t
globus_gsi_proxy_handle_set_policy(
    globus_gsi_proxy_handle_t           handle,
    unsigned char *                     policy,
    int                                 policy_NID);

globus_result_t
globus_gsi_proxy_handle_get_policy(
    globus_gsi_proxy_handle_t           handle,
    unsigned char **                    policy,
    int *                               policy_NID);

globus_result_t
globus_gsi_proxy_handle_set_group(
    globus_gsi_proxy_handle_t           handle,
    unsigned char *                     group,
    int                                 attached);

globus_result_t
globus_gsi_proxy_handle_get_group(
    globus_gsi_proxy_handle_t           handle,
    unsigned char **                    group,
    int *                               attached);

globus_result_t
globus_gsi_proxy_handle_set_pathlen(
    globus_gsi_proxy_handle_t           handle,
    int                                 pathlen);

globus_result_t
globus_gsi_proxy_handle_get_pathlen(
    globus_gsi_proxy_handle_t           handle,
    int *                               pathlen);

globus_result_t
globus_gsi_proxy_handle_clear_cert_info(
    globus_gsi_proxy_handle_t           handle);

#endif

/**
 * @defgroup globus_gsi_proxy_handle_attrs Handle Attributes
 *
 * Handle attributes are used to control additional features of the
 * GSI Proxy handle. These features are operation independent.
 *
 * Currently there are no attributes.
 *
 * @see #globus_gsi_proxy_handle_t
 */
#ifndef DOXYGEN


globus_result_t
globus_gsi_proxy_handle_attrs_init(
    globus_gsi_proxy_handle_attrs_t *   handle_attrs);

globus_result_t
globus_gsi_proxy_handle_attrs_destroy(
    globus_gsi_proxy_handle_attrs_t *   handle_attrs);

globus_result_t
globus_gsi_proxy_handle_attrs_copy(
    globus_gsi_proxy_handle_attrs_t     a,
    globus_gsi_proxy_handle_attrs_t     b);

#endif

/**
 * @defgroup globus_gsi_proxy_operations Proxy Operations
 *
 * Initiate a proxy operation.
 *
 * This module contains the API functions for a user to request proxy
 * request generation, proxy request inspection and proxy request
 * signature. 
 */
#ifndef DOXYGEN

globus_result_t
globus_gsi_proxy_create_req(
    globus_gsi_proxy_handle_t           handle,
    BIO *                               output_bio);

globus_result_t
globus_gsi_proxy_inquire_req(
    globus_gsi_proxy_handle_t           handle,
    BIO *                               input_bio);

globus_result_t
globus_gsi_proxy_sign_req(
    globus_gsi_proxy_handle_t           handle,
    globus_gsi_cred_handle_t            issuer_credential,
    BIO *                               output_bio);

globus_result_t
globus_gsi_proxy_assemble_cred(
    globus_gsi_proxy_handle_t           handle,
    globus_gsi_cred_handle_t *          proxy_credential,
    BIO *                               input_bio);

#endif
EXTERN_C_END

#endif /* GLOBUS_INCLUDE_GLOBUS_GSI_PROXY_H */
