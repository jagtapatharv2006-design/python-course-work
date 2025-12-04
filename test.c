#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ==================== STRUCTURES ====================
struct student {
    char name[1000];
    int password;
    float grade;
    int course_id;
    int id;
    char course[1000];
    char submitted_work[10000];
};

struct course_database {
    char name[1000];
    char description[10000];
    int id;
    int student_no_enrolled;
    char faculty_detail[10000];
    char course_plan[10000];
    char course_material[10000];
};

struct teacher {
    char name[1000];
    int password;
    char course[1000];
    int id;
    char schedule[100000];
    char description[10000];
};

// ==================== GLOBAL VARIABLES ====================
struct teacher teacher[1000];
struct student student[100000];
struct course_database course_database[1000];

int global_teacher_number = 0;
int global_number_of_course_offered = 0;
int global_student_serial = 0;
int teacher_login_id = 0;
char global_notice[10000] = "Welcome to the Learning Management System!";
FILE *fp[100];

#define STUDENT_FILE "studentdata.bin"
#define TEACHER_FILE "teacherdata.bin"
#define COURSE_FILE "coursedata.bin"

// ==================== FUNCTION DECLARATIONS ====================
void load_data();
void save_data();
void main_menu_teachers();
void course_work_assignment();
void student_data_to_teacher();
void student_submission_and_grade_assignment();
void post_schedule();
void main_menu_student_login(int student_id);
void sign_in();
void login();
void admin_login();
void admin_main_menu();
void notice_board(int student_id);
void add_teacher_and_course_function();
void teacher_login();
void course(int student_id);
void main_main_function();
void schedule_student(int student_id);
void course_set_up();
void print_header(const char* title);
void print_separator();
void clear_input_buffer();

// ==================== UTILITY FUNCTIONS ====================
void print_header(const char* title) {
    printf("\n");
    printf("╔════════════════════════════════════════════════════════════════════╗\n");
    printf("║              %-50s             ║\n", title);
    printf("╔════════════════════════════════════════════════════════════════════╗\n");
    printf("\n");
}

void print_separator() {
    printf("────────────────────────────────────────────────────────────────────\n");
}

void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// ==================== DATA PERSISTENCE ====================
void load_data() {
    FILE *fp;
    
    fp = fopen(STUDENT_FILE, "rb");
    if (fp != NULL) {
        fread(student, sizeof(struct student), 100000, fp);
        fclose(fp);
        global_student_serial = 0;
        for (int i = 1; i < 100000; i++) {
            if (student[i].id != 0)
                global_student_serial = i;
        }
    }
    
    fp = fopen(TEACHER_FILE, "rb");
    if (fp != NULL) {
        fread(teacher, sizeof(struct teacher), 1000, fp);
        fclose(fp);
        global_teacher_number = 0;
        for (int i = 1; i < 1000; i++) {
            if (teacher[i].id != 0)
                global_teacher_number = i;
        }
    }
    
    fp = fopen(COURSE_FILE, "rb");
    if (fp != NULL) {
        fread(course_database, sizeof(struct course_database), 1000, fp);
        fclose(fp);
        global_number_of_course_offered = 0;
        for (int i = 1; i < 1000; i++) {
            if (course_database[i].id != 0)
                global_number_of_course_offered = i;
        }
    }
}

void save_data() {
    FILE *fp;
    
    fp = fopen(STUDENT_FILE, "wb");
    if (fp != NULL) {
        fwrite(student, sizeof(struct student), global_student_serial + 1, fp);
        fclose(fp);
    }
    
    fp = fopen(TEACHER_FILE, "wb");
    if (fp != NULL) {
        fwrite(teacher, sizeof(struct teacher), global_teacher_number + 1, fp);
        fclose(fp);
    }
    
    fp = fopen(COURSE_FILE, "wb");
    if (fp != NULL) {
        fwrite(course_database, sizeof(struct course_database), global_number_of_course_offered + 1, fp);
        fclose(fp);
    }
}

// ==================== TEACHER FUNCTIONS ====================
void teacher_login() {
    int teacher_password_temp;
    
    print_header("TEACHER LOGIN");
    
    printf("Enter Teacher ID: ");
    scanf("%d", &teacher_login_id);
    
    if (teacher_login_id < 1 || teacher_login_id > global_teacher_number || teacher[teacher_login_id].id == 0) {
        printf("\n❌ Invalid Teacher ID!\n");
        return;
    }
    
    printf("Enter Password: ");
    scanf("%d", &teacher_password_temp);
    
    if (teacher[teacher_login_id].password == teacher_password_temp) {
        printf("\n✓ Login Successful!\n");
        printf("Welcome, %s\n", teacher[teacher_login_id].name);
        print_separator();
        main_menu_teachers();
    } else {
        printf("\n❌ Incorrect Password!\n");
    }
}

void main_menu_teachers() {
    int choice;
    
    while (1) {
        print_header("TEACHER DASHBOARD");
        printf("1. Provide Course Work\n");
        printf("2. View Student Data\n");
        printf("3. Student Submissions & Grade Assignment\n");
        printf("4. Post Schedule\n");
        printf("5. Course Setup\n");
        printf("6. View Course Details\n");
        printf("7. Return to Main Menu\n");
        printf("8. Logout\n");
        print_separator();
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1:
                course_work_assignment();
                break;
            case 2:
                student_data_to_teacher();
                break;
            case 3:
                student_submission_and_grade_assignment();
                break;
            case 4:
                post_schedule();
                break;
            case 5:
                course_set_up();
                break;
            case 6:
                printf("\n📚 Course: %s\n", teacher[teacher_login_id].course);
                printf("📝 Description: %s\n", teacher[teacher_login_id].description);
                break;
            case 7:
                save_data();
                main_main_function();
                return;
            case 8:
                printf("\n✓ Logged out successfully!\n");
                save_data();
                return;
            default:
                printf("\n❌ Invalid choice! Please try again.\n");
        }
    }
}

void course_set_up() {
    print_header("COURSE SETUP");
    
    printf("Setting up course: %s\n", teacher[teacher_login_id].course);
    print_separator();
    
    clear_input_buffer();
    printf("\nEnter Course Plan:\n");
    fgets(course_database[teacher_login_id].course_plan, 10000, stdin);
    course_database[teacher_login_id].course_plan[strcspn(course_database[teacher_login_id].course_plan, "\n")] = 0;
    
    printf("\nEnter Course Material/Resources:\n");
    fgets(course_database[teacher_login_id].course_material, 10000, stdin);
    course_database[teacher_login_id].course_material[strcspn(course_database[teacher_login_id].course_material, "\n")] = 0;
    
    printf("\n✓ Course setup completed successfully!\n");
    save_data();
}

void course_work_assignment() {
    char assignment_text[5000];
    
    print_header("ASSIGN COURSE WORK");
    
    printf("Course: %s\n", teacher[teacher_login_id].course);
    print_separator();
    
    clear_input_buffer();
    printf("Enter assignment description:\n");
    fgets(assignment_text, 5000, stdin);
    
    strcat(course_database[teacher_login_id].course_material, "\n\n=== ASSIGNMENT ===\n");
    strcat(course_database[teacher_login_id].course_material, assignment_text);
    
    printf("\n✓ Assignment posted successfully!\n");
    save_data();
}

void student_data_to_teacher() {
    print_header("ENROLLED STUDENTS");
    
    printf("Course: %s\n", teacher[teacher_login_id].course);
    print_separator();
    
    int found = 0;
    printf("\n%-10s %-30s %-10s\n", "ID", "Name", "Grade");
    printf("─────────────────────────────────────────────────────────\n");
    
    for (int i = 1; i <= global_student_serial; i++) {
        if (strcmp(student[i].course, teacher[teacher_login_id].course) == 0) {
            printf("%-10d %-30s %-10.2f\n", student[i].id, student[i].name, student[i].grade);
            found = 1;
        }
    }
    
    if (!found) {
        printf("No students enrolled in this course yet.\n");
    }
}

void student_submission_and_grade_assignment() {
    int student_id;
    float grade;
    
    print_header("GRADE ASSIGNMENT");
    
    student_data_to_teacher();
    
    printf("\nEnter Student ID to grade (0 to cancel): ");
    scanf("%d", &student_id);
    
    if (student_id == 0) return;
    
    if (student_id < 1 || student_id > global_student_serial) {
        printf("\n❌ Invalid Student ID!\n");
        return;
    }
    
    if (strcmp(student[student_id].course, teacher[teacher_login_id].course) != 0) {
        printf("\n❌ Student not enrolled in your course!\n");
        return;
    }
    
    printf("\n📝 Student Submission:\n");
    print_separator();
    if (strlen(student[student_id].submitted_work) > 0) {
        printf("%s\n", student[student_id].submitted_work);
    } else {
        printf("No submission yet.\n");
    }
    print_separator();
    
    printf("\nEnter grade (0-100): ");
    scanf("%f", &grade);
    
    if (grade < 0 || grade > 100) {
        printf("\n❌ Invalid grade! Must be between 0 and 100.\n");
        return;
    }
    
    student[student_id].grade = grade;
    printf("\n✓ Grade assigned successfully to %s!\n", student[student_id].name);
    save_data();
}

void post_schedule() {
    print_header("POST SCHEDULE");
    
    clear_input_buffer();
    printf("Enter schedule details:\n");
    printf("(Use underscores instead of spaces)\n");
    fgets(teacher[teacher_login_id].schedule, 100000, stdin);
    teacher[teacher_login_id].schedule[strcspn(teacher[teacher_login_id].schedule, "\n")] = 0;
    
    printf("\n✓ Schedule posted successfully!\n");
    save_data();
}

// ==================== STUDENT FUNCTIONS ====================
void sign_in() {
    int course_choice;
    int student_pin;
    char student_name[1000];
    int menu_choice;
    
    print_header("STUDENT REGISTRATION");
    
    if (global_number_of_course_offered == 0) {
        printf("❌ No courses available yet. Please contact admin.\n");
        return;
    }
    
    printf("Available Courses:\n");
    print_separator();
    for (int i = 1; i <= global_number_of_course_offered; i++) {
        printf("%d. %s\n", i, course_database[i].name);
        printf("   Description: %s\n", course_database[i].description);
        printf("   Faculty: %s\n", course_database[i].faculty_detail);
        print_separator();
    }
    
    printf("\nEnter course number to enroll: ");
    scanf("%d", &course_choice);
    
    if (course_choice < 1 || course_choice > global_number_of_course_offered) {
        printf("\n❌ Invalid course selection!\n");
        return;
    }
    
    global_student_serial++;
    student[global_student_serial].id = global_student_serial;
    student[global_student_serial].course_id = course_choice;
    strcpy(student[global_student_serial].course, course_database[course_choice].name);
    student[global_student_serial].grade = 0.0;
    
    printf("\n✓ Your Student ID: %d\n", global_student_serial);
    printf("⚠ Remember this ID for login!\n\n");
    
    printf("Set your PIN (numbers only): ");
    scanf("%d", &student_pin);
    student[global_student_serial].password = student_pin;
    
    clear_input_buffer();
    printf("Enter your full name: ");
    fgets(student_name, 1000, stdin);
    student_name[strcspn(student_name, "\n")] = 0;
    strcpy(student[global_student_serial].name, student_name);
    
    printf("\n✓ Registration Successful!\n");
    printf("Welcome, %s!\n", student_name);
    printf("Enrolled in: %s\n", course_database[course_choice].name);
    
    save_data();
    
    printf("\n1. Go to Main Menu\n2. Login Now\n3. Exit\n");
    printf("Enter choice: ");
    scanf("%d", &menu_choice);
    
    if (menu_choice == 2) {
        main_menu_student_login(global_student_serial);
    } else if (menu_choice == 3) {
        exit(0);
    }
}

void login() {
    int login_student_serial;
    int login_student_pin;
    
    print_header("STUDENT LOGIN");
    
    printf("Enter Student ID: ");
    scanf("%d", &login_student_serial);
    
    if (login_student_serial < 1 || login_student_serial > global_student_serial || student[login_student_serial].id == 0) {
        printf("\n❌ Invalid Student ID!\n");
        return;
    }
    
    printf("Enter PIN: ");
    scanf("%d", &login_student_pin);
    
    if (student[login_student_serial].password == login_student_pin) {
        printf("\n✓ Login Successful!\n");
        printf("Welcome back, %s!\n", student[login_student_serial].name);
        main_menu_student_login(login_student_serial);
    } else {
        printf("\n❌ Incorrect PIN!\n");
    }
}

void main_menu_student_login(int student_id) {
    int choice;
    
    while (1) {
        print_header("STUDENT DASHBOARD");
        printf("Student: %s (ID: %d)\n", student[student_id].name, student_id);
        printf("Course: %s\n", student[student_id].course);
        printf("Current Grade: %.2f\n", student[student_id].grade);
        print_separator();
        
        printf("\n1. View Course Materials\n");
        printf("2. Submit Assignment\n");
        printf("3. View Notice Board\n");
        printf("4. View Schedule\n");
        printf("5. View My Grade\n");
        printf("6. Return to Main Menu\n");
        printf("7. Logout\n");
        print_separator();
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1:
                course(student_id);
                break;
            case 2: {
                print_header("SUBMIT ASSIGNMENT");
                clear_input_buffer();
                printf("Enter your submission:\n");
                fgets(student[student_id].submitted_work, 10000, stdin);
                student[student_id].submitted_work[strcspn(student[student_id].submitted_work, "\n")] = 0;
                printf("\n✓ Assignment submitted successfully!\n");
                save_data();
                break;
            }
            case 3:
                notice_board(student_id);
                break;
            case 4:
                schedule_student(student_id);
                break;
            case 5:
                printf("\n📊 Your Current Grade: %.2f/100\n", student[student_id].grade);
                break;
            case 6:
                save_data();
                main_main_function();
                return;
            case 7:
                printf("\n✓ Logged out successfully!\n");
                save_data();
                return;
            default:
                printf("\n❌ Invalid choice! Please try again.\n");
        }
    }
}

void course(int student_id) {
    print_header("COURSE MATERIALS");
    
    printf("Course: %s\n", student[student_id].course);
    print_separator();
    
    printf("\n📚 Course Plan:\n");
    printf("%s\n\n", course_database[student[student_id].course_id].course_plan);
    
    printf("📖 Course Materials:\n");
    printf("%s\n", course_database[student[student_id].course_id].course_material);
}

void notice_board(int student_id) {
    print_header("NOTICE BOARD");
    printf("%s\n", global_notice);
}

void schedule_student(int student_id) {
    print_header("CLASS SCHEDULE");
    
    for (int i = 1; i <= global_teacher_number; i++) {
        if (strcmp(teacher[i].course, student[student_id].course) == 0) {
            printf("%s\n", teacher[i].schedule);
            return;
        }
    }
    
    printf("No schedule posted yet.\n");
}

// ==================== ADMIN FUNCTIONS ====================
void admin_login() {
    char admin_password[200];
    
    print_header("ADMIN LOGIN");
    
    printf("Enter Admin Password: ");
    scanf("%s", admin_password);
    
    if (strcmp(admin_password, "AtharvisKing") == 0) {
        printf("\n✓ Admin Login Successful!\n");
        admin_main_menu();
    } else {
        printf("\n❌ Access Denied! Invalid Password.\n");
    }
}

void admin_main_menu() {
    int choice;
    
    while (1) {
        print_header("ADMIN CONTROL PANEL");
        
        printf("1. Add Teacher and Course\n");
        printf("2. Update Notice Board\n");
        printf("3. View All Students\n");
        printf("4. View All Teachers\n");
        printf("5. View All Courses\n");
        printf("6. System Statistics\n");
        printf("7. Return to Main Menu\n");
        printf("8. Exit\n");
        print_separator();
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1:
                add_teacher_and_course_function();
                break;
            case 2: {
                print_header("UPDATE NOTICE");
                clear_input_buffer();
                printf("Enter new notice:\n");
                fgets(global_notice, 10000, stdin);
                global_notice[strcspn(global_notice, "\n")] = 0;
                printf("\n✓ Notice updated successfully!\n");
                save_data();
                break;
            }
            case 3: {
                print_header("ALL STUDENTS");
                printf("%-10s %-30s %-30s %-10s\n", "ID", "Name", "Course", "Grade");
                printf("────────────────────────────────────────────────────────────────────────\n");
                for (int i = 1; i <= global_student_serial; i++) {
                    if (student[i].id != 0) {
                        printf("%-10d %-30s %-30s %-10.2f\n", 
                               student[i].id, student[i].name, student[i].course, student[i].grade);
                    }
                }
                break;
            }
            case 4: {
                print_header("ALL TEACHERS");
                printf("%-10s %-30s %-30s\n", "ID", "Name", "Course");
                printf("────────────────────────────────────────────────────────────────────────\n");
                for (int i = 1; i <= global_teacher_number; i++) {
                    if (teacher[i].id != 0) {
                        printf("%-10d %-30s %-30s\n", teacher[i].id, teacher[i].name, teacher[i].course);
                    }
                }
                break;
            }
            case 5: {
                print_header("ALL COURSES");
                for (int i = 1; i <= global_number_of_course_offered; i++) {
                    if (course_database[i].id != 0) {
                        printf("\nCourse %d: %s\n", i, course_database[i].name);
                        printf("Description: %s\n", course_database[i].description);
                        print_separator();
                    }
                }
                break;
            }
            case 6: {
                print_header("SYSTEM STATISTICS");
                printf("Total Students: %d\n", global_student_serial);
                printf("Total Teachers: %d\n", global_teacher_number);
                printf("Total Courses: %d\n", global_number_of_course_offered);
                break;
            }
            case 7:
                save_data();
                main_main_function();
                return;
            case 8:
                save_data();
                exit(0);
            default:
                printf("\n❌ Invalid choice! Please try again.\n");
        }
    }
}

void add_teacher_and_course_function() {
    print_header("ADD COURSE & TEACHER");
    
    global_number_of_course_offered++;
    int course_id = global_number_of_course_offered;
    
    clear_input_buffer();
    printf("Enter Course Name: ");
    fgets(course_database[course_id].name, 1000, stdin);
    course_database[course_id].name[strcspn(course_database[course_id].name, "\n")] = 0;
    
    printf("Enter Course Description: ");
    fgets(course_database[course_id].description, 10000, stdin);
    course_database[course_id].description[strcspn(course_database[course_id].description, "\n")] = 0;
    
    course_database[course_id].id = course_id;
    course_database[course_id].student_no_enrolled = 0;
    
    printf("\n✓ Course '%s' created with ID: %d\n\n", course_database[course_id].name, course_id);
    
    global_teacher_number++;
    int teacher_id = global_teacher_number;
    
    printf("Enter Teacher Name: ");
    fgets(teacher[teacher_id].name, 1000, stdin);
    teacher[teacher_id].name[strcspn(teacher[teacher_id].name, "\n")] = 0;
    
    teacher[teacher_id].id = teacher_id;
    strcpy(teacher[teacher_id].course, course_database[course_id].name);
    
    printf("Set Teacher PIN (numbers only): ");
    scanf("%d", &teacher[teacher_id].password);
    
    clear_input_buffer();
    printf("Enter Teacher Description: ");
    fgets(teacher[teacher_id].description, 10000, stdin);
    teacher[teacher_id].description[strcspn(teacher[teacher_id].description, "\n")] = 0;
    
    strcpy(course_database[course_id].faculty_detail, teacher[teacher_id].name);
    strcat(course_database[course_id].faculty_detail, " - ");
    strcat(course_database[course_id].faculty_detail, teacher[teacher_id].description);
    
    printf("\n✓ Teacher added successfully!\n");
    printf("Teacher ID: %d\n", teacher_id);
    printf("Teacher PIN: %d\n", teacher[teacher_id].password);
    
    save_data();
}

// ==================== MAIN FUNCTION ====================
void main_main_function() {
    int choice;
    
    while (1) {
        print_header("LEARNING MANAGEMENT SYSTEM");
        
        printf("1. Admin Portal\n");
        printf("2. Teacher Portal\n");
        printf("3. Student Portal\n");
        printf("4. Exit System\n");
        print_separator();
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1:
                admin_login();
                break;
            case 2:
                teacher_login();
                break;
            case 3: {
                int student_choice;
                print_header("STUDENT PORTAL");
                printf("1. Sign Up (New Student)\n");
                printf("2. Login (Existing Student)\n");
                printf("3. Back to Main Menu\n");
                print_separator();
                printf("Enter your choice: ");
                scanf("%d", &student_choice);
                
                if (student_choice == 1) {
                    sign_in();
                } else if (student_choice == 2) {
                    login();
                } else if (student_choice == 3) {
                    continue;
                } else {
                    printf("\n❌ Invalid choice!\n");
                }
                break;
            }
            case 4:
                printf("\n✓ Thank you for using the Learning Management System!\n");
                save_data();
                exit(0);
            default:
                printf("\n❌ Invalid choice! Please try again.\n");
        }
    }
}

int main() {
    load_data();
    main_main_function();
    return 0;
}