#include <string>

#include "testfiles/testvector.hpp"
// #include "testfiles/testmap.hpp"
#include "testfiles/teststack.hpp"

#include "map/map.hpp"
#include <map>

template < typename Key, typename T >
void	test_insert_pos(std::map<Key,T>& orig, ft::map<Key,T>& my)
{
	orig.insert(std::make_pair("num1", 1));
	my.insert(ft::make_pair("num1", 1));
	orig.insert(std::make_pair("num2", 2));
	my.insert(ft::make_pair("num2", 2));
	orig.insert(std::make_pair("num3", 3));
	my.insert(ft::make_pair("num3", 3));

	typename std::map<Key,T>::iterator it1 = orig.begin();
	typename ft::map<Key,T>::iterator it2 = my.begin();
	++it1; ++it1;
	++it2; ++it2;
	orig.insert(it1, std::make_pair("num4", 4));
	my.insert(it2, ft::make_pair("num4", 4));

	compare_two_map("test_insert_pos", orig, my);
	orig.clear();
	my.clear();
}


template < typename Key, typename T >
void	test_insert_range(std::map<Key,T>& orig, ft::map<Key,T>& my)
{
	std::map<Key,T> tmp1;
	ft::map<Key,T> tmp2;

	tmp1.insert(std::make_pair("num1", 1));
	tmp2.insert(ft::make_pair("num1", 1));
	tmp1.insert(std::make_pair("num2", 2));
	tmp2.insert(ft::make_pair("num2", 2));
	tmp1.insert(std::make_pair("num3", 3));
	tmp2.insert(ft::make_pair("num3", 3));

	orig.insert(tmp1.begin(), tmp1.end());
	my.insert(tmp2.begin(), tmp2.end());

	compare_two_map("test_insert_range", orig, my);
	orig.clear();
	my.clear();
}

template < typename Key, typename T >
void	test_erase_by_pos(std::map<Key,T>& orig, ft::map<Key,T>& my)
{
	orig.insert(std::make_pair("num1", 1));
	my.insert(ft::make_pair("num1", 1));
	orig.insert(std::make_pair("num2", 2));
	my.insert(ft::make_pair("num2", 2));
	orig.insert(std::make_pair("num3", 3));
	my.insert(ft::make_pair("num3", 3));

	typename std::map<Key,T>::iterator it1 = orig.begin();
	typename ft::map<Key,T>::iterator it2 = my.begin();
	++it1; ++it1;
	++it2; ++it2;
	orig.erase(it1);
	my.erase(it2);

	compare_two_map("test_erase_by_pos", orig, my);
	orig.clear();
	my.clear();
}

template < typename Key, typename T >
void	test_erase_by_key(std::map<Key,T>& orig, ft::map<Key,T>& my)
{
	orig.insert(std::make_pair("num1", 1));
	my.insert(ft::make_pair("num1", 1));
	orig.insert(std::make_pair("num2", 2));
	my.insert(ft::make_pair("num2", 2));
	orig.insert(std::make_pair("num3", 3));
	my.insert(ft::make_pair("num3", 3));

	orig.erase("num1");
	my.erase("num1");

	compare_two_map("test_erase_by_key", orig, my);
	orig.clear();
	my.clear();
}


template < typename Key, typename T >
void	test_erase_by_range(std::map<Key,T>& orig, ft::map<Key,T>& my)
{
	orig.insert(std::make_pair("num1", 1));
	my.insert(ft::make_pair("num1", 1));
	orig.insert(std::make_pair("num2", 2));
	my.insert(ft::make_pair("num2", 2));
	orig.insert(std::make_pair("num3", 3));
	my.insert(ft::make_pair("num3", 3));

	typename std::map<Key,T>::iterator it1 = orig.begin();
	typename ft::map<Key,T>::iterator it2 = my.begin();
	++it1; ++it1;
	++it2; ++it2;
	orig.erase(orig.begin(), it1);
	my.erase(my.begin(), it2);

	compare_two_map("test_erase_by_range", orig, my);
	orig.clear();
	my.clear();
}


template < typename Key, typename T >
void	test_swap(std::map<Key,T>& orig, ft::map<Key,T>& my)
{
	std::map<Key,T> tmp1;
	ft::map<Key,T> tmp2;

	tmp1.insert(std::make_pair("num4", 4));
	tmp2.insert(ft::make_pair("num4", 4));
	tmp1.insert(std::make_pair("num5", 5));
	tmp2.insert(ft::make_pair("num5", 5));
	tmp1.insert(std::make_pair("num6", 6));
	tmp2.insert(ft::make_pair("num6", 6));

	orig.swap(tmp1);
	my.swap(tmp2);
	compare_two_map("test_swap", orig, my);
	orig.clear();
	my.clear();
}

template < typename Key, typename T >
void	test_clear(std::map<Key,T>& orig, ft::map<Key,T>& my)
{
	orig.clear();
	my.clear();
	compare_two_map("test_clear", orig, my);
}

int main(void)
{
	std::map<std::string, int> orig;
	ft::map<std::string, int> my;

	std::cout << "*******************************************" << std::endl;
	std::cout << "******            test map           ******" << std::endl;
	std::cout << "*******************************************" << std::endl;
	compare_ret("test_empty", orig.empty(), my.empty());

	std::pair<std::string,int>	tmp1("num1", 1);
	ft::pair<std::string,int>	tmp2("num1", 1);
	orig.insert(tmp1);
	my.insert(tmp2);
	compare_ret("test_size", orig.size(), my.size());
	orig.clear();
	my.clear();

	compare_ret("test_max_size", orig.max_size(), my.max_size());
	
	orig.insert(std::make_pair("num1", 1));
	my.insert(ft::make_pair("num1", 1));
	orig.insert(std::make_pair("num2", 2));
	my.insert(ft::make_pair("num2", 2));
	orig.insert(std::make_pair("num3", 3));
	my.insert(ft::make_pair("num3", 3));
	compare_ret("operator []", orig["num2"], my["num2"]);
	orig.clear();
	my.clear();

	orig.insert(std::make_pair("num1", 1));
	my.insert(ft::make_pair("num1", 1));
	orig.insert(std::make_pair("num2", 2));
	my.insert(ft::make_pair("num2", 2));
	orig.insert(std::make_pair("num3", 3));
	my.insert(ft::make_pair("num3", 3));
	compare_two_map("test_insert_one", orig, my);
	orig.clear();
	my.clear();

	test_insert_pos(orig, my);
	test_insert_range(orig, my);
	test_erase_by_pos(orig, my);
/////////////////////////////////////////////////////////////////////////
	// erase_by_key

	orig.insert(std::make_pair("num1", 1));
	my.insert(ft::make_pair("num1", 1));
	orig.insert(std::make_pair("num2", 2));
	my.insert(ft::make_pair("num2", 2));
	orig.insert(std::make_pair("num3", 3));
	my.insert(ft::make_pair("num3", 3));
	compare_two_map("test_erase_by_key", orig, my);
	orig.clear();
	my.clear();

/////////////////////////////////////////////////////////////////////////

	test_erase_by_range(orig, my);
	test_swap(orig, my);
	test_clear(orig, my);


	// // test_key_comp(orig, my);
	// // test_value_comp(orig, my);
	// test_find(orig, my);
	// test_count(orig, my);
	// test_lower_bound(orig, my);
	// test_upper_bound(orig, my);
	// test_equal_range(orig, my);

	// test_operators(orig, my);
	// test_nonmember_swap(orig, my);

	// test_reverse_iterator(orig, my);



	///////////check
	std::map<std::string, int>::iterator it1 = orig.begin();
	ft::map<std::string, int>::iterator it2 = my.begin();

	std::cout << "=====orig=====" << std::endl;
	for (; it1 != orig.end(); it1++)
		std::cout << it1->first << "\t" << it1->second << std::endl;
	std::cout << ">>>>>>my<<<<<<" << std::endl;
	for (; it2 != my.end(); it2++)
		std::cout << it2->first << "\t" << it2->second << std::endl;

	printf("\n");
	it1 = orig.begin();
	it2 = my.begin();
	std::cout << "=====orig=====" << std::endl;
	for (; it1 != orig.end(); it1++)
		std::cout << it1->first << "\t" << it1->second << std::endl;
	std::cout << ">>>>>>my<<<<<<" << std::endl;
	for (; it2 != my.end(); it2++)
		std::cout << it2->first << "\t" << it2->second << std::endl;
	///////////check









	// testvector();
	// testmap();
	// teststack();
	return (0);
}