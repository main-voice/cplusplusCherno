#pragma once

#include <iostream>
#include <assert.h>

struct Vector3 {
	float x = 0.0f, y = 0.0f, z = 0.0f;
	int* m_memoryBlock = nullptr;

public:
#if 0
	Vector3& operator = (Vector3& other)noexcept {
		std::cout << "Copy operator!\n";
		this->x = other.x;
		this->y = other.y;
		this->z = other.z;
		return *this;
	}
	const Vector3& operator = (const Vector3& other)noexcept {
		std::cout << "Const Copy operator!\n";
		this->x = other.x;
		this->y = other.y;
		this->z = other.z;
		return *this;
	}
#endif
	Vector3& operator = (const Vector3&& other) = delete;
	Vector3& operator = (Vector3&& other) {
		std::cout << "Move operator!\n";
		this->x = other.x;
		this->y = other.y;
		this->z = other.z;
		m_memoryBlock = other.m_memoryBlock;
		other.m_memoryBlock = nullptr;

		return *this;
	}

	friend std::ostream& operator<<(std::ostream& output, const Vector3& vector3) {
		std::cout << "\n(" << vector3.x << ", " << vector3.y << ", " << vector3.z << ")";
		return output;
	}
	Vector3() noexcept { m_memoryBlock = new int[5]; assert(m_memoryBlock); }
	Vector3(float scalar) noexcept
		:x(scalar), y(scalar), z(scalar) {
		m_memoryBlock = new int[5];
	}
	Vector3(float x, float y, float z) noexcept {
		this->x = x; this->y = y; this->z = z;
		m_memoryBlock = new int[5];
	}

	Vector3(const Vector3& other) noexcept
		:x(other.x), y(other.y), z(other.z) {
		printf("Copy Constructor!\n");
		for (size_t i = 0; i < 5; i++) {
			m_memoryBlock[i] = other.m_memoryBlock[i];
		}
	}

	Vector3(Vector3&& other) noexcept
		:x(other.x), y(other.y), z(other.z) {
		printf("Moved Constructor!\n");
		m_memoryBlock = other.m_memoryBlock;
		other.m_memoryBlock = nullptr;
	}

	~Vector3() {
		printf("Destory!\n");
		delete[] m_memoryBlock;
	}
};