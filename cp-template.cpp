#include <bits/stdc++.h>
using namespace std;


// =========================
// Fast memory allocator
// =========================
// Global new/delete optimization
// Put before Solution class
// =========================

constexpr size_t MAX_MEMORY = 1ULL << 28; // 256 MB

static unsigned char memory_pool[MAX_MEMORY]; // static: global lifetime storage
static size_t memory_ptr = 0;


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


// =========================
// Macros
// =========================

#define all(x) begin(x), end(x)
#define sz(x) ((int)x.size())


// =========================
// Constants
// =========================

constexpr int INF = 1e9;
constexpr ll LINF = 4e18;
constexpr int MOD = 1e9 + 7;


// =========================
// Fast IO
// =========================

static const auto init = [] {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return 0;
}();


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