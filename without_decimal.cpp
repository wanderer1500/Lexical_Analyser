#include <bits/stdc++.h>
using namespace std;

bool is_reloP(char c)
{
    return (c == '<' || c == '>' || c == '=');
}
bool is_keyword(string &token)
{
    if (token == "if" || token == "else" || token == "then")
        return true;
    else
        return false;
}
bool isDig(char c)
{
    return (c <= '9' && c >= '0');
}
bool is_letter(char c)
{
    return (c >= 'a' && c <= 'z') || (c = 'A' && c >= 'Z');
}

string proccessString(string s)
{
    string rectified = "";
    for (int i = 0; i < s.size(); i++)
    {
        if (!is_reloP(s[i]) && !isalnum(s[i]) && s[i] != ' ')
        {
            cout << "unrecognized symbol " << s[i] << "\n";
            continue;
        }
        rectified += s[i];
    }
    return rectified;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    string s;

    while (getline(cin, s))
    {
        s = proccessString(s);
        if (s.empty())
            break;
        int n = s.length();
        int tail = 0;
        int head = -1;
        while (tail < n)
        {
            string token = "";
            string num = "";
            string relOp = "";
            bool letterSeen = false;
            bool digSeen = false;
            bool relOpSeen = false;
            bool dotSeen = false;
            while (head + 1 < n)
            {
                head++;
                if (s[head] == ' ')
                    break;
                if(s[head]=='.'){
                    dotSeen = true;
                }
                if (is_reloP(s[head]))
                {
                    relOp += s[head];
                    relOpSeen = true;
                    continue;
                }
                if (digSeen && is_letter(s[head]))
                {
                    cout << "Invalid variable name\n";
                    return 0;
                }
                if (isDig(s[head]))
                {
                    if (relOpSeen)
                    {
                        head--;
                        break;
                    }
                    
                    digSeen = true;
                    if (!letterSeen )
                    {
                        if (relOpSeen)
                        {
                            head--;
                            break;
                        }
                        num += s[head];
                        
                    }
                    else
                    {
                        if (relOpSeen)
                        {
                            head--;
                            break;
                        }
                        token += s[head];
                    }
                }
                else if (isalnum(s[head]))
                {
                    if (relOpSeen)
                    {
                        head--;
                        break;
                    }
                    if (!letterSeen && num.size())
                        break;
                    letterSeen = true;
                    token += s[head];
                }
            }
            if (relOp.size())
            {
                cout << "(relop," << relOp << ")\n";
            }
            if (num.size())
            {
                cout << "(number," << num << ")" << "\n";
            }
            else if (token.size())
            {
                if (!is_keyword(token))
                    cout << "(id," << token << ")" << "\n";
                else
                    cout << "(" << token << ",)" << "\n";
            }

            if (tail > head)
            {
                tail++;
                head = tail - 1;
            }
            else
            {
                tail++;
            }
        }
    }
}