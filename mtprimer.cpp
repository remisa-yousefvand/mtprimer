#include <mutex>
#include <thread>
#include <vector>
#include <iostream>

const int DEFAULT_THREAD_COUNT = 4;

using namespace std;

mutex mtx;

void primeCalc(unsigned long from, unsigned long to) {
  for (unsigned long i = from; i < to; i++) {
    for (unsigned long j = 2; j <= (i / 2); j++) {
      if (i % j == 0) {
        i++;
        if (i < to) {
          j = 2;
          continue;
        } else {
          return;
        }
      }
    }
  mtx.lock();
  cout << i << endl;
  mtx.unlock();
  }
}

int main(int argc, char const *argv[])
{
  if (argc != 2) {
    cout << "This utility generates prime numbers." << endl;
    cout << "Usage: " << argv[0] << " [upperLimit]" << endl;
    cout << "upperLimit: Generate primes up to this number." << endl;
    return 1;
  }

  int threadCount = thread::hardware_concurrency();
  if (threadCount == 0)
    threadCount = DEFAULT_THREAD_COUNT;

  unsigned long upper = stoul(argv[1]);
  vector<thread> t;
  unsigned long step = upper / threadCount;

  for (int i = 0; i < threadCount; i++) {
    if (i == 0)
      t.push_back(thread(primeCalc, 2 + (i * step), ((i + 1) * step)));
    else
      if (i == threadCount - 1)
        t.push_back(thread(primeCalc, (i * step), upper));
      else
        t.push_back(thread(primeCalc, (i * step), ((i + 1) * step)));
  }

  for (int i = 0; i < threadCount; i++) {
    t[i].join();
  }

  return 0;
}
