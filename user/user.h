/*
for book:Ƕ��ʽʵʱ����ϵͳ��COS������ʵ��
¬����
2011�ڳɶ����ӿƼ���ѧ
*/
//#define ERRORCOMMAND    255

//#define MaxLenComBuf	100

//INT8U CommandAnalys(char *Buf);
#include    "ucos_ii.h"
OS_EVENT  *MyEventSem;

void usertask(void *pParam);
void usertask2(void *pParam);
void usertask1(void *pParam);

void UserTaskSemA(void *pParam);

void UserTaskSemB(void *pParam);

void UserTaskSemC(void *pParam);

void TaskDataProcess(void *pParam);
void TaskIO1(void *pParam);
void TaskIO2(void *pParam);
void TaskIO3(void *pParam);
void TaskIO4(void *pParam);

/* */
void TaskMutex1(void *pParam);
void TaskMutex2(void *pParam);
void TaskPrint(void *pParam);

/*��Ϣ*/
void TaskMessageSen(void *pParam);
void TaskMessageRec(void *pParam);

void TaskQSen(void *pParam);
void TaskQRec(void *pParam);

void TaskM(void *pParam);