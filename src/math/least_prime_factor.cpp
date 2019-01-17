int least_prime_factor(int n) {
    // returns smallest prime number that devides n
    for(int i = 2; i * i <= n; ++i) {
        if(n % i == 0) return least_prime_factor(i);
    }

    // n is prime
    return n;
}
