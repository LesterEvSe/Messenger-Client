#include "encryption.hpp"
#include <chrono> // for more accuracy in createPrime function
#include <QDebug> // need to delete later

Encryption::Encryption()
{
    // 1. Generate 2 prime numbers
    mpz_class p = createPrime();
    mpz_class q = createPrime();
//    qDebug() << "p " << toString(p);
//    qDebug() << "q " << toString(q);

    // 2. Calculate 'n'
    n = p * q;
//    qDebug() << "n " << n;

    // 3. Calculate 'fi(n)'
    mpz_class fi_n = (p - mpz_class(1)) * (q - mpz_class(1));
//    qDebug() << "fi(n) " << toString(fi_n);

    // 4. Selecting the recommended value of 'e'
    e = 65537;

    // 5. Calculate private key;
    // mpz_class is a C++ class wrapper, for the C structure mpz_t.
    // get_mpz_t() is needed to get a raw pointer to mpz_t

    // d * e % fi(n) = 1 therefore
    // d = (e^-1) % fi(n)
    // Modular Multiplicative Inverse here
    mpz_invert(d.get_mpz_t(), e.get_mpz_t(), fi_n.get_mpz_t());
//    qDebug() << "d " << d;
}

QString Encryption::get_e() const { return toString(e); }
QString Encryption::get_n() const { return toString(n); }

QString Encryption::toString(const mpz_class& num)
{
    static constexpr int BASE {10};
    // +2 for '\0' and sign '-'
    size_t buff_size = mpz_sizeinbase(num.get_mpz_t(), BASE) + 2;
    std::unique_ptr<char[]> buff = std::make_unique<char[]>(buff_size);

    mpz_get_str(buff.get(), BASE, num.get_mpz_t());
    return buff.get();
}

mpz_class Encryption::createPrime()
{
    mpz_class prime;
    gmp_randstate_t state;

    // Initializing a random number generator
    gmp_randinit_default(state);

    // For more accuracy
    std::chrono::high_resolution_clock::duration seed =
            std::chrono::high_resolution_clock::now().time_since_epoch();

    // Set a random generator state
    // seed.count() - get the number of ticks
    gmp_randseed_ui(state, seed.count());

    // Generating a 2048-bit prime number
    do {
        prime = mpz_class(1);

        // Generating a random number
        mpz_urandomb(prime.get_mpz_t(), state, BIT_ENCRYPTION);

        // Finding the nearest simple to the generated one
        mpz_nextprime(prime.get_mpz_t(), prime.get_mpz_t());

        // Check that the number has exactly BIT_ENCRYPTION bits
    } while (mpz_sizeinbase(prime.get_mpz_t(), 2) != BIT_ENCRYPTION);

    // To check the simplicity of a number by the Miller-Rabin test
    // 25 - number of check iterations. A reasonable limit is 15-50

    // 0 - the number is definitely not prime
    // 1 - the number is prime with a probability of 50% or close to this
    // 2 - Prime with a high probability
    if (!mpz_probab_prime_p(prime.get_mpz_t(), 25))
        return createPrime();

    // free resources
    gmp_randclear(state);

    return prime;
}

// encrypt, if true, otherwise decode
QByteArray Encryption::encode_decode(const QByteArray& bytes, bool encode) const
{
    const unsigned char* data = reinterpret_cast<const unsigned char*>(bytes.data());
    size_t num_bytes = static_cast<size_t>(bytes.size());
    mpz_class num, res;

    // 1 - Little-Endian order (The least significant byte at the beginning)
    // first 0  (endian) - Byte order for each item on a given platform
    // second 0 (nails)  - Several low of each bytes that are not imported.
    // All significant, so we import
    mpz_import(num.get_mpz_t(), num_bytes, 1, sizeof(data[0]), 0, 0, data);

    // res = num ^ e % n
    if (encode)
        mpz_powm(res.get_mpz_t(), num.get_mpz_t(), e.get_mpz_t(), n.get_mpz_t());
    else
        mpz_powm(res.get_mpz_t(), num.get_mpz_t(), d.get_mpz_t(), n.get_mpz_t());

    // 256 is (1 << 8)
    size_t res_size = mpz_sizeinbase(res.get_mpz_t(), 256);
    std::unique_ptr<unsigned char[]> res_data = std::make_unique<unsigned char[]>(res_size);

    size_t exported_size;
    mpz_export(res_data.get(), &exported_size, 1, sizeof(res_data.get()[0]), 0, 0, res.get_mpz_t());
    return QByteArray(reinterpret_cast<char*>(res_data.get()), static_cast<int>(exported_size));
}


