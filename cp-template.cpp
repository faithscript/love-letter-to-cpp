#include <bits/stdc++.h>
using namespace std;


// =========================
// Fast memory allocator
// =========================
// Global new/delete optimization — bump allocator.
// Put before Solution class.
//
// CAVEAT: delete() is a no-op, memory is never reclaimed.
// Safe for single-shot judges (process per test case, e.g. Codeforces).
// RISKY on judges that reuse one process across many test cases
// (e.g. LeetCode) — memory_ptr only grows and can exhaust
// MAX_MEMORY partway through unrelated later tests.
// Call reset() between cases if that applies, or just don't
// use this on LeetCode-style harnesses.
// =========================

constexpr size_t MAX_MEMORY = 1ULL << 28; // 256 MB

static unsigned char memory_pool[MAX_MEMORY]; // static: global lifetime storage
static size_t memory_ptr = 0;

inline void reset_memory_pool() {
    memory_ptr = 0;
}

void* operator new(size_t size) {
    if (size == 0)
        size = 1;

    size = (size + 15) & ~15; // 16-byte alignment

    if (memory_ptr + size > MAX_MEMORY)
        throw bad_alloc();

    void* ptr = memory_pool + memory_ptr;
    memory_ptr += size;

    return ptr;
}

void* operator new[](size_t size) {
    return operator new(size);
}

void operator delete(void*) noexcept {}
void operator delete[](void*) noexcept {}

// C++17 sized deletes
void operator delete(void*, size_t) noexcept {}
void operator delete[](void*, size_t) noexcept {}


// =========================
// Aliases
// =========================

using ll = long long;
using ull = unsigned long long;

using vi = vector<int>;
using vll = vector<ll>;

using pii = pair<int,int>;
using pll = pair<ll,ll>;

using vvi = vector<vi>;
using vvll = vector<vll>;

// ordered
using mii = map<int,int>;
using mll = map<ll,ll>;
using si = set<int>;
using sll = set<ll>;

// unordered
using umii = unordered_map<int,int>;
using umll = unordered_map<ll,ll>;
using usi = unordered_set<int>;
using usll = unordered_set<ll>;

// heaps (priority_queue)
using pqi = priority_queue<int>;                              // max-heap (default)
using pqll = priority_queue<ll>;                               // max-heap
using minpqi = priority_queue<int, vector<int>, greater<int>>; // min-heap
using minpqll = priority_queue<ll, vector<ll>, greater<ll>>;   // min-heap


// =========================
// Macros
// =========================

#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define sz(x) ((int)(x).size())
#define         rep(i, n)                   for (ll i = 0; i < (n); ++i) 
#define         rep1(i, a, b)               for (ll i = (a); i <= (b); ++i)
#define         rep2(i, a, b)               for (ll i = (a); i >= (b); --i)
#define         pb                          push_back 

// =========================
// Constants
// =========================

constexpr int INF = 1e9;
constexpr ll LINF = 4e18;
constexpr int MOD = 1e9 + 7;
const int MAX = 500005;


// =========================
// Fast IO
// =========================

static const auto init = [] {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return 0;
}();

/*
========================================
MODULAR INVERSE TEMPLATE
========================================

1. Prime Modulus (Fermat)
-------------------------
Use:
    modinv_prime(a, MOD)

Requirements:
- MOD is prime.
- gcd(a, MOD) = 1.
- O(log MOD).


2. Arbitrary Modulus (Extended Euclid)
--------------------------------------
Use:
    modinv(a, mod)

Requirements:
- gcd(a, mod) = 1.
- Returns -1 if no inverse exists.
- O(log mod).


3. Precompute Inverses
----------------------
Use:
    auto inv = precompute_inv(N, MOD);

Requirements:
- MOD is prime.
- inv[i] = i^{-1} (mod MOD)
- O(N).

Useful for:
- nCr
- Factorial inverses
- Frequent modular division

========================================
*/

const ll MOD = 1000000007;

// Binary Exponentiation
ll modpow(ll a, ll b) {
    a %= MOD;
    ll res = 1;

    while (b) {
        if (b & 1) res = res * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }

    return res;
}

// Modular Inverse (MOD must be prime)
ll modinv(ll a) {
    return modpow(a, MOD - 2);
}

// Inverses of 1...N
vector<ll> precompute_inv(int N) {
    vector<ll> inv(N + 1);
    inv[1] = 1;

    for (int i = 2; i <= N; i++)
        inv[i] = MOD - (MOD / i) * inv[MOD % i] % MOD;

    return inv;
}

// Factorials & Inverse Factorials
vector<ll> fact, invfact;

void init_fact(int N) {
    fact.resize(N + 1);
    invfact.resize(N + 1);

    fact[0] = 1;
    for (int i = 1; i <= N; i++)
        fact[i] = fact[i - 1] * i % MOD;

    invfact[N] = modinv(fact[N]);

    for (int i = N; i >= 1; i--)
        invfact[i - 1] = invfact[i] * i % MOD;
}

ll nCr(int n, int r) {
    if (r < 0 || r > n) return 0;
    return fact[n] * invfact[r] % MOD * invfact[n - r] % MOD;
}

ll nPr(int n, int r) {
    if (r < 0 || r > n) return 0;
    return fact[n] * invfact[n - r] % MOD;
}


// =========================
// Solution
// =========================

class Solution {
public:

    // static syntax:
    // static int dp[200005];
    // static vector<int> graph[200005];

    // hot syntax:
    // static int solve(...) noexcept __attribute__((hot));

};