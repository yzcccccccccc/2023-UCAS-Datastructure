## 环境
环境：ubuntu LTS 20.04

## GUI
使用GTK3.24实现GUI界面。使用glade完成界面设计，`GUI.glade`为GUI配置文件

## main.c
程序入口，主要实现GUI交互功能

## system_core.h
系统核心，主要实现增删、查询等功能

## data.txt
预置的交通数据，因为笔者懒所以只有火车的信息。信息主要来源于12306，也有的车次信息被笔者魔改过

## 编译命令
**gcc main.c -o main 'pkg-config --cflags --libs gtk+-3.0' -export-dynamic**

**'** 为数字1旁的 **`**

## 算法简述
### 2023.6.14
完成DFS暴力搜索，后续考虑加入A*、迭代加深等，也可能重构图结构（拆点）后使用Dijkstra算法。不过大概率最后是咕咕咕了

## 其他
data.txt和编译后的main应在同一目录下
