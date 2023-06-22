#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 定義分數對照表結構體
typedef struct {
    char grade[10];
    int minScore;
    int maxScore;
    double gpa;
} ScoreTable;

// 定義評分方式
typedef enum {
    GRADE,
    GPA,
    SCORE_RANGE
} GradingMethod;

// 定義分數資料型別
typedef union {
    char grade[10];
    double gpa;
    int score;
} Score;

// 定義學生資料型別
typedef struct {
    char studentID[20];
    Score *scores;
    double average;
} Student;

// 比較函式，用於排序學生資料
int compareStudent(const void *a, const void *b) {
    Student *student1 = (Student *)a;
    Student *student2 = (Student *)b;
    return (int)(student1->average - student2->average);
}

// 取得分數對應的 GPA
double getGPA(ScoreTable *scoreTable, int numScores, Score score) {
    for (int i = 0; i < numScores; i++) {
        if (scoreTable[i].minScore <= score.score && score.score <= scoreTable[i].maxScore) {
            return scoreTable[i].gpa;
        }
    }
    return 0.0;
}

// 換算成百分制分數
int convertToPercentage(ScoreTable *scoreTable, int numScores, Score score) {
    for (int i = 0; i < numScores; i++) {
        if (strcmp(scoreTable[i].grade, score.grade) == 0) {
            return (scoreTable[i].minScore + scoreTable[i].maxScore) / 2;
        }
    }
    return 0;
}

// 計算學生的平均分數
double calculateAverageScore(Student *students, int numStudents, int numCourses) {
    double sum = 0.0;
    for (int i = 0; i < numStudents; i++) {
        for (int j = 0; j < numCourses; j++) {
            sum += students[i].scores[j].score;
        }
        students[i].average = sum / numCourses;
        sum = 0.0;
    }
}

int main() {
    int numCourses;
    scanf("%d", &numCourses);

    GradingMethod gradingMethods[numCourses];

    ScoreTable scoreTables[numCourses];

    for (int i = 0; i < numCourses; i++) {
        char gradingMethod[5];
        scanf("%s", gradingMethod);

        if (strcmp(gradingMethod, "G") == 0) {
            gradingMethods[i] = GRADE;
        } else if (strcmp(gradingMethod, "GPA") == 0) {
            gradingMethods[i] = GPA;
        } else if (strcmp(gradingMethod, "S") == 0) {
            gradingMethods[i] = SCORE_RANGE;
        }

        if (gradingMethods[i] == GRADE) {
            scanf("%s", scoreTables[i].grade);
        } else if (gradingMethods[i] == GPA) {
            scanf("%lf", &scoreTables[i].gpa);
        } else if (gradingMethods[i] == SCORE_RANGE) {
            scanf("%d-%d", &scoreTables[i].minScore, &scoreTables[i].maxScore);
        }
    }

    int numStudents;
    scanf("%d", &numStudents);

    Student students[numStudents];

    for (int i = 0; i < numStudents; i++) {
        scanf("%s", students[i].studentID);

        students[i].scores = (Score *)malloc(numCourses * sizeof(Score));

        for (int j = 0; j < numCourses; j++) {
            if (gradingMethods[j] == GRADE) {
                scanf("%s", students[i].scores[j].grade);
            } else if (gradingMethods[j] == GPA) {
                scanf("%lf", &students[i].scores[j].gpa);
            } else if (gradingMethods[j] == SCORE_RANGE) {
                scanf("%d-%d", &students[i].scores[j].score, &students[i].scores[j].score);
            }
        }
    }

    calculateAverageScore(students, numStudents, numCourses);

    qsort(students, numStudents, sizeof(Student), compareStudent);

    for (int i = 0; i < numStudents; i++) {
        printf("%s %d\n", students[i].studentID, (int)(students[i].average + 0.5));
    }

    for (int i = 0; i < numStudents; i++) {
        free(students[i].scores);
    }

    return 0;
}
