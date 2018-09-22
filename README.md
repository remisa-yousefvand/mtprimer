# Primer

Multithread prime calculator

## Build

Release mode:

```bash
g++ -std=c++11 -pthread -Wall mtprimer.cpp -o mtprimer
```

Debug mode:

```bash
g++ -std=c++11 -g -pthread -Wall mtprimer.cpp -o mtprimer
```

## Usage

```bash
./mtprimer 10000000 > primes.txt
```