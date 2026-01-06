// FIXED WINDOW RATE LIMITTER -> A Fixed Window Rate Limiter is a rate-limiting algorithm that restricts the number of requests a user can make within a fixed time interval.

/*
maxRequest = 5;
windowSize = 5 sec

A user can make up to 5 API requests within any 5-second fixed window.
- Requests 1 to 5 → Allowed
- Request 6(within the same 5 sec) -> Rejected Too Many request
- After 5 seconds pass, the window resets
- The user can again make 5 new requests
*/

#include <bits/stdc++.h>
using namespace std;

//Abstract Class
class RateLimitter
{
public:
    virtual bool allowRequest(const string &userId) = 0;
};

struct RequestData
{
    int requestCount = 0;
    long windowStart = time(nullptr) * 1000;
};


//inherit the property of parent class
class FixedWindowRateLimiter : public RateLimitter
{
private:
    int maxRequest;
    long windowSize;
    unordered_map<string, RequestData> userRequests; //<userId,<requestCount,windowStart>>

public:
    FixedWindowRateLimiter(int maxRequest, long windowSize)
    {
        this->maxRequest = maxRequest;
        this->windowSize = windowSize;
    }

    bool allowRequest(const string &userId) override
    {
        long currentTime = time(nullptr) * 1000;

        auto &data = userRequests[userId];

        if (currentTime - data.windowStart >= windowSize)
        {
            data.requestCount = 0;
            data.windowStart = currentTime;
        }

        data.requestCount++;
        return data.requestCount <= maxRequest;
    }
};

int main()
{
    FixedWindowRateLimiter limitter(5, 5000);

    string userId = "1";

    for (int i = 1; i <= 8; i++)
    {
        bool allowed = limitter.allowRequest(userId);

        cout << "Request: " << i << " for " << userId << ": " << (allowed ? "Allowed" : "(429) Too Many Request") << endl;
    }
    return 0;
}