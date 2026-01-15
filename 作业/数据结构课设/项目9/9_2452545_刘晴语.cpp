#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>

using namespace std;


struct Edge {
    int toIdx;
    Edge* next;
};

struct Course {
    char id[10];
    char name[50];
    int hours;
    int fixedSem;
    int inDegree;
    int assignedSem;
    Edge* head; //邻接表：指向依赖这门课的后续课程
};


Course courses[100];
int semCourseLimits[9];
int totalCourses = 0;
int schedule[9][5][10]; //[学期][天][节次]存储课程在数组中的下标+1



int findCourseIdx(const char* id) {
    for (int i = 0; i < totalCourses; i++) {
        if (strcmp(courses[i].id, id) == 0) return i;
    }
    return -1;
}


void addEdge(int from, int to) {
    Edge* e = new Edge;
    e->toIdx = to;
    e->next = courses[from].head;
    courses[from].head = e;
}


//拓扑排序
bool topologicalSort() {
    int queue[100];
    int front = 0, rear = 0;
    int tempInDegree[100];

    for (int i = 0; i < totalCourses; i++) {
        tempInDegree[i] = courses[i].inDegree;
        if (tempInDegree[i] == 0) queue[rear++] = i;
    }

    for (int sem = 1; sem <= 8; sem++) {
        int countInSem = 0;
        int currentSemTasks[20];
        int taskCount = 0;

        //寻找符合本学期条件的课
        for (int i = front; i < rear && countInSem < semCourseLimits[sem]; i++) {
            int idx = queue[i];
            if (courses[idx].assignedSem == 0) {
                if (courses[idx].fixedSem == 0 || courses[idx].fixedSem == sem) {
                    courses[idx].assignedSem = sem;
                    currentSemTasks[taskCount++] = idx;
                    countInSem++;
                }
            }
        }


        for (int i = 0; i < taskCount; i++) {
            int u = currentSemTasks[i];
            Edge* p = courses[u].head;
            while (p) {
                if (--tempInDegree[p->toIdx] == 0) {
                    queue[rear++] = p->toIdx;
                }
                p = p->next;
            }
        }
    }
    return rear == totalCourses;
}

//贪心排课：分配具体时间
void arrangeTime() {
    memset(schedule, 0, sizeof(schedule));

    for (int i = 0; i < totalCourses; i++) {
        int sem = courses[i].assignedSem;
        int hoursLeft = courses[i].hours;
        int weekday = 0;

        while (hoursLeft > 0) {
            bool placed = false;
            //优先排3节连上(大节2:3-5节,大节4:8-10节)
            if (hoursLeft >= 3) {
                int slots[2] = { 2, 7 }; //索引从0开始，2对应第3节，7对应第8节
                for (int s = 0; s < 2; s++) {
                    int start = slots[s];
                    if (schedule[sem][weekday][start] == 0 && schedule[sem][weekday][start + 2] == 0) {
                        for (int k = 0; k < 3; k++) schedule[sem][weekday][start + k] = i + 1;
                        hoursLeft -= 3;
                        placed = true;
                        break;
                    }
                }
            }
            //尝试排2节(大节1:1-2节,大节3:6-7节)
            if (!placed && hoursLeft >= 2) {
                int slots[2] = { 0, 5 };
                for (int s = 0; s < 2; s++) {
                    int start = slots[s];
                    if (schedule[sem][weekday][start] == 0 && schedule[sem][weekday][start + 1] == 0) {
                        for (int k = 0; k < 2; k++) schedule[sem][weekday][start + k] = i + 1;
                        hoursLeft -= 2;
                        placed = true;
                        break;
                    }
                }
            }
            //排单节
            if (!placed) {
                for (int k = 0; k < 10; k++) {
                    if (schedule[sem][weekday][k] == 0) {
                        schedule[sem][weekday][k] = i + 1;
                        hoursLeft -= 1;
                        placed = true;
                        break;
                    }
                }
            }
            //跨天公式
            weekday = (weekday + 2) % 5;
        }
    }
}


void loadFile() {
    ifstream infile("input.txt");
    if (!infile) {
        cout << "无法打开input.txt" << endl;
        return;
    }
    infile >> totalCourses;
    int sum = 0;
    for (int i = 1; i <= 8; i++) {
        infile >> semCourseLimits[i];
        sum += semCourseLimits[i];
    }
    if (sum != totalCourses) {
        cout << "每学期课程总数不符" << endl;
        return;
    }

    for (int i = 0; i < totalCourses; i++) {
        int preCount;
        infile >> courses[i].id >> courses[i].name >> courses[i].hours >> courses[i].fixedSem >> preCount;
        courses[i].inDegree = preCount;
        courses[i].assignedSem = 0;
        courses[i].head = NULL;
        for (int j = 0; j < preCount; j++) {
            char preId[10];
            infile >> preId;
            int from = findCourseIdx(preId);
            if (from != -1) 
                addEdge(from, i);
        }
    }
    infile.close();
}

void saveSchedule() {
    ofstream outfile("schedule.txt");
    for (int sem = 1; sem <= 8; sem++) {
        outfile << "\n================ 第 " << sem << " 学期课表 ================\n";
        outfile << "节次 |  周一  |  周二  |  周三  |  周四  |  周五  |\n";
        for (int row = 0; row < 10; row++) {
            outfile << setw(3) << row + 1 << "   |";
            for (int day = 0; day < 5; day++) {
                int cIdxPlus1 = schedule[sem][day][row];
                if (cIdxPlus1 > 0) outfile << setw(9) << courses[cIdxPlus1 - 1].id << "|";
                else outfile << "           |";
            }
            outfile << "\n";
        }
    }
    outfile.close();
    cout << "课表已生成至schedule.txt" << endl;
}

int main() {
    loadFile();
    if (topologicalSort()) {
        arrangeTime();
        saveSchedule();
    }
    else {
        cout << "排课失败，可能存在先修课逻辑环" << endl;
    }
    return 0;
}