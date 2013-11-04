/*
*********************************************************************************************************
*                                               uC/OS-II
*                                         The Real-Time Kernel
*
*                         (c) Copyright 1992-2001, Jean J. Labrosse, Weston, FL
*                                          All Rights Reserved
*
*
*                                       80x86/80x88 Specific code
*                                          PROTECTED MEMORY MODEL
*
*                                          vc++6.0
*
* File         : OS_CPU_C.C
* By           : Jean J. Labrosse
*********************************************************************************************************
*/

#define  OS_CPU_GLOBALS
#include "includes.h"

/*
*********************************************************************************************************
*                                        INITIALIZE A TASK'S STACK
*
* Description: This function is called by either OSTaskCreate() or OSTaskCreateExt() to initialize the
*              stack frame of the task being created.  This function is highly processor specific.
*			   ��console��û���жϵ��ã�Ӧ��Ҳû���жϷ��ص�ַ��vc�����ı���ģʽ�µĶε�ַû�б��
*				Ӧ��Ҳ����ѹջ�����������Ҳû�аѸ���Ĵ���ѹջ
*				
* Arguments  : task          is a pointer to the task code
*
*              pdata         is a pointer to a user supplied data area that will be passed to the task
*                            when the task first executes.
*
*              ptos          is a pointer to the top of stack.  It is assumed that 'ptos' points to
*                            a 'free' entry on the task stack.  If OS_STK_GROWTH is set to 1 then 
*                            'ptos' will contain the HIGHEST valid address of the stack.  Similarly, if
*                            OS_STK_GROWTH is set to 0, the 'ptos' will contains the LOWEST valid address
*                            of the stack.
*
*              opt           specifies options that can be used to alter the behavior of OSTaskStkInit().
*                            (see uCOS_II.H for OS_TASK_OPT_???).
*
* Returns    : Always returns the location of the new top-of-stack' once the processor registers have
*              been placed on the stack in the proper order.
*
* Note(s)    : Interrupts are enabled when your task starts executing. You can change this by setting the
*              PSW to 0x0002 instead.  In this case, interrupts would be disabled upon task startup.  The
*              application code would be responsible for enabling interrupts at the beginning of the task
*              code.  You will need to modify OSTaskIdle() and OSTaskStat() so that they enable 
*              interrupts.  Failure to do this will make your system crash!
*********************************************************************************************************
*/

OS_STK *OSTaskStkInit (void (*task)(void *pd), void *pdata, OS_STK *ptos, INT16U opt)
{
    INT32U *stk;							//console �¼Ĵ���Ϊ32λ��


    opt    = opt;                           /* 'opt' is not used, prevent warning                      */
    stk    = (INT32U *)ptos;                /* Load stack pointer                                      */
    *--stk = (INT32U)pdata;         /* Simulate call to function with argument                 */                                    
	*--stk = (INT32U)0X00000000;	//�ӳ����Ǵӵ�ǰesp��4��ȡ�ô���Ĳ��������Դ˴�Ҫ�ճ�4���ֽ�
	*--stk = (INT32U)task;          /* Put pointer to task   on top of stack                   */
    *--stk = (INT32U)0x00000202;				/* EFL = 0X00000202												*/
	*--stk = (INT32U)0xAAAAAAAA;                /* EAX = 0xAAAAAAAA                                              */
    *--stk = (INT32U)0xCCCCCCCC;                /* ECX = 0xCCCCCCCC                                             */
    *--stk = (INT32U)0xDDDDDDDD;                /* EDX = 0xDDDDDDDD                                             */
    *--stk = (INT32U)0xBBBBBBBB;                /* EBX = 0xBBBBBBBB                                             */
    *--stk = (INT32U)0x00000000;                /* ESP = 0x00000000  esp�������⣬��Ϊ                                           */
    *--stk = (INT32U)0x11111111;                /* EBP = 0x11111111                                             */
    *--stk = (INT32U)0x22222222;                /* ESI = 0x22222222                                             */
    *--stk = (INT32U)0x33333333;                /* EDI = 0x33333333                                             */
                             
    return ((OS_STK *)stk);
}



/**********************************************************************************************************
;                                          START MULTITASKING
;                                       void OSStartHighRdy(void)
;
; The stack frame is assumed to look as follows:
;
; OSTCBHighRdy->OSTCBStkPtr --> EDI                               (Low memory)                           
;                               ESI
;                               EBP
;                               ESP
;                               EBX
;                               EDX
;                               ECX
;                               EAX
;                               Flags to load in PSW
;                               OFFSET  of task code address
;								4 empty byte
;                               OFFSET  of 'pdata'					(High memory)
;                                              
;
; Note : OSStartHighRdy() MUST:
;           a) Call OSTaskSwHook() then,
;           b) Set OSRunning to TRUE,
;           c) Switch to the highest priority task.
;*********************************************************************************************************/

void OSStartHighRdy(void)
{
	OSTaskSwHook();
	OSRunning = TRUE;
	_asm{
		mov ebx, [OSTCBCur]	;OSTCBCur�ṹ�ĵ�һ����������esp
		mov esp, [ebx]		;�ָ���ջ

		popad		;�ָ�����ͨ�üĴ�������8��
		popfd		;�ָ���־�Ĵ���
		ret			;ret ָ���൱��pop eip ������ģʽ�²�����ʹ��eip
		;��Զ��������
	}
}

 /*$PAGE*/
/*********************************************************************************************************
;                                PERFORM A CONTEXT SWITCH (From task level)
;                                           void OSCtxSw(void)
;
; Note(s): 1) �˺���Ϊ�ֶ������л�����
;
;          2) The stack frame of the task to suspend looks as follows:
;
;                 SP -> OFFSET  of task to suspend    (Low memory)
;                       PSW     of task to suspend    (High memory)
;
;          3) The stack frame of the task to resume looks as follows:
;
; OSTCBHighRdy->OSTCBStkPtr --> EDI                               (Low memory)                           
;                               ESI
;                               EBP
;                               ESP
;                               EBX
;                               EDX
;                               ECX
;                               EAX
;                               Flags to load in PSW
;                               OFFSET  of task code address				(High memory)
;                                    
;*********************************************************************************************************/

void OSCtxSw(void)
{

	_asm{
		lea	 eax, nextstart	;�����л��������nextstart��ʼ
		push eax
		pushfd				;��־�Ĵ�����ֵ
		pushad				;����EAX -- EDI		
		mov ebx, OSTCBCur
		mov [ebx], esp		;�Ѷ�ջ��ڵĵ�ַ���浽��ǰTCB�ṹ��
	}

	OSTaskSwHook();
	OSTCBCur = OSTCBHighRdy;	
	OSPrioCur = OSPrioHighRdy;

	_asm{
		mov ebx, OSTCBCur
		mov esp, [ebx]		;�õ�OSTCBHighRdy��esp
		
		popad				;�ָ�����ͨ�üĴ�������8��
		popfd				;�ָ���־�Ĵ���
		ret					;��ת��ָ����������
	}
nextstart:			//�����л����������е�ַ
		return;
}

/*********************************************************************************************************
;                                PERFORM A CONTEXT SWITCH (From an ISR)
;                                        void OSIntCtxSw(void)
;
; Note(s): 1) Context���������߳����Ե������ģ�����л������Ƚϼ򵥣��ȱ�����Ӧ�Ĵ���
			  Ȼ���Ҫ���е����������������Context�ṹ�����棬����л�����ջ��������	��
;
; OSTCBHighRdy->OSTCBStkPtr --> EDI                               (Low memory)                           
;                               ESI
;                               EBP
;                               ESP
;                               EBX
;                               EDX
;                               ECX
;                               EAX
;                               Flags to load in PSW
;                               OFFSET  of task code address				(High memory)
;*********************************************************************************************************/
extern CONTEXT Context;
extern HANDLE mainhandle;

void OSIntCtxSw(void)
{
	OS_STK *sp;
	OSTaskSwHook();

	
	sp = (OS_STK *)Context.Esp;	//�õ����̵߳�ǰ��ջָ��
	//�ڶ�ջ�б�����Ӧ�Ĵ�����
	*--sp = Context.Eip;	//�ȱ���eip
	*--sp = Context.EFlags;	//����efl
	*--sp = Context.Eax;
	*--sp = Context.Ecx;
	*--sp = Context.Edx;
	*--sp = Context.Ebx;
	*--sp = Context.Esp;	//��ʱ�����esp�Ǵ���ģ���OSTCBCur��������ȷ��
	*--sp = Context.Ebp;
	*--sp = Context.Esi;
	*--sp = Context.Edi;	
	OSTCBCur->OSTCBStkPtr = (OS_STK *)sp;	//���浱ǰesp
	
	OSTCBCur = OSTCBHighRdy;		//�õ���ǰ����������ȼ������tcb
	OSPrioCur = OSPrioHighRdy;		//�õ���ǰ��������������ȼ�
	sp = OSTCBHighRdy->OSTCBStkPtr;	//�õ�����ִ�е�����Ķ�ջָ��
	
	
	//�ָ����д������ļĴ���
	Context.Edi = *sp++;
	Context.Esi = *sp++;
	Context.Ebp = *sp++;
	Context.Esp = *sp++;		//��ʱ�������еõ���esp�ǲ���ȷ��
	Context.Ebx = *sp++;
	Context.Edx = *sp++;
	Context.Ecx = *sp++;
	Context.Eax = *sp++;
	Context.EFlags = *sp++; 
	Context.Eip = *sp++;
	
	Context.Esp = (unsigned long)sp;		//�õ���ȷ��esp
	
	SetThreadContext(mainhandle, &Context);	//�������߳�������
}

/*********************************************************************************************************
;                                            HANDLE TICK ISR
;
; Description:  �˺���Ϊʱ�ӵ��ȹؼ�����ͨ��timeSetEvent����������ʱ�ӽ��ģ�timeSetEvent������һ��
				�̵߳��ô˺������˺�������������ͬ�����У�Ӧ�˲������ж�������������д˺�����
				���˺�����ģ���жϵĲ�������������жϴ��ڹر�״̬�����˳�
;
; Arguments  : none
;
; Returns    : none
;
; Note(s)    :  �˺������жϺ����ͬ����û����������Ĵ��������Ҳ�����iretָ�����OSIntCtxSw()ʵ��Ҳ��һ��
				����Ҫ���ص��ú�����
;*********************************************************************************************************/

void __stdcall OSTickISRuser(unsigned int a,unsigned int b,unsigned long c,unsigned long d,unsigned long e)
{
	if(!FlagEn)
		return;	//�����ǰ�жϱ������򷵻�

	SuspendThread(mainhandle);		//��ֹ���̵߳����У�ģ���жϲ���.��û�б���Ĵ���
	GetThreadContext(mainhandle, &Context);	//�õ����߳������ģ�Ϊ�л�������׼��

	OSIntNesting++;
	if (OSIntNesting == 1) {
		OSTCBCur->OSTCBStkPtr = (OS_STK *)Context.Esp;	//���浱ǰesp
	}	
	OSTimeTick();		//ucos�ڲ���ʱ
	OSIntExit();		//���ڲ���ʹ���жϷ���ָ����Դ˺�����Ҫ���ص�

	ResumeThread(mainhandle);	//ģ���жϷ��أ����̵߳��Լ���ִ��

}
/*$PAGE*/
#if OS_CPU_HOOKS_EN
/*
*********************************************************************************************************
*                                       OS INITIALIZATION HOOK
*                                            (BEGINNING)
*
* Description: This function is called by OSInit() at the beginning of OSInit().
*
* Arguments  : none
*
* Note(s)    : 1) Interrupts should be disabled during this call.
*********************************************************************************************************
*/
#if OS_VERSION > 203
void OSInitHookBegin (void)
{
}
#endif

/*
*********************************************************************************************************
*                                       OS INITIALIZATION HOOK
*                                               (END)
*
* Description: This function is called by OSInit() at the end of OSInit().
*
* Arguments  : none
*
* Note(s)    : 1) Interrupts should be disabled during this call.
*********************************************************************************************************
*/
#if OS_VERSION > 203
void OSInitHookEnd (void)
{
}
#endif


/*
*********************************************************************************************************
*                                          TASK CREATION HOOK
*
* Description: This function is called when a task is created.
*
* Arguments  : ptcb   is a pointer to the task control block of the task being created.
*
* Note(s)    : 1) Interrupts are disabled during this call.
*********************************************************************************************************
*/
void OSTaskCreateHook (OS_TCB *ptcb)
{
    ptcb = ptcb;                       /* Prevent compiler warning                                     */
}


/*
*********************************************************************************************************
*                                           TASK DELETION HOOK
*
* Description: This function is called when a task is deleted.
*
* Arguments  : ptcb   is a pointer to the task control block of the task being deleted.
*
* Note(s)    : 1) Interrupts are disabled during this call.
*********************************************************************************************************
*/
void OSTaskDelHook (OS_TCB *ptcb)
{
    ptcb = ptcb;                       /* Prevent compiler warning                                     */
}

/*
*********************************************************************************************************
*                                           TASK SWITCH HOOK
*
* Description: This function is called when a task switch is performed.  This allows you to perform other
*              operations during a context switch.
*
* Arguments  : none
*
* Note(s)    : 1) Interrupts are disabled during this call.
*              2) It is assumed that the global pointer 'OSTCBHighRdy' points to the TCB of the task that
*                 will be 'switched in' (i.e. the highest priority task) and, 'OSTCBCur' points to the 
*                 task being switched out (i.e. the preempted task).
*********************************************************************************************************
*/
void OSTaskSwHook (void)
{
}

/*
*********************************************************************************************************
*                                           STATISTIC TASK HOOK
*
* Description: This function is called every second by uC/OS-II's statistics task.  This allows your 
*              application to add functionality to the statistics task.
*
* Arguments  : none
*********************************************************************************************************
*/
void OSTaskStatHook (void)
{
}
void   OSTaskReturnHook(OS_TCB          *ptcb)
{

}
#if OS_DEBUG_EN > 0u
void          OSDebugInit             (void)
{
}
#endif
/*
*********************************************************************************************************
*                                           OSTCBInit() HOOK
*
* Description: This function is called by OSTCBInit() after setting up most of the TCB.
*
* Arguments  : ptcb    is a pointer to the TCB of the task being created.
*
* Note(s)    : 1) Interrupts may or may not be ENABLED during this call.
*********************************************************************************************************
*/
#if OS_VERSION > 203
void OSTCBInitHook (OS_TCB *ptcb)
{
    ptcb = ptcb;                                           /* Prevent Compiler warning                 */
}
#endif


/*
*********************************************************************************************************
*                                               TICK HOOK
*
* Description: This function is called every tick.��ӡ��ʱ��Ϣ
				
*
* Arguments  : none
*
* Note(s)    : 1) Interrupts may or may not be ENABLED during this call.
*********************************************************************************************************
*/
void OSTimeTickHook (void)
{

//	_log("   tasktick\n");

}


/*
*********************************************************************************************************
*                                             IDLE TASK HOOK
*
* Description: This function is called by the idle task.  This hook has been added to allow you to do  
*              such things as STOP the CPU to conserve power.
*
* Arguments  : none 
*
* Note(s)    : 1) Interrupts are enabled during this call.
*********************************************************************************************************
*/
#if OS_VERSION >= 251
void OSTaskIdleHook (void)
{
	Sleep(1);		
}
#endif
#endif
