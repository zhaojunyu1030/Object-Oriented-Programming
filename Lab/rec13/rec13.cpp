/* rec13.cpp
 * created by Junyu (Leo) Zhao on 4/25/2025
 */

#include <iostream>
#include <fstream>
#include <vector>      // task 1
#include <list>        // task 2
#include <algorithm>   // task 3
#include <string>      // task 21
#include <set>         // task 22
#include <map>         // task 23
using namespace std;

// Task 9
void printList(const list<int>& lst) {
    for (list<int>::const_iterator it = lst.begin(); it != lst.end(); it++) {
        cout << *it << ' ';
    }
}

// Task 10
void printList2(const list<int>& lst) {
    for (int val : lst) {
        cout << val << ' ';
    }
}

// Task 11
void printList3(const list<int>& lst) {
    for (auto val : lst) {
        cout << val << ' ';
    }
}

// Task 12
list<int>::const_iterator find(const list<int>& lst, int value) {
    for (list<int>::const_iterator it = lst.begin(); it != lst.end(); ++it) {
        if (*it == value) {
            return it;
        }
    } return lst.end();
}

// Task 13
auto autoFind(const list<int>& lst, int value) {
    for (auto it = lst.begin(); it != lst.end(); it++) {
        if (*it == value) {
            return it;
        }
    } return lst.end();
}

// Task 15
bool isEven(int val) {
    return val % 2 == 0;
}

// Task 19
list<int>::iterator outFind(list<int>::iterator begin, list<int>::iterator end, int val) {
    cout << "Running ourFind(): " << endl;
    for (list<int>::iterator it = begin; it != end; ++it) {
        if (*it == val) {
            return it;
        }
    } return end;
}

// Task 20
template<typename T, typename U>
T ourFind_template(T begin, T end, U val) {
    cout << "Running ourFind() in template: " << endl;
    for (T i = begin; i != end; ++i) {
        if (*i == val) {
            return i;
        }
    } return end;
}

int main() {
    // 1. Create a vector with some values and display using ranged for
    cout << "Task 1:\n";
    vector<int> vec {6, 2, 3, 1, 4, 5};
    for (int i : vec) {
        cout << i << ' ';
    }

    cout << "\n=======\n";

    // 2. Initalize a list as a copy of values from the vector
    cout << "Task 2:\n";
    list<int> lst = list(vec.begin(), vec.end());

    cout << "\n=======\n";

    // 3. Sort the original vector.  Display both the vector and the list
    cout << "Task 3:\n";
    sort(vec.begin(), vec.end());

    cout << "\n=======\n";

    // 4. print every other element of the vector.
    cout << "Task 4:\n";
    for (size_t i = 0; i < vec.size(); i++) {
        cout << vec[i] << ' ';
    }

    cout << "\n=======\n";

    // 5. Attempt to print every other element of the list using the
    //    same technique.
    cout << "Task 5:\n";
    // sort(values_list.begin(), values_list.end());
    // for (size_t i = 0; i < values_list.size(); i++) {
    //     cout << values_list[i] << ' ';
    // }

    cout << "\n=======\n";

    //
    // Iterators
    //

    // 6. Repeat task 4 using iterators.  Do not use auto;
    cout << "Task 6:\n";
    vector<int>::iterator vec_it = vec.begin();
    while (vec_it != vec.end()) {
        cout << *vec_it << ' ';
        ++vec_it;
    }

    cout << "\n=======\n";

    // 7. Repeat the previous task using the list.  Again, do not use auto.
    //    Note that you cannot use the same simple mechanism to bump
    //    the iterator as in task 6.
    cout << "Task 7:\n";
    list<int>::iterator list_it = lst.begin();
    while (list_it != lst.end()) {
        cout << *list_it << ' ';
        ++list_it;
    }

    cout << "\n=======\n";

    // 8. Sorting a list
    cout << "Task 8:\n";
    lst.sort();
    for (list<int>::iterator list_it = lst.begin();
        list_it != lst.end(); list_it++) {
        cout << *list_it << ' ';
    }

    cout << "\n=======\n";

    // 9. Calling the function to print the list
    cout << "Task 9:\n";

    cout << "=======\n";

    // 10. Calling the function that prints the list, using ranged-for
    cout << "Task 10:\n";

    cout << "=======\n";

    //
    // Auto
    //

    // 11. Calling the function that, using auto, prints alterate
    // items in the list
    cout << "Task 11:\n";

    cout << "=======\n";


    // 12.  Write a function find that takes a list and value to search for.
    //      What should we return if not found
    cout << "Task 12:\n";

    cout << "=======\n";

    // 13.  Write a function find that takes a list and value to search for.
    //      What should we return if not found
    cout << "Task 13:\n";

    cout << "=======\n";

    //
    // Generic Algorithms
    //

    // 14. Generic algorithms: find
    cout << "Task 14:\n";
    cout << *find(lst.begin(), lst.end(), 4);
    list<int>::iterator it = find(lst.begin(), lst.end(), 8);
    if (it == lst.end()) {
        cout << "Not found." << endl;
    } else { cout << *it << endl; }


    cout << "=======\n";

    // 15. Generic algorithms: find_if
    cout << "Task 15:\n";
    list<int>::iterator it15 = find_if(lst.begin(), lst.end(), isEven);
    if (it15 == lst.end()) {
        cout << "Not found." << endl;
    } else { cout << *it15 << endl; }

    cout << "=======\n";

    // 16. Lambda
    cout << "Task 16:\n";
    list<int>::iterator it16 = find_if(lst.begin(), lst.end(),
        [] (int num) { return num % 2 == 0; });
    if (it16 == lst.end()) {
        cout << "Not found." << endl;
    } else {
        cout << *it16;
    }

    cout << "=======\n";

    // 17. Lambda capture
    cout << "Task 17:\n";
    int divisor;
    cin >> divisor;
    list<int>::iterator it17 = find_if(lst.begin(), lst.end(),
        [divisor] (int num) { return num % divisor == 0; });
    if (it17 == lst.end()) {
        cout << "Not found." << endl;
    } else {
        cout << *it17 << endl;
    }

    cout << "=======\n";

    // 18. Generic algorithms: copy to an array
    cout << "Task 18:\n";
    int* arr = new int[lst.size()];
    copy(lst.begin(), lst.end(), arr);
    for (size_t i = 0; i < lst.size(); i++) {
        cout << arr[i] << ' ';
    } cout << endl;
    delete [] arr;

    cout << "=======\n";

    //
    // Templated Functions
    //

    // 19. Implement find as a function for lists
    cout << "Task 19:\n";
    cout << "find 3: " << *outFind(lst.begin(), lst.end(), 3) << endl;
    cout << "find 44: " << endl;
    list<int>::iterator it19 = outFind(lst.begin(), lst.end(), 44);
    if (it19 == lst.end()) {
        cout << "Not found." << endl;
    } else {
        cout << *it19 << endl;
    }

    cout << "=======\n";

    // 20. Implement find as a templated function
    cout << "Task 20:\n";
    cout << "find 3: \n" << *ourFind_template(lst.begin(), lst.end(), 3) << endl;
    cout << "find 44: " << endl;
    list<int>::iterator it20 = ourFind_template(lst.begin(), lst.end(), 44);
    if (it20 == lst.end()) {
        cout << "Not found." << endl;
    } else {
        cout << *it20 << endl;
    }

    cout << "=======\n";

    //
    // Associative collections
    //

    // 21. Using a vector of strings, print a line showing the number
    //     of distinct words and the words themselves.
    cout << "Task 21:\n";
    ifstream ifs("pooh-nopunc.txt");
    if (!ifs) {
        cerr << "Failed to open file." << endl;
        exit(1);
    }

    vector<string> words;
    string word;
    while (ifs >> word) {
        if (words.end() == find(words.begin(), words.end(), word)) {
            words.push_back(word);
        }
    }

    cout << words.size();
    // for (const string& str : words) {
    //     cout << str << endl;
    // }

    cout << "\n=======\n";

    // 22. Repeating previous step, but using the set
    cout << "Task 22:\n";
    ifs.clear();
    ifs.seekg(0, ios::beg);

    set<string> words_set;
    while(ifs >> word) {
        words_set.insert(word);
    }

    cout << words_set.size() << endl;

    cout << "=======\n";

    // 23. Word co-occurence using map
    cout << "Task 23:\n";
    ifs.clear();
    ifs.seekg(0, ios::beg);

    map<string, vector<int>> wordMap;
    int index = 1;
    while (ifs >> word) {
        wordMap[word].push_back(index);
        index++;
    }

    for (const auto& pair : wordMap) {
        cout << "\"" << pair.first << "\" positions: ";
        for (int i : pair.second) {
            cout << i << ' ';
        } cout << endl;
    } ifs.close();

    cout << "=======\n";
}
