# ThingsL (单片机文本可视化状态机框架)

- **ThingsL**主要用于单片机裸机编程中的多任务(事情)流程处理，它使用简单静态列表管理事情和步骤。
- **ThingsL**是一种特定形式的**状态机**和**伪RTOS**框架，它为动作流程自动化管理提供一套轻量、简便、直观的C语言代码接口函数及列表框架，他的列表形式非常直观无须转换成状态图也能快速理解其状态转移的顺序和结构。


### 名词解释

- 列表：这里主要分成2种列表，一个**事情列表**，一个**步骤列表**，我们对列表里的内容进行增加或修改就可以实现某些流程上的功能而不必去修改底层调度的代码，这样做到将业务解耦代码的复用。
- 事情：一系列步骤组成一件事情；一组事情组成一张事情列表；
- 步骤：一件事情可以分解成若干个步骤；一组步骤组成一行事情记录；
- 环节：步骤的两个细分称为环节，每个步骤预设两个环节，一个**预处理环节**一般只调用一次，一个**定时回调环节**。；

```
层次：
-列表 
--事情
---步骤
----环节
```

### 打开方式

- MCU STM32F401CCU6
- [STM32CubeIDE Version: 1.9.0：./ThingsLonedemo/.project](./ThingsLonedemo/.project)
- [iar 9.10.2 工程文件：./ThingsLonedemo/EWARM/Project.eww](./ThingsLonedemo/EWARM/Project.eww)
- [电路原理图：./ThingsLpcb/tPen.pdf](./ThingsLpcb/tPen.pdf)
- [主要代码：./ThingsLonedemo/Core/Src/ThingsL.c](./ThingsLonedemo/Core/Src/ThingsL.c)

