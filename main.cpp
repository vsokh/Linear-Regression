#include <exception>
#include <vector>
#include <iostream>
#include <fstream>
#include <string_view>

class CSVRow
{
	public:
		std::string_view operator[](std::size_t index) const
		{ return std::string_view(&m_line[m_data[index] + 1], m_data[index + 1] - (m_data[index] + 1)); }

		std::size_t size() const
		{ return m_data.size() - 1; }

		void readNextRow(std::istream& str)
		{
			std::getline(str, m_line);

			m_data.clear();
			m_data.emplace_back(-1);
			std::string::size_type pos = 0;
			while ((pos = m_line.find(',', pos)) != std::string::npos)
			{
				m_data.emplace_back(pos);
				++pos;
			}
			pos = m_line.size();
			m_data.emplace_back(pos);
		}

	private:
		std::string			m_line;
		std::vector<int>	m_data;
};

std::istream& operator>>(std::istream& str, CSVRow& data)
{
	data.readNextRow(str);
	return str;
}

class CSVIterator
{
	public:
		typedef std::input_iterator_tag iterator_category;
		typedef CSVRow					value_type;
		typedef std::size_t				difference_type;
		typedef value_type*			    pointer;
		typedef value_type&			    reference;

		CSVIterator(std::istream& str)
			: m_str(str.good() ? &str : nullptr)
		{ ++(*this); }

		CSVIterator()
			: m_str(nullptr)
		{}

		CSVIterator& operator++()
		{
			if (m_str && !((*m_str) >> m_row))
			{
				m_str = nullptr;
			}
			return *this;
		}
		CSVIterator operator++(int)
		{
			CSVIterator tmp(*this);
			++(*this);
			return tmp;
		}
		const CSVRow& operator*() const
		{ return m_row; }

		const CSVRow* operator->() const
		{ return &m_row; }

		bool operator==(const CSVIterator& rhs)
		{ return (this == &rhs || (this->m_str == nullptr && rhs.m_str == nullptr)); }

		bool operator!=(const CSVIterator& rhs)
		{ return !((*this) == rhs); }

	private:
		std::istream*	m_str;
		CSVRow			m_row;
};

class CSVRange
{
	std::istream& stream;

	public:
	CSVRange(std::istream& str)
		: stream(str)
	{}

	CSVIterator begin() const
	{ return CSVIterator{stream}; }

	CSVIterator end() const
	{ return CSVIterator{}; }

};

int main(int argc, char** argv)
{
	try
	{
		std::ifstream	file("data.csv");
		for (const auto& row : CSVRange(file)
		{
			std::cout << row[1] << std::endl;
		}
	}
	catch(std::exception const& e)
	{
		std::cout << e.what() << std::endl;
	}
	return 0;
}
