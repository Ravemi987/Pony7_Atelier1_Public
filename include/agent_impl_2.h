#ifndef __AGEN_IMPL_DEUX__H__
#define __AGEN_IMPL_DEUX__H__

#include <stdio.h>
#include <stdlib.h>

#include "model.h"
#include "utils.h"
#include "action.h"
#include "state.h"
#include "agent.h"

/* Typedef */

typedef void (*ActionFunc)(void *context);


void scanSimu(void *args);

void exploitSimu(void *args);

void escalationSimu(void *args);

void exfiltrationSimu(void *args);

int generateCyberSimpleMatrices(RLState *sArray, RLAction*aArray,
                                   float **T, float **R);

#endif
