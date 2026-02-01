/*
1. Default constructor
2. Parameterized ctor
3. Copy Ctor
4. Copy Assigment ctor
5. Move Ctor
6. Move Assignment ctor
7. Utilites
      a. length
      b. [] index
      c. concat(c=a+b)
      d. comparison (==)
      e. not equal(!=)
      f. raw pointer
      g. substr
      i. cout
8. Destructor
*/

#include<iostream>
#include<cstring>
using namespace std;

class MyString {
private:
	char* data;
	size_t len;

public:
	// Assigning default values
	MyString(){
		data = NULL;
		len = 0;
	}
	// Assinging passed values
    // const bcz string literals are immutables
    // and constructor does not modify input->only read and deep copy.
	MyString(const char* str){
        if(str == NULL){
            data = NULL;
            len = 0;
            return;
        }

        len = strlen(str);
        data = new char[len+1];
        strcpy(data, str);
	}

    // Copy constructor->Deep Copy->to avoid double free
    MyString(const MyString& other) {
        len = other.len;

        if(other.data){
            data = new char[len+1];
            strcpy(data, other.data);
        }
        else{
            data = NULL;
        }
    }

    // Copy assignment(=) operator
    MyString& operator=(const MyString& other){
        // check self assignment operator
        if(this == &other){
            return *this;
        }

        // to prevent memory leak;
        delete[] data;

        len = other.len;
        // Deep copy
        if(other.data){
            data = new char[len+1];
            strcpy(data, other.data);
        }
        else{
            data = NULL;
        }

        return *this;
    }

    //Move constructor-> steals resources->avoids deep copy->improves performance
    MyString(MyString&& other) noexcept {
        data = other.data;
        len = other.len;

        other.data = NULL;
        other.len = 0;
    }

    //Move Assignment Operator
    MyString& operator=(MyString&& other) noexcept {
        // check self assignment operator
        if(this == &other){
            return *this;
        }

        // to prevent memory leak;
        delete[] data;

        data = other.data;
        len = other.len;

        other.data = NULL;
        other.len = 0;

        return *this;
    }

    // Utilities Functions

    // Length
    size_t length() const {
        return len;
    }

    // operator[]
    const char& operator[](size_t index) const {
        return data[index];
    }

    // String concatenation
    MyString operator+(MyString& other) const{
        MyString result;
        result.len = this->len + other.len;
        result.data =  new char[result.len+1];

        if(data){
            strcpy(result.data, data);
        }
        else{
            result.data[0] = '\0';
        }

        if(other.data)
            strcat(result.data, other.data);

        return result;

    }

    // Comparison operators
    bool operator==(const MyString& other) const {
        return strcmp(data, other.data) == 0;
    }

    // not equal to
    bool operator!=(const MyString& other) const {
        return !(*this == other);
    }

    // raw pointer access
    const char* c_str() const {
      return data;
    }

    // substring
    MyString substr(size_t pos, size_t count) const {
        MyString result;

        if(data==NULL || pos>=len)
            return result; // empty string
                        
        size_t n = (pos + count) > len ? (len - pos) : count;

        result.len = n;
        result.data = new char[n+1];

        memcpy(result.data, data+pos, n);
        result.data[n] = '\0';

        return result;
    }

    // cout
    friend std::ostream& operator<<(std::ostream& os, const MyString& s) {
        return os << s.data;
    }

    // Destructor
    ~MyString(){
        delete[] data;
    }

};

int main(){
    MyString s1("Deepanker");
    MyString s2(" Rawat");

    MyString c = s1 + s2;
    cout << c[2] << " " << c.length() << endl;

    for(int i=0;i<c.length();i++){
        cout<<c[i];
    }
    cout<<endl;

    std::cout << "Concatenated: " << c << "\n"; // Deepanker Rawat

    std::cout << "Length: " << c.length() << "\n";         // 15
    std::cout << "C-String: " << c.c_str() << "\n";        // Deepanker Rawat
    std::cout << "Substring (6,5): " << c.substr(6, 5) << "\n"; // ker R

    std::cout << "Char at index 0: " << c[0] << "\n";       // D

    MyString d("Hello World");
    std::cout << "c == d: " << (c == d ? "True" : "False") << "\n"; // False

    MyString e = std::move(c);
    std::cout << "Moved string: " << e << "\n"; // Deepanker Rawa
    std::cout << "Original after move: " << c << "\n"; // (empty or garbage-safe)

}

/*
deepankerrawat@MacBookAir Implementation % ./a.out                  
e 15
Deepanker Rawat
Concatenated: Deepanker Rawat
Length: 15
C-String: Deepanker Rawat
Substring (6,5): ker R
Char at index 0: D
c == d: False
Moved string: Deepanker Rawat
zsh: segmentation fault  ./a.out
deepankerrawat@MacBookAir Implementation % 
*/


