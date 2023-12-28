#include "aas.h"
#include "ui_aas.h"

AAS::AAS(QWidget *parent) : QWidget(parent), ui(new Ui::AAS)
{
    ui->setupUi(this);
}
AAS::~AAS()
{
    delete ui;
}

bool AAS::BFS(void)
{ // BFS
    queue<int> q;
    for (int u = 0; u < numTeachers; ++u)
    { // Traverse all the teach pair
        if (pairU[u] == NIL)
        { // If the teacher is not be paired
            dist[u] = 0;
            q.push(u);
        }
        else
            dist[u] = INF;
    }
    dist[NIL] = INF;
    while (!q.empty())
    { // Update until the queue is empty
        int u = q.front();
        q.pop();
        if (dist[u] < dist[NIL])
            for (int v = 0; v < numCourses; ++v)
                if (adjMatrix[u][v] && dist[pairV[v]] == INF)
                { // If the course is not be paired and never be visited
                    dist[pairV[v]] = dist[u] + 1;
                    q.push(pairV[v]);
                }
    }
    return (dist[NIL] != INF);
}
bool AAS::DFS(int u)
{ // DFS
    if (u != NIL)
    { // Using DFS need the teacher is not be paired
        for (int v = 0; v < numCourses; ++v)
            if (adjMatrix[u][v] && dist[pairV[v]] == dist[u] + 1 && DFS(pairV[v]))
            { // Judge whether there is any a road
                pairV[v] = u;
                pairU[u] = v;
                return true;
            }
        dist[u] = INF;
        return false;
    }
    return true;
}
int AAS::HopcroftKarp(void)
{ // Start to use the Hopcroft-Karp
    int matching = 0;
    while (BFS())
        for (int u = 0; u < numTeachers; ++u)
            if (pairU[u] == NIL && DFS(u))
                matching++;
    return matching;
}
void AAS::populateTableWidget(void)
{ // Update the table
    ui->tableWidget->clear();
    ui->tableWidget->setRowCount(numTeachers);
    ui->tableWidget->setColumnCount(numCourses);
    ui->tableWidget->setHorizontalHeaderLabels(courseNames);
    ui->tableWidget->setVerticalHeaderLabels(teacherNames);
    for (int i = 0; i < numTeachers; ++i)
    { // Insert teachers
        for (int j = 0; j < numCourses; ++j)
        { // Insert Courses
            QTableWidgetItem *item = new QTableWidgetItem();
            if (adjMatrix[i][j])
                item->setText("o");
            else
                item->setText("x");
            item->setTextAlignment(Qt::AlignCenter);
            ui->tableWidget->setItem(i, j, item);
        }
    }
}


void AAS::on_loadButton_clicked()
{ // Read data from teach.txt file
    teacherNames.clear();
    courseNames.clear();
    adjMatrix.clear();
    numTeachers = 0;
    numCourses = 0;
    ifstream file(".\\teach.txt");
    if (file.is_open())
    { // Enter the file
        string line;
        QSet<QString> uniqueCourses;
        while (getline(file, line))
        { // Read line by line
            QStringList parts = QString::fromStdString(line).split(" ", QString::SkipEmptyParts);
            if (parts.size() > 1)
            {
                QString teacherName = parts[0];
                teacherNames.append(teacherName);
                for (int i = 1; i < parts.size(); ++i)
                {
                    QString courseName = parts[i];
                    if (!uniqueCourses.contains(courseName))
                    {
                        courseNames.append(courseName);
                        uniqueCourses.insert(courseName);
                    }
                }
            }
        }
        file.close();
    }
    else
        QMessageBox::warning(this, "Warning", "Cannot open teach.txt!");
    numTeachers = teacherNames.size();
    numCourses = courseNames.size();
    adjMatrix.resize(numTeachers);
    for (auto &row : adjMatrix)
        row.resize(numCourses, false);
    ifstream fileAgain(".\\teach.txt");
    if (fileAgain.is_open())
    { // Enter the file to paint the matrix
        string line;
        int teacherIndex = 0;
        while (getline(fileAgain, line))
        { // Read line by line to populate adjMatrix
            QStringList parts = QString::fromStdString(line).split(" ", QString::SkipEmptyParts);
            if (parts.size() > 1)
            {
                for (int i = 1; i < parts.size(); ++i)
                {
                    QString courseName = parts[i];
                    int courseIndex = courseNames.indexOf(courseName);
                    if (courseIndex != -1 && teacherIndex < numTeachers)
                        adjMatrix[teacherIndex][courseIndex] = true;
                }
                ++teacherIndex;
            }
        }
        QMessageBox::information(this, "Success", "Loaded successfully!");
        fileAgain.close();
    }
    QStringListModel *teacherModel = new QStringListModel(this);
    QStringListModel *courseModel = new QStringListModel(this);
    teacherModel->setStringList(teacherNames);
    courseModel->setStringList(courseNames);
    ui->teacherView->setModel(teacherModel);
    ui->courseView->setModel(courseModel);
    populateTableWidget();
}
void AAS::on_startButton_clicked()
{
    pairU.resize(numTeachers, NIL);
    pairV.resize(numCourses, NIL);
    dist.resize(numTeachers, 0);
    int maxMatching = HopcroftKarp();
    QStringListModel *matchingModel = new QStringListModel(this);
    QStringList matchingList;
    matchingList.append("Max Matching: " + QString::number(maxMatching));
    for (int u = 0; u < numTeachers; ++u)
    { // Load the Model
        if (pairU[u] == NIL)
            matchingList.append(teacherNames[u] + ": None");
        else
            matchingList.append(teacherNames[u] + ": " + courseNames[pairU[u]]);
    }
    matchingModel->setStringList(matchingList);
    ui->listView->setModel(matchingModel);
}
