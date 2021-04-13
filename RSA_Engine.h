#ifndef RSA_ENGINE_H
#define RSA_ENGINE_H

#include <string>
#include <BigInteger.h>
#define BI BigInteger

class RSA_Engine
{
    BI P_Al, Q_Al, N_Al, d_Al, s_Al, e_Al;
    BI P_Bob, Q_Bob, N_Bob, d_Bob, s_Bob, e_Bob;

public:
    enum {Alice, Bob};
    BI getBI(int i);
    void generateBI();
    string encode(string, int);
    string decode(string, int);

    RSA_Engine();
private:
    BI encChar(char c, BI publicKey, BI N);
    BI decChar(BI character, int flag);
    void countP(), countQ(),
         countN(), countD(),
         countS(), countE();
    bool isPrime(BI);
    BI greatestCommonDivisor(BI x, BI y);
    bool isCoPrime(BI x, BI y);
};

#endif // RSA_ENGINE_H
