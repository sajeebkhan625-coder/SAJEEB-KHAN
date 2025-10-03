#include <stdio.h>
#include <string.h>

#define MAX 100
#define DAYS 30   // 1 month = 30 days

struct Student {
    int id;
    char name[50];
    char batch[20];
    char section[10];
    int present[DAYS + 1]; // store attendance for 30 days
};

struct Student students[MAX];
int total;

void inputAllStudents() {
    printf("How many students? ");
    scanf("%d", &total);
    for (int i = 0; i < total; i++) {
        printf("\nEnter details for student %d:\n", i + 1);
        printf("ID: ");
        scanf("%d", &students[i].id);
        printf("Name: ");
        scanf(" %[^\n]", students[i].name);
        printf("Batch: ");
        scanf(" %[^\n]", students[i].batch);
        printf("Section: ");
        scanf(" %[^\n]", students[i].section);

        // Initialize all days as absent
        for (int d = 1; d <= DAYS; d++) {
            students[i].present[d] = 0;
        }
    }
    printf("\nAll students information stored successfully.\n");
}

void markByID(int day) {
    int id, found = 0;
    printf("Enter ID: ");
    scanf("%d", &id);
    for (int i = 0; i < total; i++) {
        if (students[i].id == id) {
            students[i].present[day] = 1; // Mark present for that day
            printf("Attendance marked for %s (Day %d)\n", students[i].name, day);
            found = 1;
            break;
        }
    }
    if (!found) printf("ID not found.\n");
}

void showDailyReport(int day) {
    printf("\n--- Daily Report: Day %d ---\n", day);
    for (int i = 0; i < total; i++) {
        if (students[i].present[day] == 1)
            printf("ID: %d, Name: %s -> Present\n", students[i].id, students[i].name);
        else
            printf("ID: %d, Name: %s -> Absent\n", students[i].id, students[i].name);
    }
}

void showMonthlyReport() {
    printf("\n======= Monthly Attendance Report =======\n");
    for (int i = 0; i < total; i++) {
        int presentCount = 0;
        for (int d = 1; d <= DAYS; d++) {
            if (students[i].present[d] == 1) presentCount++;
        }
        int absentCount = DAYS - presentCount;
        printf("ID: %d, Name: %s -> Present: %d days, Absent: %d days\n",
               students[i].id, students[i].name, presentCount, absentCount);
    }
}

int main() {
    inputAllStudents();

    // Take attendance for each day
    for (int day = 1; day <= DAYS; day++) {
        printf("\n========== Day %d Attendance ==========\n", day);
        char choice;
        do {
            markByID(day); // mark for this day
            printf("Do you want to enter another ID for Day %d? (y/n): ", day);
            scanf(" %c", &choice);
        } while (choice == 'y' || choice == 'Y');

        // Show daily report at the end of the day
        showDailyReport(day);
    }

    // After 1 month, show report
    showMonthlyReport();
}

