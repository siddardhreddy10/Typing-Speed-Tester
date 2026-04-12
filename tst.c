#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <conio.h>
#include <time.h>

extern void start_timer();
extern int get_timer_flag();
extern int my_strcmp(const char *a, const char *b);
extern int my_strlen(const char *s);

char user_input[500];
int input_pos = 0;
char *text_to_type = "";
time_t time_start;

void input()
{
    char ch;
    while (get_timer_flag() == 0)
    {
        if (_kbhit())
        {
            ch = _getch();
            if (ch == '\b')
            {
                if (input_pos > 0)
                {
                    input_pos--;
                    user_input[input_pos] = '\0';
                    printf("\b \b");
                    fflush(stdout);
                }
            }
            else if (ch >= 32 && ch <= 126)
            {
                user_input[input_pos] = ch;
                input_pos++;
                user_input[input_pos] = '\0';
                printf("%c", ch);
                fflush(stdout);
            }
        }
        Sleep(10);
    }
}

void results()
{
    int correct = 0;
    int wrong = 0;
    int total = 0;
    int i = 0;
    int j = 0;
    char orig_word[100];
    char type_word[100];

    int orig_len = my_strlen(text_to_type);
    int type_len = my_strlen(user_input);

    int elapsed = (int)(time(NULL) - time_start);
    if (elapsed < 1)
    {
        elapsed = 1;
    }
    printf("RESULTS\n");
    printf("_______\n");

    while (i <= orig_len)
    {
        int ow = 0;
        while (i <= orig_len && text_to_type[i] != ' ' && text_to_type[i] != '\0')
        {
            orig_word[ow++] = text_to_type[i++];
        }
        orig_word[ow] = '\0';
        i++;

        int tw = 0;
        while (j <= type_len && user_input[j] != ' ' && user_input[j] != '\0')
        {
            type_word[tw++] = user_input[j++];
        }
        type_word[tw] = '\0';
        j++;

        if (ow == 0)
        {
            break;
        }

        total++;

        if (my_strcmp(orig_word, type_word) == 0)
        {
            printf("Fine%s\n", orig_word);
            correct++;
        }
        else
        {
            printf("expected: %-20s got: %s\n", orig_word, type_word);
            wrong++;
        }
    }

    int accuracy = 0;
    if (total > 0)
    {
        accuracy = (correct * 100) / total;
    }
    int total_chars = my_strlen(user_input);
    int wpm = (total_chars / 5) * 60 / elapsed;
    printf("\nTotal Words  : %d\n", total);
    printf("Correct      : %d\n", correct);
    printf("Wrong        : %d\n", wrong);
    printf("Accuracy     : %d%%\n", accuracy);
    printf("WPM          : %d\n", wpm);
}
void test()
{
    memset(user_input, 0, 500);
    input_pos = 0;

    system("cls");
    printf("TYPE THIS TEXT\n");
    printf("   %s\n\n", text_to_type);
    printf("Press ENTER to start...\n");

    while (getchar() != '\n')
    {
        ;
    }
    system("cls");
    printf("   %s\n", text_to_type);
    printf("You have 60 seconds\n\n");
    fflush(stdout);

    time_start = time(NULL);
    start_timer();
    input();

    printf("\n\nTIME IS UP!\n");
    fflush(stdout);

    results();

    printf("\nPress ENTER to go back...\n");
    while (getchar() != '\n')
    {
        ;
    }
}

void paragraph()
{
    int ch;
    system("cls");
    printf("PARAGRAPH'S\n");
    printf("1. Easy\n");
    printf("2. Medium\n");
    printf("3. Hard\n\n");
    printf("Choice: ");
    scanf("%d", &ch);
    while (getchar() != '\n')
    {
        ;
    }

    if (ch == 1)
    {
        text_to_type = "The sun shines bright and the children play happily in the garden. Birds sing melodiously while the breeze carries the scent of flowers. It is a simple day filled with joy and laughter.";
    }
    else if (ch == 2)
    {
        text_to_type = "Despite the heavy rain, the determined traveler continued his journey across the winding path, hoping to reach the distant village before nightfall. His boots sank into the mud, yet his spirit remained unbroken.";
    }
    else if (ch == 3)
    {
        text_to_type = "Philosophical contemplation demands patience and an intricate understanding of abstract concepts, where perseverance and intellectual curiosity intertwine to unravel profound truths. The pursuit of wisdom stretches endlessly across the horizon of human imagination.";
    }
    else
    {
        printf("Invalid choice.\n");
        Sleep(1000);
        return;
    }
    test();
}

void code()
{
    int ch;
    system("cls");
    printf("CODE'S\n");
    printf("1. Easy\n");
    printf("2. Medium\n");
    printf("3. Hard\n\n");
    printf("Choice: ");
    scanf("%d", &ch);
    while (getchar() != '\n')
    {
        ;
    }

    if (ch == 1)
    {
        text_to_type = "int main() { int x = 5; int y = 10; int sum = x + y; if(sum > 10) { printf(Greater); } else { printf(Less); } return 0; }";
    }
    else if (ch == 2)
    {
        text_to_type = "int main() { for(int i = 1; i <= 10; i++) { if(i % 2 == 0) { printf(even); } else { printf(odd); } } return 0; }";
    }
    else if (ch == 3)
    {
        text_to_type = "int factorial(int n) { int result = 1; for(int i = 1; i <= n; i++) { result *= i; } return result; } int main() { int fact = factorial(5); printf(fact); return 0; }";
    }
    else
    {
        printf("Invalid choice.\n");
        Sleep(1000);
        return;
    }
    test();
}

int main()
{
    int ch;
    while (1)
    {
        system("cls");
        printf("\n________________________________\n");
        printf("    TYPING SPEED TESTER\n");
        printf("________________________________\n\n");
        printf("1. Paragraph Typing\n");
        printf("2. Code Copying\n");
        printf("3. Exit\n\n");
        printf("Choice: ");
        scanf("%d", &ch);
        while (getchar() != '\n')
        {
            ;
        }

        if (ch == 1)
        {
            paragraph();
        }
        else if (ch == 2)
        {
            code();
        }
        else if (ch == 3)
        {
            printf("\nGoodbye!\n\n");
            break;
        }
        else
        {
            printf("Invalid choice.\n");
            Sleep(1000);
        }
    }
    return 0;
}