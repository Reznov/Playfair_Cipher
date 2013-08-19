//**************************************
// Name: Playfair Cipher
// Description:Encryption algorithm implementing the playfair cipher
// By: Reznov
//
// Inputs:None
//
// Returns:None
//
// Assumes:None
//
// Side Effects:None
//**************************************

/******************** Encryption Program ********************
function: Encrypt and Decrypt data using the Playfair Cipher
This program will encrypt data entered at the command or by
opening a file and encrypt the data. Once encrypted, the
ciphertext can be sent to stdout or be redirected to a file.
Data can also be decrypted by manually entering ciphertext
at the command line or by opening a file.
The Matrix table can be viewed using the print matrix function
*************************************************************/
#include<iostream>
#include<fstream>
#include<string>
#include<cmath>
#include<stdlib.h>

using namespace std;

int menu();
string getkey();
string keyboardinput();
string Create_Matrix(string);
string encrypt(string, string);
string decrypt(string, string);
string format(string);
string inputfile();
int outputmethod();
void outputfile(string);
void Print_Matrix(string);

int main()
{
    /******* Variable Declarations *****************
    Purpose: Declare variables for main function
    Initialize all variables
    ***********************************************/
    int choice = 0;
    string filename;
    string key;
    int method = 0;
    string plaintext = "";
    string ciphertext = "";
    string matrix = "";

    while (choice != 6)
    {
        choice = menu();
        switch(choice)
        {
        case 1:
            key = getkey();
            matrix = Create_Matrix(key);
            plaintext = keyboardinput();
            plaintext = format(plaintext);
            ciphertext = encrypt(plaintext, matrix);
            method = outputmethod();
            if (method == 1)
            {
                cout<<"Ciphertext: "<<ciphertext<<endl;
            }
            else if (method == 2)
            {
                outputfile(ciphertext);
            }
            else
                cout<<"invalid choice"<<endl;
            break;
            /**** Encrypt from a File ***********************
                input: Input from plain.txt
            ************************************************/
        case 2:
            key = getkey();
            matrix = Create_Matrix(key);
            plaintext = inputfile();
            plaintext = format(plaintext);
            ciphertext = encrypt(plaintext, matrix);//Submit data to encryption function
            method = outputmethod();
            if (method == 1)
            {
                cout<<"Ciphertext: "<<ciphertext<<endl;
            }
            else if (method == 2)
            {
                outputfile(ciphertext);
            }
            else
                cout<<"invalid choice"<<endl;
            break;
            /**** Decrypt from the Keyboard ****************/
        case 3:
            key = getkey();
            matrix = Create_Matrix(key);
            ciphertext = keyboardinput();
            method = outputmethod();
            if (method == 1)
            {
                cout<<"The original message: "<<plaintext<<endl;
            }
            else if (method == 2)
            {
                outputfile(plaintext);
            }
            else
                cout<<"invalid choice"<<endl;
            break;
            /**** Decrypt from a File ***********************
            input: Input from cipher.txt
            ************************************************/
        case 4:
            key = getkey();
            matrix = Create_Matrix(key);
            ciphertext = inputfile();
            plaintext = decrypt(ciphertext, matrix);//Submit data to Decryption function
            method = outputmethod();
            if (method == 1)
            {
                cout<<"The original message: "<<plaintext<<endl;
            }
            else if (method == 2)
            {
                outputfile(plaintext);
            }
            else
                cout<<"invalid choice"<<endl;
            break;
            /**** Print the 5x5 Matrix ****************/
        case 5:
            Print_Matrix(matrix);
            break;
            /**** Exit Program *****/
        case 6:
            exit (0);
        default:
            cout<<"Your choice is invalid, please try again"<<endl;
        }
    }
    return 0;
}

/************ getkey Function *****************
Purpose: Gets a key from the user
return: String containining the key
*************************************************/
string getkey()
{
    string tempkey;
    cout<<"please input the key"<<endl;
    cin>> tempkey;
    return tempkey;
}

/************ Keyboardinput Function *****************
Purpose: Gets input from the Keyboard
return: String containing keyboard input
*************************************************/
string keyboardinput()
{
    string temptext;
    cout<<"Write the message"<<endl;
    cin.ignore(); //bug fix for getline function
    getline(cin,temptext); //Get text from user
    return temptext;
}

/************ Create_Matrix Function *****************
Purpose: Creates a matrix based off the keyword
Input: String with keyword
return: String containing a logical matrix of 25
*************************************************/
string Create_Matrix(string keyword)
{
    char array[24];
    int i = 0;
    int k = 0;
    int value = 0;
    int count = 0;
    bool unique = true;
    int len = keyword.length();
    int run = 1;
    /*** Change all w's into v's *****/
    for (int tmp = 0; tmp < len; tmp++)
    {
        if (keyword[tmp] == 'w')
        {
            keyword[tmp] = 'v';
        }
    }
    /**********************************/
    for (run = 0; run < len; run++) //run loop once for each letter of key
    {
        for (k = 0; k < run; k++)
        {
            if (keyword[run] == keyword[k])
            {
                unique = false;
            }
        }
        if (unique == true) //Letter has not been used in table
        {
            array[i] = keyword[run]; //give the location the correct ascii value
            i++;//increment matrix since it has been filled
        }
        unique = true;
    }
    /*** put the rest of the characters in **/
    while (count < 26)
    {
        for (k = 0; k < len; k++)
        {
            if (value == keyword[k] - 97)
            {
                unique = false;
            }
        }
        if (unique == true) //Letter has not been used in table
        {
            if (value != 9) //not j since it is being bunched with i
            {
                array[i] = 97 + value; //give the location the correct ascii value
                i++;//increment matrix since it has been filled
            }
        }
        value++;
        count++;
        k = 0;
        unique = true;
    }
    return array;
}

/************ Print_Matrix Function *****************
Purpose: Prints a visual matrix
Input: String containing the matrix
return: No return
*************************************************/
void Print_Matrix(string matrix)
{
    system("CLS");
    cout<<"The Current Matrix"<<endl;
    cout<<"------------------"<<endl;
    cout<<" "<<endl;
    for (int j = 0; j < 25; j++)
    {
        cout<<matrix[j]<<matrix[j + 1]<< matrix[j + 2]<< matrix[j + 3]<< matrix[j + 4]<< endl;
        j = j + 4;
    }
    cout<<""<<endl;
    cout<<"In Continuous Form"<<endl;
    cout<<"------------------"<<endl;
    cout<<matrix<<endl;
    cout<<""<<endl;
    system("PAUSE");
}

/************ Encrypt Function *****************
------------------------------------------------
Purpose: Encrypt string using matrix
Input: String with plaintext, string matrix
return: ciphertext in a string
*************************************************/
string encrypt(string plain, string matrix)
{
    string ciphertxt = plain;
    int loc[2];
    int row[2];
    int col[2];
    int shift = 0;
    int original_row = 0;
    int n = 0;
    cout<<"Plaintext arrival: " <<plain<<endl;
    int textlen = plain.length();
    for (n = 0; n < textlen; n = n + 2) //run half the length (diagrams)
    {
        //Assign letters to their locations in matrix
        for (int temp = 0; temp < 26; temp++)
        {
            if (plain[n] == matrix[temp])
            {
                loc[0] = temp; //location of the first letter in pair
            }
            if (plain[n+1] == matrix[temp])
            {
                loc[1] = temp; //location of the second letter in pair
            }
        }
        /* Find Row and Column Numbers */
        for (int m = 0; m < 2; m++)
        {
            if (loc[m] < 5 ) // Location second row
            {
                row[m] = 1;
            }
            else if (loc[m] > 4 && loc[m] < 10) // Location second row
            {
                row[m] = 2;
            }
            else if (loc[m] > 9 && loc[m] < 15 ) // Location third row
            {
                row[m] = 3;
            }
            else if (loc[m] > 14 && loc[m] < 20) // Location fourth row
            {
                row[m] = 4;
            }
            else // Location fifth row
            {
                row[m] = 5;
            }
            if (loc[m] == 0 || loc[m] == 5 || loc[m] == 10 || loc[m] == 15 || loc[m] == 20)
            {
                // Location first column
                col[m] = 1;
            }
            else if (loc[m] == 1 || loc[m] == 6 || loc[m] == 11 || loc[m] == 16 || loc[m] == 21)
            {
                // Location second column
                col[m] = 2;
            }
            else if (loc[m] == 2 || loc[m] == 7 || loc[m] == 12 || loc[m] == 17 || loc[m] == 22)
            {
                // Location third column
                col[m] = 3;
            }
            else if (loc[m] == 3 || loc[m] == 8 || loc[m] == 13 || loc[m] == 18 || loc[m] == 23)
            {
                // Location fourth column
                col[m] = 4;
            }
            else
            {
                // Location fifth column
                col[m] = 5;
            }
        }
        //Start that encryption and shifting :-)
        if (row[0] == row[1] || col[0] == col[1]) //same row or same column: special case
        {
            if (row[0] == row[1]) //same row
            {
                original_row = row[0]; //sets a baseline for starting row
                loc[0] = (loc[0] + 1);
                loc[1] = (loc[1] + 1);
                /* Find Row after shift */
                for (int m = 0; m < 2; m++)
                {
                    if (loc[m] < 5 )
                    {
                        row[m] = 1;
                    }
                    else if (loc[m] > 4 && loc[m] < 10)
                    {
                        row[m] = 2;
                    }
                    else if (loc[m] > 9 && loc[m] < 15 )
                    {
                        row[m] = 3;
                    }
                    else if (loc[m] > 14 && loc[m] < 20)
                    {
                        row[m] = 4;
                    }
                    else
                    {
                        row[m] = 5;
                    }
                }
                if (row[0] != original_row)
                {
                    loc[0] = loc[0] - 5;
                }
                if (row[1] != original_row)
                {
                    loc[1] = loc[1] - 5;
                }
                ciphertxt[n] = matrix[loc[0]]; //assign the resultant location to be cipher char
                ciphertxt[n+1] = matrix[loc[1]];
                ciphertxt[n] = ciphertxt[n] - 32;//convert lowercase to uppercase
                ciphertxt[n+1] = ciphertxt[n+1] - 32; //convert lowercase to uppercase
            }
            if (col[0] == col[1]) //same column
            {
                loc[0] = (loc[0] + 5) ;
                loc[1] = (loc[1] + 5) ;
                if (loc[0] > 24)
                {
                    loc[0] = loc[0] - 25;
                }
                if (loc[1] > 24)
                {
                    loc[1] = loc[1] - 25;
                }
                ciphertxt[n] = matrix[loc[0]]; //assign the result location to be cipher char
                ciphertxt[n+1] = matrix[loc[1]];
                ciphertxt[n] = ciphertxt[n] - 32;//convert lowercase to uppercase
                ciphertxt[n+1] = ciphertxt[n+1] - 32; //convert lowercase to uppercase
            }
        }
        else if (col[0] < col[1]) //if the second letter has a higher column
        {
            shift = abs(col[0] - col[1]); //col difference between char 1 - char 2
            loc[0] = loc[0] + shift;//location point right after shift
            loc[1] = loc[1] - shift;
            ciphertxt[n] = matrix[loc[0]]; //assign the result location to be cipher char
            ciphertxt[n+1] = matrix[loc[1]];
            ciphertxt[n] = ciphertxt[n] - 32;//convert lowercase to uppercase
            ciphertxt[n+1] = ciphertxt[n+1] - 32; //convert lowercase to uppercase
        }
        else if (col[0] > col[1]) //if the first letter has a higher column
        {
            shift = (col[0] - col[1]); //col difference between char 1 - char 2
            loc[0] = loc[0] - shift;//location point right after shift
            loc[1] = loc[1] + shift;
            ciphertxt[n] = matrix[loc[0]];
            ciphertxt[n+1] = matrix[loc[1]];
            ciphertxt[n] = ciphertxt[n] - 32;//convert lowercase to uppercase
            ciphertxt[n+1] = ciphertxt[n+1] - 32; //convert lowercase to uppercase
        }
    }
    return ciphertxt;
}

/************ Decrypt Function *****************
------------------------------------------------
Purpose: Decrypt string using matrix
Input: String with ciphertext, string matrix
return: Plaintext in a string
*************************************************/
string decrypt(string cipher, string matrix )
{
    string plain = cipher;
    int loc[2];
    int row[2];
    int col[2];
    int shift = 0;
    int original_row = 0;
    int n = 0;
    int m = 0;
    int textlen = cipher.length();
    for (n = 0; n < textlen; n = n + 2) //run half the length
    {
        loc[0] = 0;
        loc[1] = 0;
        plain[n] = plain[n] + 32;//convert from upper to lowercase
        plain[n+1] = plain[n+1] + 32; //convert from upper to lowercase

        //Assign letters to their locations in matrix
        for (int temp = 0; temp < 26; temp++)
        {
            if (plain[n] == matrix[temp])
            {
                loc[0] = temp; //location of the first letter in pair
            }
            if (plain[n+1] == matrix[temp])
            {
                loc[1] = temp; //location of the second letter in pair
            }
        }
        /* Find Row and Column Numbers */
        for (m = 0; m < 2; m++)
        {
            if (loc[m] < 5 ) // Location second row
            {
                row[m] = 1;
            }
            else if (loc[m] > 4 && loc[m] < 10) // Location second row
            {
                row[m] = 2;
            }
            else if (loc[m] > 9 && loc[m] < 15 ) // Location third row
            {
                row[m] = 3;
            }
            else if (loc[m] > 14 && loc[m] < 20) // Location fourth row
            {
                row[m] = 4;
            }
            else // Location fifth row
            {
                row[m] = 5;
            }
            //GET column Locations
            if (loc[m] == 0 || loc[m] == 5 || loc[m] == 10 || loc[m] == 15 || loc[m] == 20)
            {
                // Location first column
                col[m] = 1;
            }
            else if (loc[m] == 1 || loc[m] == 6 || loc[m] == 11 || loc[m] == 16 || loc[m] == 21)
            {
                // Location second column
                col[m] = 2;
            }
            else if (loc[m] == 2 || loc[m] == 7 || loc[m] == 12 || loc[m] == 17 || loc[m] == 22)
            {
                // Location third column
                col[m] = 3;
            }
            else if (loc[m] == 3 || loc[m] == 8 || loc[m] == 13 || loc[m] == 18 || loc[m] == 23)
            {
                // Location fourth column
                col[m] = 4;
            }
            else
            {
                // Location fifth column
                col[m] = 5;
            }
        }
        //Start that encryption and shifting :-)
        if (row[0] == row[1] || col[0] == col[1])
        {
            //same row or same column: special case
            if (row[0] == row[1])
            {
                //same row
                original_row = row[0]; //sets a baseline for starting row
                loc[0] = (loc[0] - 1);
                loc[1] = (loc[1] - 1);
                // Find Row after shift
                for (m = 0; m < 2; m++)
                {
                    if (loc[m] < 5 )
                    {
                        row[m] = 1;
                    }
                    else if (loc[m] > 4 && loc[m] < 10)
                    {
                        row[m] = 2;
                    }
                    else if (loc[m] > 9 && loc[m] < 15 )
                    {
                        row[m] = 3;
                    }
                    else if (loc[m] > 14 && loc[m] < 20)
                    {
                        row[m] = 4;
                    }
                    else
                    {
                        row[m] = 5;
                    }
                }

                if (row[0] != original_row || loc[0] < 0)
                {
                    loc[0] = loc[0] + 5;
                }
                if (row[1] != original_row || loc[1] < 0)
                {
                    loc[1] = loc[1] + 5;
                }
                plain[n] = matrix[loc[0]]; //assign the result location to be cipher char
                plain[n+1] = matrix[loc[1]];

            } //ends if row = row...moves along to column
            else if (col[0] == col[1]) //same column
            {
                if (loc[0] > loc[1]) //account for upper rollover
                {
                    loc[0] = (loc[0] - 5) ;
                    loc[1] = (loc[1] - 5) ;
                    if (loc[1] < 0)
                    {
                        loc[1] = (loc[1] + 25) ;
                    }
                }
                else if (loc[0] < loc[1] && loc[0] < 4) //account for lower rollover
                {
                    loc[0] = (loc[0] + 5) ; //Inverse of encryption shift
                    loc[1] = (loc[1] - 5) ; //Inverse of encryption shift
                }
                else
                {
                    if (loc[1] - loc[0] == 20) //account for adjacent column special case
                    {
                        loc[0] = loc[0] + 20; //Inverse of encryption shift
                        loc[1] = (loc[1] - 5) ; //Inverse of encryption shift
                    }

                    else //normal cases
                    {
                        loc[0] = (loc[0] - 5) ; //Inverse of encryption shift
                        loc[1] = (loc[1] - 5) ; //Inverse of encryption shift
                        if (loc[0] > 24)
                        {
                            loc[0] = loc[0] - 25; //account for wraparound
                        }
                        if (loc[1] > 24)
                        {
                            loc[1] = loc[1] - 25; //account for wraparound
                        }
                    }
                }
                plain[n] = matrix[loc[0]]; //assign the result location to be cipher char
                plain[n+1] = matrix[loc[1]]; //assign the result location to be cipher char
            }
        }
        else if (col[0] < col[1]) //if the second letter has a higher column
        {
            shift = abs(col[0] - col[1]);//col difference between char 1 - char 2
            loc[0] = loc[0] + shift;//location point right after shift
            loc[1] = loc[1] - shift;//location point right after shift
            plain[n] = matrix[loc[0]]; //assign the result location to be cipher char
            plain[n+1] = matrix[loc[1]]; //assign the result location to be cipher char
        }

        else if (col[0] > col[1]) //if the first letter has a higher column
        {
            shift = (col[0] - col[1]); //col difference between char 1 - char 2
            loc[0] = loc[0] - shift;//location point right after shift
            loc[1] = loc[1] + shift;//location point right after shift
            plain[n] = matrix[loc[0]]; //assign the result location to be cipher char
            plain[n+1] = matrix[loc[1]]; //assign the result location to be cipher char
        }
    }
    return plain;
}

/***************** Format ************************
Purpose: To format the plaintext for encryption
************************************************/
string format(string text)
{
    int i = 0;
    int j = 0;
    int len = 0;
    len = text.length();
    /*** Change all j's into i's *****/
    for (int tmp = 0; tmp < len; tmp++)
    {
        if (text[tmp] == 'j')
        {
            text[tmp] = 'i';
        }
    }
    /**********************************/
    if (len % 2 == 0)
    {
        cout<<"plaintext is even"<<endl;
    }
    else
    {
        cout<< "plaintext is odd"<<endl;
        text = text + "x"; //add x as a filler to the end
    }
    len = text.length();
    /*** Assign 'x' to letters that repeat in a diagram ***/
    for (i = 0; i < len; i = i + 2) //run for half of string length
    {
        if (text[i+1] == text[i]) //if char = previous char
        {
            text = text + " ";//increase length
            len = text.length();
            for (j = len -1; j > i; j--) //j starts a top len, will run till it hits i
            {
                text[j] = text[j-1]; //last letter = previous letter
            }
            text[i + 1] = 'x';
        }
        else //not a repeat character, move along
        {}
    }
    return text;
}

/***************** outputmethod ************************
Purpose: determines how to output results
*****************************************************/
int outputmethod()
{
    int method;
    cout<<"What output method do you want?"<<endl;
    cout<<"1. Output to monitor"<<endl;
    cout<<"2. Output to file"<<endl;
    cin >> method;
    system("CLS");
    return method;
}

/***************** outputfile ************************
Purpose: To print data to file
*****************************************************/
void outputfile(string info)
{
    ofstream outfile;
    string filename;
    int i = 0;
    cout<<"Please enter filename for output (ex C://plain.txt)"<<endl;
    cin>> filename;
    outfile.open(filename.c_str(), ios :: out);
    if ( !outfile )
    {
        cout << "PROBLEM! " << endl;
    }
    if (outfile.is_open())
    {
        outfile << info;
        outfile.close();
    }
}

/***************** Input File ************************
Purpose: To get input file and pull in data
*****************************************************/
string inputfile()
{
    ifstream Inputfile;
    string text;
    string filename;
    int i = 0;
    cout<<"Please enter filename for input (ex C://plain.txt)"<<endl;
    cin>> filename;
    Inputfile.open(filename.c_str(), ios :: in);
    if ( !Inputfile )
    {
        cout << "PROBLEM! " << endl;
        return 0;
    }
    while ( Inputfile )
    {
        Inputfile >> text;
    }
    Inputfile.close();
    return text;
}
//same old menu
int menu()
{
    int menuselect;
    cout<<"|--------------------------------------------------|"<<endl;
    cout<<"|*The Playfair Cipher* |"<<endl;
    cout<<"| |"<<endl;
    cout<<"---------------------------------------------------|"<<endl;
    cout<<"| Please Make a Selection |"<<endl;
    cout<<"| |"<<endl;
    cout<<"| |"<<endl;
    cout<<"| Encryption Functions |"<<endl;
    cout<<"| 1: Encrypt the message (Keyboard source)|"<<endl;
    cout<<"| 2: Encrypt the message (File source) |"<<endl;
    cout<<"| 3: Decrypt the message (Keyboard source)|"<<endl;
    cout<<"| 4: Decrypt the message (File source) |"<<endl;
    cout<<"| |"<<endl;
    cout<<"| Extras |"<<endl;
    cout<<"| 5. View Matrix|"<<endl;
    cout<<"| |"<<endl;
    cout<<"| Exit |"<<endl;
    cout<<"| 6. Quit|"<<endl;
    cout<<"----------------------------------------------------"<<endl;
    cin>> menuselect;
    return menuselect;
}
