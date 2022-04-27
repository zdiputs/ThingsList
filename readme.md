## 概述

- 这是一个单片机裸机多任务(事情)流程处理的的例子。
- **特点**:代码量小，只需要一个.c文件 将跟业务强相关的代码概括成列表与底层驱动分离。
- **名词解释**
     ①事情：几件可以并行处理的任务
     ②步骤：事情里面按照一定顺序执行的任务节点
     ③环节：这里把每个步骤分解成一个预处理环节和一个间隔调用的环节
     ④列表：这里主要分成2种列表，一个事情列表，一个步骤列表，我们对列表里的内容进行增加或修改就可以实现某些流程上的功能而不必去修改底层调度的代码，这样做到将业务解耦代码的复用。

### 打开方式

1. 单片机型号STM32F401CCU6
2. [STM32CubeIDE Version: 1.9.0：./tPen/.project](./tPen/.project)   工程文件:./tPen/.project
3. [iar 9.10.2 工程文件：./tPen/EWARM/Project.eww](./tPen/EWARM/Project.eww) 
4. [电路原理图：./Pen电路.pdf](./Pen电路.pdf) 
5. [主要代码：./tPen/Core/Src/supperListList.c](./tPen/Core/Src/supperListList.c)

### 代码摘要

```C
/********************************************************************************
事情List:SUPPER_FRAME
  步骤List:LISTLIST_FRAME
    每个步骤里面划2个环节:StepSegFlag
比如：
事情A-----------------------步骤1    环节Pre   环节Poll   环节JUMP  
事情B------|           |----步骤2
          |            |----步骤3
          |
          |---------------步骤1
          |---------------步骤2
          |---------------步骤3
          |---------------步骤4
--------------------------------------------------------------------------------
也可以这么看
这里事情的序号是i  事情里面步骤的呼号是j
               j=0    j=1    j=2     j=3    j=4
  i=0事情A     步骤1  步骤2  步骤3   步骤4   步骤4
  i=1事情B     步骤1  步骤2  步骤3   步骤4
  i=2事情C     步骤1  步骤2  步骤3  
********************************************************************************/
SUPPER_FRAME sppuerList[supperNum] =
{
  {"事情A",1, 1, 0, supperTaskA,&sppuerListListA[0],&tingsA_runData},
  {"事情B",1, 1, 0, supperTaskB,&sppuerListListB[0],&tingsB_runData}
};
// A事情中 的3行记录分别是三个步骤
LISTLIST_FRAME sppuerListListA[ListListANum] = {
  {"A步骤1", STEP_PRE, 100, 1,funcStepA1Pre,funcStepA1Jue}, // A1步骤记录体
  {"A步骤2", STEP_PRE, 100, 2,funcStepA2Pre,funcStepA2Jue}, // A2步骤记录体
  {"A步骤3", STEP_PRE, 100, 0,funcStepA3Pre,funcStepA3Jue}  // A2步骤记录体
};

// A事情中 的3行记录分别是三个步骤
LISTLIST_FRAME sppuerListListB[ListListBNum] = {
  {"B步骤1", STEP_PRE, 100, 1,funcStepB1Pre,funcStepB1Jue}, // B1步骤记录体
  {"B步骤2", STEP_PRE, 100, 2,funcStepB2Pre,funcStepB2Jue}, // B2步骤记录体
  {"B步骤3", STEP_PRE, 100, 0,funcStepB3Pre,funcStepB3Jue}  // B3步骤记录体

};
```
