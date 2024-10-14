/**
 * @file tkl_mutex.c
 * @brief this file was auto-generated by tuyaos v&v tools, developer can add implements between BEGIN and END
 * 
 * @warning: changes between user 'BEGIN' and 'END' will be keeped when run tuyaos v&v tools
 *           changes in other place will be overwrited and lost
 *
 * @copyright Copyright 2020-2021 Tuya Inc. All Rights Reserved.
 * 
 */

// --- BEGIN: user defines and implements ---
#include "tkl_mutex.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "tuya_error_code.h"
// --- END: user defines and implements ---

/**
* @brief Create mutex
*
* @param[out] pMutexHandle: mutex handle
*
* @note This API is used to create and init mutex.
*
* @return OPRT_OK on success. Others on error, please refer to tuya_error_code.h
*/
OPERATE_RET tkl_mutex_create_init(TKL_MUTEX_HANDLE *handle)
{
    // --- BEGIN: user implements ---
    if(!handle)
        return OPRT_INVALID_PARM;
    
#if configUSE_RECURSIVE_MUTEXES
	*handle = (TKL_MUTEX_HANDLE)xSemaphoreCreateRecursiveMutex();
#else
	*handle = (TKL_MUTEX_HANDLE)xSemaphoreCreateMutex();
#endif

	if (NULL == *handle) {
		return OPRT_OS_ADAPTER_MUTEX_CREAT_FAILED;
	}
	
    return OPRT_OK;
    // --- END: user implements ---
}

/**
* @brief Lock mutex
*
* @param[in] mutexHandle: mutex handle
*
* @note This API is used to lock mutex.
*
* @return OPRT_OK on success. Others on error, please refer to tuya_error_code.h
*/
OPERATE_RET tkl_mutex_lock(const TKL_MUTEX_HANDLE handle)
{
    // --- BEGIN: user implements ---
    if(!handle) {
        return OPRT_INVALID_PARM;
    }
    
    BaseType_t ret;
#if configUSE_RECURSIVE_MUTEXES
    ret = xSemaphoreTakeRecursive((SemaphoreHandle_t)handle, portMAX_DELAY);
#else
    ret = xSemaphoreTake((SemaphoreHandle_t)handle, portMAX_DELAY);
#endif
    if (pdTRUE != ret) {
        return OPRT_OS_ADAPTER_MUTEX_LOCK_FAILED;
    }

    return OPRT_OK;
    // --- END: user implements ---
}

/**
* @brief Try Lock mutex
*
* @param[in] mutexHandle: mutex handle
*
* @note This API is used to try lock mutex.
*
* @return OPRT_OK on success. Others on error, please refer to tuya_error_code.h
*/
OPERATE_RET tkl_mutex_trylock(const TKL_MUTEX_HANDLE mutexHandle)
{
    // --- BEGIN: user implements ---
    BaseType_t ret;

    if (NULL == mutexHandle) {
        return OPRT_INVALID_PARM;
    }
    
    ret = xSemaphoreTakeRecursive((SemaphoreHandle_t)mutexHandle, 0);
    if (pdTRUE != ret) {
        return OPRT_OS_ADAPTER_MUTEX_LOCK_FAILED;
    }
    
    return OPRT_OK;
    // --- END: user implements ---
}

/**
* @brief Unlock mutex
*
* @param[in] mutexHandle: mutex handle
*
* @note This API is used to unlock mutex.
*
* @return OPRT_OK on success. Others on error, please refer to tuya_error_code.h
*/
OPERATE_RET tkl_mutex_unlock(const TKL_MUTEX_HANDLE handle)
{
    // --- BEGIN: user implements ---
    BaseType_t ret;

    if(!handle) {
        return OPRT_INVALID_PARM;
    }
    
#if configUSE_RECURSIVE_MUTEXES
    ret = xSemaphoreGiveRecursive((SemaphoreHandle_t)handle);
#else
    ret = xSemaphoreGive((SemaphoreHandle_t)handle);
#endif

    if (pdTRUE != ret) {
        return OPRT_OS_ADAPTER_MUTEX_UNLOCK_FAILED;
    }

    return OPRT_OK;
    // --- END: user implements ---
}

/**
* @brief Release mutex
*
* @param[in] mutexHandle: mutex handle
*
* @note This API is used to release mutex.
*
* @return OPRT_OK on success. Others on error, please refer to tuya_error_code.h
*/
OPERATE_RET tkl_mutex_release(const TKL_MUTEX_HANDLE handle)
{
    // --- BEGIN: user implements ---
    if(!handle) {
        return OPRT_INVALID_PARM;
    }
    
    vSemaphoreDelete((SemaphoreHandle_t)handle);
	
    return OPRT_OK;
    // --- END: user implements ---
}
