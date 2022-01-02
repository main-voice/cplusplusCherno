#include <iostream>
#include <string>
#include "Vector.h"
#include "vec3.h"

template <typename T>
void PrintVector(const Vector<T>& vector) {
	std::cout << "==========================\n";
	for (size_t i = 0; i < vector.Size(); i++) {
		std::cout << vector[i] << std::endl;
	}
	std::cout << "==========================\n";
}


void PrintVector(Vector<Vector3>& vector) {
	std::cout << "==========================\n";
	for (size_t i = 0; i < vector.Size(); i++) {
		//std::cout << vector[i].x << ", " << vector[i].y << ", " << vector[i].z << ", " << std::endl;
		std::cout << vector[i] << std::endl;
	}
	std::cout << "==========================\n";
}

int main()
{
#if 0
	{
		Vector<Vector3> vector;
#if 0
		vector.PushBack(Vector3(1.0f));
		vector.PushBack(Vector3(1.2f, 3.2f, 5.4f));
		vector.PushBack(Vector3());
		PrintVector(vector);
#endif

		vector.EmplaceBack(1.0f);
		vector.EmplaceBack(1.2f, 3.2f, 5.4f);
		vector.EmplaceBack();
		vector.EmplaceBack(6.2f, -5.2f, 2.4f);
		vector.EmplaceBack(4.2f, 6.2f, 5.4f);

		PrintVector(vector);

		vector.PopBack();//we have call the destructor of Vector3
		vector.PopBack();

		PrintVector(vector);
		vector.EmplaceBack(1.2f, 3.2f, .5f);
		vector.EmplaceBack(3.2f, 4.64f, 7.4f);

		PrintVector(vector);

	}
#endif

#if 0
	Vector<int> i_vector;
	i_vector.PushBack(1);
	i_vector.PushBack(2);
	i_vector.PushBack(3);
	i_vector.PushBack(4);
	i_vector.PushBack(5);

	std::cout << "Normal Loop:\n";
	for (size_t i = 0; i < i_vector.Size(); i++) {
		std::cout << i_vector[i] << std::endl;
	}

	std::cout << "Range-based for loop:\n";
	for (int value : i_vector) {
		std::cout << value << std::endl;
	}

	std::cout << "Iterator:\n";
	for (Vector<int>::Iterator it = i_vector.begin(); it != i_vector.end(); it++) {
		std::cout << *it << std::endl;
	}
#endif // integer

#if 0
	Vector<std::string> str_vector;
	str_vector.EmplaceBack("1");
	str_vector.EmplaceBack("2");
	str_vector.EmplaceBack("Main Voice");
	str_vector.EmplaceBack("4");
	str_vector.EmplaceBack("5");
	std::cout << "==================\n";

	std::cout << "Normal Loop:\n";
	for (size_t i = 0; i < str_vector.Size(); i++) {
		std::cout << str_vector[i] << std::endl;
	}
	std::cout << "==================\n";
	std::cout << "Range-based for loop:\n";
	for (auto& value : str_vector) {
		std::cout << value << std::endl;
	}
	std::cout << "==================\n";

	std::cout << "Iterator:\n";
	for (Vector<std::string>::Iterator it = str_vector.begin();
		it != str_vector.end(); it++) {
		std::cout << *it << std::endl;
	}
#endif //string



#if 1
	Vector<std::string> str_vector;
	std::string str1 = "1";
	str_vector.PushBack(str1);
	str_vector.PushBack("2");
	str_vector.PushBack("Main Voice");
	str_vector.PushBack("4");
	str_vector.PushBack("5");
	std::cout << "==================\n";

	std::cout << "Normal Loop:\n";
	for (size_t i = 0; i < str_vector.Size(); i++) {
		std::cout << str_vector[i] << std::endl;
	}
	std::cout << "==================\n";
	std::cout << "Range-based for loop:\n";
	for (auto& value : str_vector) {
		std::cout << value << std::endl;
	}
	std::cout << "==================\n";

	std::cout << "Iterator:\n";
	for (Vector<std::string>::Iterator it = str_vector.begin();
		it != str_vector.end(); it++) {
		std::cout << *it << std::endl;
	}
#endif //string

	return 0;
}