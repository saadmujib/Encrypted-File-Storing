#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <cstdio>

using namespace std;

void mainMenu();

void login();
bool checkloginF();
string userValidation(string name);
void logMenu(string n);
void encryption(string n);
void encryptxor(string a, string b);
void encryptvigenere(string a, string b);
bool CheckandWritefname(string a, string b);
string genkey(int length);
void decryption(string n);
void decryptxor(int key, string encrypted, string out);
void decryptvigenere(string key, string encrypted, string out);
void showFiles(string n);

void signup();
void storelogins(string name, string pass);
void createDB(string n, string p);

void exit();

void mainMenu()
{
    int ch = -1;
    cout << "1. Login\n2. Sign-up\n3. Exit\n";
    do
    {
        cout << "Please choose correct options (1-3): ";
        cin >> ch;
    } while (ch < 1 or ch > 3);

    if (ch == 1)
    {
        if (checkloginF())
        {
            login();
        }
        else
        {
            cout << "No logins exists! Sing up first...\n";
            signup();
        }
    }
    else if (ch == 2)
    {
        signup();
    }
    else
    {
        exit();
    }
}

void login()
{
    string userN;
    string pass;
    cout << "\n__Login form__\n";
    cout << "Enter your username: ";
    cin >> userN;
    string expectPass = userValidation(userN);
    while (expectPass == " ")
    {
        cout << "Username does not exists!\n";
        cout << "Enter correct username: ";
        cin >> userN;
        expectPass = userValidation(userN);
    }
    cout << "Enter your password: ";
    cin >> pass;
    while (pass != expectPass)
    {
        cout << "Wrong password...!\n";
        cout << "Enter correct password: ";
        cin >> pass;
    }
    cout << "\n__Successfully logged-in__\n";
    logMenu(userN);
}

bool checkloginF()
{
    string temp;
    int c = 0;
    ifstream fin("logins.txt");
    while (getline(fin, temp))
    {
        c++;
    }
    fin.close();
    return c;
}

string userValidation(string name)
{
    string temp;
    ifstream fin("logins.txt");
    while (getline(fin, temp))
    {
        string n = temp.substr(0, 8);
        if (n == name)
        {
            fin.close();
            return temp.substr(13, 8);
        }
    }
    fin.close();
    return " ";
}

void logMenu(string n)
{
    int c;
    cout << "\n1. Encrypt a new file\n2. Decrypt a existing file\n3. Exit\n";
    cin >> c;

    while (c < 1 or c > 3)
    {
        cout << "Invalid Choice...! Enter again: ";
        cin >> c;
    }

    if (c == 1)
    {
        encryption(n);
        logMenu(n);
    }
    else if (c == 2)
    {
        decryption(n);
        logMenu(n);
    }
    else
    {
        exit();
    }
}

void encryption(string n)
{
    int c1;
    cout << "\nEnter encryption level :\n1. Low Level\n2. High Level\n";
    cin >> c1;
    while (c1 != 1 and c1 != 2)
    {
        cout << "Invalid Choice...! Enter again: ";
        cin >> c1;
    }
    string a;
    cout << "Enter file name (.txt format): ";
    cin >> a;
    while (CheckandWritefname(a, (n + "1.txt")))
    {
        cout << "\nAn encrypted file with similar name exits, choose another file: ";
        cin >> a;
    }
    if (c1 == 1)
    {
        encryptxor(a, n);
    }
    else
    {
        encryptvigenere(a, n);
    }
}

void encryptxor(string a, string b)
{
    string out = b + "2.txt";
    ifstream fin(a);
    if (!fin.is_open())
    {
        cout << "File doesn't exist.\n";
        encryption(b);
        return;
    }

    string content = "", line;
    while (getline(fin, line))
    {
        content += line + '\n';
    }
    fin.close();
    content.pop_back();

    int key = rand() % 100 + 1;
    string encrypted = "";

    for (int i = 0; i < content.length(); i++)
    {
        char c = content[i] ^ (char)(key);
        encrypted += c;
    }

    ofstream fout(out, ios::app);
    fout << ("1 " + a) << endl;
    fout << key << endl;
    fout << encrypted << endl;
    fout << "END" << endl;
    fout.close();
    remove(a.c_str());

    cout << "File encrypted successfully\n";
}

void encryptvigenere(string a, string b)
{
    string out = b + "2.txt";
    ifstream fin(a);
    if (!fin.is_open())
    {
        cout << "File doesn't exist.\n";
        encryption(b);
        return;
    }

    string content = "", line;
    while (getline(fin, line))
    {
        content += line + '\n';
    }
    fin.close();
    content.pop_back();

    int k = rand() % 5 + 1;
    string key = genkey(k);

    string encrypted = "";
    int x = 0;
    for (int i = 0; i < content.length(); i++)
    {
        if (content[i] != '\n')
        {
            encrypted += (char)((int)content[i] + (int)key[x]);
            x = (x + 1) % key.length();
        }
        else
        {
            encrypted += '\n';
        }
    }

    ofstream fout(out, ios::app);
    fout << ("2 " + a) << endl;
    fout << key << endl;
    fout << encrypted << endl;
    fout << "END" << endl;
    fout.close();
    remove(a.c_str());

    cout << "File encrypted successfully!\n(Note: Orignal file has been deleted, and encrypted file has been saved to our database.)\n";
}

bool CheckandWritefname(string a, string b)
{
    string t;
    ifstream f(b);
    while (getline(f, t))
    {
        if (a == t)
        {
            f.close();
            return true;
        }
    }
    fstream file(b, ios::in | ios::out | ios::app);
    file << a << endl;
    file.close();
    return false;
}

string genkey(int length)
{
    string key = "";
    for (int i = 0; i < length; i++)
    {
        key += ('a' + (rand() % 26));
    }
    return key;
}

void decryption(string n)
{
    int c = 0;
    string fname = (n + "1.txt");
    string temp;
    ifstream fin(fname);
    while (getline(fin, temp))
    {
        c++;
    }
    fin.close();
    if (c == 0)
    {
        cout << "There are no files!\n";
        encryption(n);
    }
    else
    {
        cout << "Here are your files!\n\n";
        showFiles(n);
        cout << endl;
    }
    int a;
    cout << "Choose file to decrypt 1 to " << c << " : ";
    cin >> a;
    while (a < 1 || a > c)
    {
        cout << "Invalid choice. Enter again : ";
        cin >> a;
    }

    c = 0;
    ifstream in(fname);
    while (getline(in, temp))
    {
        c++;
        if (c == a)
        {
            break;
        }
    }
    in.close();
    ifstream file((n + "2.txt"));
    string name, key;
    while (getline(file, name))
    {
        int len = name.length() - 2;
        if (name.substr(2, len) == temp)
        {
            if (name[0] == '1')
            {
                getline(file, key);
                int k = stoi(key);
                string encrypted = "", line;
                while (getline(file, line))
                {
                    if (line == "END")
                    {
                        break;
                    }
                    encrypted += (line + '\n');
                }
                encrypted.pop_back();
                file.close();
                decryptxor(k, encrypted, temp);
                break;
            }
            else
            {
                getline(file, key);
                string encrypted = "", line;
                while (getline(file, line))
                {
                    if (line == "END")
                    {
                        break;
                    }
                    encrypted += line + '\n';
                }
                encrypted.pop_back();
                file.close();
                decryptvigenere(key, encrypted, temp);
                break;
            }
        }
    }
}

void decryptxor(int key, string encrypted, string out)
{
    string decrypted = "";

    for (int i = 0; i < encrypted.length(); i++)
    {
        char c = encrypted[i] ^ (char)(key);
        decrypted += c;
    }

    ofstream fout(out);
    fout << decrypted;
    fout.close();

    cout << "File decrypted successfully\n";
}

void decryptvigenere(string key, string encrypted, string out)
{
    string decrypted = "";
    int x = 0;
    for (int i = 0; i < encrypted.length(); i++)
    {
        if (encrypted[i] != '\n')
        {
            decrypted += (char)((int)encrypted[i] - (int)key[x]);
            x = (x + 1) % key.length();
        }
        else
        {
            decrypted += '\n';
        }
    }

    ofstream fout(out);
    fout << decrypted;
    fout.close();

    cout << "File decrypted successfully\n";
}

void showFiles(string n)
{
    string fname = (n + "1.txt");
    string temp;
    ifstream fin(fname);
    int c = 1;
    while (getline(fin, temp))
    {
        cout << c << ") " << temp << endl;
        c++;
    }
}

void signup()
{
    string userN;
    string pass;
    string Cpass;
    string ifExist;
    cout << "\n__Sign-up form__\n";
    cout << "Enter username (Must contain 8-Characters): ";
    cin >> userN;
    while (userN.length() != 8)
    {
        cout << "Invalid username...!\n";
        cout << "It must be 8 characters long\n";
        cout << "Enter username (Must contain 8-Characters): ";
        cin >> userN;
    }
    ifExist = userValidation(userN);
    if (ifExist != " ")
    {
        int c;
        cout << "Username already exists!\n";
        cout << "Wants to log in ?\n";
        cout << "1. Yes\n2. No\n";
        cin >> c;
        if (c == 1)
        {
            login();
        }
        else
        {
            signup();
        }
    }

    cout << "Enter password (Must contain 8-Characters): ";
    cin >> pass;
    while (pass.length() != 8)
    {
        cout << "Invalid password...!\n";
        cout << "It must be 8 characters long\n";
        cout << "Enter password (Must contain 8-Characters): ";
        cin >> pass;
    }
    cout << "Confirm your password: ";
    cin >> Cpass;
    while (Cpass != pass)
    {
        cout << "Incorrect password... Enter again: ";
        cin >> Cpass;
    }
    storelogins(userN, pass);
    createDB(userN, pass);
    mainMenu();
}

void storelogins(string name, string pass)
{
    fstream file("logins.txt", ios::in | ios::out | ios::app);
    if (file.is_open())
    {
        file << name << "     " << pass << endl;
        cout << "Congrats! Signed in successfully...\n\n";
    }
    else
    {
        cout << "Oops there is an error while storing logins!\n";
        signup();
    }
    file.close();
}

void createDB(string n, string p)
{
    string str1 = n;
    string str2 = n;

    str1 += "1.txt";
    str2 += "2.txt";

    fstream file1(str1, ios::in | ios::out | ios::app);
    file1.close();
    fstream file2(str2, ios::in | ios::out | ios::app);
    file2.close();
}

void exit()
{
    cout << "Thanks for using this application (^_^)\n";
}

int main()
{
    srand(time(NULL));
    cout << "\t-----Welcome to our Application!-----\n\n";
    cout << "Hello Sir! How may i help u?\n";
    mainMenu();
    return 0;
}
