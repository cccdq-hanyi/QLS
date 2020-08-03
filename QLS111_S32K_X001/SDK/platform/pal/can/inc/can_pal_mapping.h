/*
 * Copyright 2017 NXP
 * All rights reserved.
 *
 * THIS SOFTWARE IS PROVIDED BY NXP "AS IS" AND ANY EXPRESSED OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL NXP OR ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
 * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 * THE POSSIBILITY OF SUCH DAMAGE.
 */

/*!
 * @file can_pal_mapping.h
 *
 * @page misra_violations MISRA-C:2012 violations
 *
 * @section [global]
 * Violates MISRA 2012 Advisory Rule 2.5, global macro not referenced
 * This macro is used by user.
 */

#ifndef CAN_PAL_MAPPING_H
#define CAN_PAL_MAPPING_H

#include "device_registers.h"

#if (defined(CPU_S32K144HFT0VLLT) || defined(CPU_S32K144LFT0MLLT) || defined(CPU_S32K146) || \
     defined(CPU_S32K148) || defined(CPU_MPC5741P) || defined(CPU_MPC5742P) || \
     defined(CPU_MPC5743P) || defined(CPU_MPC5744P))

/*
 * @brief Define instances for S32K144, S32K146, S32K148 and MPC574xP (FlexCAN)
 *
 * Implements : can_instance_t_Class
 */
typedef enum
{
    CAN_OVER_FLEXCAN0_INSTANCE = 0U,
    CAN_OVER_FLEXCAN1_INSTANCE = 1U,
    CAN_OVER_FLEXCAN2_INSTANCE = 2U,
} can_instance_t;

/* On S32K144, S32K146, S32K148, MPC574xP there are 3 available instances which support CAN */
#define NUMBER_OF_CAN_PAL_INSTANCES 3U

/* Defines the index limits for all CANs */
#define FLEXCAN_HIGH_INDEX      2U

#elif (defined(CPU_S32K142))

/*
 * @brief Define instances for S32K142 (FlexCAN)
 *
 * Implements : can_instance_t_Class
 */
typedef enum
{
    CAN_OVER_FLEXCAN0_INSTANCE = 0U,
    CAN_OVER_FLEXCAN1_INSTANCE = 1U,
} can_instance_t;

/* On S32K142 there are 2 available instances which support CAN */
#define NUMBER_OF_CAN_PAL_INSTANCES 2U

/* Defines the index limits for all CANs */
#define FLEXCAN_HIGH_INDEX      1U

#elif (defined(CPU_S32V234))

/*
 * @brief Define instances for S32V234 (FlexCAN)
 *
 * Implements : can_instance_t_Class
 */
typedef enum
{
    CAN_OVER_FLEXCAN0_INSTANCE = 0U,
    CAN_OVER_FLEXCAN1_INSTANCE = 1U,
} can_instance_t;

/* On S32V234 there are 2 available instances which support CAN */
#define NUMBER_OF_CAN_PAL_INSTANCES 2U

/* Defines the index limits for all CANs */
#define FLEXCAN_LOW_INDEX   0U
#define FLEXCAN_HIGH_INDEX  1U

#elif (defined(CPU_MPC5747C) || defined(CPU_MPC5748C) || defined(CPU_MPC5746G) || \
       defined(CPU_MPC5747G) || defined(CPU_MPC5748G) || defined(CPU_MPC5744C) || \
       defined(CPU_MPC5745C) || defined(CPU_MPC5746C))

/*
 * @brief Define instances for MPC574xG and MPC574xC (FlexCAN)
 *
 * Implements : can_instance_t_Class
 */
typedef enum
{
    CAN_OVER_FLEXCAN0_INSTANCE = 0U,
    CAN_OVER_FLEXCAN1_INSTANCE = 1U,
    CAN_OVER_FLEXCAN2_INSTANCE = 2U,
    CAN_OVER_FLEXCAN3_INSTANCE = 3U,
    CAN_OVER_FLEXCAN4_INSTANCE = 4U,
    CAN_OVER_FLEXCAN5_INSTANCE = 5U,
    CAN_OVER_FLEXCAN6_INSTANCE = 6U,
    CAN_OVER_FLEXCAN7_INSTANCE = 7U,
} can_instance_t;

/* On MPC574xG and MPC574xC there are 8 available instances which support CAN */
#define NUMBER_OF_CAN_PAL_INSTANCES 8U

/* Defines the index limits for all CANs */
#define FLEXCAN_LOW_INDEX   0U
#define FLEXCAN_HIGH_INDEX  7U

#elif (defined(CPU_MPC5745B) || defined(CPU_MPC5744B) || defined(CPU_MPC5746B))

/*
 * @brief Define instances for MPC574xB (FlexCAN)
 *
 * Implements : can_instance_t_Class
 */
typedef enum
{
    CAN_OVER_FLEXCAN0_INSTANCE = 0U,
    CAN_OVER_FLEXCAN1_INSTANCE = 1U,
    CAN_OVER_FLEXCAN2_INSTANCE = 2U,
    CAN_OVER_FLEXCAN3_INSTANCE = 3U,
    CAN_OVER_FLEXCAN4_INSTANCE = 4U,
    CAN_OVER_FLEXCAN5_INSTANCE = 5U,
} can_instance_t;

/* On MPC574xB there are 6 available instances which support CAN */
#define NUMBER_OF_CAN_PAL_INSTANCES 6U

/* Defines the index limits for all CANs */
#define FLEXCAN_LOW_INDEX   0U
#define FLEXCAN_HIGH_INDEX  5U

#elif (defined(CPU_S32MTV) || defined(CPU_S32K116))

/*
 * @brief Define instances for S32MTV and S32K116 (FlexCAN)
 *
 * Implements : can_instance_t_Class
 */
typedef enum
{
    CAN_OVER_FLEXCAN0_INSTANCE = 0U,
} can_instance_t;

/* On S32MTV and S32K116 there is 1 available instance which supports CAN */
#define NUMBER_OF_CAN_PAL_INSTANCES 1U

/* Defines the index limits for all CANs */
#define FLEXCAN_HIGH_INDEX      0U

#endif

#endif /* CAN_PAL_MAPPING_H */
