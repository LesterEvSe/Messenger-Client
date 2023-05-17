#ifndef ENCRYPTION_HPP
#define ENCRYPTION_HPP

#include <gmpxx.h> // gmp.h for C
#include <random>
#include <QString>
#include <QByteArray>

// Singleton class
class Encryption
{
private:
    // Can be changed, the higher the number,
    // the better the encryption
    static constexpr int BIT_ENCRYPTION {2048};

    // Module from the number 'n', which has 2*BIT_ENCRYPTION bits
    // Get the number of bytes in the block
    static constexpr int BLOCK_SIZE {2 * BIT_ENCRYPTION / 8};

    // n = p * q, where p and q are prime numbers
    mpz_class n;

    // private key
    mpz_class d;

    // public key
    mpz_class e;

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

    QString get_e() const;
    QString get_n() const;
    QByteArray encode_decode(const QByteArray& bytes, bool encode) const;

};

#endif // ENCRYPTION_HPP
