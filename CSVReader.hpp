#include <vector>
#include <iostream>
#include <fstream>
#include <string_view>

class CSVRow
{
	public:
		std::string_view operator[](std::size_t index) const;
		std::size_t size() const;
		void readNextRow(std::istream& str);

	private:
		std::string			m_line;
		std::vector<int>	m_data;
};

class CSVIterator
{
	public:
		typedef std::input_iterator_tag iterator_category;
		typedef CSVRow					value_type;
		typedef std::size_t				difference_type;
		typedef value_type*			    pointer;
		typedef value_type&			    reference;

		CSVIterator(std::istream& str);
		CSVIterator();

		CSVIterator& operator++();
		CSVIterator operator++(int);

		const CSVRow& operator*() const;
		const CSVRow* operator->() const;

		bool operator==(const CSVIterator& rhs);
		bool operator!=(const CSVIterator& rhs);

	private:
		std::istream*	m_str;
		CSVRow			m_row;
};

class CSVRange
{
	std::istream& stream;

	public:
		CSVRange(std::istream& str);

		CSVIterator begin() const;
		CSVIterator end() const;
};
