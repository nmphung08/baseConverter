#include <iostream>
#include <string>
#include <math.h>
#include <sstream>
#include <stack>
using namespace std;

struct number
{
  string str;
  int base;
};
float mod(float n, int m)
{
    int temp = (int)n / m;
    return n - temp*m;
}
int getNumb (char c)
{
    if ((int)c>='A') return (int)c - 55;
    return (int)c - 48;
}
char getChar(int i)
{   
    if (i>=10)
        return static_cast<char>(i + 55);
    else
        return static_cast<char>(i + 48);
}
bool baseCheck (number n)
{
    for (int i=0;i<n.str.length();i++)
        if (getNumb(n.str[i])>= n.base)
            return 0;
    return 1;
}
float toDec (number numb)	//buoc trung gian: chuyen qua he 10
{
    float temp;
    int tempIndex; //bien tam de luu chi so cua dau cham (".")
    bool realCheck;
    for(int i=0;i<numb.str.length();i++)
        if (numb.str[i]=='.')
        {
            tempIndex = i;
            realCheck = 1;
            break;
        }
    if (realCheck)
    {
    for(int i=tempIndex-1;i>=0;i--)
        temp+= getNumb(numb.str[i])*pow(numb.base,tempIndex - 1 - i);
    for (int i=tempIndex+1;i<numb.str.length();i++)
        temp+= getNumb(numb.str[i])*pow(numb.base,tempIndex - i);
    return temp;
    }
    else 
    {
        for (int i=numb.str.length()-1;i>=0;i--)
            temp+= getNumb(numb.str[i])*pow(numb.base,numb.str.length()-1-i);
            return temp;
    }
}

void fromDec(float decVar, number& numb)
{
    if (mod(decVar, 1) > 0)
    {
        float temp = decVar - (int)(decVar / 1); //bien tam giu phan so thuc
        int tempBase = numb.base;
        stack<char> cs;
        while (decVar != 0)
        {
            cs.push(getChar(mod(decVar, tempBase)));
            decVar = (int)(decVar/tempBase);
        }
        while(!cs.empty())
        {
            numb.str+=cs.top();
            cs.pop();
        }
        numb.str+='.';
        while(temp != 0)
        {
            temp *= tempBase;
            numb.str+=getChar((int)(temp/1));
            temp = mod(temp, 1);
        }
        
    }
    else
    {
        int tempBase = numb.base;
        stack<char> cs;
        while (decVar != 0)
        {
            cs.push(getChar(mod(decVar, tempBase)));
            decVar = (int)(decVar/tempBase);
        }
        while(!cs.empty())
        {
            numb.str+=cs.top();
            cs.pop();
        } 
    }
}
void baseConverter (number b1, number& b2)
{
    fromDec(toDec(b1),b2);
}

int main ()
{
    cout << "Base converter: " << endl;
    number b1, b2;
    cout << "From base: ";
    cin >> b1.base;
    cout << "To base: ";
    cin >> b2.base;
    cin.ignore();
    cout << "Number input: ";
    getline(cin,b1.str);
    while(!baseCheck(b1))
    {
        cout<<"Number error.."<<endl;
        cout<<"Number input: ";
        getline(cin,b1.str);
    }
    baseConverter(b1,b2);
    cout<<endl;
    cout<<"From "<<b1.base<<" base to "<<b2.base<<" base: "<<b1.str<<" --> "<<b2.str<<endl;


    return 0;
}
