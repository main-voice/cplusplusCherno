#pragma once

template <typename Vector>
class VectorIterator
{
public:
	using ValueType = typename Vector::ValueType;
	using PointerType = ValueType*;
	using ReferenceType = ValueType&;

public:
	VectorIterator(PointerType ptr)// the basic of the iterator, where it's currently pointing to
		:m_ptr(ptr) {
	}

	VectorIterator& operator++()
	{
		m_ptr++; // m_ptr will point to a value of specific type, when it increases itself, it just will move to current+sizeof(T)
		return*this;
	}

	const VectorIterator operator++(int)
	{
		VectorIterator it = *this;
		//m_ptr++;
		++(*this);
		return it;
	}

	VectorIterator& operator--()
	{
		m_ptr--; // m_ptr will point to a value of specific type, when it increases itself, it just will move to current+sizeof(T)
		return*this;
	}

	const VectorIterator operator--(int)
	{
		VectorIterator it = *this;
		//m_ptr++;
		--(*this);
		return it;
	}

	ReferenceType operator[](int index)
	{
		return *(m_ptr + index);
	}

	PointerType operator->()
	{
		return m_ptr;
	}

	ReferenceType operator*()
	{
		return *m_ptr;
	}

	bool operator==(VectorIterator other)const
	{
		return m_ptr == other.m_ptr;
	}

	bool operator!=(VectorIterator other)const
	{
		return !(*this == other);
	}
private:
	PointerType m_ptr;
};


template <typename T>
class Vector
{
private:
	size_t m_size = 0;
	size_t m_capacity = 0;
	T* m_data = nullptr;

public:
	using ValueType = T;
	using Iterator = VectorIterator<Vector<ValueType>>;

private:
	void ReAlloc(size_t newCapacity)
	{
		// 1. allocate a new block of memory
		// 2. copy/move old elements into new block
		// 3. delete

		//T* newBlock = new T[newCapacity];
		////because of the pointer, may delete twice(when we pop one element, we call its destructor, and when we delete the vector, we call destructor of every element again, so we maybe call the destructor twice), we instead want to call the version that do not call the constructor(or the destructor), we just want to get(delete) a block of memory which had better be empty

		T* newBlock = (T*)(::operator new(newCapacity * sizeof(T)));
		if (newCapacity < m_size) {
			m_size = newCapacity;
		}

		//this will make an error, because we call the move operator which move an existing object to another place where exist an object had been created, but when we allocate memory above, we didn't call the constructor. So it will not gonna work.
		/*for (size_t i = 0; i < m_size; i++)
			newBlock[i] = std::move(m_data[i]);*/

		for (size_t i = 0; i < m_size; i++)
		{
			new(&newBlock[i]) T(std::move(m_data[i]));
		}

		for (size_t i = 0; i < m_size; i++)
		{
			m_data[i].~T();
		}
		//delete[]m_data;
		//same as delete, we shouldn't call the destructor
		::operator delete(m_data, m_capacity * sizeof(T));

		m_data = newBlock;

		m_capacity = newCapacity;
	}

public:
	// some basic operation of the vector
	Vector()
	{
		//allocate two elements by default
		ReAlloc(2);
	}
	~Vector() {
		//delete[] m_data;//if Vector<Vector<>*> the user shuold free the memory instead of here
		Clear();//Clear will go through and call all the destructors
		::operator delete(m_data, m_capacity * sizeof(T));//this will never call any destructor 
		std::cout << "Destory the Vector\n";
	}

	template<typename... Args>
	T& EmplaceBack(Args&&...args)
	{
		if (m_size >= m_capacity) {
			ReAlloc(m_capacity + m_capacity / 2);
		}

		//construct elements here
		//m_data[m_size] = T(std::forward<Args>(args)...);
		//actually we still create a temporary object here, and we destory them. At the beginning, we create in the frame of stack of main, and we copy/move that object into this stack. Now we create in the frame of this, and we move that object to its destination

		//Why not construct it inside your data storage ?
		//We could use the placement new operator, just like below
		new(&m_data[m_size]) T(std::forward<Args>(args)...);

		return m_data[m_size++];
	}

	void PopBack()
	{
		if (m_size > 0) {
			m_size--;
			m_data[m_size].~T();//call the destructor explicitly
		}
	}

	void Clear()
	{
		for (size_t i = 0; i < m_size; i++) {
			m_data[i].~T();
		}
		m_size = 0;
	}

	void PushBack(const T& value)
	{
		if (m_size >= m_capacity) {
			ReAlloc(m_capacity + m_capacity / 2);
		}

		//m_data[m_size] = std::move(value); // move operator, it failed (type is std::string)
		//m_data[m_size] = (value); // copy operator, it failed
		new(&m_data[m_size]) T(std::move(value)); // because you just allocate a block of memory and you disn't call the constructor, so if you use string and pushback
		m_size++;
	}

	size_t Size()const { return m_size; }

	T& operator[] (size_t posi)
	{
		if (posi >= m_size) {
			return m_data[m_size];
		}
		return *(m_data + posi);
	}

	const T& operator[] (size_t posi) const
	{
		if (posi >= m_size) {
			return m_data[m_size];
		}
		return *(m_data + posi);
	}

public:
	//the iterator of this class

	Iterator begin() //it need to return a new iterator at a patricular position
	{
		return Iterator(m_data);//is this ?
	}

	Iterator end() //it need to return a new iterator at a patricular position
	{
		return Iterator(m_data + m_size);// apparently it's outside of the caild range
	}


};
