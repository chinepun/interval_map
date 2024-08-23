#include <map>
#include <iostream>
#include <iterator>
template<typename K, typename V>
class interval_map {
	friend void IntervalMapTest();
	V m_valBegin;
	std::map<K,V> m_map;
public:
	// constructor associates whole range of K with val
	interval_map(V const& val)
	: m_valBegin(val)
	{}

	// Assign value val to interval [keyBegin, keyEnd).
	// Overwrite previous values in this interval.
	// Conforming to the C++ Standard Library conventions, the interval
	// includes keyBegin, but excludes keyEnd.
	// If !( keyBegin < keyEnd ), this designates an empty interval,
	// and assign must do nothing.
// template<typename K, typename V>
	void assign( K const& keyBegin, K const& keyEnd, V const& val ) {
		// INSERT YOUR SOLUTION HERE

		// typedef typename std::map<K, V>::iterator MapIterator;	
		using MapIterator = typename std::map<K, V>::iterator;

		if ( !(keyBegin < keyEnd) ) return;

		if (m_map.empty())
		{
			if (val == m_valBegin) return;
			m_map.insert(m_map.begin(), std::make_pair(keyBegin, val));

			m_map.insert(std::make_pair(keyEnd, m_valBegin));
			return;
		}

		m_map.insert(std::make_pair(keyBegin, val));
		MapIterator end_value = std::prev(m_map.end());
	
		if (end_value->first < keyEnd)
		{
			if (end_value->second == m_valBegin)
			{ 
				m_map.erase(end_value);
			}	
			
			m_map.insert(std::make_pair(keyEnd, m_valBegin));
		}

		MapIterator value = m_map.find(keyBegin);
		MapIterator prev_value = std::prev(value);
		MapIterator next_value = std::next(value);

		// must be canonical
		if ( prev_value->second == value->second || value->second == next_value->second ) 
		{ 
			m_map.erase(value);
		}

		if (m_map.begin()->second == m_valBegin)
		{
			m_map.erase(m_map.begin());
		}
	}

	void print()
	{
		for (const auto &[k, v] : m_map)
		{
			std::cout << k << ',' << v << std::endl;
		}
	}

	// look-up of the value associated with key
	V const& operator[]( K const& key ) const {
		auto it=m_map.upper_bound(key);
		if(it==m_map.begin()) {
			return m_valBegin;
		} else {
			return (--it)->second;
		}
	}
};

// Many solutions we receive are incorrect. Consider using a randomized test
// to discover the cases that your implementation does not handle correctly.
// We recommend to implement a test function that tests the functionality of
// the interval_map, for example using a map of int intervals to char.


int main()
{
	// using namespace std;

	interval_map<int, char> m1{'A'};
	int one = 1,
	 five = 5, 
	 seven = 7, 
	 three = 3, 
	 two = 2, nine = 9,
	 negaative_one = -1;

	m1.assign(one, five, 'W');
	m1.assign(negaative_one, nine, 'L');
	m1.assign(three, seven, 'F');
	m1.print();
	std::cout << "----------------";


	interval_map<int, char> m2{'L'};
	// m2.assign(1, 4, 'B');
	// m2.assign(3, 5, 'A');
	m2.assign(-1, 3, 'A');
	m2.assign(0, 5, 'C');
	m2.assign(1, 2, 'C');
	m2.assign(1, 3, 'B');
	m2.assign(2, 3, 'B');
	m2.assign(-3, 2, 'D');
	m2.assign(6, 10, 'F');
	m2.assign(-7, 6, 'L');

	m2.print();
	return 0;
}