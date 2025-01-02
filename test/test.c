#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 1024
#define DELIMITER "|"
#define PRNTR_DESC_INDEX 5 // Index for PRNTR_DESC

typedef struct
{
    char name[100];
    int count;
} Company;

int compare(const void *a, const void *b)
{
    Company *companyA = (Company *) a;
    Company *companyB = (Company *) b;

    // Sort by count in descending order
    if (companyB->count != companyA->count)
    {
        return companyB->count - companyA->count;
    }

    // If counts are equal, sort alphabetically
    return strcmp(companyA->name, companyB->name);
}

int main()
{
    FILE *file = fopen("input.txt", "r");
    if (file == NULL)
    {
        printf("Error: Could not open file.\n");
        return 1;
    }

    char line[MAX_LINE_LENGTH];
    char *token;
    int initialSize = 10; // Initial size for dynamic allocation
    Company *companies = malloc(sizeof(Company) * initialSize);
    int companyCount = 0;

    // Read the header line
    if (fgets(line, MAX_LINE_LENGTH, file) != NULL)
    {
        // Skip the header line
    }

    // Process each line in the file
    while (fgets(line, MAX_LINE_LENGTH, file) != NULL)
    {
        int column = 0;
        token = strtok(line, DELIMITER);

        while (token != NULL)
        {
            if (column == PRNTR_DESC_INDEX)
            {
                int found = 0;

                // Check if the company is already in the list
                for (int i = 0; i < companyCount; i++)
                {
                    if (strcmp(companies[i].name, token) == 0)
                    {
                        companies[i].count++;
                        found = 1;
                        break;
                    }
                }

                // If not found, add a new company
                if (!found)
                {
                    if (companyCount >= initialSize)
                    {
                        // Double the size of the array if it's full
                        initialSize *= 2;
                        companies = realloc(companies, sizeof(Company) * initialSize);
                        if (companies == NULL)
                        {
                            printf("Error: Memory allocation failed.\n");
                            fclose(file);
                            return 1;
                        }
                    }
                    strcpy(companies[companyCount].name, token);
                    companies[companyCount].count = 1;
                    companyCount++;
                }

                break;
            }
            token = strtok(NULL, DELIMITER);
            column++;
        }
    }

    fclose(file);

    // Sort the companies array
    qsort(companies, companyCount, sizeof(Company), compare);

    // Print the top 5 companies
    printf("Top 5 companies:\n");
    for (int i = 0; i < 5 && i < companyCount; i++)
    {
        printf("%s: %d\n", companies[i].name, companies[i].count);
    }

    // Free the dynamically allocated memory
    free(companies);

    return 0;
}
