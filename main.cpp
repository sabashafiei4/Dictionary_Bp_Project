#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>

#pragma warning(disable : 4996)

struct info
{
    char fname[20];
    char lname[20];
    char user_name[20];
    char password[20];
    char phone[20];
    char email[20];
};

struct NodeIn
{
    struct info data;
    struct NodeIn *next;
};
struct Words
{
    char Word[20];
    char Meaning[20][20];
};
struct NodeWo
{
    struct Words data;
    struct NodeWo *next;
};

void insert(struct NodeWo **head, Words data)
{
    NodeWo *newNode = (NodeWo *)malloc(sizeof(NodeWo));
    strcpy(newNode->data.Word, data.Word);
    for (int i = 0;; i++)
    {
        if (strcmp(data.Meaning[i], "") == 0)
        {
            for (; i <= 19; i++)
            {
                strcpy(newNode->data.Meaning[i], "");
            }
            break;
        }
        strcpy(newNode->data.Meaning[i], data.Meaning[i]);
    }
    if (*head == NULL)
    {
        *head = newNode;
        (*head)->next = NULL;
        return;
    }
    newNode->data = data;
    newNode->next = *head;
    *head = newNode;
}
void deleteNode(struct NodeWo **head, Words data)
{
    if (*head == NULL)
    {
        printf("there is no words\n");
        return;
    }
    struct NodeWo *temp = *head;
    struct NodeWo *prev = NULL;

    if (strcmp(temp->data.Word, data.Word) == 0)
    {
        *head = temp->next;
        free(temp);
        return;
    }

    while (temp != NULL && strcmp(temp->data.Word, data.Word) != 0)
    {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL)
    {
        printf("This word is not in dictionary!!\n");
        return;
    }

    prev->next = temp->next;
    free(temp);
}

//////////////////////////////////////////////////////////////////////
void make_linklist(struct NodeWo **head, const char *Filename)
{
    char p[200];
    Words newword;
    FILE *fp;
    fp = fopen(Filename, "r+");
    if (fp == NULL)
    {
        fp = fopen(Filename, "w+");
        if (fp == NULL)
        {
            printf("Error opening file\n");
            return;
        }
        fprintf(fp, "EOF");
        fclose(fp);
        return;
    }
    while (true)
    {
        fgets(p, sizeof(p), fp);
        if (strcmp(p, "EOF") == 0)
        {
            break;
        }
        char W[20];
        int i = 0;
        for (;; i++)
        {
            if (p[i] == ':')
            {
                newword.Word[i] = '\0';
                i++;
                break;
            }
            newword.Word[i] = p[i];
        }
        int endline = 0;
        for (int j = 0;; j++)
        {
            for (int k = 0;; k++, i++)
            {

                if (p[i] == ',')
                {
                    newword.Meaning[j][k] = '\0';
                    i++;
                    break;
                }
                if (p[i] == '\n')
                {
                    newword.Meaning[j][k] = '\0';
                    j++;
                    endline = 1;
                    break;
                }
                newword.Meaning[j][k] = p[i];
            }
            if (endline == 1)
            {
                for (; j <= 19; j++)
                {
                    strcpy(newword.Meaning[j], "");
                }
                break;
            }
        }
        insert(head, newword);
    }
}
void save_to_file(struct NodeWo **head, const char *Filename)
{
    FILE *fp = fopen(Filename, "w");
    if (fp == NULL)
    {
        printf("Error opening file\n");
        return;
    }
    struct NodeWo *temp = *head;
    while (*head != NULL)
    {
        temp = *head;
        *head = (*head)->next;
        fprintf(fp, "%s:", temp->data.Word);
        for (int i = 0; i < 20; i++)
        {
            if (strcmp(temp->data.Meaning[i], "") != 0)
            {
                fprintf(fp, "%s", temp->data.Meaning[i]);
                if (i < 9 && strcmp(temp->data.Meaning[i + 1], "") != 0)
                {
                    fprintf(fp, ",");
                }
            }
        }
        fprintf(fp, "\n");
        free(temp);
    }
    // fprintf(fp, "\n");
    fprintf(fp, "EOF");
    fclose(fp);
}
//////////////////////////////////////////////////////////////////////
void removeword(struct NodeWo **head, char *deleteWord)
{

    struct Words remove;
    strcpy(remove.Word, deleteWord);
    deleteNode(head, remove);
}
void addword(struct NodeWo **head)
{
    Words newWord;
    printf("\nEnter the new word to add: ");
    scanf("%s", newWord.Word);
    printf("\nEnter the meaning of the word: \n");
    printf("\n((Enter 0 to exit ))");
    for (int i = 0;; i++)
    {
        if (i > 9)
        {
            break;
        }
        char input[20];
        scanf("%s", input);
        if (strcmp(input, "0") == 0)
        {
            for (;; i++)
            {
                if (i == 20)
                {
                    break;
                }
                else
                {
                    strcpy(newWord.Meaning[i], "");
                }
            }
            break;
        }
        else
        {
            strcpy(newWord.Meaning[i], input);
        }
    }
    insert(head, newWord);
    printf("\nWord added successfully!\n");
}
void Edit_Word(struct NodeWo **head, char *editword)
{

    struct NodeWo *temp = *head;
    for (; temp != NULL;)
    {
        if (strcmp(temp->data.Word, editword) == 0)
        {
            break;
        }
        temp = temp->next;
    }
    if (temp == NULL)
    {
        printf("This word not found!!\n");
        return;
    }

    for (;;)
    {
        system("cls||clear");
        printf("Word: %s", temp->data.Word);
        printf("\nMeanings :\n");
        for (int i = 0;; i++)
        {
            if (strcmp(temp->data.Meaning[i], "") == 0)
            {
                break;
            }
            printf("%d- %s\n", i + 1, temp->data.Meaning[i]);
        }
        printf("\n------------------------------------------\n");
        printf("\n1- Add a meaning\n");
        printf("2- Edit an existing meanings\n");
        printf("3- Remove a specific meaning\n");
        printf("4- Back\n");
        printf("\nEnter your choice: ");
        int choice;
        scanf("%d", &choice);

        if (choice == 1)
        {
            printf("Enter the new Meaning: ");
            for (int i = 0;; i++)
            {
                if (i == 20)
                {
                    printf("You can't add Meaning to %s word\n", temp->data.Word);
                    getchar();
                    break;
                }
                if (strcmp(temp->data.Meaning[i], "") == 0)
                {
                    scanf("%s", temp->data.Meaning[i]);
                    break;
                }
            }
        }
        else if (choice == 2)
        {
            printf("Enter the meaning number to edit: ");
            int subchoice;
            scanf("%d", &subchoice);
            int i = 0;
            for (;; i++)
            {
                if (strcmp(temp->data.Meaning[i], "") == 0)
                {
                    i--;
                    break;
                }
            }
            if (subchoice - 1 > i || subchoice <= 0)
            {
                printf("\nWrong Meaning number input!!\n");
                getchar();
                getchar();
                continue;
            }
            printf("Enter the new meaning to edit: ");
            scanf("%s", temp->data.Meaning[subchoice - 1]);
        }
        else if (choice == 3)
        {
            printf("Enter the number of the meaning to remove: ");
            int index;
            scanf("%d", &index);
            int i = 0;
            for (;; i++)
            {
                if (strcmp(temp->data.Meaning[i], "") == 0)
                {
                    i--;
                    break;
                }
            }
            if (index - 1 > i || index <= 0)
            {
                printf("\nWrong Meaning number input!!\n");
                getchar();
                getchar();
                continue;
            }
            for (int j = index - 1; j < 9; j++)
            {
                strcpy(temp->data.Meaning[j], temp->data.Meaning[j + 1]);
            }
            strcpy(temp->data.Meaning[9], "");
        }
        else if (choice == 4)
        {
            return;
        }
        else
        {
            printf("Invalid choice!\n");
        }
    }
}

void show_all_word(struct NodeWo **head)
{
    int count = 0;
    struct NodeWo Sorted[50];
    struct NodeWo *temp = *head;
    /*for (; temp;) {






    }*/
    system("cls||clear");
    printf("--------------------------------\n");
    for (; temp != NULL;)
    {
        printf("Word : %s\n", temp->data.Word);
        for (int i = 0;; i++)
        {
            if (strcmp(temp->data.Meaning[i], "") == 0)
            {
                break;
            }
            printf("%d- %s\n", i + 1, temp->data.Meaning[i]);
        }
        printf("--------------------------------\n");
        temp = temp->next;
    }
    getchar();
    getchar();
}

void suggensted_words(struct NodeWo **head)
{
    system("cls||clear");
    struct NodeWo *SuggestedHead = NULL;
    make_linklist(&SuggestedHead, "SuggestedWords.txt");
    if (SuggestedHead == NULL)
    {
        printf("\n--There is no word to suggest--\n");
        getchar();
        getchar();
        return;
    }
    struct NodeWo *temp = SuggestedHead;

    for (; temp != NULL;)
    {
        system("cls||clear");
        printf("\t\t\t\t<<SUGGESTED Words>>\t\t\t\t\n-----------------------------------------\n");
        printf("|Enter + to add in dictionary|\n|Enter - to reject suggestion|\n-----------------------------------------\n");
        printf("Word : %s\n", temp->data.Word);
        for (int i = 0;; i++)
        {
            if (strcmp(temp->data.Meaning[i], "") == 0)
            {
                break;
            }
            printf("%d- %s\n", i + 1, temp->data.Meaning[i]);
        }
        printf("--------------------------------\n");
        for (;;)
        {
            char choose;
            scanf("%c", &choose);
            if (choose == '+')
            {
                insert(head, temp->data);
                deleteNode(&SuggestedHead, temp->data);
                break;
            }
            else if (choose == '-')
            {
                deleteNode(&SuggestedHead, temp->data);
                break;
            }
            else
            {
                printf("\nWrong input!!\n");
                getchar();
                getchar();
            }
        }

        temp = temp->next;
    }
    save_to_file(&SuggestedHead, "SuggestedWords.txt");
    getchar();
    getchar();
}

void read_from_file(struct NodeWo **head, char *filename)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("File not found or could not be opened.\n");
        return;
    }
    char trash[200];
    fgets(trash, sizeof(trash), file);
    while (true)
    {
        char p[200];
        fgets(p, sizeof(p), file);
        if (strcmp(p, "EOF") == 0)
        {
            break;
        }
        struct Words new_Word;
        int i = 0;
        for (;; i++)
        {
            if (p[i] == ':')
            {
                i++;
                break;
            }
            if (p[i] == '\n')
            {
                printf("---Invalid format in file---\n");
                getch();
                return;
            }
        }
        for (int j = 0;; j++, i++)
        {
            if (p[i] == ',')
            {
                new_Word.Word[j] = '\0';
                i++;
                break;
            }
            new_Word.Word[j] = p[i];
        }
        for (;; i++)
        {
            if (p[i] == ':')
            {
                i++;
                break;
            }
            if (p[i] == '\n')
            {
                printf("---Invalid format in file---\n");
                getch();
                return;
            }
        }
        int endline = 0;
        for (int j = 0;; j++)
        {
            for (int k = 0;; k++, i++)
            {

                if (p[i] == '-')
                {
                    new_Word.Meaning[j][k] = '\0';
                    i++;
                    break;
                }
                if (p[i] == '\n')
                {

                    new_Word.Meaning[j][k] = '\0';
                    j++;
                    endline = 1;
                    break;
                }
                new_Word.Meaning[j][k] = p[i];
            }
            if (endline == 1)
            {
                for (; j <= 19; j++)
                {
                    strcpy(new_Word.Meaning[j], "");
                }
                break;
            }
        }
        insert(head, new_Word);
    }
    fclose(file);
    printf("Dictionary loaded from file successfully.\n");
}
void management()
{
    struct NodeWo *head = NULL;
    make_linklist(&head, "dictionary.txt");
    for (;;)
    {

        char input;
        system("cls||clear");
        printf("\nManager Account");
        printf("\n1. Add Word");
        printf("\n2. Edit Word");
        printf("\n3. Remove word");
        printf("\n4. Read From File");
        printf("\n5. Suggested Word");
        printf("\n6. Show All Word");
        printf("\n7. Back");
        printf("\nPlease enter your choice: ");
        input = getch();

        switch (input)
        {
        case '1':
            show_all_word(&head);
            addword(&head);
            break;
        case '2':
            show_all_word(&head);
            printf("\nEnter the word to edit: ");
            char editword[20];
            scanf("%s", editword);
            Edit_Word(&head, editword);
            break;
        case '3':
            show_all_word(&head);
            printf("\nEnter the word to remove: ");
            char deleteWord[20];
            scanf("%s", deleteWord);
            removeword(&head, deleteWord);
            break;
        case '4':
            printf("\nEnter the file address to read: ");
            char filename[20];
            scanf("%s", filename);
            read_from_file(&head, filename);
            break;
        case '5':
            suggensted_words(&head);
            break;
        case '6':
            show_all_word(&head);
            break;
        case '7':
            save_to_file(&head, "dictionary.txt");
            return;
        default:
            printf("Invalid choice!\n");
        }
    }
}
//////////////////////////////////////////////////////////////////////
void search(struct NodeWo **head, struct NodeWo **Litnerhead, struct NodeWo **NewWordshead, struct NodeWo **SuggestedHead)
{
    char SearchWord[50];
    for (int t = 0; t < 50; t++)
    {
        SearchWord[t] = '\0';
    }
    getchar();
    int i = 0;
    bool found = false;
    for (;;)
    {

        system("cls||clear");
        printf("\t\t\t\t#@Search@#\t\t\t\t\n-----------------------------------------\n");
        printf("((Press Enter key to search the word))\n\n");

        printf("Enter the word to search: %s", SearchWord);
        char c;
        c = getch();
        if (c == '\r')
        {
            break;
        }
        SearchWord[i] = c;
        SearchWord[i + 1] = '\0';
        printf("\nEnter the word to search: %s", SearchWord);
        i++;
        struct NodeWo *temp = *head;
        while (temp)
        {
            if (strcmp(temp->data.Word, SearchWord) == 0)
            {
                found = true;
                break;
            }
            temp = temp->next;
        }
        if (found)
        {
            printf("\n--------------------------------\n");
            printf("Word : %s\n", temp->data.Word);
            for (int i = 0;; i++)
            {
                if (strcmp(temp->data.Meaning[i], "") == 0)
                {
                    break;
                }
                printf("%d- %s\n", i + 1, temp->data.Meaning[i]);
            }
            printf("--------------------------------\n");
            printf("\n-((Enter +  to add in your Litner Box))-\n");
            printf("\n-((Enter =  to add meaning in dictionary))-\n");
            printf("\n-((Enter any key  exit))-\n");
            char choose;
            choose = getch();
            switch (choose)
            {

            case '+':
                insert(Litnerhead, temp->data);
                insert(NewWordshead, temp->data);
                printf("\n-Word added to your litner-\n");
                getch();
                return;
            case '=':
                Edit_Word(head, temp->data.Word);
                return;

            default:
                return;
            }
        }
    }
    printf("\n-----------------------------------------\n");
    printf("Word not found!!\n");
    printf("-----------------------------------------\n");
    printf("Similar Words : \n");
    char similar[50][50];
    int j = 0;
    struct NodeWo *search = *head;
    for (; search;)
    {
        int diff_count = 0;
        int a = strlen(SearchWord);
        int b = strlen(search->data.Word);
        if ((a - b) < 2 && (a - b) > -2)
        {
            for (int i = 0; SearchWord[i] != '\0' && search->data.Word[i] != '\0'; i++)
            {
                if (SearchWord[i] != search->data.Word[i])
                {
                    diff_count++;
                }
            }
            if (diff_count < 2)
            {
                strcpy(similar[j], search->data.Word);
                j++;
            }
        }

        search = search->next;
    }
    for (int k = 0; k < j; k++)
    {
        printf("%d- %s\n", k + 1, similar[k]);
    }
    printf("Do you want to suggest this word to management?(y/n)\n");
    char choose;
    choose = getchar();
    switch (choose)
    {

    case 'y':
        struct Words sugg;
        strcpy(sugg.Word, SearchWord);
        for (int i = 0; i < 19; i++)
        {
            strcpy(sugg.Meaning[i], "");
        }
        insert(SuggestedHead, sugg);
        printf("Word suggested to manager\n");
        break;
    case 'n':
        break;
    default:
        printf("Wrong input\n");
    }
    getch();
}
void New_Words(struct NodeWo **head, struct NodeWo **Litnerhead, struct NodeWo **NewWordshead, struct NodeWo **Reviewhead)
{
    system("cls||clear");
    printf("\t\t\t\t<<New Word>>\t\t\t\t\n-----------------------------------------\n");
    struct NodeWo *temp = *NewWordshead;
    if (temp == NULL)
    {
        printf("\nThere is not any new Word!!\n\n");
        getch();
        return;
    }
    bool Posht_Roo = false;
    bool next = false;
    for (;;)
    {
        system("cls||clear");
        printf("\t\t\t\t<<New Word>>\t\t\t\t\n-----------------------------------------\n");
        if (next)
        {
            next = false;
            Posht_Roo = false;
            insert(Reviewhead, temp->data);
            struct NodeWo *Del = temp;
            temp = temp->next;
            deleteNode(NewWordshead, Del->data);
            continue;
        }
        if (temp == NULL)
        {
            printf("\nNew words ended");
            getch();
            return;
        }
        if (!Posht_Roo)
        {
            printf("Word : %s", temp->data.Word);
            printf("\n-----------------------------------------\n");
        }
        else
        {
            for (int i = 0;; i++)
            {
                if (strcmp(temp->data.Meaning[i], "") == 0)
                {
                    break;
                }
                printf("%d- %s\n", i + 1, temp->data.Meaning[i]);
            }
            printf("--------------------------------\n");
        }
        printf("((Enter space to turn card over))\n");
        printf("Press Enter button to see next card\n");
        printf("((Enter D to delete word from Lintner))\n");
        printf("((Enter E to Edit word))\n");
        char choose;
        choose = getch();
        if (choose == '\r')
        {
            next = true;
        }
        else if (choose == ' ')
        {
            Posht_Roo = !Posht_Roo;
        }
        else if (choose == 'E')
        {
            // Edit_Word(head,temp->data.Word);
        }
        else if (choose == 'D')
        {
            removeword(Litnerhead, temp->data.Word);
        }
        else
        {
            printf("Wrong input!!\n");
            getch();
        }
    }
}
void Review(struct NodeWo **head, struct NodeWo **Litnerhead, struct NodeWo **Reviewhead, struct NodeWo **Consolidationhead)
{
    system("cls||clear");
    printf("\t\t\t\t<<Review>>\t\t\t\t\n-----------------------------------------\n");
    struct NodeWo *temp = *Reviewhead;
    if (temp == NULL)
    {
        printf("\nThere is not any Words!!\n\n");
        getch();
        return;
    }
    bool Posht_Roo = false;
    bool next = false;
    for (;;)
    {
        system("cls||clear");
        printf("\t\t\t\t<<Review>>\t\t\t\t\n-----------------------------------------\n");
        if (next)
        {
            next = false;
            Posht_Roo = false;
            temp = temp->next;
            continue;
        }
        if (temp == NULL)
        {
            printf("\nReview ended");
            getch();
            return;
        }
        if (!Posht_Roo)
        {
            printf("Word : %s", temp->data.Word);
            printf("\n-----------------------------------------\n");
        }
        else
        {
            for (int i = 0;; i++)
            {
                if (strcmp(temp->data.Meaning[i], "") == 0)
                {
                    break;
                }
                printf("%d- %s\n", i + 1, temp->data.Meaning[i]);
            }
            printf("--------------------------------\n");
        }
        printf("1- I knew\n");
        printf("2- Ididn't know\n");
        printf("((Enter space to turn card over))\n");
        printf("((Press Enter button to see next card))\n");
        printf("((Enter D to delete word from Lintner))\n");
        printf("((Enter E to Edit word))\n");

        char choose;
        choose = getch();
        if (choose == '\r')
        {
            next = true;
        }
        else if (choose == ' ')
        {
            Posht_Roo = !Posht_Roo;
        }
        else if (choose == '1')
        {
            insert(Consolidationhead, temp->data);
            struct NodeWo *Del = temp;
            temp = temp->next;
            deleteNode(Reviewhead, Del->data);
            printf("Word moved to Consolidation box.\n");
            getch();
            continue;
        }
        else if (choose == '2')
        {
            printf("Word remains in review box.\n");
            getch();
            next = true;
        }
        else if (choose == 'E')
        {
            Edit_Word(head, temp->data.Word);
        }
        else if (choose == 'D')
        {
            removeword(Litnerhead, temp->data.Word);
        }
        else
        {
            printf("Wrong input!!\n");
            getch();
        }
    }
}
void Consolidation(struct NodeWo **head, struct NodeWo **Litnerhead, struct NodeWo **Reviewhead, struct NodeWo **Consolidationhead, struct NodeWo **Learnedhead)
{
    system("cls||clear");
    printf("\t\t\t\t<<Consolidation>>\t\t\t\t\n-----------------------------------------\n");
    struct NodeWo *temp = *Consolidationhead;
    if (temp == NULL)
    {
        printf("\nThere is not any Words!!\n\n");
        getch();
        return;
    }
    bool Posht_Roo = false;
    bool next = false;
    for (;;)
    {
        system("cls||clear");
        printf("\t\t\t\t<<Consolidation>>\t\t\t\t\n-----------------------------------------\n");
        if (next)
        {
            next = false;
            Posht_Roo = false;
            temp = temp->next;
            continue;
        }
        if (temp == NULL)
        {
            printf("\n Consolidation words ended");
            getch();
            return;
        }
        if (!Posht_Roo)
        {
            printf("Word : %s", temp->data.Word);
            printf("\n-----------------------------------------\n");
        }
        else
        {
            for (int i = 0;; i++)
            {
                if (strcmp(temp->data.Meaning[i], "") == 0)
                {
                    break;
                }
                printf("%d- %s\n", i + 1, temp->data.Meaning[i]);
            }
            printf("--------------------------------\n");
        }
        printf("1- I knew\n");
        printf("2- Ididn't know\n");
        printf("((Enter space to turn card over))\n");
        printf("((Press Enter button to see next card))\n");
        printf("((Enter D to delete word from Lintner))\n");
        printf("((Enter E to Edit word))\n");

        char choose;
        choose = getch();
        if (choose == '\r')
        {
            next = true;
        }
        else if (choose == ' ')
        {
            Posht_Roo = !Posht_Roo;
        }
        else if (choose == '1')
        {
            insert(Learnedhead, temp->data);
            struct NodeWo *Del = temp;
            temp = temp->next;
            deleteNode(Consolidationhead, Del->data);
            printf("Word moved to Learned box.\n");
            getch();
            continue;
        }
        else if (choose == '2')
        {
            insert(Reviewhead, temp->data);
            struct NodeWo *Del = temp;
            temp = temp->next;
            deleteNode(Consolidationhead, Del->data);
            printf("Word moved to Review box.\n");
            getch();
            next = true;
        }
        else if (choose == 'E')
        {
            Edit_Word(head, temp->data.Word);
        }
        else if (choose == 'D')
        {
            removeword(Litnerhead, temp->data.Word);
        }
        else
        {
            printf("Wrong input!!\n");
            getch();
        }
    }
}
void Learned(struct NodeWo **head, struct NodeWo **Litnerhead, struct NodeWo **Learnedhead)
{
    system("cls||clear");
    printf("\t\t\t\t<<New Word>>\t\t\t\t\n-----------------------------------------\n");
    struct NodeWo *temp = *Learnedhead;
    if (temp == NULL)
    {
        printf("\nThere is not any new Word!!\n\n");
        getch();
        return;
    }
    bool Posht_Roo = false;
    bool next = false;
    for (;;)
    {
        system("cls||clear");
        printf("\t\t\t\t<<Learned Word>>\t\t\t\t\n-----------------------------------------\n");
        if (next)
        {
            next = false;
            Posht_Roo = false;
            temp = temp->next;
            continue;
        }
        if (temp == NULL)
        {
            printf("\nLearned words ended");
            getch();
            return;
        }
        if (!Posht_Roo)
        {
            printf("Word : %s", temp->data.Word);
            printf("\n-----------------------------------------\n");
        }
        else
        {
            for (int i = 0;; i++)
            {
                if (strcmp(temp->data.Meaning[i], "") == 0)
                {
                    break;
                }
                printf("%d- %s\n", i + 1, temp->data.Meaning[i]);
            }
            printf("--------------------------------\n");
        }
        printf("((Enter space to turn card over))\n");
        printf("Press Enter button to see next card\n");
        printf("((Enter D to delete word from Lintner))\n");
        printf("((Enter E to Edit word))\n");
        char choose;
        choose = getch();
        if (choose == '\r')
        {
            next = true;
        }
        else if (choose == ' ')
        {
            Posht_Roo = !Posht_Roo;
        }
        else if (choose == 'E')
        {
            // Edit_Word(head,temp->data.Word);
        }
        else if (choose == 'D')
        {
            removeword(Litnerhead, temp->data.Word);
        }
        else
        {
            printf("Wrong input!!\n");
            getch();
        }
    }
}
/////////
void Litner(struct NodeWo **head, struct NodeWo **Litnerhead, struct NodeWo **NewWordshead, struct NodeWo **Reviewhead, struct NodeWo **Consolidationhead, struct NodeWo **Learnedhead)
{
    for (;;)
    {
        system("cls||clear");
        printf("\t\t\t\t<<Litner>>\t\t\t\t\n-----------------------------------------\n");
        printf("1.New Words\n");
        printf("2.Review\n");
        printf("3.Consolidation\n");
        printf("4.Learned Words\n");
        printf("5.Back\n");
        char ch;
        ch = getch();
        switch (ch)
        {
        case '1':
            New_Words(head, Litnerhead, NewWordshead, Reviewhead);
            break;
        case '2':
            Review(head, Litnerhead, Reviewhead, Consolidationhead);
            break;
        case '3':
            Consolidation(head, Litnerhead, Reviewhead, Consolidationhead, Learnedhead);
            break;
        case '4':
            Learned(head, Litnerhead, Learnedhead);
            break;
        case '5':
            return;
        }
    }
}

void Test(struct NodeWo **head, struct NodeWo **Litnerhead)
{
}
void ShowInformation(struct info person)
{
    system("cls||clear");
    printf("\t\t\t\t<<Information>>\t\t\t\t\n-----------------------------------------\n");
    printf("Full-name: %s %s \nUsername : %s\nEmail addres : %s\nPhonenumber : %s\n", person.fname, person.lname, person.user_name, person.email, person.phone);
    printf("-----------------------------------------\n");
    getchar();
    getchar();
}

void edit_information(struct info *user)
{
    printf("Enter new First Name: ");
    scanf("%s", user->fname);
    printf("Enter new Last Name: ");
    scanf("%s", user->lname);
    printf("Enter new User Name: ");
    scanf("%s", user->user_name);
    printf("Enter new Password: ");
    scanf("%s", user->password);
    printf("Enter new Phone: ");
    scanf("%s", user->phone);
    printf("Enter new Email: ");
    scanf("%s", user->email);

    FILE *fp;
    struct info users[100];
    int c = 0;
    int found = 0;

    fp = fopen("USER.txt", "r");
    if (fp == NULL)
    {
        printf("Error opening file\n");
        return;
    }

    while (fscanf(fp, "%s %s %s %s %s %s", users[c].fname, users[c].lname, users[c].user_name, users[c].password, users[c].phone, users[c].email) != EOF)
    {
        if (strcmp(users[c].user_name, user->user_name) == 0)
        {

            strcpy(users[c].fname, user->fname);
            strcpy(users[c].lname, user->lname);
            strcpy(users[c].user_name, user->user_name);
            strcpy(users[c].password, user->password);
            strcpy(users[c].phone, user->phone);
            strcpy(users[c].email, user->email);
            found = 1;
        }
        c++;
    }
    fclose(fp);

    if (found)
    {
        fp = fopen("USER.txt", "w");
        if (fp == NULL)
        {
            printf("Error opening file\n");
            return;
        }

        for (int i = 0; i < c; i++)
        {
            fprintf(fp, "%s %s %s %s %s %s\n", users[i].fname, users[i].lname, users[i].user_name, users[i].password, users[i].phone, users[i].email);
        }
        fclose(fp);

        printf("Information updated successfully!\n");
    }
    else
    {
        printf("User not found!\n");
    }
}

void user(struct info person)
{

    for (;;)
    {
        struct NodeWo *head = NULL;
        make_linklist(&head, "dictionary.txt");
        struct NodeWo *SuggestedHead = NULL;
        make_linklist(&SuggestedHead, "SuggestedWords.txt");
        /////////////////////////////////////
        struct NodeWo *Litnerhead = NULL;
        char fname1[20];
        strcpy(fname1, person.user_name);
        strcat(fname1, "-Litner.txt");
        make_linklist(&Litnerhead, fname1);
        ////////////////////////////////////
        struct NodeWo *NewWordshead = NULL;
        char fname2[20];
        strcpy(fname2, person.user_name);
        strcat(fname2, "-NewWord.txt");
        make_linklist(&NewWordshead, fname2);
        ///////////////////////////////////
        struct NodeWo *Reviewhead = NULL;
        char fname3[20];
        strcpy(fname3, person.user_name);
        strcat(fname3, "-Review.txt");
        make_linklist(&Reviewhead, fname3);
        //////////////////////////////////
        struct NodeWo *Consolidationhead = NULL;
        char fname4[20];
        strcpy(fname4, person.user_name);
        strcat(fname4, "-Consolidationhead.txt");
        make_linklist(&Consolidationhead, fname4);
        ///////////////////////////////////
        struct NodeWo *Learnedhead = NULL;
        char fname5[20];
        strcpy(fname5, person.user_name);
        strcat(fname5, "-Learned.txt");
        make_linklist(&Learnedhead, fname5);
        ///////////////////////////////////
        char usr;
        system("cls||clear");
        printf("\t\t\t###User Account\n");
        printf("1.Search\n");
        printf("2.Litner\n");
        printf("3.Test\n");
        printf("4.Show Information\n");
        printf("5.Edit information\n");
        printf("6.Back\n");
        usr = getch();
        switch (usr)
        {
        case '1':
            search(&head, &Litnerhead, &NewWordshead, &SuggestedHead);
            break;

        case '2':
            Litner(&head, &Litnerhead, &NewWordshead, &Reviewhead, &Consolidationhead, &Learnedhead);
            break;
        case '3':
            Test(&head, &Litnerhead);
            break;
        case '4':
            ShowInformation(person);
            break;
        case '5':
            edit_information(&person);
            break;

        case '6':
            save_to_file(&head, "dictionary.txt");
            save_to_file(&Litnerhead, fname1);
            save_to_file(&NewWordshead, fname2);
            save_to_file(&Reviewhead, fname3);
            save_to_file(&Consolidationhead, fname4);
            save_to_file(&Learnedhead, fname5);
            save_to_file(&SuggestedHead, "SuggestedWords.txt");
            return;
        default:
            printf("\n!!Wrong input!!\n");
            getchar();
            getchar();
            continue;
        }
        save_to_file(&head, "dictionary.txt");
        save_to_file(&Litnerhead, fname1);
        save_to_file(&NewWordshead, fname2);
        save_to_file(&Reviewhead, fname3);
        save_to_file(&Consolidationhead, fname4);
        save_to_file(&Learnedhead, fname5);
        save_to_file(&SuggestedHead, "SuggestedWords.txt");
    }
}
//////////////////////////////////////////////////////////////////////
void sign_in()
{
    int i = 0;
    struct info vrodi;
    struct info pers;
    FILE *fp;

    fp = fopen("USER.txt", "r+");
    if (fp == NULL)
    {
        fp = fopen("USER.txt", "w+");
    }
    if (fp == NULL)
    {
        printf("Error opening file\n");
        return;
    }

    printf("ENTER YOUR USER_NAME: ");
    scanf("%s", vrodi.user_name);
    printf("ENTER YOUR PASSWORD: ");
    while (1)
    {
        char ch = getch();
        if (ch == 13)
        {
            vrodi.password[i] = '\0';
            break;
        }
        else if (ch == 8)
        {
            if (i > 0)
            {
                i--;
                printf("\b \b");
            }
        }
        else
        {
            vrodi.password[i] = ch;
            i++;
            printf("*");
        }
    }

    int found = 0;
    if (strcmp(vrodi.user_name, "admin") == 0 && strcmp(vrodi.password, "admin") == 0)
    {
        management();
        fclose(fp);
        return;
    }

    while (fscanf(fp, "%s %s %s %s %s %s", pers.fname, pers.lname, pers.user_name, pers.password, pers.phone, pers.email) != EOF)
    {
        if (strcmp(pers.user_name, vrodi.user_name) == 0 && strcmp(pers.password, vrodi.password) == 0)
        {
            printf("\nYOUR INFORMATION IS CORRECT :)\n");
            user(pers);
            found = 1;
            break;
        }
    }

    if (!found)
    {
        printf("\nYOUR INFORMATION IS WRONG OR YOU DON'T HAVE AN ACCOUNT IN THIS APP!\n");
    }

    fclose(fp);
}
void sign_up()
{
    struct info p;
    int i = 0;
    FILE *fp;
    fp = fopen("USER.txt", "a+");

    printf("ENTER YOUR NAME: ");
    scanf("%s", p.fname);
    printf("ENTER YOUR LAST NAME: ");
    scanf("%s", p.lname);
    printf("ENTER YOUR USER_NAME: ");
    scanf("%s", p.user_name);
    printf("ENTER YOUR PASSWORD: ");
    while (1)
    {
        char ch = getch();

        if (ch == 13)
        {
            p.password[i] = '\0';
            break;
        }
        else if (ch == 8)
        {
            if (i > 0)
            {
                i--;
                printf("\b \b");
            }
        }
        else
        {
            p.password[i] = ch;
            i++;
            printf("*");
        }
    }

    printf("\nENTER YOUR PHONE: ");
    scanf("%s", p.phone);
    printf("ENTER YOUR EMAIL: ");
    scanf("%s", p.email);
    fprintf(fp, "%s %s %s %s %s %s\n", p.fname, p.lname, p.user_name, p.password, p.phone, p.email);
    // fclose(fp);
}
void forgot_password()
{
    struct info vrodi;
    struct info pers;
    FILE *fp;

    fp = fopen("USER.txt", "r");
    if (fp == NULL)
    {
        printf("Error opening file\n");
        return;
    }

    printf("ENTER YOUR USER_NAME: ");
    scanf("%s", vrodi.user_name);
    printf("ENTER YOUR PHONE NUMBER: ");
    scanf("%s", vrodi.phone);

    int found = 0;
    while (fscanf(fp, "%s %s %s %s %s %s", pers.fname, pers.lname, pers.user_name, pers.password, pers.phone, pers.email) != EOF)
    {
        if (strcmp(vrodi.user_name, pers.user_name) == 0 && strcmp(vrodi.phone, pers.phone) == 0)
        {
            found = 1;
            printf("ENTER NEW PASSWORD: ");
            scanf("%s", pers.password);
            break;
        }
    }

    fclose(fp);

    if (found)
    {
        fp = fopen("USER.txt", "w");
        if (fp == NULL)
        {
            printf("Error opening file\n");
            return;
        }
        fprintf(fp, "%s %s %s %s %s %s\n", pers.fname, pers.lname, pers.user_name, pers.password, pers.phone, pers.email);
        fclose(fp);
        printf("PASSWORD UPDATED SUCCESSFULLY\n");
    }
    else
    {
        printf("ACCOUNT NOT FOUND\n");
    }
}
//////////////////////////////////////////////////////////////////////
void menu()
{

    int choose;
    while (1)
    {
        system("cls||clear");
        printf("MENU");
        printf("\n1. SIGN UP");
        printf("\n2. SIGN IN");
        printf("\n3. FORGOT PASSWORD");
        printf("\n4. EXIT");
        printf("\nPlease enter your choice: ");
        scanf("%d", &choose);

        switch (choose)
        {
        case 1:
            sign_up();
            break;
        case 2:
            sign_in();
            break;
        case 3:
            forgot_password();
            break;
        case 4:
            printf("GOOD BYE!\n");
            exit(0);
        default:
            printf("Invalid choice!\n");
        }
    }
}
int main()
{
    menu();
    return 0;
}