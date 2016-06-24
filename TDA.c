/*!
 * \author : Varun Vijaykumar <varun.vijaykumar75@gmail.com>
 * \file   : TDA.c
 * \date   : 27 May 2016
 * \brief  : Time Demand Analysis (TDA)
 */

#include "TDA.h"

struct _TDA_details TDA(struct _task_details *taskDetails, int numOftasks)
{
  int iter;
  int timeDemand = 0;
  int old_timeDemand = 0;
  int confirmationLoop = 0;
  int passed = 0;
  int failed = 0;
  struct _TDA_details TDADetail;
  int i;
  for (i = 0; i < numOftasks; i++)
  {
    iter = 0;
    old_timeDemand = 0;
      
  iterate: // start again to verify

    timeDemand = 0;
      
    iter++;
    
    // Time Demand Calculation
    timeDemand = taskDetails[i].exec_time;
    int j;
    for (j = 0; j < numOftasks; j++)
    {
      if (taskDetails[i].priority > taskDetails[j].priority)
      {
        timeDemand = timeDemand + ((int)(ceil((float)old_timeDemand / (float)taskDetails[j].periodicity)) * taskDetails[j].exec_time);
      }
    }
      
    if (old_timeDemand == timeDemand)
    {
      if (confirmationLoop == CONFIRM_LIMIT)
      {
        confirmationLoop = 0;

        if (timeDemand <= taskDetails[i].periodicity)
        {
          TDADetail.criticalTime[i] = timeDemand;
          passed++;
        }
        else
        {
            // Logging Failure
            TDADetail.failedTask[failed].ID = taskDetails[i].ID;
            TDADetail.failedTask[failed].priority = taskDetails[i].priority;
            failed++;
        }
      }
      else
      {
        confirmationLoop++;
        goto iterate;
      }
    }
    else
    {
      if (iter != ITER_LIMIT)
      {
        old_timeDemand = timeDemand;
        goto iterate;
      }
      else
      {
        // Logging Failure
        TDADetail.failedTask[failed].ID = taskDetails[i].ID;
        TDADetail.failedTask[failed].priority = taskDetails[i].priority;
        failed++;
      }
    }
  }

  TDADetail.numberOfFailedTasks = failed;
    
  if (passed == numOftasks)
    TDADetail.status = "yes";
  else
    TDADetail.status = "no";

  return TDADetail;
}

void TDAAnalyse (struct _task_details *taskDetails,int numOftasks)
{

  struct _TDA_details tdaDetails = TDA(taskDetails, numOftasks);

  printf("%s:", tdaDetails.status);

  if (strcmp(tdaDetails.status, "yes") == 0)
  {
    int i;
    for (i = 0; i < numOftasks; i++)
    {
      if (i != (numOftasks-1))
      {
          printf("%d %d ", taskDetails[i].ID, tdaDetails.criticalTime[i]);
      }
      else
      {
          printf("%d %d", taskDetails[i].ID, tdaDetails.criticalTime[i]);
      }
    }
  }
  else
  {
      int currentHighestPriority = tdaDetails.failedTask[0].priority;
      int k;
      for (k = 1 ; k < tdaDetails.numberOfFailedTasks; k++ )
      {
          if (currentHighestPriority > tdaDetails.failedTask[k].priority)
          {
              currentHighestPriority = tdaDetails.failedTask[k].priority;
          }
      }
    printf("%d",currentHighestPriority);
  }
  printf("\n");
}

/*!
 * \brief Main function.
 * \details Function to read all the task sets supplied by the user,
 *          initiate the Time Demand analysis.
 * \param[in] argc Number of arguments passed to the binary.
 * \param[in] argv[] array of strings arguments passed to binary.
 */
int main(int argc, const char *argv[])
{
  if (argc == 1)
  {
    printf("Please enter the correct set of data ! \n ");
    return -1;
  }

  int numOfArgs = argc - 1;

  // Each will have 4 -- (<ID>␣<period>␣<executiontime>␣<priority>)
  int numOftasks = numOfArgs / 4;

  struct _task_details initialTaskDetails[numOftasks];

  int parser = 1;
  int i;
  for (i = 0; i < numOftasks; i++)
  {
    initialTaskDetails[i].ID = atoi(argv[parser++]);
    initialTaskDetails[i].periodicity = atoi(argv[parser++]);
    initialTaskDetails[i].exec_time = atoi(argv[parser++]);
    initialTaskDetails[i].priority = atoi(argv[parser++]);
  }

  // Passing for TDA analysis
  TDAAnalyse(initialTaskDetails, numOftasks);
  
  return 0;
}
