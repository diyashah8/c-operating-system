// Write a C program to implement deadlock detection algorithm
#include <stdio.h>

static int mark[20];
int i, j, np, nr;

int main()
{
    int alloc[30][10], request[30][10], avail[10], r[10], w[10];

    printf("\nEnter the no. of processes: ");
    scanf("%d", &np);

    printf("\nEnter the no. of resources: ");
    scanf("%d", &nr);

    for (i = 0; i < nr; i++)
    {
        printf("\nTotal amount of the resource R%d: ", i + 1);
        scanf("%d", &r[i]);
    }

    printf("\nEnter the request matrix:\n");
    for (i = 0; i < np; i++)
        for (j = 0; j < nr; j++)
            scanf("%d", &request[i][j]);

    printf("\nEnter the allocation matrix:\n");
    for (i = 0; i < np; i++)
        for (j = 0; j < nr; j++)
            scanf("%d", &alloc[i][j]);

    // Available resource calculation
    for (j = 0; j < nr; j++)
    {
        avail[j] = r[j];
        for (i = 0; i < np; i++)
        {
            avail[j] -= alloc[i][j];
        }
    }

    // Marking processes with zero allocation
    for (i = 0; i < np; i++)
    {
        int count = 0;
        for (j = 0; j < nr; j++)
        {
            if (alloc[i][j] == 0)
                count++;
            else
                break;
        }

        if (count == nr)
            mark[i] = 1;
    }

    // Initialize work vector w with available
    for (j = 0; j < nr; j++)
        w[j] = avail[j];

    // Mark processes with request <= work
    int found;
    do
    {
        found = 0;
        for (i = 0; i < np; i++)
        {
            if (mark[i] == 0)
            {
                int flag = 1;
                for (j = 0; j < nr; j++)
                {
                    if (request[i][j] > w[j])
                    {
                        flag = 0;
                        break;
                    }
                }

                if (flag)
                {
                    for (j = 0; j < nr; j++)
                        w[j] += alloc[i][j];

                    mark[i] = 1;
                    found = 1;
                }
            }
        }
    } while (found);

    // Check deadlock
    int deadlock = 0;
    for (i = 0; i < np; i++)
    {
        if (mark[i] == 0)
        {
            printf("\nProcess P%d is deadlocked", i);
            deadlock = 1;
        }
    }

    if (!deadlock)
        printf("\nNo deadlock detected");

    return 0;
}