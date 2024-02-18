# AAS-AcademicSchedulingSystem-NEU-DataStructureCourseDesign

This is Academic Scheduling System

Programming language: C++

Compilation: minGW-based using Qmake

IDE: VScode

Development framework: QT

This program is designed to solve the bipartite graph problem for the academic scheduling

An undirected graph is said to be a bipartite graph if the set of vertices can be divided into two mutually disjoint subsets.

If the two vertices of each edge in the graph belong to two different sets of vertices. Then the graph is said to be a bipartite graph.

A bipartite graph can be used to represent the scheduling relationship between teachers and courses.

Suppose that each instructor can teach several courses, but can teach only one course in a semester, and each course is taught by only one instructor per semester.

In a bipartite graph, the matching with the highest number of edges is called the maximal matching of the graph.

A match in which all the vertices of the graph are vertices of some matching edge is called a perfect match.

The program design is based on the bipartite graph matching algorithm to solve the faculty scheduling program.

Data structures such as STL's adjacency matrix structure graph are used. Basic operations are applied to realize the algorithm to solve the academic scheduling according to the incremental and generalized paths.

Hopcroft-Karp algorithm is used.

教务排课表系统

编程语言：C++

编译：基于minGW使用Qmake编译

IDE：VScode

开发框架：QT

该程序旨在解决教务排课表的二分图问题

如果一个无向图的顶点集合可以分为两个互不相交的子集，并且图中每条边的两个顶点都属于两个不同的顶点集。则称该图为一个二分图。

可以用一个二分图表示教师与课程的排课关系。假设每位教师可以胜任多门课程，但一个学期只能讲授一门课程，每学期的每门课程只需一位教师讲授。

在二分图中，边数最多的匹配称为图的最大匹配。图的所有顶点都是某条匹配边的顶点，称这个匹配为完全匹配。

该程序设计基于二分图的匹配算法求解教务排课表程序。

采用STL的邻接矩阵结构图等数据结构。应用基本运算，实现按照增广路径的算法求解教务排课表。

使用的算法为Hopcroft-Karp算法。
