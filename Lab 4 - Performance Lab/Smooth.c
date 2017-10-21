#include <stdio.h>
#include <stdlib.h>
#include "defs.h"
#include <pthread.h>
#include <semaphore.h>
const int MAXTHREADS = 15;
/*
 * Please fill in the following team struct
 */
team_t team = {
    "",            /* UID */
    
    "",          /* Full name */
    "",  /* Email */
    
    "",                   /* Leave Blank */
    ""                    /* Leave Blank */
};

void smoothAll (int dim, int start, int end, pixel *src, pixel *dst);
void *threaded (void * args);

typedef struct    //Struct to pass to threads
{
    int dim;
    int start;
    int end;
    pixel *src;
    pixel *dst;
} param;

char smooth_descr[] = "smooth: Current working version";

void smooth(int dim, pixel *src, pixel *dst)
{
    
    int N = min(MAXTHREADS, dim>>5);
    int  i, bplace = 0, workload = (dim-2)/N, sq1 = dim*(dim-1), sq2 = dim*dim-1;
    param b[MAXTHREADS];
    pthread_t silk[MAXTHREADS];
    
    
    //Corners First
    //Top Left
    dst[0].red = (src[0].red+src[1].red+src[dim].red+src[dim+1].red)>>2;
    dst[0].blue = (src[0].blue+src[1].blue+src[dim].blue+src[dim+1].blue)>>2;
    dst[0].green = (src[0].green+src[1].green+src[dim].green+src[dim+1].green)>>2;
    
    
    //Top Right
    dst[dim-1].red = (src[dim-1].red+src[dim-2].red+src[2*dim-1].red+src[2*dim-2].red)>>2;
    dst[dim-1].blue = (src[dim-1].blue+src[dim-2].blue+src[2*dim-1].blue+src[2*dim-2].blue)>>2;
    dst[dim-1].green = (src[dim-1].green+src[dim-2].green+src[2*dim-1].green+src[2*dim-2].green)>>2;
    
    
    //Bottom Right
    dst[(dim*dim-1)].red = (src[sq2].red+src[sq2-1].red+src[sq1-1].red+src[sq1-2].red)>>2;
    dst[(dim*dim-1)].blue = (src[sq2].blue+src[sq2-1].blue+src[sq1-1].blue+src[sq1-2].blue)>>2;
    dst[(dim*dim-1)].green = (src[sq2].green+src[sq2-1].green+src[sq1-1].green+src[sq1-2].green)>>2;
    
    
    //Bottom Left
    dst[(dim*(dim-1))].red = (src[sq1].red+src[sq1 +1].red+src[sq1-dim].red+src[sq1-dim+1].red)>>2;
    dst[(dim*(dim-1))].blue = (src[sq1].blue+src[sq1 +1].blue+src[sq1-dim].blue+src[sq1-dim+1].blue)>>2;
    dst[(dim*(dim-1))].green = (src[sq1].green+src[sq1 +1].green+src[sq1-dim].green+src[sq1-dim+1].green)>>2;
    
    
    //Create N-1 threads
    for (i = 0; i < N-1; i++)
    {
        
        b[i].dim = dim;
        b[i].src = src;
        b[i].dst = dst;
        b[i].start = bplace + 1;
        bplace = bplace + workload;
        b[i].end = bplace;
        
        pthread_create(&silk[i], NULL, threaded, (void*)&b[i]);
        
    }
    
    //Make the main thread work too
    smoothAll(dim, bplace+1, dim-2, src, dst);
    
    for(i = 0; i < N-2; i++);
    {
        pthread_join(silk[i], NULL);
    }
    
}


void smoothAll (int dim, int start, int end, pixel *src, pixel *dst)    //Do smooth function on sides and center, from start up to end
{
    int p, p1, p2, ii, jj, il, ir, id;
    
    for(ii = start; ii != end+1; ii++)
    {
        //Left
        il = ii*dim;
        dst[il].red = (src[il].red+src[il+1].red+src[il-dim].red+src[il-dim+1].red+src[il+dim].red+src[il+dim+1].red)/6;
        dst[il].blue = (src[il].blue +src[il+1].blue +src[il-dim].blue+src[il-dim+1].blue+src[il+dim].blue+src[il+dim+1].blue)/6;
        dst[il].green = (src[il].green+src[il+1].green+src[il-dim].green+src[il-dim+1].green+src[il+dim].green+src[il+dim+1].green)/6;
        
        
        //Right
        ir = (ii+1)*dim - 1;
        dst[ir].red = (src[ir].red+src[ir-1].red+src[ir-dim].red+src[ir-dim-1].red+src[ir+dim].red+src[ir+dim-1].red)/6;
        dst[ir].blue = (src[ir].blue +src[ir-1].blue +src[ir-dim].blue+src[ir-dim-1].blue+src[ir+dim].blue+src[ir+dim-1].blue)/6;
        dst[ir].green = (src[ir].green+src[ir-1].green+src[ir-dim].green+src[ir-dim-1].green+src[ir+dim].green+src[ir+dim-1].green)/6;
        
        //Down
        id = dim*(dim-1) + ii;
        dst[id].red = (src[id].red+src[id-1].red+src[id+1].red+src[id-dim].red+src[id-dim-1].red+src[id-dim+1].red)/6;
        dst[id].blue = (src[id].blue +src[id-1].blue+src[id+1].blue+src[id-dim].blue+src[id-dim-1].blue+src[id-dim+1].blue)/6;
        dst[id].green = (src[id].green +src[id-1].green +src[id+1].green +src[id-dim].green +src[id-dim-1].green +src[id-dim+1].green)/6;
        
        
        //UP
        dst[ii].red = (src[ii].red+src[ii-1].red+src[ii+1].red+src[dim+ii].red+src[dim+ii-1].red+src[dim+ii+1].red)/6;
        dst[ii].blue = (src[ii].blue +src[ii-1].blue+src[ii+1].blue+src[dim+ii].blue+src[dim+ii-1].blue+src[dim+ii+1].blue)/6;
        dst[ii].green = (src[ii].green +src[ii-1].green +src[ii+1].green +src[dim+ii].green +src[dim+ii-1].green +src[dim+ii+1].green)/6;
    }
    
    
    for(ii = start; ii != end+1; ii++)
    {
        
        for(jj = 1; jj != dim-1;jj++) //Center
        {
            p = ii*dim + jj;
            p1 = p-dim;
            p2 = p+dim;
            dst[p].red = (src[p1-1].red + src[p1].red + src[p1+1].red + src[p-1].red + src[p].red + src[p+1].red + src[p2-1].red + src[p2].red + src[p2+1].red)/9;
            dst[p].blue = (src[p1-1].blue+src[p1].blue+src[p1+1].blue+src[p-1].blue+src[p].blue+src[p+1].blue+src[p2-1].blue+src[p2].blue+src[p2+1].blue)/9;
            dst[p].green = (src[p1-1].green+src[p1].green+src[p1+1].green+src[p-1].green+src[p].green+src[p+1].green+src[p2-1].green+src[p2].green+src[p2+1].green)/9;
            
        }
        
    }
    
    return;
}


void omicorn(param* a)    //Calls smoothAll given a parameter param
{
    smoothAll(a->dim, a->start, a->end, a->src, a->dst);
}

void *threaded (void * args)    //Thread function, receive void argument transformed to param type
{
    param* q1 = (param*)args;
    omicorn(q1);
    
    pthread_exit(0);
}
