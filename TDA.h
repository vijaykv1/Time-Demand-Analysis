/*!
 * \author : Varun Vijaykumar <varun.vijaykumar75@gmail.com>
 * \file   : TDA.h
 * \date   : 27 May 2016
 * \brief  : Time Demand Analysis (TDA)
 */

#ifndef TDA_h
#define TDA_h

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ITER_LIMIT 24   /*!< Iteration Limit for the TDA Analysis */
#define CONFIRM_LIMIT 3 /*!< Confirmation Limit for the TDA Analysis */

/*!
 * \brief Structure to describe the task details received.
 */
struct _task_details {
    int ID;           /*!< Identity of the Task */
    int periodicity;  /*!< Periodicity of the Task */
    int exec_time;    /*!< Execution Time of the Task */
    int priority;     /*!< Priority of the task  */
};

/*!
 * \brief Structure to describe the TDA Analysis Output.
 */
struct _TDA_details {
    char *status;                         /*!< Schedulability status of the TaskSets */
    int numberOfFailedTasks;              /*!< Number of Failed Tasks */
    struct _task_details failedTask[10];  /*!< In case of failure the failed task */
    int criticalTime[200];                /*!< In case of Success, the critical time is used */
};

/*!
 * \brief Time Demand Analysis Function.
 * \details Function to calculate the Time Demand analysis of all
 *          the task sets passed.
 * \param[in] taskDetails Taskset(s) received from the user.
 * \param[in] numOftasks Number of taskset(s) sent.
 * \param[out] The details of the TDA conducted.
 */
struct _TDA_details TDA(struct _task_details *taskDetails, int numOftasks);

/*!
 * \brief Time Demand Analysis initiation Function
 * \details Function to initiate the Time Demand analysis of all
 *          the task sets passed and print out the results
 *          obtained.
 * \param[in] taskDetails Taskset(s) received from the user.
 * \param[in] numOfTasks Number of taskset(s) sent.
 */
void TDAAnalyse (struct _task_details *taskDetails,int numOftasks);

#endif /* TDA_h */
