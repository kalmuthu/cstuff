/* Copyright (c) Michael Moser (2011) . 3-clause BSD License applies */

#include <vtest/vtest.h>
#include <tutils/testthread.h>
#include <stdint.h>
#include <stdio.h>


#define THREAD_NUM  50

typedef struct tagTEST_CTX {
    uint64_t test_counter;
} TEST_CTX;


//#define NLOOP 1000000ULL
#define NLOOP 10000ULL


void tfunc( void *ctx, void *thread_ctx, int thread_idx, int thread_num  )
{
   uint64_t i;
   TEST_CTX *tc = (TEST_CTX *) ctx;

   (void) thread_ctx;
   (void) thread_idx;
   (void) thread_num;

   for( i = 0; i < NLOOP; i++ ) {
      __sync_fetch_and_add( &tc->test_counter, i );
   }
}



void TEST_THREAD_test()
{
  TEST_THREAD thr;
  TEST_CTX ttt;

  ttt.test_counter = 0;

  VASSERT( TEST_THREAD_init ( &thr, 4 ,  0, tfunc, 0, &ttt ) == 0 );
  VASSERT( TEST_THREAD_run ( &thr ) == 0 );

  //printf("\n%lld\n", ttt.test_counter );
  VASSERT( ttt.test_counter == 4 * ( ((NLOOP - 1) * NLOOP ) / 2 ) );

}

