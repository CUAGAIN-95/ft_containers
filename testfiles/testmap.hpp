#ifndef TESTMAP_HPP
# define TESTMAP_HPP

# include "test.hpp"

template < class Ret >
void	compare_ret(const std::string func_name, const Ret orig, const Ret my);

template < typename Key, typename T >
void	test_empty(std::map<Key,T>& orig, ft::map<Key,T>& my)
{
	compare_ret("test_empty", orig.empty(), my.empty());
}

template < typename Key, typename T >
void	test_size(std::map<Key,T>& orig, ft::map<Key,T>& my)
{
	std::pair<std::string,int>	tmp1("num1", 1);
	ft::pair<std::string,int>	tmp2("num1", 1);
	orig.insert(tmp1);
	my.insert(tmp2);
	compare_ret("test_size", orig.size(), my.size());
	orig.clear();
	my.clear();
}

template < typename Key, typename T >
void	test_max_size(std::map<Key,T>& orig, ft::map<Key,T>& my)
{
	compare_ret("test_max_size", orig.max_size(), my.max_size());
}

template < typename Key, typename T >
void	test_index_operator(std::map<Key,T>& orig, ft::map<Key,T>& my)
{
	orig.insert(std::make_pair("num1", 1));
	my.insert(ft::make_pair("num1", 1));
	orig.insert(std::make_pair("num2", 2));
	my.insert(ft::make_pair("num2", 2));
	orig.insert(std::make_pair("num3", 3));
	my.insert(ft::make_pair("num3", 3));

	compare_ret("operator []", orig["num2"], my["num2"]);
	orig.clear();
	my.clear();
}

template < typename Key, typename T >
void	test_insert_one(std::map<Key,T>& orig, ft::map<Key,T>& my)
{
	orig.insert(std::make_pair("num1", 1));
	my.insert(ft::make_pair("num1", 1));
	orig.insert(std::make_pair("num2", 2));
	my.insert(ft::make_pair("num2", 2));
	orig.insert(std::make_pair("num3", 3));
	my.insert(ft::make_pair("num3", 3));

	compare_two_map("test_insert_one", orig, my);
	orig.clear();
	my.clear();
}

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
	compare_two_map("test_swap", orig, my);
}

// template < typename Key, typename T >
// void	test_key_comp(std::map<Key,T>& orig, ft::map<Key,T>& my)
// {

// }

template < typename Key, typename T >
void	test_find(std::map<Key,T>& orig, ft::map<Key,T>& my)
{
	orig.insert(std::make_pair("num1", 1));
	my.insert(ft::make_pair("num1", 1));
	orig.insert(std::make_pair("num2", 2));
	my.insert(ft::make_pair("num2", 2));
	orig.insert(std::make_pair("num3", 3));
	my.insert(ft::make_pair("num3", 3));

	typename std::map<Key,T>::iterator it1 = orig.find("num2");
	typename ft::map<Key,T>::iterator it2 = my.find("num2");
	compare_ret("test_find", it1->second, it2->second);
	orig.clear();
	my.clear();
}

template < typename Key, typename T >
void	test_count(std::map<Key,T>& orig, ft::map<Key,T>& my)
{
	orig.insert(std::make_pair("num1", 1));
	my.insert(ft::make_pair("num1", 1));
	orig.insert(std::make_pair("num2", 2));
	my.insert(ft::make_pair("num2", 2));
	orig.insert(std::make_pair("num3", 3));
	my.insert(ft::make_pair("num3", 3));

	compare_ret("test_count", orig.count("num4"), my.count("num4"));
	orig.clear();
	my.clear();
}

template < typename Key, typename T >
void	test_lower_bound(std::map<Key,T>& orig, ft::map<Key,T>& my)
{
	orig.insert(std::make_pair("num1", 1));
	my.insert(ft::make_pair("num1", 1));
	orig.insert(std::make_pair("num2", 2));
	my.insert(ft::make_pair("num2", 2));
	orig.insert(std::make_pair("num3", 3));
	my.insert(ft::make_pair("num3", 3));
	orig.insert(std::make_pair("num4", 4));
	my.insert(ft::make_pair("num4", 4));
	orig.insert(std::make_pair("num5", 5));
	my.insert(ft::make_pair("num5", 5));
	orig.insert(std::make_pair("num6", 6));
	my.insert(ft::make_pair("num6", 6));

	typename std::map<Key,T>::iterator it1 = orig.lower_bound("num4");
	typename ft::map<Key,T>::iterator it2 = my.lower_bound("num4");

	compare_ret("test_lower_bound", it1->first, it2->first);
	orig.clear();
	my.clear();
}

template < typename Key, typename T >
void	test_upper_bound(std::map<Key,T>& orig, ft::map<Key,T>& my)
{
	orig.insert(std::make_pair("num1", 1));
	my.insert(ft::make_pair("num1", 1));
	orig.insert(std::make_pair("num2", 2));
	my.insert(ft::make_pair("num2", 2));
	orig.insert(std::make_pair("num3", 3));
	my.insert(ft::make_pair("num3", 3));
	orig.insert(std::make_pair("num4", 4));
	my.insert(ft::make_pair("num4", 4));
	orig.insert(std::make_pair("num5", 5));
	my.insert(ft::make_pair("num5", 5));
	orig.insert(std::make_pair("num6", 6));
	my.insert(ft::make_pair("num6", 6));

	typename std::map<Key,T>::iterator it1 = orig.upper_bound("num4");
	typename ft::map<Key,T>::iterator it2 = my.upper_bound("num4");

	compare_ret("test_upper_bound", it1->first, it2->first);
	orig.clear();
	my.clear();
}

template < typename Key, typename T >
void	test_equal_range(std::map<Key,T>& orig, ft::map<Key,T>& my)
{
	orig.insert(std::make_pair("num1", 1));
	my.insert(ft::make_pair("num1", 1));
	orig.insert(std::make_pair("num2", 2));
	my.insert(ft::make_pair("num2", 2));
	orig.insert(std::make_pair("num3", 3));
	my.insert(ft::make_pair("num3", 3));
	orig.insert(std::make_pair("num4", 4));
	my.insert(ft::make_pair("num4", 4));
	orig.insert(std::make_pair("num5", 5));
	my.insert(ft::make_pair("num5", 5));
	orig.insert(std::make_pair("num6", 6));
	my.insert(ft::make_pair("num6", 6));

	typedef typename std::map<Key,T>::iterator orig_iter;
	typedef typename ft::map<Key,T>::iterator my_iter;
	std::pair<orig_iter,orig_iter> p1 = orig.equal_range("num4");
	ft::pair<my_iter,my_iter> p2 = my.equal_range("num4");

	std::cout.width(42);
	std::cout << "test_equal_range" << " >> ";
	if ((p1.first->first != p2.first->first) || (p1.second->first != p2.second->first))
		std::cout << "diff" << std::endl;
	else
		std::cout << "same" << std::endl;
	orig.clear();
	my.clear();
}

template < typename Key, typename T >
void	test_operators(std::map<Key,T>& orig, ft::map<Key,T>& my)
{
	std::map<Key,T> tmp1;
	ft::map<Key,T> tmp2;

	tmp1.insert(std::make_pair("num1", 1));
	tmp2.insert(ft::make_pair("num1", 1));
	tmp1.insert(std::make_pair("num2", 2));
	tmp2.insert(ft::make_pair("num2", 2));
	tmp1.insert(std::make_pair("num3", 3));
	tmp2.insert(ft::make_pair("num3", 3));
	tmp1.insert(std::make_pair("num4", 4));
	tmp2.insert(ft::make_pair("num4", 4));

	orig.insert(std::make_pair("num1", 1));
	my.insert(ft::make_pair("num1", 1));
	orig.insert(std::make_pair("num2", 2));
	my.insert(ft::make_pair("num2", 2));
	orig.insert(std::make_pair("num3", 3));
	my.insert(ft::make_pair("num3", 3));
	orig.insert(std::make_pair("num4", 4));
	my.insert(ft::make_pair("num4", 4));
	
	compare_ret("operator == ", orig == tmp1, my == tmp2);
	compare_ret("operator != ", orig != tmp1, my != tmp2);
	
	orig.erase(orig.begin());
	my.erase(my.begin());

	compare_ret("operator < ", orig < tmp1, my < tmp2);
	compare_ret("operator > ", orig > tmp1, my > tmp2);
	compare_ret("operator <= ", orig <= tmp1, my <= tmp2);
	compare_ret("operator >= ", orig >= tmp1, my >= tmp2);
	orig.clear();
	my.clear();
}


template < typename Key, typename T >
void	test_nonmember_swap(std::map<Key,T>& orig, ft::map<Key,T>& my)
{
	std::map<Key,T> tmp1;
	ft::map<Key,T> tmp2;

	tmp1.insert(std::make_pair("num1", 1));
	tmp2.insert(ft::make_pair("num1", 1));
	tmp1.insert(std::make_pair("num2", 2));
	tmp2.insert(ft::make_pair("num2", 2));
	tmp1.insert(std::make_pair("num3", 3));
	tmp2.insert(ft::make_pair("num3", 3));
	tmp1.insert(std::make_pair("num4", 4));
	tmp2.insert(ft::make_pair("num4", 4));

	std::swap(orig, tmp1);
	std::swap(my, tmp2);
	compare_two_map("test_nonmember_swap", orig, my);
	orig.clear();
	my.clear();
}

template < typename Key, typename T >
void	test_reverse_iterator(std::map<Key,T>& orig, ft::map<Key,T>& my)
{
	orig.insert(std::make_pair("num1", 1));
	my.insert(ft::make_pair("num1", 1));
	orig.insert(std::make_pair("num2", 2));
	my.insert(ft::make_pair("num2", 2));
	orig.insert(std::make_pair("num3", 3));
	my.insert(ft::make_pair("num3", 3));
	orig.insert(std::make_pair("num4", 4));
	my.insert(ft::make_pair("num4", 4));
	std::cout.width(42);
	std::cout << "test_reverse_iterator" << " >> " << std::endl;
	std::cout.width(42);
	std::cout << "orig map:\t";
	for (typename std::map<Key,T>::reverse_iterator rit = orig.rbegin(); rit != orig.rend(); ++rit)
		std::cout << "(" << rit->first << "," << rit->second << ") ";
	std::cout << std::endl;
	std::cout.width(42);
		std::cout << "my map:\t";
	for (typename ft::map<Key,T>::reverse_iterator rit = my.rbegin(); rit != my.rend(); ++rit)
		std::cout << "(" << rit->first << "," << rit->second << ") ";
	std::cout << std::endl;
}

void	testmap()
{
	std::cout << "*******************************************" << std::endl;
	std::cout << "******            test map           ******" << std::endl;
	std::cout << "*******************************************" << std::endl;
	std::map<std::string, int> orig;
	ft::map<std::string, int> my;

	test_empty(orig, my);
	test_size(orig, my);
	test_max_size(orig, my);
	test_index_operator(orig, my);
	test_insert_one(orig, my);
	test_insert_pos(orig, my);
	test_insert_range(orig, my);
	test_erase_by_pos(orig, my);
	test_erase_by_key(orig, my);
	test_erase_by_range(orig, my);
	test_swap(orig, my);
	test_clear(orig, my);
	// test_key_comp(orig, my);
	// test_value_comp(orig, my);
	test_find(orig, my);
	test_count(orig, my);
	test_lower_bound(orig, my);
	test_upper_bound(orig, my);
	test_equal_range(orig, my);

	test_operators(orig, my);
	test_nonmember_swap(orig, my);

	test_reverse_iterator(orig, my);
}

#endif