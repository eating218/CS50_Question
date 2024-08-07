#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int length = 26;
int n_ornot(string vector, int number);
string create_table(string vector);
string substitution(string table, string input, int input_leng);

int main(int argc, string argv[])
{
    if (argc != 2) // 要有兩個輸入
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    int number = strlen(argv[1]);
    if (n_ornot(argv[1], number)) // 檢查是否為字母
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    else if (number != 26) // 輸入沒有26個字母
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }
    else // 輸入有26個字母
    {
        string key_table = create_table(argv[1]);
        string input = get_string("plaintext:  ");
        string output = substitution(key_table, input, strlen(input));
        printf("ciphertext: %s\n", output);

        free(key_table);
        free(output);

        return 0;
    }
}

int n_ornot(string vector, int number)
{
    for (int i = 0; i < number; i++)
    {
        if (!isalpha(vector[i])) // 若有不是字母的字符
        {
            return 1; // 返回1
        }
    }
    return 0; // 全部是字母，返回0
}

string create_table(string vector) // 金鑰對照表
{
    char *table_out = (char *)malloc((length + 1) * sizeof(char));
    for (int i = 0; i < length; i++)
    {
        if (islower(vector[i]))
        {
            table_out[i] = toupper(vector[i]);
        }
        else
        {
            table_out[i] = vector[i];
        }
    }
    table_out[length] = '\0';
    return table_out;
}

string substitution(string table, string input, int input_leng)
{
    char *output = (char *)malloc((input_leng + 1) * sizeof(char));

    for (int i = 0; i < input_leng; i++)
    {
        if (isalpha(input[i]))
        {
            if (islower(input[i]))
            {
                output[i] = tolower(table[input[i] - 'a']);
            }
            else
            {
                output[i] = table[input[i] - 'A'];
            }
        }
        else
        {
            output[i] = input[i];
        }
    }
    output[input_leng] = '\0';
    return output;
}
