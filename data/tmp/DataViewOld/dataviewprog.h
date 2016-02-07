/****************************/
/*       danprog.h         */
/****************************/
#ifndef DANPROG
#define DANPROG

/*==========================*/

#include "AbonentList.h"
#include "AbonentNetworkTool.h"
#include "DataView.h"
#include <QDir>

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

#include "id_const.h"

extern "C"
{
#include "../include/sysprog.h"
#include "../include/systype.h"
#include "../include/DTW.h"
}


using namespace std;

/*--------------------------*/
#define taskListLen 3
/*--------------------------*/

enum
{
	mess_Start = 1,
	mess_Stop,
};

// Параметры кнопок Ввода в окнах ввода параметров элементарных движений траектории.
#define W_input				70					// Ширина кнопок ВВОДА и ОТМЕНЫ
#define H_input				30					// Высота кнопок ВВОДА и ОТМЕНЫ

#define MAXTTH				100
#define MAXZON				50



static  TASKPTR		taskList[taskListLen];
static  TASKDATA	*iTP_Task (UCHAR initNumb);
static  TASKDATA	*bTP_Task (UCHAR initNumb);
static  TASKDATA	*TP_Param (UCHAR initNumb);
static  TASKDATA	*dataList[taskListLen-1]={0,0};
static  UCHAR 		numbList[taskListLen-1]={0,0};
static  TRANFORM	*boxList[taskListLen-1]={0,0};
/*..........................*/

typedef struct
{
	TRANDATA	topData;
	int 			Regim;
}INDATA;

typedef struct
{
	TRANDATA	trandata;
	UCHAR			messType;
}MESS_TMPL_STRUC;

void buttonStop(int ID);

void setRunMainWindow();

extern int mainPid;


#endif

/****************************/
/*   end danprog.h          */
/****************************/

