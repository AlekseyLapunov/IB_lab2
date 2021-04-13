#include "RSA_Engine.h"
#include <QDebug>
#include <ctime>


BigInteger RSA_Engine::getBI(int i)
{
    switch (i)
    {
    case 0:
        return P_Al;
        break;
    case 1:
        return Q_Al;
        break;
    case 2:
        return N_Al;
        break;
    case 3:
        return d_Al;
        break;
    case 4:
        return s_Al;
        break;
    case 5:
        return e_Al;
        break;
    case 6:
        return P_Bob;
        break;
    case 7:
        return Q_Bob;
        break;
    case 8:
        return N_Bob;
        break;
    case 9:
        return d_Bob;
        break;
    case 10:
        return s_Bob;
        break;
    case 11:
        return e_Bob;
        break;
    default:
        break;
    }
    return 0;
}

void RSA_Engine::generateBI()
{
    countP(), countQ(), countN(),
            countD(), countS(), countE();
}

string RSA_Engine::encode(string toEncode, int flag)
{
    string output = "";
    BI publicKey = 1, N = 1;
    if(flag == Alice)
    {
        N = N_Bob;
        publicKey = s_Bob;
    }
    else if(flag == Bob)
    {
        N = N_Al;
        publicKey = s_Al;
    }

    for (int i = 0; i < (int)toEncode.length(); i++)
    {
        BigInteger number = encChar(toEncode[i], publicKey, N);
        output.append(number.getNumber());
        output += " ";
    }

    return output;
}

string RSA_Engine::decode(string toDecode, int flag)
{
    string decoded = "";

    size_t pos = 0;
    string token;
    string delimetre = " ";

    while ((pos = toDecode.find(delimetre)) != std::string::npos)
    {
        token = toDecode.substr(0, pos);
        BI character = BI(token);
        BI decryptedChar = decChar(character, flag);

        decoded += (char) atoi(decryptedChar.getNumber().c_str());

        toDecode.erase(0, pos + delimetre.length());
    }

    return decoded;
}

BI RSA_Engine::decChar(BI character, int flag)
{
    BI current = BI(character);
    BI privateKey = 1, N = 1;

    if(flag == Alice)
    {
        N = N_Al;
        privateKey = e_Al;
    }
    else if(flag == Bob)
    {
        N = N_Bob;
        privateKey = e_Bob;
    }

    for (BI i = BI(1); i < privateKey; i++)
    {
        current *= character;
    }

    BI ost = (current % N) + 64;

    return ost;
}

BI RSA_Engine::encChar(char c, BI publicKey, BI N)
{
    BigInteger charPos = BigInteger((c - 64));
    BigInteger current = BigInteger(charPos.getNumber());

    for (BigInteger i = BigInteger(1); i < publicKey; i++)
    {
        current *= charPos;
    }

    BigInteger ost = current % N;
    return ost;
}

void RSA_Engine::countP()
{
    P_Al = BI((rand()%(100 - 31)) + 31);
    while (!isPrime(P_Al))
    {
        P_Al++;
    }
    P_Bob = BI((rand()%(100 - 31)) + 31);
    while (!isPrime(P_Bob))
    {
        P_Bob++;
    }
}

void RSA_Engine::countQ()
{
    Q_Al = BI((rand()%(100 - 31)) + 31);
    while (!isPrime(Q_Al))
    {
        Q_Al++;
    }
    Q_Bob = BI((rand()%(100 - 31)) + 31);
    while (!isPrime(Q_Bob))
    {
        Q_Bob++;
    }
}

void RSA_Engine::countN()
{
    N_Al = P_Al * Q_Al;
    N_Bob = P_Bob * Q_Bob;
}

void RSA_Engine::countD()
{
    d_Al = (P_Al - 1)*(Q_Al - 1);
    d_Bob = (P_Bob - 1)*(Q_Bob - 1);
}

void RSA_Engine::countS()
{
    BI number = 2;
    while (!isCoPrime(number, d_Al) || s_Al > d_Al)
    {
        number++;
    }
    s_Al = number;

    number = 2;
    while (!isCoPrime(number, d_Bob) || s_Al > d_Bob)
    {
        number++;
    }
    s_Bob = number;
}

void RSA_Engine::countE()
{
    BI k = 1;
    while (true)
    {
        k = k + d_Al;

        if (k % s_Al == 0)
        {
            e_Al = (k / s_Al);
            break;
        }
    }

    k = 1;
    while (true)
    {
        k = k + d_Bob;

        if (k % s_Bob == 0)
        {
            e_Bob = (k / s_Bob);
            break;
        }
    }
}

bool RSA_Engine::isPrime(BI number)
{
    bool flag = true;

    if(number > 2)
    for (BigInteger i = 2; i <= (number / 2); ++i)
    {
        if (number % i == 0)
        {
            flag = false;
            break;
        }
    }

    return flag;
}

BI RSA_Engine::greatestCommonDivisor(BigInteger x, BigInteger y)
{
    if (y == 0)
        return x;
    return greatestCommonDivisor(y, x % y);
}

bool RSA_Engine::isCoPrime(BigInteger x, BigInteger y)
{
    return greatestCommonDivisor(x, y) == 1;
}

RSA_Engine::RSA_Engine()
{
    P_Al = 1, Q_Al = 1, N_Al = 1, d_Al = 1, s_Al = 1, e_Al = 1;
    P_Bob = 1, Q_Bob = 1, N_Bob = 1, d_Bob = 1, s_Bob = 1, e_Bob = 1;
    srand(time(0));
}
