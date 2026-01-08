#include <bits/stdc++.h>
#include <windows.h>
using namespace std;

// Abstract Class
class RateLimitter
{
public:
    virtual bool allowRequest(const string &userId) = 0;
};

class TokenBucketRateLimitter : public RateLimitter
{
private:
    int tokens;
    int capacity;
    int refillRate;
    long lastRefillTime;

    long currentTimeMills()
    {
        return time(nullptr) * 1000;
    }

    void refill()
    {
        long now = currentTimeMills();
        long elapsedSeconds = (now - lastRefillTime) / 1000;

        if (elapsedSeconds > 0)
        {
            tokens = min(capacity,
                         {tokens + elapsedSeconds * refillRate});
            lastRefillTime += elapsedSeconds * 1000;
        }
    }

public:
    TokenBucketRateLimitter(int capacity, int refillRate)
        : capacity(capacity),
          tokens(capacity),
          refillRate(refillRate),
          lastRefillTime(currentTimeMills()) {}

    bool allowRequest(const string &userId) override
    {
        refill();

        if (tokens >= 1)
        {
            tokens--;
            return true;
        }
        return false;
    }
};


int main()
{
    TokenBucketRateLimitter limiter(5, 1); // capacity = 5, refill = 1 token/sec
    string userId = "user1";

    for (int i = 1; i <= 20; i++)
    {
        bool allowed = limiter.allowRequest(userId);

        cout << "Request " << i << ": "
             << (allowed ? "Allowed" : "Rejected (429)") << endl;

        Sleep(100);

    }

    return 0;
}