#include <iostream>
#include <forward_list>
#include <span>
#include <vector>
#include <algorithm>

using namespace std;

forward_list<span<char>> tokenize(string &text)
{
    forward_list<span<char>> result;
    string current_token;
    int i = 0, n = text.size();

    string operators = "+-*/%=!<>&|~^";
    vector<string> operators2 = {
        "==", "!=", "<=", 
        ">=", "++", "--", "+=", "-=",
        "*=", "/=", "%=", "&&", "||",
        "<<", ">>", "->"
    };

    while (i < n)
    {
        if (isspace(text[i]))
        {
            i++;
            continue;  
        }
        int start = i;

        if (isalpha(text[i]) || text[i] == '_')
        {
            while (i < n && (isalnum(text[i]) || text[i] == '_'))
                i++;
            result.push_front(span<char>(text.data() + start, i - start));
            continue;
        }

        if (isdigit(text[i]))
        {
            while (i < n && isdigit(text[i]))
                i++;
            if (i < n && text[i] == '.')
            {
                i++;
                if (i < n && isdigit(text[i]))
                {
                    while (i < n && isdigit(text[i]))
                        i++;
                }
            }
            result.push_front(span<char>(text.data() + start, i - start));
            continue;
        }

        if (operators.find(text[i]) != string::npos)
        {
            string op;
            if (i + 1 < n)
                op = text.substr(i, 2);
            if (find(operators2.begin(), operators2.end(), op) != operators2.end())
                i += 2;
            else
                i++;
            result.push_front(span<char>(text.data() + start, i - start));
            continue;
        }

        i++;
        result.push_front(span<char>(text.data() + start, i - start));
    }
    result.reverse();
    return result;
}

void print_tokens(string &text)
{
    auto tokens = tokenize(text);
    for (auto token : tokens)
    {
        for (char c : token)
            cout << c;
        cout << '\n';
    }
}

int main()
{
    string text1 = "abc xyz _temp variable123";
    cout << "TEXT1: " << text1 << '\n';
    print_tokens(text1);

    string text2 = "123 456 0 99999";
    cout << "\nTEXT2: " << text2 << '\n';
    print_tokens(text2);

    string text3 = "a+b-c*d/e%f";
    cout << "\nTEXT3: " << text3 << '\n';
    print_tokens(text3);

    string text4 = "a==b != c <= d >= e";
    cout << "\nTEXT4: " << text4 << '\n';
    print_tokens(text4);

    string text5 = "a && b || !c";
    cout << "\nTEXT5: " << text5 << '\n';
    print_tokens(text5);

    string text6 = "f(a, b, c);";
    cout << "\nTEXT6: " << text6 << '\n';
    print_tokens(text6);

    string text7 = "x++ y-- a+=10 b*=2";
    cout << "\nTEXT7: " << text7 << '\n';
    print_tokens(text7);

    string text8 = "result = (a + b*2) >= 100 && flag != 0;";
    cout << "\nTEXT8: " << text8 << '\n';
    print_tokens(text8);

    string text9 = "if(x>=10) { x += 5; return x; }";
    cout << "\nTEXT9: " << text9 << '\n';
    print_tokens(text9);
    return 0;
}