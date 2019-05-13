#include<iostream>
#include<vector>
#include<string>
#include <conio.h>

unsigned long long power(unsigned long long number, unsigned long long power) {
	unsigned long long pow = 1;
	for (int i = 0; i < power; i++) {
		pow *= number;
	}
	return pow;
}
unsigned long long powModSimple(unsigned long long exponent, unsigned long long power, unsigned long long mod)
{
	if (power == 0) {
		return 1 % mod;
	}
	else if (power == 1) {
		return exponent % mod;
	}
	else {
		unsigned long long result = exponent;

		for (int i = 1; i < power; i++)
		{
			result = (result*exponent) % mod;
		}
		return result;
	}
}
std::vector <unsigned long long> binaryTable;
void decToBin(unsigned long long power)
{
	unsigned long long binBasic = 1;

	while (power > 0) {

		if (power % 2 == 1) {
			binaryTable.push_back(binBasic);
		}
		else {
			binaryTable.push_back(power % 2);
		}
		power = power / 2;
		binBasic = binBasic * 2;
	}
}

std::vector <unsigned long long> nextPowers;
void changeAlgorithm(unsigned long long exponent, unsigned long long mod)
{
	unsigned long long power = 1;
	nextPowers.push_back((exponent * 1) % mod);
	int e = binaryTable.size();

	for (int i = 0; i < e - 1; i++) {

		nextPowers.push_back((nextPowers[i] * nextPowers[i]) % mod);
		power = power * 2;
	}
}

unsigned long long powModFast( long long exponent, long long power, long long mod)
{
	if (power == 0) {
		
		return 1 % mod;
	}
	else if (power == 1) {
		
		return exponent % mod;
	}
	else {
		long long result = 1;
		decToBin(power);
		changeAlgorithm(exponent, mod);
		int r = binaryTable.size();

		for (int i = 0; i < r; i++) {

			if (binaryTable[i] != 0) {				
				result = (result * nextPowers[i]) % mod; // rozwiazanie powyzszego bledu
			}
		}	
		return result;
	}
}

long long invMod(long long a, long long b) {
	std::vector<long long> q;
	q.push_back(0);
	q.push_back(0);

	std::vector<long long> r;
	std::vector<long long> s;

	if (a > b) {
		r.push_back(a);
		r.push_back(b);
		s.push_back(1);
		s.push_back(0);
	}
	else {
		r.push_back(b);
		r.push_back(a);
		s.push_back(0);
		s.push_back(1);
	}

	int i = 0;
	while (r[i] != 0) {
		i++;
		if (i > 1) {
			q.push_back(r[i - 2] / r[i - 1]);
			r.push_back(r[i - 2] - q[i] * r[i - 1]);
			s.push_back(s[i - 2] - q[i] * s[i - 1]);
		}
		//std::cout << q[i] << "\t" << r[i] << "\t" << s[0] << std::endl;
	}
	std::cout << std::endl;
	if (a * s[s.size() - 2] % b == 1 || a * (s[s.size() - 2] + b) % b == 1) {
		if (s[s.size() - 2] < 0)
		{
			return s[s.size() - 2] + b;
		}
		else {
			return s[s.size() - 2];
		}
	}
	else {
		return -1;
	}
}

bool isPrime(unsigned long long  n)
{
	if (n <= 1)
		return false;
	if (n == 2)
		return true;
	for (unsigned long long i = 2; i <= unsigned long long(sqrt(n)); ++i)
		if (n % i == 0)
			return false;
	return true;
}
long long nwd(long long a, long long b)
{
	long long t;

	while (b != 0)
	{
		t = b;
		b = a % b;
		a = t;
	};
	return a;
}
long long crypt(char a, long long e, long long n) {
	
	long long cAscii = 0;	
	cAscii = powModFast(long long(a), e, n);	
	
	binaryTable.clear();
	nextPowers.clear();
	return cAscii;
}

long long chain_calc(char a, char b, char c, long long chainSize) {
	long long result = 0;
	long long aAscii = long long(a);
	long long bAscii = long long(b);
	long long cAscii = long long(c);
	
	if (chainSize == 1) {

	}
	else if (chainSize == 2) {
		result = aAscii*256 + bAscii;
	}
	else if (chainSize == 3) {
		result = aAscii * 256 * 256 + bAscii * 256 + cAscii;
	}
	return result;
}
long long encrypt(long long a, long long d, long long n) {
	long long cAscii = powModFast(a, d, n);
	binaryTable.clear();
	nextPowers.clear();
	return cAscii;
}

long long rsaSimple(long long p, long long q, long long n, long long fiN, long long e, long long d, std::string words) {
	std::vector<long long>crypted(words.size());
	std::cout << "Kody znakow po szyfrowaniu" << std::endl;
	for (int i = 0; i < words.size(); i++) {
		crypted[i] = crypt(words[i], e, n);
		std::cout << crypted[i] << " ";
	}
	std::cout << "\n\n";

	std::cout << "Znaki po szyfrowaniu" << std::endl;
	for (int i = 0; i < crypted.size(); i++) {
		std::cout << char(crypted[i]) << " ";
	}
	std::cout << "\n\n";

	std::cout << "Kody znakow po deszyfrowaniu" << std::endl;
	std::vector<long long> encrypted;
	for (int i = 0; i < crypted.size(); i++) {
		encrypted.push_back(encrypt(crypted[i], d, n));
		std::cout << encrypted[i] << " ";
	}
	std::cout << "\n\n";

	std::cout << "znaki po deszyfrowaniu" << std::endl;
	for (int i = 0; i < crypted.size(); i++) {
		std::cout << char(encrypted[i]);
	}
	std::cout << "\n\n";	
}
int main() {
	long long p = 0, q = 0, n, fiN, e = 0, d, m, c;
	std::string words;	
	
	bool prime = true;
	while (prime) {
		if (!isPrime(p)) {
			std::cout << "Podaj p jako liczba pierwsza" << std::endl;
			std::cin >> p;
		}
		else {
			prime = false;
		}
	}
	prime = true;
	while (prime) {
		if (!isPrime(q)) {
			std::cout << "Podaj q jako liczba pierwsza" << std::endl;
			std::cin >> q;
		}
		else {
			prime = false;
		}
	}	
	n = p * q;
	std::cout <<"n: "<< n << std::endl;
	fiN = (p - 1)*(q - 1);
	std::cout << "fi(n): " << fiN << std::endl;
	std::cout << "Podaj e wzglednie pierwsze z fi(n) i nieparzyste oraz z przedzialu 1<e<fi(n)" << std::endl;
	std::cin >> e;
	d = invMod(e, fiN);

	std::cout << "d: " << d << "\n\n";
	
	bool check = true;
	while (check) {
		if (nwd(e, fiN) != 1 || e % 2 == 0 || 1>e || e>fiN)
		{
			std::cout << "Podaj e wzglednie pierwsze z fi(n) i nieparzyste oraz z przedzialu 1<e<fi(n)" << std::endl;
			std::cin >> e;
		}
		else {
			check = false;
		}
	}	
	
	std::cout << "Podaj zdanie: " << std::endl;
	std::cin.ignore();
	getline(std::cin, words, '\n');		

	std::cout << "\n\n";	
	
	std::cout << "Szyfrowanie blokami";
	std::cout << "-------------------------------------------------------\n\n";
	int chainSize = 0;
	if (n < power(256, 2))
	{
		chainSize = 1;
	}
	else if (n > power(256, 2) && n < power(256, 3)) {
		chainSize = 2;
	}
	else {
		chainSize = 3;
	}
	
	std::cout << "rozmiar bloku: " <<chainSize<< std::endl;
	
	int j = 0;
	if (chainSize == 1) {	
		rsaSimple(p, q, n, fiN, e, d, words);	
	}
	else {
		std::cout << "kody po szyfrowaniu dla kazdego bloku" << std::endl;		
		while (j < words.size()) {
			if (chainSize == 2) {
				std::cout << words[j] << words[j + 1] << " ->> " << chain_calc(words[j], words[j + 1], '0', chainSize) << " ";
			}
			else if (chainSize == 3) {
				std::cout << words[j] << words[j + 1] << words[j + 2] << " ->> " << chain_calc(words[j], words[j + 1], words[j + 2], chainSize) << " ";
			}
			j = j + chainSize;
		}
	}	
	std::cout << "\n\n";

	
	
	if (chainSize == 1) {

	}
	else {
		j = 0;
		std::cout << "tekst zaszyfrowany" << std::endl;
		while (j < words.size()) {
			
			if (chainSize == 2) {
				std::cout << char(chain_calc(words[j], words[j + 1], '0', chainSize));

			}
			else if (chainSize == 3) {
				std::cout << char(chain_calc(words[j], words[j + 1], words[j + 2], chainSize));
			}
			j = j + chainSize;
		}
	}
	
	std::cout << "\n\n";

	
	
	
	if (chainSize == 1) {

	}
	else {
		std::cout << "Deszyfrowanie blokami-------------------------------------- \n\n";
		std::cout << "Kody liczb w ascii po deszyfrowaniu" << std::endl;
		j = 0;
		while (j < words.size()) {
			if (chainSize == 2) {
				std::cout << (chain_calc(words[j], words[j + 1], '0', chainSize) >> 8) << " " << powModFast(chain_calc(words[j], words[j + 1], '0', chainSize), 1, 256) << "/ ";
				binaryTable.clear();
				nextPowers.clear();
			}else if (chainSize == 3) {
				long long conv = chain_calc(words[j], words[j + 1], words[j + 2], chainSize);
				std::cout << conv / power(256, 2) << " " << conv / 256 << " " << powModFast(conv, 1, 256) << "/ ";
				binaryTable.clear();
				nextPowers.clear();
			}
			j = j + chainSize;
		}
	}	
	
	if (chainSize == 1) {

	}
	else {
		std::cout << "\n\n";
		std::cout << "tekst odszyfrowany" << std::endl;
		j = 0;
		while (j < words.size()) {
			if (chainSize == 2) {
				std::cout << char((chain_calc(words[j], words[j + 1], '0', chainSize) >> 8)) << char(powModFast(chain_calc(words[j], words[j + 1], '0', chainSize), 1, 256));
				binaryTable.clear();
				nextPowers.clear();
			}
			else if (chainSize == 1) {
				std::cout << words[j] << std::endl;

			}
			else if (chainSize == 3) {
				long long conv = chain_calc(words[j], words[j + 1], words[j + 2], chainSize);
				std::cout << char(conv / power(256, 2)) << char(conv / 256) << char(powModFast(conv, 1, 256));
				binaryTable.clear();
				nextPowers.clear();
			}
			j = j + chainSize;
		}
	}
	std::cout << "\n";
	std::cout << "Prawidlowy deszyfr" << std::endl;
	for (int i = 0; i < words.size(); i++) {
		std::cout << long long(words[i]) << " ";
	}
	std::cout << "\n\n";
	
	system("pause");
	return 0;
}