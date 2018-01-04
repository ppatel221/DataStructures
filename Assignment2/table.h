#include <string>
#include <utility>
using namespace std;

template <class TYPE>
class Table {
public:
    Table()
    {
    }
    virtual bool update(const string& key, const TYPE& value) = 0;
    virtual bool remove(const string& key) = 0;
    virtual bool find(const string& key, TYPE& value) = 0;
    virtual int numRecords() const = 0;
    virtual bool isEmpty() const = 0;
    virtual ~Table()
    {
    }
};

template <class TYPE>
class SimpleTable : public Table<TYPE> {
    struct Record {
        TYPE data_;
        string key_;
        Record(const string& key, const TYPE& data)
        {
            key_ = key;
            data_ = data;
        }
    };

    Record** records_;
    int max_;
    int size_;
    int search(const string& key);
    void sort();
    void grow();

public:
    SimpleTable(int maxExpected);
    SimpleTable(const SimpleTable& other);
    SimpleTable(SimpleTable&& other);
    virtual bool update(const string& key, const TYPE& value);
    virtual bool remove(const string& key);
    virtual bool find(const string& key, TYPE& value);
    virtual const SimpleTable& operator=(const SimpleTable& other);
    virtual const SimpleTable& operator=(SimpleTable&& other);
    virtual ~SimpleTable();
    virtual bool isEmpty() const
    {
        return size_ == 0;
    }
    virtual int numRecords() const
    {
        return size_;
    }
};

//returns index of where key is found.
template <class TYPE>
int SimpleTable<TYPE>::search(const string& key)
{
    int left = 0;
    int right = size_ - 1;

    while (left <= right) {
        int middle = (left + right) / 2;

        if (records_[middle]->key_ == key)
            return middle;

        else if (records_[middle]->key_ > key)
            right = middle - 1;
        else
            left = middle + 1;
    }
    return -1;
}
//sort the according to key in table
template <class TYPE>
void SimpleTable<TYPE>::sort()
{
    int minIdx = 0;
    for (int i = 0; i < size_; i++) {
        minIdx = i;
        for (int j = i + 1; j < size_; j++) {
            if (records_[j]->key_ < records_[minIdx]->key_) {
                minIdx = j;
            }
        }
        Record* tmp = records_[i];
        records_[i] = records_[minIdx];
        records_[minIdx] = tmp;
    }
}

// grow the array by one element
template <class TYPE>
void SimpleTable<TYPE>::grow()
{
    Record** newArray = new Record*[max_ * 2];

    if (newArray) {
        max_ = max_ * 2;
        for (int i = 0; i < size_; i++) {
            newArray[i] = records_[i];
        }
        delete[] records_;
        records_ = newArray;
    }
}

//Creates a record with the size of maxExpected.
template <class TYPE>
SimpleTable<TYPE>::SimpleTable(int maxExpected)
    : Table<TYPE>()
{
    records_ = new Record*[maxExpected];
    max_ = maxExpected;
    size_ = 0;
}

//copy constructor to copy records
template <class TYPE>
SimpleTable<TYPE>::SimpleTable(const SimpleTable<TYPE>& other)
{
    records_ = new Record*[other.max_];
    max_ = other.max_;
    size_ = 0;
    for (int i = 0; i < other.size_; i++) {
        records_[size_++] = new Record(other.records_[i]->key_, other.records_[i]->data_);
    }
}

//move constructor to copy records
template <class TYPE>
SimpleTable<TYPE>::SimpleTable(SimpleTable<TYPE>&& other)
{
    size_ = other.size_;
    max_ = other.max_;
    records_ = other.records_;

    other.records_ = nullptr;
    other.size_ = 0;
    other.max_ = 0;
}

//passes key-value pair to update a record. Returns true if the record is updated, otherwise false
template <class TYPE>
bool SimpleTable<TYPE>::update(const string& key, const TYPE& value)
{
    int idx = search(key);
    if (idx == -1) {
        if (size_ == max_) {
            grow();
        }

        int i = size_;
        while ((i > 0) && key < records_[i - 1]->key_) {
            records_[i] = records_[i - 1];
            --i;
        }

        records_[i] = new Record(key, value);
        ++size_;
    }
    else {
        records_[idx]->data_ = value;
    }
    return true;
}

//passes a key. if table has a record with matching key, the record is removed from the table.
template <class TYPE>
bool SimpleTable<TYPE>::remove(const string& key)
{
    int idx = search(key);
    if (idx != -1) {
        delete records_[idx];
        for (int i = idx; i < size_ - 1; i++) {
            records_[i] = records_[i + 1];
        }
        size_--;
        return true;
    }
    else {
        return false;
    }
}

//passes key and a reference for passing back a found value. if the table has a record with matching key. function returns true nad passes back the value from the record, False otherwise.
template <class TYPE>
bool SimpleTable<TYPE>::find(const string& key, TYPE& value)
{
    int idx = search(key);
    if (idx == -1)
        return false;
    else {
        value = records_[idx]->data_;
        return true;
    }
}

//Assignment operator
template <class TYPE>
const SimpleTable<TYPE>& SimpleTable<TYPE>::operator=(const SimpleTable<TYPE>& other)
{
    
    if(this != &other){
        if(max_ < other.max_){
            delete [] records_;

            records_ = new Record*[max_];
            size_=0;
            max_ = other.max_;
        }

        for(int i=other.size_; i < size_ ; i++){
            delete records_[i];
            records_[i]=nullptr;
        }

        for(int i=0; i< other.size_; ++i){
            if(records_[i]){
                *records_[i] = *other.records_[i];
            }else{
                records_[i] = new Record(other.records_[i]->key_, other.records_[i]->data_);
            }
        }
        size_ = other.size_;
        max_ = other.max_;
    }
    return *this;
}

//move assignment operator
template <class TYPE>
const SimpleTable<TYPE>& SimpleTable<TYPE>::operator=(SimpleTable<TYPE>&& other)
{
    swap(records_, other.records_);
    swap(size_, other.size_);
    swap(max_, other.max_);
    return *this;
}

//deletes all records.
template <class TYPE>
SimpleTable<TYPE>::~SimpleTable()
{
    if (records_) {
        int sz = size_;
        for (int i = 0; i < sz; i++) {
            remove(records_[0]->key_);
        }
        delete[] records_;
    }
}

template <class TYPE>
class LPTable : public Table<TYPE> {
    struct Record {
        TYPE data_;
        string key_;

        Record(const string& key, const TYPE& data)
        {
            key_ = key;
            data_ = data;
        }
    };

    Record** myTable;
    int max_;
    int count_;

public:
    LPTable(int maxExpected);
    LPTable(const LPTable& other);
    LPTable(LPTable&& other);
    virtual bool update(const string& key, const TYPE& value);
    virtual bool remove(const string& key);
    virtual bool find(const string& key, TYPE& value);
    virtual const LPTable& operator=(const LPTable& other);
    virtual const LPTable& operator=(LPTable&& other);
    virtual ~LPTable();
    bool isEmpty() const;
    int numRecords() const;
    int findIndex(const string& key);
    bool isFull() const;
};

//initializing table of size max_
template <class TYPE>
LPTable<TYPE>::LPTable(int maxExpected)
    : Table<TYPE>()
{
    if (maxExpected > 0) {
        max_ = maxExpected * 3;
        count_ = 0;
        myTable = new Record*[max_];

        for (int i = 0; i < max_; i++) {
            myTable[i] = nullptr;
        }
    }
    else {
        max_ = count_ = 0;
        myTable = nullptr;
    }
}

//copy constructor to copy records into table.
template <class TYPE>
LPTable<TYPE>::LPTable(const LPTable<TYPE>& other)
{
    myTable = new Record*[other.max_];
    max_ = other.max_;

    for (int i = 0; i < max_; i++) {
        if (other.myTable[i]) {
            myTable[i] = new Record(other.myTable[i]->key_, other.myTable[i]->data_);
        }
        else {
            myTable[i] = nullptr;
        }
    }
    count_ = other.count_;
}

//move constructor
template <class TYPE>
LPTable<TYPE>::LPTable(LPTable<TYPE>&& other)
{
    myTable = other.myTable;
    count_ = other.myTable;
    max_ = other.myTable;

    other.myTable = nullptr;
    other.max_ = 0;
    other.count_ = 0;
}

//returns true if table is empty, false otherwise
template <class TYPE>
bool LPTable<TYPE>::isEmpty() const
{
    if (count_ == 0) {
        return true;
    }
    else {
        return false;
    }
}

//returns true if table is full, false otherwise
template <class TYPE>
bool LPTable<TYPE>::isFull() const
{
    if (count_ == max_) {
        return true;
    }
    else {
        return false;
    }
}

//returns number of records in the table
template <class TYPE>
int LPTable<TYPE>::numRecords() const
{
    return count_;
}

//finds and returns index of a given key 
template <class TYPE>
int LPTable<TYPE>::findIndex(const string& key)
{
    std::hash<std::string> hashFunction;
    int idx = -1;

    if (max_ != 0) {
        idx = hashFunction(key) % max_;
    }

    return idx;
}

//passed key-value pair. Returns true if the table added the record successfully, false otherwise 
template <class TYPE>
bool LPTable<TYPE>::update(const string& key, const TYPE& value)
{
    bool result = false;
    int idx = 0;
    idx = findIndex(key);

    while (myTable[idx] != nullptr && myTable[idx]->key_ != key && idx < (max_ - 1)) {
        idx++;

        if (idx == max_) {
            idx = 0;
        }
    }

    if (myTable[idx] == nullptr) {
        myTable[idx] = new Record(key, value);
        result = true;
    }
    else if (myTable[idx]->key_ == key) {
        myTable[idx]->data_ = value;
        result = true;
    }
    return result;
}

//passed a key and reference for passing back found value. If table has a record with matching key, It retrns true and passes value from the record. Otherwise returns false.
template <class TYPE>
bool LPTable<TYPE>::find(const string& key, TYPE& value)
{
    int idx = 0;
    int i = 0;
    bool result = false;
    idx = findIndex(key);

    if (myTable[idx] != nullptr) {
        if (myTable[idx]->key_ == key) {
            value = myTable[idx]->data_;
            result = true;
        }
        else {
            if (idx == max_ - 1) {
                i = 0;
            }
            else {
                i = idx + 1;
            }

            while (i != idx && !result && myTable[i] != nullptr) {
                if (myTable[i]->key_ == key) {
                    value = myTable[i]->data_;
                    result = true;
                }

                if (i >= max_ - 1) {
                    i = 0;
                }
                else {
                    i = i + 1;
                }
            }
        }
    }
    else {
        result = false;
    }

    return result;
}

//paased a key, if table contains a record with matching key, the record is removed.
template <class TYPE>
bool LPTable<TYPE>::remove(const string& key)
{
    int idx = 0;
    bool deleted = false;
    idx = findIndex(key);
    int i = 0;

    if (myTable[idx] != nullptr) {
        if (myTable[idx]->key_ == key) {
            myTable[idx]->key_ = "NO DATA";
            deleted = true;
        }
        else {
            if (idx == max_ - 1) {
                i = 0;
            }
            else {
                i = idx + 1;
            }

            while (i != idx && !deleted && myTable[i] != nullptr) {
                if (myTable[i]->key_ == key) {
                    myTable[i]->key_ = "NO DATA";
                    deleted = true;
                }

                if (i >= max_ - 1) {
                    i = 0;
                }
                else {
                    i = i + 1;
                }
            }
        }
    }
    return deleted;
}

//Assignment operator
template <class TYPE>
const LPTable<TYPE>& LPTable<TYPE>::operator=(const LPTable<TYPE>& other)
{
    if (this != &other) {
        delete[] myTable;
        max_ = other.max_;
        count_ = other.count_;

        if (other.myTable != nullptr) {
            myTable = new Record*[other.max_];

            for (int i = 0; i < max_; i++) {
                if (other.myTable[i] != nullptr) {
                    myTable[i] = new Record(other.myTable[i]->key_, other.myTable[i]->data_);
                }
                else {
                    myTable[i] = nullptr;
                }
            }
        }
        else {
            myTable = nullptr;
        }
    }

    return *this;
}

//Move assignment operator
template <class TYPE>
const LPTable<TYPE>& LPTable<TYPE>::operator=(LPTable<TYPE>&& other)
{
    if (this != &other) {
        delete[] myTable;
        max_ = other.max_;
        count_ = other.count_;
        myTable = other.myTable;
        other.max_ = 0;
        other.count_ = 0;
        other.myTable = nullptr;
    }

    return *this;
}

//deletes all records from table.
template <class TYPE>
LPTable<TYPE>::~LPTable()
{
    for (int i = 0; i < max_; i++) {
        if (myTable[i] != nullptr) {
            delete myTable[i];
            myTable[i] = nullptr;
        }
    }

    delete[] myTable;
    myTable = nullptr;
}
