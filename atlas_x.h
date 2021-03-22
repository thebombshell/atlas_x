
#ifndef ATLAS_X_H
#define ATLAS_X_H

#include "thread.h"

typedef unsigned long long int atlas_component_type;

#define ATLAS_COMPONENT_TYPE_INVALID				0x00000000
#define ATLAS_COMPONENT_TYPE_ENTITY					0x00000001

typedef struct atlas_component
{
	struct atlas_component* next;
	atlas_component_type type;
	mutex mutex;
	
} atlas_component;

typedef struct
{
	atlas_component* next;
	atlas_component_type type;
	mutex mutex;
	
} atlas_entity;

typedef void (*atlas_job_func)(void* t_job);

typedef struct
{
	queue job_queue;
	atlas_job_func job_func;
	list component_list;
	
} atlas_system;

typedef struct
{
	list entities;
	list systems;
	
} atlas;

int atlas_init(atlas* t_atlas);

void atlas_final(atlas* t_atlas);

void atlas_run();

#endif