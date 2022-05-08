# ThingsStepList 
## 全名：Things Step Segment List And Event 【事情步骤环节列表以及事件】

- **ThingsStepList**主要用于单片机裸机编程中的多任务(事情)流程处理，它使用简单静态列表管理事情和步骤。
- **ThingsStepList**是一种特定形式的**状态机**和**伪RTOS**框架，它为动作流程自动化管理提供一套轻量、简便、直观的C语言代码接口函数及列表框架，他的列表形式非常直观无须转换成状态图也能快速理解其状态转移的顺序和结构。


### 名词解释

- 【列表】：这里主要分成2种列表，一个**事情列表**，一个**步骤列表**，我们对列表里的内容进行增加或修改就可以实现某些流程上的功能而不必去修改底层调度的代码，这样做到将业务解耦代码的复用。
- 【事情】：一系列步骤组成一件事情；一组事情组成一张事情列表；**几件事情可以是并行的**;
- 【步骤】：一件事情可以分解成若干个步骤；一组步骤组成一行事情记录；**一件事情里的步骤是顺序执行的**；
- 【环节】：每个步骤预设两个环节，一个**预处理环节**一般只调用一次，一个**定时回调环节**；
- 【事件】：这里会将一些例如按键的触发及携带的数据存放到一个事件数组中，利用**放事件**，**取事件**，**删事件**这三个函数使这个事件数组组成一个先进先出的队列。


### demo打开方式

- MCU STM32F401CCU6
- [STM32CubeIDE Version: 1.9.0：./ThingsLpiddemo/.project](./ThingsLpiddemo/.project)
- [iar 9.10.2 工程文件：./ThingsLpiddemo/EWARM/tPen.eww](./ThingsLpiddemo/EWARM/tPen.eww)
- [电路原理图：./ThingsLpcb/tPen.pdf](./ThingsLpcb/tPen.pdf)
- [代码：./ThingsList.c](./ThingsList.c)

