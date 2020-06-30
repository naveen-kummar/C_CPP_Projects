#include <iostream>
#include <string>
#include <memory>
#include <algorithm>
#include<vector>

using namespace std;

class IMemo
{
    virtual size_t Length() const = 0;
};

class MemoryBlock : public IMemo
{
public:

    // Simple constructor that initializes the resource.
    MemoryBlock(size_t length)
        : _length(length)
        , _data(new int[length])
    {
        std::cout << "Normal ctor In MemoryBlock(size_t). length = "
            << _length << "." << std::endl;
    }

    // Destructor.
    virtual ~MemoryBlock()
    {
        std::cout << "Normal Dtor In ~MemoryBlock(). length = "
            << _length << ".";

        if (_data != nullptr)
        {
            //std::cout << " Deleting resource.";
            // Delete the resource.
            delete[] _data;
        }

        std::cout << std::endl;
    }

    // Copy constructor.
    MemoryBlock(const MemoryBlock& other)
        : _length(other._length)
        , _data(new int[other._length])
    {
        std::cout << "Normal Copy In MemoryBlock(const MemoryBlock&). length = "
            << other._length << ". Copying resource." << std::endl;

        std::copy(other._data, other._data + _length, _data);
    }

    // Copy assignment operator.
    MemoryBlock& operator=(const MemoryBlock& other)
    {
        std::cout << "Normal assignment In operator=(const MemoryBlock&). length = "
            << other._length << ". Copying resource." << std::endl;

        if (this != &other)
        {
            // Free the existing resource.
            delete[] _data;

            _length = other._length;
            _data = new int[_length];
            std::copy(other._data, other._data + _length, _data);
        }
        return *this;
    }

    // Move constructor.
    MemoryBlock(MemoryBlock&& other) noexcept
        : _data(nullptr)
        , _length(0)
    {
        std::cout << "MOVE COPY In MemoryBlock(MemoryBlock&&). length = "
            << other._length << ". Moving resource." << std::endl;

        // Copy the data pointer and its length from the
        // source object.
        _data = other._data;
        _length = other._length;

        // Release the data pointer from the source object so that
        // the destructor does not free the memory multiple times.
        other._data = nullptr;
        other._length = 0;
    }

    // Move assignment operator.
    MemoryBlock& operator=(MemoryBlock&& other) noexcept
    {
        std::cout << "MOVE ASSIGNMENT In operator=(MemoryBlock&&). length = "
            << other._length << "." << std::endl;

        if (this != &other)
        {
            // Free the existing resource.
            delete[] _data;

            // Copy the data pointer and its length from the
            // source object.
            _data = other._data;
            _length = other._length;

            // Release the data pointer from the source object so that
            // the destructor does not free the memory multiple times.
            other._data = nullptr;
            other._length = 0;
        }
        return *this;
    }

    // Retrieves the length of the data resource.
    size_t Length() const override
    {
        return _length;
    }

private:
    size_t _length; // The length of the resource.
    int* _data; // The resource.
};

int main2()
{
    {
        //MemoryBlock local(32);
      //  std::shared_ptr<MemoryBlock> unique_local = std::make_shared < MemoryBlock>(42);
        vector<std::shared_ptr<IMemo>> vec;
        cout << "1 Size of vector = " << vec.size() << endl;
        vec.push_back(std::move(std::make_unique < MemoryBlock>(42)));
        //v.push_back(std::make_unique<MemoryBlock>(75));

        // Insert a new element into the second position of the vector.
        //v.insert(v.begin() + 1, MemoryBlock(50));

        cout << "2 Size of vector = " << vec.size() << endl;
       
        for (auto e : vec)
        {
            e.reset();
        }

    }


    getchar();
    return 0;

}