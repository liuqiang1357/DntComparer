﻿DntComparer v1.0 -20140125
---------------------
Author:xiaot	Email:liuqiang1357@163.com
Qt:5.2.0	mingw:4.8.0
on Microsoft Windows 7 (32-bit)

项目主页：https://github.com/liuqiang1357/DntComparer

说明：
先打开dnt1，再打开dnt2,按比较按键开始比较
比较结果分为修改，删减，增加三种。两文件不同的部分用彩色标出，红色标签为dnt1，蓝色标签为dnt2。

性能：
打开文件的速度大概为2M每秒 导出xlsx速度大概为10万个单元格每秒 导出时单元格过多可能导致内存溢出

注意：
uistring.xml 必须符合标准xml规范 放在程序的同一目录下 不可改名 可以替换
打开文件过程中可以用停止按钮停止加载


文件数据结构：
文件=表头+列信息+数据体
表头：4字节（00）+2字节列数（整型）+4字节行数（整型）
列信息：（2字节标题字节数（整型）+标题（字符型）*标题字节数+1字节列数据类型（整型））*表头列数
数据体：（4字节列编号（整型）+列数据（对应列数据类型决定）*表头列数）*表头行数

数据类型：
01：字符串型：2字节字符串长度+内容（字符串）
02：32位整型数：长度为4字
03：32位整型数：长度为4字
04：32位浮点数：长度为4字
05：32位浮点数：长度为4字