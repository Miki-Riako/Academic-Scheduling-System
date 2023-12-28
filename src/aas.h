#ifndef AAS_H
#define AAS_H

#include "header.h"

QT_BEGIN_NAMESPACE
namespace Ui
{
    class AAS;
}
QT_END_NAMESPACE

class AAS : public QWidget
{
    Q_OBJECT

public:
    AAS(QWidget *parent = nullptr);
    ~AAS();
    bool BFS(void);
    bool DFS(int u);
    int HopcroftKarp(void);
    void populateTableWidget(void);

private slots:
    void on_loadButton_clicked();
    void on_startButton_clicked();

private:
    Ui::AAS *ui;
    int numTeachers;
    int numCourses;
    vector<vector<bool> > adjMatrix;
    vector<int> pairU, pairV, dist;
    QStringList teacherNames, courseNames;
};
#endif // AAS_H
