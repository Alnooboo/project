#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// medical tests:
enum Test
{
    blood = 1,
    urine,
    stool
};

enum Gender
{
    male = 1,
    female
};

enum Color
{
    yellow = 0,
    orange,
    red,
    brown
};

enum Condition
{
    negative = 0,
    positive
};
// test Structures:
// blood test:
struct Blood
{
    int Hemoglobin;
    int WhiteBlood;
    int PlateletCount;
    int BloodGlucose;
    int Cholesterol;
};

// Urine test:
struct Urine
{
    enum Color urineColor;
    int pH;
    enum Condition Protein;
    enum Condition Glucose;
    int SpecificGravity;
};

// Stool test:
struct Stool
{
    enum Color urineColor;
    enum Condition BloodinStool;
    int pH;
    enum Condition Parasites;
    enum Condition OccultBlood;
};
// Patients structure
struct Patient
{
    char name[50];
    int patientId;
    int age;
    enum Gender patientgender;
    int phoneNumber;
    char diseaseName[50];
    enum Test requiredTest;
    char notes[100];

    // Structures for test results
    struct Blood bloodTest;
    struct Urine urineTest;
    struct Stool stoolTest;
};

// Doctors structure
struct Doctor
{
    int doctorId;
    int password;
    char field[50];
};

// Lab Tech structure
struct LabTech
{
    int labTechId;
    int password;
};

// Admin Structure
struct Admin
{
    int adminId;
    char password[20];
};

int adminfunc(struct Doctor *doctors, int *numDoctors, struct LabTech *labTechs, int *numLabTechs);
int doctorfunc(struct Patient *patients, int *numpatients, int **testValuesarr);
int labTechfunc(struct Patient *patients, int *numpatients, int **testValuesarr, int *numtests);
void readDoctorsFromFile(struct Doctor *doctors, int *numDoctors);
void readLabTechsFromFile(struct LabTech *labTechs, int *numLabTechs);
void readPatientsFromFile(struct Patient *patients, int *numpatients);
void readTestValuesFromFile(int **testValuesarr, int *numpatients);
int loginAdmin(struct Admin *admins, int numAdmins);
int loginDoctor(struct Doctor *doctors, int numDoctors);
int loginLabTech(struct LabTech *labTechs, int numLabTechs);
int doesDoctorExist(struct Doctor *doctors, int numDoctors, int doctorId);
int doesLabTechExist(struct LabTech *labTechs, int numLabTechs, int labTechId);
int doesPatientExist(struct Patient *patients, int numpatients, const char *patientName);
void seeAllDoctors(struct Doctor *doctors, int *numDoctors);
void seeAllLabTecs(struct LabTech *labTechs, int *numLabTechs);
void seeAllPatientsIdandName(struct Patient *patients, int *numpatients, int **testValuesarr);
void seePatientData(struct Patient *patients, int *numpatients, int ***testValuesarr);
void addDoctor(struct Doctor *doctors, int *numDoctors);
void addLabTech(struct LabTech *labTechs, int *numLabTechs);
void addPatient(struct Patient *patients, int *numpatients);
void deleteDoctor(struct Doctor *doctors, int *numDoctors, int doctorId);
void deleteLabTech(struct LabTech *labTechs, int *numLabTechs, int labTechId);
bool isPatientIdUnique(struct Patient *patients, int numpatients, int patientId);
void writePatientToFile(struct Patient *patient, const char *fileName);
void testValues(struct Patient *patients, int *numpatients, int **testValuesarr, int *numtests);
bool checkPatientsTest(int patientId, int **testValuesarr, int numtests);
void seeTestResults(struct Patient *patients, int patientIndex, int numtests, int **testValuesarr);

int main()
{

    struct Admin admins[] = {{1, "admin123"}, {2, "admin456"}};
    struct Doctor doctors[100];
    struct LabTech labTechs[100];
    struct Patient patients[100];
    

    int numAdmins = sizeof(admins) / sizeof(admins[0]);
    int numDoctors = 0;
    int numLabTechs = 0;
    int numpatients = 0;
    int numtests = 0;
int testValuesarr[100][6];
    // Call the function to read doctor data from the file
    readDoctorsFromFile(doctors, &numDoctors);
    readLabTechsFromFile(labTechs, &numLabTechs);
    readPatientsFromFile(patients, &numpatients);
    readTestValuesFromFile(testValuesarr, &numtests);

    // Main login loop
    int userType;
    do
    {

        printf("Select user type:\n");
        printf("1. Admin\n2. Doctor\n3. Lab Tech\n4. Exit\n");
        scanf("%d", &userType);

        switch (userType)
        {
        case 1:
            if (loginAdmin(admins, numAdmins))
            {
                adminfunc(doctors, &numDoctors, labTechs, &numLabTechs);
            }
            else
            {
                printf("Login failed. Invalid credentials.\n");
            }
            break;
        case 2:
            if (loginDoctor(doctors, numDoctors))
            {
                doctorfunc(patients, &numpatients, testValuesarr);
            }
            else
            {
                printf("Login failed. Invalid credentials.\n");
            }
            break;
        case 3:
            if (loginLabTech(labTechs, numLabTechs))
            {
                labTechfunc(patients, &numpatients, (int **)testValuesarr, &numtests);
            }
            else
            {
                printf("Login failed. Invalid credentials.\n");
            }
            break;
        case 4:
            printf("Exiting the application.\n");
            break;
        default:
            printf("Invalid choice. Please try again.\n");
        }
    } while (userType != 4);

    return 0;
}

// admin role:
int adminfunc(struct Doctor *doctors, int *numDoctors, struct LabTech *labTechs, int *numLabTechs)
{
    int AdminNavigate1;
    do
    {
        printf("-------------------------------\n");
        printf("Select action type:\n");
        printf("1. Add\n2. Delete\n3. See all\n4. Go back to Welcome page\n5. Exit:");
        scanf("%d", &AdminNavigate1);

        if (AdminNavigate1 == 1)
        {

            int AdminNavigate2 = 0;
            printf("-------------------------------\n");

            printf("Please enter '1' to add new Doctor\n");
            printf("Please enter '2' to add new Lab Tech\n");
            printf("Please enter '3' to go back to Admin page\n");
            printf("Please enter '4' to exit from the system\n");
            scanf("%d", &AdminNavigate2);

            if (AdminNavigate2 == 1)
            {
                addDoctor(doctors, numDoctors);
            }
            else if (AdminNavigate2 == 2)
            {
                addLabTech(labTechs, numLabTechs);
            }
            else if (AdminNavigate2 == 3)
            {
                return 0;
            }
            else if (AdminNavigate2 == 4)
            {
                exit(0);
            }
            else
            {
                printf("Invalid input!\nPlease enter one of these numbers\n");
            }
            break;
        }
        else if (AdminNavigate1 == 2)
        {
            int AdminNavigate3 = 0;
            printf("-------------------------------\n");

            printf("Please enter '1' to delete Doctor\n");
            printf("Please enter '2' to delete Lab Tech\n");
            printf("Please enter '3' to go back to Admin page\n");
            printf("Please enter '4' to exit from the system\n");
            scanf("%d", &AdminNavigate3);

            if (AdminNavigate3 == 1)
            {
                int doctorId;
                printf("Enter the ID of the doctor to delete: ");
                scanf("%d", &doctorId);
                deleteDoctor(doctors, numDoctors, doctorId);
            }
            else if (AdminNavigate3 == 2)
            {
                int labTechId;
                printf("Enter the ID of the Lab techId to delete: ");
                scanf("%d", &labTechId);
                deleteLabTech(labTechs, numLabTechs, labTechId);
            }
            else if (AdminNavigate3 == 3)
            {
                return 0;
            }
            else if (AdminNavigate3 == 4)
            {
                exit(0);
            }
            else
            {
                printf("Invalid input!\nPlease enter one of these numbers\n");
            }
            break;
        }
        else if (AdminNavigate1 == 3)
        {
            int AdminNavigate4 = 0;
            printf("-------------------------------\n");

            printf("Please enter '1' to see all Doctor\n");
            printf("Please enter '2' to see all Lab Tech\n");
            printf("Please enter '3' to go back to Admin page\n");
            printf("Please enter '4' to exit from the system\n");
            scanf("%d", &AdminNavigate4);

            if (AdminNavigate4 == 1)
            {
                seeAllDoctors(doctors, numDoctors);
            }
            else if (AdminNavigate4 == 2)
            {
                seeAllLabTecs(labTechs, numLabTechs);
            }
            else if (AdminNavigate4 == 3)
            {
                return 0;
            }
            else if (AdminNavigate4 == 4)
            {
                exit(0);
            }
            else
            {
                printf("Invalid input!\nPlease enter one of these numbers\n");
            }
            break;
        }
        else if (AdminNavigate1 == 4)
        {
            return 0;
        }
        else
        {
            printf("Invalid choice. Please try again.\n");
        }

    } while (AdminNavigate1 != 6);

    return 0;
}

// doctor role:
int doctorfunc(struct Patient *patients, int *numpatients, int **testValuesarr)
{

    int DoctorNavigate;
    do
    {
        printf("-------------------------------\n");
        printf("Select action type:\n");
        printf("1. Add Patient\n2. See Patient Info\n3. Go back to Welcome page\n4. Exit\n");
        scanf("%d", &DoctorNavigate);

        if (DoctorNavigate == 1)
        {
            addPatient(patients, numpatients);
        }
        else if (DoctorNavigate == 2)
        {
            seePatientData(patients, numpatients, testValuesarr);
        }
        else if (DoctorNavigate == 3)
        {
            return 0;
        }
        else if (DoctorNavigate == 4)
        {
            exit(0);
        }
        else
        {
            printf("Invalid choice. Please try again.\n");
        }

    } while (DoctorNavigate != 5);

    return 0;
}

// lab tech role:
int labTechfunc(struct Patient *patients, int *numpatients, int **testValuesarr, int *numtests)
{
    int LabTechNavigate;
    do
    {

        printf("-------------------------------\n");
        printf("Select action type:\n");
        printf("1. Add Patient Test\n2. Go back to Welcome page\n3. Exit\n");
        scanf("%d", &LabTechNavigate);

        if (LabTechNavigate == 1)
        {
            seeAllPatientsIdandName(patients, numpatients, *testValuesarr);
testValues(patients, &numpatients, &testValuesarr, &numtests);
        }
        else if (LabTechNavigate == 2)
        {
            return 0;
        }
        else if (LabTechNavigate == 3)
        {
            exit(0);
        }
        else
        {
            printf("Invalid choice. Please try again.\n");
        }

    } while (LabTechNavigate != 4);

    return 0;
}

// update the arrays:

// for doctors:
void readDoctorsFromFile(struct Doctor *doctors, int *numDoctors)
{
    FILE *doctorFile = fopen("doctors.txt", "r");
    if (doctorFile != NULL)
    {
        while (fscanf(doctorFile, "%d %d %s", &doctors[*numDoctors].doctorId, &doctors[*numDoctors].password, doctors[*numDoctors].field) == 3)
        {
            (*numDoctors)++;
        }
        fclose(doctorFile);
    }
}
// for lab techs:
void readLabTechsFromFile(struct LabTech *labTechs, int *numLabTechs)
{
    FILE *labTechFile = fopen("labtech.txt", "r");
    if (labTechFile != NULL)
    {
        while (fscanf(labTechFile, "%d %d", &labTechs[*numLabTechs].labTechId, &labTechs[*numLabTechs].password) == 2)
        {
            (*numLabTechs)++;
        }
        fclose(labTechFile);
    }
}
// for patients:
void readPatientsFromFile(struct Patient *patients, int *numpatients)
{
    FILE *patientFile = fopen("patient.txt", "r");
    if (patientFile != NULL)
    {
        while (fscanf(patientFile, "%d %s %d %d %d %s %d %s",
                      &patients[*numpatients].patientId,
                      patients[*numpatients].name,
                      &patients[*numpatients].age,
                      (int *)&patients[*numpatients].patientgender,
                      &patients[*numpatients].phoneNumber,
                      patients[*numpatients].diseaseName,
                      (int *)&patients[*numpatients].requiredTest,
                      patients[*numpatients].notes) == 8)

        {
            (*numpatients)++;
        }
        fclose(patientFile);
    }
}
// for test values
void readTestValuesFromFile(int **testValuesarr, int *numtests)
{
    FILE *file = fopen("testResults.txt", "r");
    if (file != NULL)
    {
        while (fscanf(file, "%d %d %d %d %d %d\n",
        &testValuesarr[*numtests][0], &testValuesarr[*numtests][1],
        &testValuesarr[*numtests][2], &testValuesarr[*numtests][3],
        &testValuesarr[*numtests][4], &testValuesarr[*numtests][5]) != 6)
        {
            (*numtests)++;
        }

        fclose(file);
    }
}

// Implement login functions
int loginAdmin(struct Admin *admins, int numAdmins)
{
    printf("hello Admin!\n");
    printf("-------------------------------\n");

    return 1; // Placeholder for successful login
}

int loginDoctor(struct Doctor *doctors, int numDoctors)
{
    printf("hello Doctor!\n");
    printf("-------------------------------\n");
    return 1; // Placeholder for successful login
}

int loginLabTech(struct LabTech *labTechs, int numLabTechs)
{
    printf("hello Lab tech!\n");
    printf("-------------------------------\n");
    return 1; // Placeholder for successful login
}

// exsit ceck:

// for doctors
int doesDoctorExist(struct Doctor *doctors, int numDoctors, int doctorId)
{
    for (int i = 0; i < numDoctors; ++i)
    {
        if (doctors[i].doctorId == doctorId)
        {
            return 1; // Doctor exists
        }
    }
    return 0; // Doctor does not exist
}
// for lab techs
int doesLabTechExist(struct LabTech *labTechs, int numLabTechs, int labTechId)
{
    for (int i = 0; i < numLabTechs; ++i)
    {
        if (labTechs[i].labTechId == labTechId)
        {
            return 1; // Lab tech exists
        }
    }
    return 0; // Lab tech does not exist
}
// for patients
int doesPatientExist(struct Patient *patients, int numpatients, const char *patientName)
{
    for (int i = 0; i < numpatients; ++i)
    {
        // Use strcmp for case-sensitive string comparison
        if (strcmp(patients[i].name, patientName) == 0)
        {
            return 1; // Patient exists
        }
    }
    return 0; // Patient does not exist
}

// see all func

// for doctor:
void seeAllDoctors(struct Doctor *doctors, int *numDoctors)
{
    printf("-------------------------------\n");
    printf("List of Doctors:\n");
    for (int i = 0; i < *numDoctors; ++i)
    {
        printf("ID: %d, Password: %d, field: %s\n", doctors[i].doctorId, doctors[i].password, doctors[i].field);
    }
}
// for lab tech:
void seeAllLabTecs(struct LabTech *labTechs, int *numLabTechs)
{
    printf("-------------------------------\n");
    printf("List of Lab Tech:\n");
    for (int i = 0; i < *numLabTechs; ++i)
    {
        printf("ID: %d, Password: %d\n", labTechs[i].labTechId, labTechs[i].password);
    }
}
// for patients:
void seeAllPatientsIdandName(struct Patient *patients, int *numpatients, int **testValuesarr)
{
    for (int i = 0; i < *numpatients; ++i)
    {
        printf("-------------------------------\n");
        printf("%dth Patient info:\n", i + 1);
        if (checkPatientsTest(patients[i].patientId, testValuesarr, *numpatients))
        {
            printf("id: %d name:%s DONE!\n", patients[i].patientId, patients[i].name);
        }
        else
        {
            printf("id: %d name:%s\n", patients[i].patientId, patients[i].name);
        }
    }
}

// for specific patient name
void seePatientData(struct Patient *patients, int *numpatients, int ***testValuesarr)
{
    // Get input for the new patient
    printf("Enter the patient's name: ");
    scanf("%49s", patients[*numpatients].name);
    int patientNum = 0;
    // Check if the patient already exists
    if (!doesPatientExist(patients, *numpatients, patients[*numpatients].name))
    {

        for (int i = 0; i < *numpatients; ++i)
        {
            // Use strcmp for case-sensitive string comparison
            if (strcmp(patients[i].name, patients[*numpatients].name) == 0)
            {
                patientNum = i;
            }
        }
        printf("-------------------------------\n");
        printf("Patient info:\n");

        printf("id: %d name:%s age:%d gender:%d phone num:%d disease name%s req test:%d notes:%s\n",
               patients[patientNum].patientId,
               patients[patientNum].name,
               patients[patientNum].age,
               patients[patientNum].patientgender,
               patients[patientNum].phoneNumber,
               patients[patientNum].diseaseName,
               patients[patientNum].requiredTest,
               patients[patientNum].notes);
    }
    int seeData;
    do
    {
        printf("Select action type:\n");
        printf("1. See test results\n2. Go back to menu\n");
        scanf("%d", &seeData);

        switch (seeData)
        {
        case 1:
            seeTestResults(patients, patientNum, *numpatients, testValuesarr);
            break;
        case 2:
            return;
        default:
            printf("Invalid choice. Please try again.\n");
            break;
        }
    } while (1); // Infinite loop until a valid choice is made
}

// add func

// for doctors:
void addDoctor(struct Doctor *doctors, int *numDoctors)
{
    // Increment the number of doctors
    (*numDoctors)++;

    // Get input for the new doctor
    printf("Enter the new doctor's ID: ");
    scanf("%d", &doctors[*numDoctors - 1].doctorId);

    // Check if the doctor already exists
    if (doesDoctorExist(doctors, *numDoctors - 1, doctors[*numDoctors - 1].doctorId))
    {
        printf("Error: Doctor with ID %d already exists.\n", doctors[*numDoctors - 1].doctorId);
        // Decrement the number of doctors to discard the invalid entry
        (*numDoctors)--;
        return;
    }

    printf("Enter the new doctor's password: ");
    scanf("%d", &doctors[*numDoctors - 1].password);

    printf("Enter the field for the new doctor: ");
    scanf("%s", doctors[*numDoctors - 1].field);

    // Save the changes to a file (you can adapt this based on your file handling requirements)
    FILE *file = fopen("doctors.txt", "a");
    if (file != NULL)
    {
        fprintf(file, "%d %d %s\n", doctors[*numDoctors - 1].doctorId, doctors[*numDoctors - 1].password, doctors[*numDoctors - 1].field);
        fclose(file);
    }
    else
    {
        printf("Error: Could not open the file for writing.\n");
    }

    printf("Doctor added successfully!\n");
}
// for lab techs:
void addLabTech(struct LabTech *labTechs, int *numLabTechs)
{
    // Increment the number of lab techs
    (*numLabTechs)++;

    // Get input for the new leb tech
    printf("Enter the new Lab tech's ID: ");
    scanf("%d", &labTechs[*numLabTechs - 1].labTechId);

    // Check if the leb tech already exists
    if (doesLabTechExist(labTechs, *numLabTechs - 1, labTechs[*numLabTechs - 1].labTechId))
    {
        printf("Error: leb tech with ID %d already exists.\n", labTechs[*numLabTechs - 1].labTechId);
        // Decrement the number of leb tech to discard the invalid entry
        (*numLabTechs)--;
        return;
    }

    printf("Enter the new leb tech's password: ");
    scanf("%d", &labTechs[*numLabTechs - 1].password);

    // Save the changes to a file (you can adapt this based on your file handling requirements)
    FILE *file = fopen("labtech.txt", "a");
    if (file != NULL)
    {
        fprintf(file, "%d %d\n", labTechs[*numLabTechs - 1].labTechId, labTechs[*numLabTechs - 1].password);
        fclose(file);
    }
    else
    {
        printf("Error: Could not open the file for writing.\n");
    }

    printf("lab tech added successfully!\n");
}
// for patient:
void addPatient(struct Patient *patients, int *numpatients)
{
    printf("Enter the new patient's name: ");
    scanf("%49s", patients[*numpatients].name);

    // Check if the patient already exists
    if (doesPatientExist(patients, *numpatients, patients[*numpatients].name))
    {
        printf("Error: patient with name %s already exists.\n", patients[*numpatients].name);
        return;
    }

    // Increment the number of patients after checking existence
    (*numpatients)++;

    int newPatientId;
    do
    {
        newPatientId = rand() % 1000;
    } while (!isPatientIdUnique(patients, *numpatients, newPatientId));

    patients[*numpatients - 1].patientId = newPatientId;

    printf("Enter the new patient's age: ");
    scanf("%d", &patients[*numpatients - 1].age);

    printf("Enter the new patient's gender (1 for male, 2 for female): ");
    scanf("%d", &patients[*numpatients - 1].patientgender);

    printf("Enter the new patient's phoneNumber: ");
    scanf("%d", &patients[*numpatients - 1].phoneNumber);

    printf("Enter the new patient's diseaseName: ");
    scanf("%49s", patients[*numpatients - 1].diseaseName);

    printf("Enter the new patient's requiredTest (1 for blood, 2 for urine, 3 for stool): ");
    scanf("%d", &patients[*numpatients - 1].requiredTest);

    printf("Enter the new patient's notes: ");
    scanf("%99s", patients[*numpatients - 1].notes);

    // Save the changes to a file
    FILE *file = fopen("patient.txt", "a");
    if (file != NULL)
    {
        fprintf(file, "%d %s %d %d %d %s %d %s\n",
                patients[*numpatients - 1].patientId,
                patients[*numpatients - 1].name,
                patients[*numpatients - 1].age,
                patients[*numpatients - 1].patientgender,
                patients[*numpatients - 1].phoneNumber,
                patients[*numpatients - 1].diseaseName,
                patients[*numpatients - 1].requiredTest,
                patients[*numpatients - 1].notes);
        fclose(file);
    }
    else
    {
        printf("Error: Could not open the file for writing.\n");
    }

    if (patients[*numpatients - 1].requiredTest == 1)
    {
        writePatientToFile(&patients[*numpatients - 1], "bloodTest.txt");
    }
    else if (patients[*numpatients - 1].requiredTest == 2)
    {
        writePatientToFile(&patients[*numpatients - 1], "urineTest.txt");
    }
    else if (patients[*numpatients - 1].requiredTest == 3)
    {
        writePatientToFile(&patients[*numpatients - 1], "stoolTest.txt");
    }

    printf("Patient added successfully!\n");
}

// delete fun:

// for doctors:
void deleteDoctor(struct Doctor *doctors, int *numDoctors, int doctorId)
{
    int doctorIndex = -1;

    // Find the index of the doctor with the given ID
    for (int i = 0; i < *numDoctors; ++i)
    {
        if (doctors[i].doctorId == doctorId)
        {
            doctorIndex = i;
            break;
        }
    }

    // Check if the doctor was found
    if (doctorIndex != -1)
    {
        // Move all doctors after the found one to the previous index
        for (int i = doctorIndex; i < *numDoctors - 1; ++i)
        {
            doctors[i] = doctors[i + 1];
        }

        // Decrement the number of doctors
        (*numDoctors)--;

        printf("Doctor with ID %d deleted successfully.\n", doctorId);

        // Save the changes to a file (you can adapt this based on your file handling requirements)
        FILE *file = fopen("doctors.txt", "w");
        if (file != NULL)
        {
            for (int i = 0; i < *numDoctors; ++i)
            {
                fprintf(file, "%d %d %s\n", doctors[i].doctorId, doctors[i].password, doctors[i].field);
            }
            fclose(file);
        }
        else
        {
            printf("Error: Could not open the file for writing.\n");
        }
    }
    else
    {
        printf("Error: Doctor with ID %d not found.\n", doctorId);
    }
}
// for lab techs:
void deleteLabTech(struct LabTech *labTechs, int *numLabTechs, int labTechId)
{
    int labTechIndex = -1;

    // Find the index of the lab tech with the given ID
    for (int i = 0; i < *numLabTechs; ++i)
    {
        if (labTechs[i].labTechId == labTechId)
        {
            labTechIndex = i;
            break;
        }
    }

    // Check if the lab tech was found
    if (labTechIndex != -1)
    {
        // Move all lab techs after the found one to the previous index
        for (int i = labTechIndex; i < *numLabTechs - 1; ++i)
        {
            labTechs[i] = labTechs[i + 1];
        }

        // Decrement the number of lab techs
        (*numLabTechs)--;

        printf("lab tech with ID %d deleted successfully.\n", labTechId);

        // Save the changes to a file
        FILE *file = fopen("labtech.txt", "w");
        if (file != NULL)
        {
            for (int i = 0; i < *numLabTechs; ++i)
            {
                fprintf(file, "%d %d\n", labTechs[i].labTechId, labTechs[i].password);
            }
            fclose(file);
        }
        else
        {
            printf("Error: Could not open the file for writing.\n");
        }
    }
    else
    {
        printf("Error: lab tech with ID %d not found.\n", labTechId);
    }
}

// give patients uniqe ID
bool isPatientIdUnique(struct Patient *patients, int numpatients, int patientId)
{
    for (int i = 0; i < numpatients; ++i)
    {
        if (patients[i].patientId == patientId)
        {
            return false; // ID is not unique
        }
    }
    return true; // ID is unique
}

// assignt test to the doctor
void writePatientToFile(struct Patient *patient, const char *fileName)
{
    FILE *file = fopen(fileName, "a");
    if (file != NULL)
    {
        fprintf(file, "%d\n", patient->patientId);
        fclose(file);
    }
    else
    {
        printf("Error: Could not open the file '%s' for writing.\n", fileName);
    }
}

// enter test values:
void testValues(struct Patient *patients, int *numpatients, int **testValuesarr, int *numtests)
{
    int proceed;

    printf("1. to proceed\n2. to return to the menu\n");
    scanf("%d", &proceed);

    if (proceed == 1)
    {
        printf("Enter the patient's name: ");
        scanf("%49s", patients[*numpatients].name);

        // Check if the patient already exists
        if (!doesPatientExist(patients, *numpatients, patients[*numpatients].name))
        {
            int patientIndex;
            for (int i = 0; i < *numpatients; ++i)
            {
                if (strcmp(patients[i].name, patients[*numpatients].name) == 0)
                {
                    patientIndex = i;
                    break;
                }
            }
            if (checkPatientsTest(patients[patientIndex].patientId, testValuesarr, *numpatients))
            {
                numtests++;
                // double pointer to store the test values and patients's ID

                testValuesarr[numtests - 1][0] = patients[patientIndex].patientId;
                // Assign test values based on the type of test
                switch (patients[patientIndex].requiredTest)
                {
                case blood:

                    printf("Enter Hemoglobin: ");
                    scanf("%d", &patients[patientIndex].bloodTest.Hemoglobin);
                    testValuesarr[numtests - 1][1] = patients[patientIndex].bloodTest.Hemoglobin;
                    printf("Enter White Blood Count: ");
                    scanf("%d", &patients[patientIndex].bloodTest.WhiteBlood);
                    testValuesarr[numtests - 1][2] = patients[patientIndex].bloodTest.WhiteBlood;
                    printf("Enter Platelet Count: ");
                    scanf("%d", &patients[patientIndex].bloodTest.PlateletCount);
                    testValuesarr[numtests - 1][3] = patients[patientIndex].bloodTest.PlateletCount;
                    printf("Enter Blood Glucose count: ");
                    scanf("%d", &patients[patientIndex].bloodTest.BloodGlucose);
                    testValuesarr[numtests - 1][4] = patients[patientIndex].bloodTest.BloodGlucose;
                    printf("Enter Cholesterol Count: ");
                    scanf("%d", &patients[patientIndex].bloodTest.Cholesterol);
                    testValuesarr[numtests - 1][5] = patients[patientIndex].bloodTest.Cholesterol;
                    break;

                case urine:
                    printf("Enter Urine Color (0 for yellow, 1 for orange, 2 for red, 3 for brown): ");
                    scanf("%d", &patients[patientIndex].urineTest.urineColor);
                    testValuesarr[numtests - 1][1] = patients[patientIndex].urineTest.urineColor;
                    printf("Enter pH: ");
                    scanf("%d", &patients[patientIndex].urineTest.pH);
                    testValuesarr[numtests - 1][2] = patients[patientIndex].urineTest.pH;
                    printf("Enter Protein condition (0 for negative, 1 for positive): ");
                    scanf("%d", &patients[patientIndex].urineTest.Protein);
                    testValuesarr[numtests - 1][3] = patients[patientIndex].urineTest.Protein;
                    printf("Enter Glucose condition (0 for negative, 1 for positive): ");
                    scanf("%d", &patients[patientIndex].urineTest.Glucose);
                    testValuesarr[numtests - 1][4] = patients[patientIndex].urineTest.Glucose;
                    printf("Enter SpecificGravity: ");
                    scanf("%d", &patients[patientIndex].urineTest.SpecificGravity);
                    testValuesarr[numtests - 1][5] = patients[patientIndex].urineTest.SpecificGravity;
                    break;

                case stool:
                    printf("Enter Stool Color (0 for yellow, 1 for orange, 2 for red, 3 for brown): ");
                    scanf("%d", &patients[patientIndex].stoolTest.urineColor);
                    testValuesarr[numtests - 1][1] = patients[patientIndex].stoolTest.urineColor;
                    printf("Enter Blood in Stool condition (0 for negative, 1 for positive): ");
                    scanf("%d", &patients[patientIndex].stoolTest.BloodinStool);
                    testValuesarr[numtests - 1][2] = patients[patientIndex].stoolTest.BloodinStool;
                    printf("Enter pH: ");
                    scanf("%d", &patients[patientIndex].stoolTest.pH);
                    testValuesarr[numtests - 1][3] = patients[patientIndex].stoolTest.pH;
                    printf("Enter Parasites condition (0 for negative, 1 for positive): ");
                    scanf("%d", &patients[patientIndex].stoolTest.Parasites);
                    testValuesarr[numtests - 1][4] = patients[patientIndex].stoolTest.Parasites;
                    printf("Enter OccultBlood condition (0 for negative, 1 for positive): ");
                    scanf("%d", &patients[patientIndex].stoolTest.OccultBlood);
                    testValuesarr[numtests - 1][5] = patients[patientIndex].stoolTest.OccultBlood;
                    break;

                default:
                    printf("Invalid test type.\n");
                    break;
                }

                // Save the changes to a file (you can adapt this based on your file handling requirements)
                FILE *file = fopen("testResults.txt", "a");
                if (file != NULL)
                {
                    fprintf(file, "%d %d %d %d %d %d\n", testValuesarr[numtests - 1][0], testValuesarr[numtests - 1][1],
                            testValuesarr[numtests - 1][2], testValuesarr[numtests - 1][3],
                            testValuesarr[numtests - 1][4], testValuesarr[numtests - 1][5]);

                    fclose(file);
                }
                else
                {
                    printf("Error: Could not open the file for writing.\n");
                }
            }
            else
            {
                printf("Error: test values have already given to :%s.\n", patients[*numpatients].name);
            }
        }
        else
        {
            printf("Error: there is no patient with name :%s.\n", patients[*numpatients].name);
        }
    }
    else if (proceed == 2)
    {
        return;
    }
    else
    {
        printf("Invalid choice. Please try again.\n");
    }
}

// Check if patient's test values have already been given
bool checkPatientsTest(int patientId, int **testValuesarr, int numtests)
{
    for (int i = 0; i < numtests; ++i)
    {
        if (testValuesarr[i][0] == patientId)
        {
            return false; // Patient ID found in the assigned tests
        }
    }
    return true; // Patient ID not found in the assigned tests
}

// Function to display patient information and test results
void seeTestResults(struct Patient *patients, int patientIndex, int numtests, int **testValuesarr)
{
    printf("Error: the progeam stopped here!1.\n");
    // Check if test results are assigned by checking the file
    if (checkPatientsTest(patients[patientIndex].patientId, testValuesarr, numtests))
    {
        printf("Error: the progeam stopped here!2.\n");
        printf("No test results assigned for %s yet.\n", patients[patientIndex].name);
    }
    else
    {
        // Display test results from the double pointer

        // Find the index of the patient in the double pointer
        int assignedIndex = -1;
        for (int i = 0; i < numtests; ++i)
        {
            if (testValuesarr[i][0] == patients[patientIndex].patientId)
            {
                assignedIndex = i;
                break;
            }
        }

        if (assignedIndex != -1)
        {
            printf("\nTest Results for %s:\n", patients[patientIndex].name);

            switch (patients[patientIndex].requiredTest)
            {
            case blood:
                printf("Hemoglobin: %d\n", testValuesarr[assignedIndex][1]);
                printf("White Blood Count: %d\n", testValuesarr[assignedIndex][2]);
                printf("Platelet Count: %d\n", testValuesarr[assignedIndex][3]);
                printf("Blood Glucose: %d\n", testValuesarr[assignedIndex][4]);
                printf("Cholesterol: %d\n", testValuesarr[assignedIndex][5]);
                break;

            case urine:
                printf("Urine Color: %d\n", testValuesarr[assignedIndex][1]);
                printf("pH: %d\n", testValuesarr[assignedIndex][2]);
                printf("Protein: %d\n", testValuesarr[assignedIndex][3]);
                printf("Glucose: %d\n", testValuesarr[assignedIndex][4]);
                printf("Specific Gravity: %d\n", testValuesarr[assignedIndex][5]);
                break;

            case stool:
                printf("Stool Color: %d\n", testValuesarr[assignedIndex][1]);
                printf("Blood in Stool: %d\n", testValuesarr[assignedIndex][2]);
                printf("pH: %d\n", testValuesarr[assignedIndex][3]);
                printf("Parasites: %d\n", testValuesarr[assignedIndex][4]);
                printf("Occult Blood: %d\n", testValuesarr[assignedIndex][5]);
                break;

            default:
                printf("Invalid test type.\n");
                break;
            }
        }
        else
        {
            printf("Error: Test results not found for %s.\n", patients[patientIndex].name);
        }
    }
}
