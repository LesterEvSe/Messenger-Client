#ifndef ENCRYPTION_HPP
#define ENCRYPTION_HPP

#include <random>
#include <QString>
#include <gmpxx.h> // gmp.h for C

// Singleton class
class Encryption
{
private:
    static constexpr int BASE {10};

    // Can be changed, the higher the number,
    // the better the encryption
    static constexpr int BIT_ENCRYPTION {2048};

    // n = p * q, where p and q are prime numbers
    QString n;

    // private key
    QString d;

    // public key
    QString e;

    static QString   toString(const mpz_class& num);
    static mpz_class createPrime();

    Encryption(const Encryption&)   = delete;
    Encryption(Encryption&&)        = delete;
    Encryption& operator= (const Encryption&)   = delete;
    Encryption& operator= (Encryption&&)        = delete;
    Encryption();

public:
    static Encryption* get() {
        static Encryption rsa = Encryption();
        return &rsa;
    }

    const QString& get_e() const;
    const QString& get_n() const;

    QString encrypt(const QString& str) const;
    QString decode (const QString& str) const;
};

#endif // ENCRYPTION_HPP
