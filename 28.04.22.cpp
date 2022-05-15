#include <iostream>
#include <stack>

typedef unsigned int uint;

bool is_beg_end(int a, int b);
bool is_expr(const char* s, uint& pos);

int main() {
    uint p;
    char s1[] = "({x-y-z}*[x+2y]-(z+4x));";
    if (is_expr(s1, p))
        std::cout << "Good." << std::endl;
    else
        std::cout << "Error, strpos: " << s1 + p << std::endl;

    //...

    char s2[] = "([x-y-z}*[x+2y)-{z+4x)].";
    if (is_expr(s2, p))
        std::cout << "Good." << std::endl;
    else
        std::cout << "Error, strpos: " << s2 + p << std::endl;

    std::cin.get();
    return 0;
}

struct binfo {
    int  ch;
    uint pos;
    binfo(void) {}
    binfo(int c, uint p) :ch(c), pos(p) {}
};

bool is_expr(const char* s, uint& p) {
    const char* t = s;
    std::stack<binfo> st;

    for (; *s; ++s) {
        switch (*s) {
        case '(':
        case '{':
        case '[':
            st.push(binfo(*s, static_cast<uint>(s - t)));
            break;
        case ')':
        case '}':
        case ']':
            if (st.empty() || !is_beg_end(st.top().ch, *s)) {
                p = static_cast<uint>(s - t);
                return false;
            }
            st.pop();
            break;
        }
    }

    bool ret = st.empty();
    for (; !st.empty(); st.pop())
        p = st.top().pos;
    return !*s && ret;
}

bool is_beg_end(int a, int b) {
    return (a == '(' && b == ')') ||
        (a == '{' && b == '}') ||
        (a == '[' && b == ']');
}