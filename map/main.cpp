#include <iostream>
#include <vector>

#include <map>
#include <unordered_map>

struct CityRecord
{
	std::string Name;
	uint64_t Population;
	double Latitude, Longitude;
	
};

//for map, you need to provide the overloading of less than operator
//for unordered_map, you need to provide the hash function
namespace std {
	template<>
	struct hash<CityRecord>
	{
		//return a 64bit integer which is the hash value
		size_t operator()(const CityRecord& key)
		{
			return hash<std::string>()(key.Name);
		}
	};
}


int main()
{
	std::unordered_map<std::string, CityRecord> cityMap;
	cityMap["Berlin"] = CityRecord{ "Berlin",50000,2.4,7.7 };
	cityMap["Shanghai"] = CityRecord{ "Shanghai",50000,2.4,7.7 };
	cityMap["Paris"] = CityRecord{ "Paris",50000,2.4,7.7 };
	cityMap["London"] = CityRecord{ "London",50000,2.4,7.7 };
	cityMap["Peking"] = CityRecord{ "Peking",50000,2.4,7.7 };
	cityMap["Melbourne"] = CityRecord{ "Melbourne",50000,2.4,7.7 };
		
	auto& x = cityMap["Berlin"];
	//notice, the first type is the key, and you have to provide the hash function so that the compiler know how to hash that user-defined type.
	std::unordered_map<std::string, CityRecord> u_cityMap;
	std::unordered_map<CityRecord, uint16_t> u_cityMap2;

	//what did the operator of index[] actually do? 
	//if I use cityMap["berlin"], the map will automatically insert it. there is no const version of this operation, you can hit F12 to prove that.
	//insert "Berlin" into the unordered_map, and then give me a reference to that newly inserted cityRecord.
	//what's the advantage here?
	//if I want to fill out a bunch of data and I just want to have access to taht cityRecord already in the right place, this is great
	auto& berlinData1 = cityMap["berlin"];
	berlinData1.Population = 1233456;

	//the downside here is that you're creating it first on the stack and then you copy it from stack into the map.
	CityRecord berlinData2;
	berlinData2.Name = "berlin";
	berlinData2.Population = 5151515;
	cityMap["berlin"] = berlinData2;

	//if you certainly don't want to insert a new data, you can use .at() function.
	//and you have to prove that this element has already existed or you'll get a crash.
	const auto& cities = cityMap;
	//const auto& berlinData3 = cities.at("b");

	//so how to check?
	if (cities.find("b") != cities.end()) {
		const auto& berlinData3 = cities.at("b");
	}

	//usually vector is the most popular data structure because it just stores all your memory in a row and you probably do not need these fancy indexing system like this.
	//however iterating through maps is not the slowest thing in the world, it is slower than a vector for sure.

	for (auto& [name, city]:cityMap)
	{
		std::cout << name << "\n Population: " << city.Population << "\n";;
	}

	if(const auto it = cities.find("Berlin"); it != cities.end()) {//C++17 if-initializer syntax
		const CityRecord& berlinData = it->second;
		// ...
	}
	std::cin.get();
	return 0;
}