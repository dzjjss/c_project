#include <assert.h>
#include <iostream>
#include <string>


using namespace std;

char*  replaceAllC(char* msg, char toChange, char changeTo);
string replaceAllCPP(string msg, char toChange, char changeTo);

int main()
{
    string msg1;
    string subString1;
    char   findChar;
    char*  a_msg2       = new char[100];
    char*  a_subString2 = new char[100];

    cout << "Please enter a string message" << endl;
    getline(cin, msg1);
    cout << "Please enter text to find in your message" << endl;
    getline(cin, subString1);
    cout << "Please enter a character to find in  your message" << endl;
    cin >> findChar;
    size_t subIdx = msg1.find(subString1);
    if (subIdx != string::npos) {
        cout << "The substring was found at index " << subIdx << endl;
    }
    else {
        cout << "The substring was NOT found" << endl;
    }
    int    charCount = 0;
    size_t offset    = msg1.find(findChar);
    while (offset != string::npos) {
        charCount++;
        offset = msg1.find(findChar, offset + 1);
    }
    cout << "Character " << findChar << " was found " << charCount << " times." << endl;

    cout << "Original message is: " << msg1 << endl
         << "Replaced message is: " << replaceAllCPP(msg1, 'b', 'c') << endl;

    /*
    printf("Please enter a message < 100 character \n");
    gets_s(a_msg2, 100);
    //scanf_s("%s", a_msg2, 100);
    printf("Please short text to find in your message. \n");
    gets_s(a_subString2, 100);
    //scanf_s("%s", a_subString2, 100);
    printf("Please enter a character to find in  your message \n");
    scanf_s("%c", &findChar, 1);

    char* p_subPtr = strstr(a_msg2, a_subString2);
    if (p_subPtr)
    {
        printf("The substring was found at index %i\n", p_subPtr - a_msg2);
    }
    else
    {
        printf("The substring was NOT found\n");
    }
    int msgLen = strlen(a_msg2);
    int numFound = 0;
    for (int i = 0; i < msgLen; i++)
    {
        if (a_msg2[i] == findChar)
        {
            numFound++;
        }
    }
    printf("Character %c was found %i times\n", findChar, numFound);

    printf("Original messsage: %s\n", a_msg2);
    replaceAllC(a_msg2, 'a', 'A');
    printf("Messsage after replace: %s\n", a_msg2);
    */
}

char* replaceAllC(char* msg, char toChange, char changeTo)
{
    if (msg == NULL) {
        return NULL;
    }
    int len = strlen(msg);
    for (int i = 0; i < len; i++) {
        if (msg[i] == toChange) {
            msg[i] = changeTo;
        }
    }
    return msg;
}

string replaceAllCPP(string msg, char toChange, char changeTo)
{
    size_t offset = msg.find(toChange);
    while (offset != string::npos) {
        msg.replace(offset, 1, 1, changeTo);
        offset = msg.find(toChange, offset + 1);
    }
    return msg;
}