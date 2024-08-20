#include <stdio.h>
#include <string.h>

#define TOTAL_SLOTS 5
#define MAX_PATIENTS 100

int Authentication();
int find_patient(int id);
void add_patient();
void edit_patient();
void display_slots();
void reserve_slot();
void cancel_reservation();
void admin_mode();
void view_patient_record( int id);
void view_todays_reservations(int slot[], int patient_ids[]);
void user_mode();

int password = 1234;
int pass;
int patient_count = 0;
int IDs[MAX_PATIENTS];
char names[MAX_PATIENTS][50];
int ages[MAX_PATIENTS];
char genders[MAX_PATIENTS];
int slot[TOTAL_SLOTS] = {1, 1, 1, 1, 1}; // 1 means available, 0 means reserved.
int patient_ids[TOTAL_SLOTS] = {0};


int main()
{
	while(1){
    int mode;
    printf("Welcome to the Clinic Management System\n");
    printf("Please choose mode:\n");
    printf("1. Admin Mode\n");
    printf("2. User Mode\n");
    printf("Please enter your choice: ");
    scanf("%d", &mode);
	

    switch (mode)
    {
        case 1:
            admin_mode();
            break;
        case 2: // user mode
            user_mode();
            break;
        default:
            printf("Invalid mode selected. Exiting...\n");
            break;
    }

   
}
    return 0;
}
int Authentication()
{
    printf("Please enter the password: ");
    scanf("%d", &pass);

    if (pass != password)
    {
        for (int i = 0; i < 2; i++)
        {
            printf("Wrong password. Try again: ");
            scanf("%d", &pass);

            if (pass == password)
            {
                return 1;
            }
        }

        printf("Sorry, system is closed. Exiting...\n");
        return 0;
    }

    return 1;
}

int find_patient(int id)
{
    for (int i = 0; i < patient_count; i++)
    {
        if (IDs[i] == id)
        {
            return i;
        }
    }

    return -1; // ID not found
}

void add_patient()
{
    int id;

    if (patient_count >= MAX_PATIENTS)
    {
        printf("Cannot add more patients.\n");
        return;
    }

    printf("Please enter patient ID: ");
    scanf("%d", &id);

    if (find_patient(id) != -1)
    {
        printf("The ID already exists.\n");
        return;
    }

    printf("Please enter patient name: ");
    scanf("%49s", names[patient_count]); // %49s to prevent buffer overflow

    printf("Please enter patient age: ");
    scanf("%d", &ages[patient_count]);

    printf("Please enter patient gender (m/f): ");
    scanf(" %c", &genders[patient_count]); // space before %c to consume any leftover whitespace

    IDs[patient_count] = id;
    patient_count++;
    printf("Patient record added successfully.\n");
}

void edit_patient()
{
    int id;
    printf("Please enter the ID of the patient to edit: ");
    scanf("%d", &id);
    int index = find_patient(id);

    if (index == -1)
    {
        printf("Incorrect ID.\n");
        return;
    }

    printf("Editing patient record for ID %d\n", id);
    printf("Please enter new patient name: ");
    scanf("%49s", names[index]);

    printf("Please enter new patient age: ");
    scanf("%d", &ages[index]);

    printf("Please enter new patient gender: ");
    scanf(" %c", &genders[index]);

    printf("Patient record updated successfully.\n");
}

void display_slots()
{
    for (int i = 0; i < TOTAL_SLOTS; i++)
    {
        if (slot[i] == 1)
            printf("Slot %d: from %.1fpm to %.1fpm (available)\n", i + 1, 2.0 + i, 2.0 + i + 0.5);
        else
            printf("Slot %d: from %.1fpm to %.1fpm (reserved for patient ID %d)\n", i + 1, 2.0 + i, 2.0 + i + 0.5, patient_ids[i]);
    }
}

void reserve_slot()
{
    int slot_num, id;
    display_slots();
    printf("Please enter the patient ID to reserve a slot: ");
    scanf("%d", &id);

    printf("Please enter the slot number (1 to 5): ");
    scanf("%d", &slot_num);

    if (slot_num < 1 || slot_num > TOTAL_SLOTS)
    {
        printf("Invalid slot number.\n");
        return;
    }

    if (slot[slot_num - 1] == 0)
    {
        printf("The slot is already reserved.\n");
        return;
    }

    slot[slot_num - 1] = 0;
    patient_ids[slot_num - 1] = id; // store patient id
    printf("Slot %d has been reserved for patient ID %d.\n", slot_num, id);
}

void cancel_reservation()
{
    int id;
    printf("Please enter the patient ID to cancel the reservation: ");
    scanf("%d", &id);

    for (int i = 0; i < TOTAL_SLOTS; i++)
    {
        if (slot[i] == 0 && patient_ids[i] == id)
        {
            slot[i] = 1;
            patient_ids[i] = 0;
            printf("The reservation for patient ID %d has been cancelled. Slot %d is now available.\n", id, i + 1);
            return;
        }
    }

    printf("No reservation found for patient ID %d.\n", id);
}

void admin_mode()
{
    int choice;
	int exit_flag=0;

    for (int i = 3; i > 0; i--)
    {
		if(exit_flag==1)
			break;
        if (Authentication()&&exit_flag==0)

        {
            while (1)
            {
				if(exit_flag==1)
					break;
                printf("\nAdmin Menu:\n");
                printf("1. Add New Patient\n");
                printf("2. Edit Patient Record\n");
                printf("3. Reserve a Slot\n");
                printf("4. Cancel Reservation\n");
                printf("5. Exit\n");
                printf("Please enter your choice: ");
                scanf("%d", &choice);

                switch (choice)
                {
                    case 1:
                        add_patient();
                        break;
                    case 2:
                        edit_patient();
                        break;
                    case 3:
                        reserve_slot();
                        break;
                    case 4:
                        cancel_reservation();
                        break;
                    case 5:
                        printf("Exiting admin mode...\n");
						exit_flag=1;
                        break; // Exit the while loop and return from admin_mode
                    default:
                        printf("Invalid choice. Please try again.\n");
                        break;
                }
            }
        }
        else
        {
            printf("System is closed due to multiple failed login attempts.\n");
            return;
        }
    }
}

void view_patient_record(int id)
{
	int index=find_patient(id);
	if(index==-1)
	{
	printf("No record found for patient ID %d.\n", id);	
	}
    
            printf("Patient ID: %d\n", id);
            printf("Name: %s\n", names[index]);
            printf("Age: %d\n", ages[index]);
            printf("Gender: %c\n", genders[index]);
          
       
}

void view_todays_reservations(int slot[], int patient_ids[])
{
    printf("Today's Reservations:\n");
    for (int i = 0; i < TOTAL_SLOTS; i++)
    {
        if (slot[i] == 0) // The slot is reserved
        {
            printf("Slot %d: %.1fpm to %.1fpm, Reserved by Patient ID %d\n",
                   i + 1, 2.0 + i, 2.0 + i + 0.5, patient_ids[i]);
        }
    }
}

void user_mode()
{
    int choice, id;

    while (1)
    {
        printf("\nUser Menu:\n");
        printf("1. View Patient Record\n");
        printf("2. View Today's Reservations\n");
        printf("3. Exit\n");
        printf("Please enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                printf("Please enter the Patient ID: ");
                scanf("%d", &id);
                view_patient_record(id);
                break;
            case 2:
                view_todays_reservations(slot, patient_ids);
                break;
            case 3:
                printf("Exiting user mode...\n");
                return; 
            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
    }
}
