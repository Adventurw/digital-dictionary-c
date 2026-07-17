#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct dictionary
{
    struct dictionary *left;
    struct dictionary *right;

    char word[50];
    char meaning[200];
    char synonym[100];
} *Root = NULL;

typedef struct dictionary d;

int check(char a[], char b[]);
void Search();
void Insert_word(d *temp);
void View(d *ptr);

int check(char a[], char b[])
{
    int result = strcmp(a, b);

    if(result > 0)
        return 1;
    else if(result < 0)
        return -1;

    return 0;
}

void Insert_word(d *temp)
{
    d *ptr, *parent;

    if (Root == NULL)
    {
        Root = temp;
        printf("\nWord inserted successfully!\n");
        return;
    }

    ptr = Root;
    parent = NULL;

    while (ptr != NULL)
    {
        parent = ptr;

        if (check(temp->word, ptr->word) < 0)
        {
            ptr = ptr->left;
        }
        else if (check(temp->word, ptr->word) > 0)
        {
            ptr = ptr->right;
        }
        else
        {
            printf("\nWord already exists in the dictionary!\n");
            free(temp);
            return;
        }
    }

    if (check(temp->word, parent->word) < 0)
    {
        parent->left = temp;
    }
    else
    {
        parent->right = temp;
    }

    printf("\nWord inserted successfully!\n");
}
void Search()
{
    char w[50];
    d *ptr;

    if (Root == NULL)
    {
        printf("\nDictionary is empty!\n");
        return;
    }

    printf("\nEnter word to search: ");
    scanf(" %49s", w);

    ptr = Root;

    while (ptr != NULL)
    {
        if (check(w, ptr->word) < 0)
        {
            ptr = ptr->left;
        }
        else if (check(w, ptr->word) > 0)
        {
            ptr = ptr->right;
        }
        else
        {
            printf("\n=========================================\n");
            printf("Word     : %s\n", ptr->word);
            printf("Meaning  : %s\n", ptr->meaning);
            printf("Synonym  : %s\n", ptr->synonym);
            printf("=========================================\n");

            return;
        }
    }

    printf("\nWord \"%s\" was not found in the dictionary.\n", w);
}
void View(d *ptr)
{
    if (ptr == NULL)
        return;

    View(ptr->left);

    printf("%-20s %-35s %-20s\n",
           ptr->word,
           ptr->meaning,
           ptr->synonym);

    View(ptr->right);
}
int main()
{
    int ch = 0;
    d *temp;

    while (1)
    {
        printf("\n=====================================\n");
        printf("        DIGITAL DICTIONARY\n");
        printf("=====================================\n");
        printf("1. Search Word\n");
        printf("2. Insert Word\n");
        printf("3. View Dictionary\n");
        printf("4. Exit\n");
        printf("-------------------------------------\n");
        printf("Enter your choice: ");

        scanf("%d", &ch);

        switch (ch)
        {
            case 1:

                printf("\n========== SEARCH ==========\n");
                Search();
                break;

            case 2:

                temp = (d *)malloc(sizeof(d));

                if (temp == NULL)
                {
                    printf("\nMemory Allocation Failed!\n");
                    break;
                }

                temp->left = NULL;
                temp->right = NULL;

                printf("\n========== INSERT NEW WORD ==========\n");

                printf("Enter Word: ");
                scanf(" %49s", temp->word);

                getchar();      // remove newline left by scanf

                printf("Enter Meaning: ");
                fgets(temp->meaning, sizeof(temp->meaning), stdin);

                temp->meaning[strcspn(temp->meaning, "\n")] = '\0';

                printf("Enter Synonym: ");
                fgets(temp->synonym, sizeof(temp->synonym), stdin);

                temp->synonym[strcspn(temp->synonym, "\n")] = '\0';

                Insert_word(temp);

                break;

            case 3:

                printf("\n===============================================================\n");
                printf("                     DIGITAL DICTIONARY\n");
                printf("===============================================================\n");

                if (Root == NULL)
                {
                    printf("\nDictionary is empty!\n");
                }
                else
                {
                    printf("%-20s %-35s %-20s\n",
                           "Word",
                           "Meaning",
                           "Synonym");

                    printf("--------------------------------------------------------------------------\n");

                    View(Root);
                }

                break;

            case 4:

                printf("\n=====================================\n");
                printf("Thank you for using Digital Dictionary!\n");
                printf("=====================================\n");

                return 0;

            default:

                printf("\nInvalid choice! Please try again.\n");
        }
    }

    return 0;
}