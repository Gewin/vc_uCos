/*
*********************************************************************************************************
*                                                uC/OS-II
*                                          The Real-Time Kernel
*

*********************************************************************************************************
*/
/*
for book:Ƕ��ʽʵʱ����ϵͳ��COSԭ����ʵ��
¬����
2011�ڳɶ����ӿƼ���ѧ
*/
#include "includes.h"

/*
*********************************************************************************************************
*                                               CONSTANTS
*********************************************************************************************************
*/

#define  TASK_STK_SIZE               512       /* Size of each task's stacks (# of WORDs)            */
#define TaskStart_Prio	1
#define Task1_Prio		2





OS_STK  TaskStk[OS_MAX_TASKS][TASK_STK_SIZE];    // Tasks stacks
HANDLE mainhandle;		//���߳̾��
CONTEXT Context;		//���߳��л�������
BOOLEAN FlagEn = 1;		//����һ��ȫ�ֱ�������Ϊ�Ƿ�ʱ�ӵ��ȵı�־


void TaskStart(void * pParam) ;
void Task1(void * pParam) ;                            /* Function prototypes of tasks                  */

void VCInit(void);						//��ʼ����ر���,һ����Ҫ

/*$PAGE*/
/*
*********************************************************************************************************
*                                                MAIN
*********************************************************************************************************
*/


int main(int argc, char **argv)
{
	int p[2];
	p[0]=0;
	p[1]=100;
	VCInit();	
	OSInit();
	//FS_Init();        
	OSTaskCreate(TaskStart, 0, &TaskStk[1][TASK_STK_SIZE-1], TaskStart_Prio);
    
    OSTaskCreate(usertask, 0, &TaskStk[5][TASK_STK_SIZE-1], 5);
    OSTaskCreate(usertask, 100, &TaskStk[6][TASK_STK_SIZE-1], 6);

	//OSTaskCreate(usertask1, p, &TaskStk[0][TASK_STK_SIZE-1], 5);
    //OSTaskCreate(usertask2, p+1, &TaskStk[3][TASK_STK_SIZE-1], 6);
    /*
	OSTaskCreate(UserTaskSemA, 0, &TaskStk[5][TASK_STK_SIZE-1], 7);
    OSTaskCreate(UserTaskSemB, 0, &TaskStk[6][TASK_STK_SIZE-1], 6);
    OSTaskCreate(UserTaskSemC, 0, &TaskStk[7][TASK_STK_SIZE-1], 5);
    */
	/*
	OSTaskCreate(TaskDataProcess, 0, &TaskStk[5][TASK_STK_SIZE-1],5);
	OSTaskCreate(TaskIO1, 0, &TaskStk[6][TASK_STK_SIZE-1], 6);
    OSTaskCreate(TaskIO2, 0, &TaskStk[7][TASK_STK_SIZE-1], 7);
    OSTaskCreate(TaskIO3, 0, &TaskStk[8][TASK_STK_SIZE-1], 8);
    OSTaskCreate(TaskIO4, 0, &TaskStk[9][TASK_STK_SIZE-1], 9);
    */
    /*
    OSTaskCreate(TaskMutex1, 0, &TaskStk[6][TASK_STK_SIZE-1], 6);
    OSTaskCreate(TaskMutex2, 0, &TaskStk[7][TASK_STK_SIZE-1], 60);
    OSTaskCreate(TaskPrint, 0, &TaskStk[8][TASK_STK_SIZE-1], 30);
    */
	   
	/*OSTaskCreate(TaskMessageSen, 0, &TaskStk[6][TASK_STK_SIZE-1], 6);
    OSTaskCreate(TaskMessageRec, 0, &TaskStk[7][TASK_STK_SIZE-1], 7);
    */

    // OSTaskCreate(TaskQSen, 0, &TaskStk[7][TASK_STK_SIZE-1], 5);
	// OSTaskCreate(TaskQRec, 0, &TaskStk[8][TASK_STK_SIZE-1], 6);
    // OSTaskCreate(TaskQRec, 0, &TaskStk[9][TASK_STK_SIZE-1], 7);
    
	//OSTaskCreate(TaskM, 0, &TaskStk[8][TASK_STK_SIZE-1], 6);
	OSStart();	
	//FS_Exit();        
	return 0;
}

void VCInit(void)
{
	HANDLE cp,ct;
	Context.ContextFlags = CONTEXT_CONTROL;
	cp = GetCurrentProcess();	//�õ���ǰ���̾��
	ct = GetCurrentThread();	//�õ���ǰ�߳�α���
	DuplicateHandle(cp, ct, cp, &mainhandle, 0, TRUE, 2);	//α���ת��,�õ��߳�����
		
}

void TaskStart(void * pParam) 
{	
	char err;	
	OS_EVENT *sem1;
    
	/*ģ�����ö�ʱ���жϡ�����һ����ʱ���߳�,ÿ���ж�100��,�жϷ������OSTickISRuser*/
	timeSetEvent(1000/OS_TICKS_PER_SEC, 0, OSTickISRuser, 0, TIME_PERIODIC);
	OSStatInit(); /*ͳ�������ʼ��*/
	sem1 = OSSemCreate(0); 
	OSSemPend(sem1, 0, &err);   //�ȴ��¼���������������
}
