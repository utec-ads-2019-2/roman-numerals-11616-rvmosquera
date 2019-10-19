#include <string>
#include <stdexcept>
#include <iostream>
#include <assert.h>
#include <iostream>
#include <unordered_map>

using namespace std;

unordered_map<char, int> letters;

#ifndef NDEBUG
#   define ASSERT(condition, message1, message2) \
    do { \
        if (! (condition)) { \
            std::cerr << "Assertion `" #condition "` failed in " << __FILE__ \
                      << " line " << __LINE__ << ": " << message1 << " " << message2 << std::endl; \
            std::terminate(); \
        } \
    } while (false)
#else
#   define ASSERT(condition, message) do { } while (false)
#endif

string roman_to_arabic(string num) {
    int res = 0;
    char prev;

    for (auto it = num.end() - 1; it >= num.begin(); --it) {
        auto it2 = it;

        if (it2 != num.begin())
            --it2;

        if (*it == 'X') {
            if (*it2 == 'I')
                res = res + letters['I'] * -1;

            if (prev == 'C' || prev == 'L')
                continue;

        } else if (*it == 'V') {
            if (*it2 == 'I')
                res = res + letters['I'] * -1;

        } else if (*it == 'I') {
            if (prev == 'V' || prev == 'X')
                continue;

        } else if (*it == 'L') {
            if (*it2 == 'X')
                res = res + letters['X'] * -1;

        } else if (*it == 'C') {
            if (*it2 == 'X')
                res = res + letters['X'] * -1;

            if (prev == 'M' || prev == 'D')
                continue;

        } else if (*it == 'D' || *it == 'M') {
            if (*it2 == 'C')
                res = res + letters['C'] * -1;
        }
        res = res + letters[*it];
        prev = *it;
    }

    return to_string(res);
}

string arabic_to_roman(string num) {
    string res;
    string pattern = "MDCLXVI";
    int i = 0, index = 0;

    for (auto it = num.end() - 1; it >= num.begin(); --it) {
        auto arabic = *it;

        int digit = stoi(string(1, arabic));

        switch (i) {
            case 0:
                index = 6;
                break;
            case 1:
                index = 4;
                break;
            case 2:
                index = 2;
                break;
            case 3:
                index = 0;
                break;
        }

        switch (digit) {
            case 4: {
                res = string(1, pattern[index]) + string(1, pattern[index - 1]) + res;
            }
                break;
            case 9: {
                res = string(1, pattern[index]) + string(1, pattern[index - 2]) + res;
            }
                break;
            case 5: {
                res = string(1, pattern[index - 1]) + res;
            }
                break;
            default: {
                auto rest = digit % 5;
                auto quot = digit / 5;

                while (rest > 0) {
                    res = pattern[index] + res;
                    --rest;
                }

                if (quot != 0)
                    res = string(1, pattern[index - 1]) + res;
            }
        }
        ++i;
    }

    return res;
}

class Tester {
public:
    Tester() {
        letters.insert({'M', 1000});
        letters.insert({'D', 500});
        letters.insert({'C', 100});
        letters.insert({'L', 50});
        letters.insert({'X', 10});
        letters.insert({'V', 5});
        letters.insert({'I', 1});
    }

    static void execute_udebug_test() {
        string nums[] = {"3999",
                         "I",
                         "CCXII",
                         "1",
                         "CCXL",
                         "473",
                         "CDXXVIII",
                         "3762",
                         "MMMCMLVII",
                         "87",
                         "MMMCMXI",
                         "991",
                         "MDCCXC",
                         "1523",
                         "MDLIV",
                         "44",
                         "MCCLXXXV",
                         "2876",
                         "MVII",
                         "28",
        };

        string exp_result[] = {"MMMCMXCIX",
                               "1",
                               "212",
                               "I",
                               "240",
                               "CDLXXIII",
                               "428",
                               "MMMDCCLXII",
                               "3957",
                               "LXXXVII",
                               "3911",
                               "CMXCI",
                               "1790",
                               "MDXXIII",
                               "1554",
                               "XLIV",
                               "1285",
                               "MMDCCCLXXVI",
                               "1007",
                               "XXVIII"
        };

        string result;
        for (int i = 0; i < 20; i++) {

            if (isdigit(nums[i][0])) {
                result = arabic_to_roman(nums[i]);
            } else {
                result = roman_to_arabic(nums[i]);
            }

            ASSERT(result == exp_result[i], "Wrong result in ", nums[i]);
        }
        cout << "udebug test OK" << endl;
    }

    static void execute_16321_test() {
        string nums[] = {"IV",
                         "VI",
                         "IXX",
                         "XLVI",
                         "45",
                         "40",
                         "49",
                         "94",
                         "294",
                         "544",
                         "999",
                         "2789",
                         "CD"
        };

        string exp_result[] = {"4",
                               "6",
                               "19",
                               "46",
                               "XLV",
                               "XL",
                               "XLIX",
                               "XCIV",
                               "CCXCIV",
                               "DXLIV",
                               "CMXCIX",
                               "MMDCCLXXXIX",
                               "400"
        };

        string result;
        for (int i = 0; i < 13; i++) {

            if (isdigit(nums[i][0])) {
                result = arabic_to_roman(nums[i]);
            } else {
                result = roman_to_arabic(nums[i]);
            }

            ASSERT(result == exp_result[i], "Wrong result in ", nums[i]);
        }
        cout << "16321 test OK" << endl;

    }
};

int main() {
    string num;

    letters.insert({'M', 1000});
    letters.insert({'D', 500});
    letters.insert({'C', 100});
    letters.insert({'L', 50});
    letters.insert({'X', 10});
    letters.insert({'V', 5});
    letters.insert({'I', 1});

    //while (scanf("%s", &num) != EOF) {
    while (cin >> num) {

        if (isdigit(num[0])) {
            cout << arabic_to_roman(num) << endl;
        } else {
            cout << roman_to_arabic(num) << endl;
        }

    }
    /*
    Tester::execute_udebug_test();
    Tester::execute_16321_test();*/
}