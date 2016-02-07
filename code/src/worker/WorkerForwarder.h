//
// Created by fabio on 29.01.16.
//

#ifndef CODE_WORKERFORWARDER_H
#define CODE_WORKERFORWARDER_H

#include "../TypesExtern.h"


void place_task_forwarder_master(void* context, Task task);

void place_task_forwarder_taskstealing(void* context, Task task);

#endif //CODE_WORKERFORWARDER_H
