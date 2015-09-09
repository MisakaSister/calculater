#include<iostream>
#include<string>
#include<vector>
using namespace std;
enum Kind
{
    op,
    num,
};
struct Token
{
    Kind kind;
};
struct Operator
{
    Kind kind;
    char value;
};
struct Number
{
    Kind kind;
    int value;
};

int Express();
int Term();
int Factor();
int ExpRest(int inh);
int TermRest(int inh);

inline bool isNum(char ch)
{
    return ch <= '9' && ch >= '0';
}

inline bool isOp(char ch)
{
    return ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '(' || ch == ')';
}

vector<Token*>::iterator lookhead;
vector<Token*> tokens;

void tokenizer(string express)
{
    for(auto it = express.begin(); it != express.end();)
    {
        if(it != express.end() && isNum(*it))
        {
            int intValue = 0;
            while(it != express.end() && isNum(*it))
            {
                intValue *= 10;
                intValue += (*it) - '0';
                ++it;
            }
            Number* num = new Number;
            num->kind = Kind::num;
            num->value = intValue;
            tokens.push_back((Token*)num);
            //cout<<num->value<<endl;
        }
        if(it != express.end() && isOp(*it))
        {
            Operator* ope = new Operator;
            ope->kind = Kind::op;
            ope->value = *it;
            ++it;
            tokens.push_back((Token*)ope);
            //cout<<ope->value<<endl;
        }
    }

}

void match(char ch)
{
    if((*lookhead)->kind == Kind::op)
    {
        if(ch ==((Operator*)(*lookhead))->value)
            ++lookhead;
    }
    else if(ch == 'n')
        ++lookhead;


}

int Express()
{
    int t = Term();
    int r = ExpRest(t);
    return r;
}

int ExpRest(int inh)
{
    if(lookhead == tokens.end())
        return inh;
    // if((*lookhead)->kind == Kind::num)
    //     return inh;
    char c = ((Operator*)(*lookhead))->value;
    if(((Operator*)(*lookhead))->value == '+')
    {
        match('+');
        int t = Term();
        return ExpRest(inh + t);
    }
    else if(((Operator*)(*lookhead))->value == '-')
    {
        match('-');
        int t = Term();
        return ExpRest(inh - t);
    }
    else return inh;
}

int Term()
{
    int f = Factor();
    return TermRest(f);
}

int TermRest(int inh)
{
    if(lookhead == tokens.end())
        return inh;
    // if((*lookhead)->kind == Kind::num)
    //     return inh;
    if(((Operator*)(*lookhead))->value == '*')
    {
        match('*');
        int f = Factor();
        return TermRest(inh * f);
    }
    else if(((Operator*)(*lookhead))->value == '/')
    {
        match('/');
        int f = Factor();
        return TermRest(inh / f);
    }
    else return inh;
}

int Factor()
{
    if((*lookhead)->kind == Kind::num)
    {
        int val = ((Number*)(*lookhead))->value;
        match('n');
        return val;
    }
    else if((*lookhead)->kind == Kind::op)
    {
        if(((Operator*)(*lookhead))->value == '(')
        {
            match('(');
            int val = Express();
            match(')');
            return val;
        }
    }
}

int main()
{
    string express;
    while(cin>>express)
    {
        tokenizer(express);
        lookhead = tokens.begin();

        int ans = Express();
        cout<<ans<<endl;
        tokens.clear();
    }

    return 0;
}

