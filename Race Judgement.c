#include <stdlib.h>
#include <stdio.h>

#define n_sector 3


float fabs(float num)
{
    if (float<0)
        return -num;
    else
        return num;
}


int gt(float a, float b)
{
    return (a - b) > ( (fabs(a) < fabs(b) ? fabs(b) : fabs(a)) * 0.0001);
}


int lt(float a, float b)
{
    return (b - a) > ( (fabs(a) < fabs(b) ? fabs(b) : fabs(a)) * 0.0001);
}


float*** create_sector_times(unsigned int* n_drivers, unsigned int* n_laps){
    int i,j,k;
    float*** sector_times; 
    scanf("%d %d ", n_drivers, n_laps);
    sector_times = (float***) malloc(*n_drivers * sizeof(float**));
    for (i=0;i<*n_drivers;i++)
    {
        sector_times[i] = (float**) malloc(*n_laps * sizeof(float*));
        for (j=0;j<*n_laps;j++)
            sector_times[i][j] = (float*) malloc(3 * sizeof(float));
    }
    for (i=0;i<*n_drivers;i++)
        for (j=0;j<*n_laps;j++)
           for (k=0;k<3;k++)
               scanf("%f ", &sector_times[i][j][k]);
    return sector_times;
}


unsigned int** create_positions(unsigned int* p_drivers, unsigned int* n_races){
    int i,j;
    unsigned int** positions; 
    scanf("%d %d ", p_drivers, n_races);
    positions = (unsigned int**) malloc(*p_drivers * sizeof(unsigned int*));
    for (i=0;i<*p_drivers;i++)
        positions[i] = (unsigned int*) malloc(*n_races * sizeof(unsigned int));
    for (i=0;i<*p_drivers;i++)
        for (j=0;j<*n_races;j++)
            scanf("%d ", &positions[i][j]);
    return positions;
}


float** calculate_lap_times(float*** sector_times, unsigned int n_drivers, unsigned int n_laps){
    int i,j,k;
    float total;
    float** lap_times = (float**) malloc(n_drivers * sizeof(float*));
    for (i=0;i<n_drivers;i++)
        lap_times[i] = (float*) malloc(n_laps * sizeof(float));
    for (i=0;i<n_drivers;i++)
        for (j=0;j<n_laps;j++)
        {
            total = 0;
            for (k=0;k<3;k++)
                total += sector_times[i][j][k];
            lap_times[i][j] = total;
        }
    return lap_times;
}


unsigned int find_fastest_lap(float** lap_times, unsigned int n_drivers, unsigned int n_laps){
    int i,j;
    unsigned int fdriver = 0;
    float flap = lap_times[0][0];
    for (i=0;i<n_drivers;i++)
        for (j=0;j<n_laps;j++)
        {
            if (lt(lap_times[i][j], flap))
            {
                flap = lap_times[i][j];
                fdriver = i;
            }
        }
    return fdriver;
}


unsigned int find_driver_fastest_lap(float** sector_times_of_driver, unsigned int n_laps){
    int i,j;
    float total;
    unsigned int flap = 0;
    float fastest = sector_times_of_driver[0][0] + sector_times_of_driver[0][1] + sector_times_of_driver[0][2];
    for (i=0;i<n_laps;i++)
    {
        total = 0;
        for (j=0;j<3;j++)
            total += sector_times_of_driver[i][j];
        if (lt(total,fastest))
        {
            fastest = total;
            flap = i;
        }
    }
    return flap;
}


float* selection_sort(float* arr, unsigned int len, char ord)
{
    int i, j, min, max;
    float t;
    float* sorted_arr = (float*) malloc(len * sizeof(float));
    for (i=0;i<len;i++)
        sorted_arr[i] = arr[i];
    if (ord == 'A')
    {
        for (i=0;i<len-1;i++)
        {
            min = i;
            for (j=i+1;j<len;j++)
                if (lt(sorted_arr[j],sorted_arr[min]))
                    min = j;
            if (min!=i)
            {
                t = sorted_arr[i];
                sorted_arr[i] = sorted_arr[min];
                sorted_arr[min] = t;
            }
        }
    }
    if (ord == 'D')
    {
        for (i=0;i<len-1;i++)
        {
            max = i;
            for (j=i+1;j<len;j++)
                if (gt(sorted_arr[j],sorted_arr[max]))
                    max = j;
            if (max!=i)
            {
                t = sorted_arr[i];
                sorted_arr[i] = sorted_arr[max];
                sorted_arr[max] = t;
            }
        }
    }
    return sorted_arr;
}


unsigned int* find_finishing_positions(float** lap_times, unsigned int n_drivers, unsigned int n_laps){
    int i,j,min,t1;
    float sum,t2;
    float* totals = (float*) malloc(n_drivers * sizeof(float));
    unsigned int* positions = (unsigned int*) malloc(n_drivers * sizeof(unsigned int));
    for (i=0;i<n_drivers;i++)
    {
        sum = 0;
        for (j=0;j<n_laps;j++)
            sum += lap_times[i][j];
        totals[i] = sum;
    }
    for (i=0;i<n_drivers;i++)
        positions[i] = i;
    for (i=0;i<n_drivers-1;i++)
    {
        min = i;
        for (j=i+1;j<n_drivers;j++)
            if (lt(totals[j],totals[min]))
                min = j;
        if (min!=i)
        {
            t2 = totals[i];
            totals[i] = totals[min];
            totals[min] = t2;
            t1 = positions[i];
            positions[i] = positions[min];
            positions[min] = t1;                
        }
    }
    return positions;
}


float* find_time_diff(float** lap_times, unsigned int n_drivers, unsigned int n_laps, unsigned int driver1,
    unsigned int driver2){
    int i;
    float diff, sum=0;
    float* diff_arr = (float*) malloc(n_laps * sizeof(float));
    for (i=0;i<n_laps;i++)
    {
        diff = lap_times[driver1][i] - lap_times[driver2][i];
        sum += diff;
        diff_arr[i] = sum;
    }
    return diff_arr;
}


unsigned int* calculate_total_points(unsigned int** positions, unsigned int p_drivers, unsigned int n_races){
    int i,j,sum;
    unsigned int* total_points = (unsigned int*) malloc(p_drivers * sizeof(unsigned int));
    unsigned int* point_map = (unsigned int*) malloc(p_drivers * sizeof(unsigned int));
    for (i=0;i<p_drivers;i++)
        scanf("%d ", &point_map[i]);
    for (i=0;i<p_drivers;i++)
    {
        sum = 0;
        for (j=0;j<n_races;j++)
        {
            sum += point_map[positions[i][j]-1];
        }
        total_points[i] = sum;
    }
    return total_points;
}


unsigned int find_season_ranking(unsigned int* total_points, unsigned int p_drivers, unsigned int id){
    int i;
    unsigned int rank = 1;
    for (i=0;i<p_drivers;i++)
    {
        if (total_points[i]>total_points[id])
            rank++;
        if (total_points[i]==total_points[id])
            if (i<id)
                rank++;
    }
    return rank;
}
