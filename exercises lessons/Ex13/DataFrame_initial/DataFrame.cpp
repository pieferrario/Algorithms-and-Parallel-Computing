#include "DataFrame.h"

DataFrame::DataFrame (void)
  : added_first_column (false), n_rows (0) 
{}


std::vector<DataFrame::key_type>
DataFrame::split (const key_type & s,  char delim) const
{
  key_type word;
  std::vector<key_type> v;
  std::istringstream columns (s);

  while (std::getline (columns, word, delim)) v.push_back (word);

  return v;
}


void
DataFrame::print (void) const
{
  for (const value_type & element : df_data)
    {
      std::cout << element.first << " :: ";

      for (const double & d : element.second)
        std::cout << d << " ";

      std::cout << std::endl;
    }
}


// Question 1
DataFrame::DataFrame (const key_type & c_names)
  : DataFrame ()
{
    // the split function returns a vector of strings. each of them is the first element of each couple of the map.
    std::vector<key_type> columns = split(c_names, ' ');
    for (key_type const & column : columns)
    {
        // the first elem of a map is const and can't be modified. by subscripting we just create a new element.
        // duplicates are handled automatically.
        df_data[column] = {};
    }
}


// UTILITY for next questions
bool
DataFrame::check_column_name (const key_type & column_name) const
{
    // before changing a column's value, i must check that the column exists.
    if (df_data.find(column_name) == df_data.cend())
    {
        return false;
    }
    return true;
}


// UTILITY for next questions
void
DataFrame::set_column_data (const key_type & column_name,
                            const mapped_type & column_data)
{
    if (added_first_column == false) // This is a check for the first initialisation only.
    {
        added_first_column = true;
        n_rows = column_data.size();
        for (auto iterator = df_data.begin(); iterator != df_data.end(); ++iterator)
        {
            // resize changes the size of vector container after it is declared
            (iterator -> second).resize(n_rows);
        }
    }

    if (column_data.size() != n_rows) // all the columns must be equally long
    {
        std::cout << "The provided column has the wrong number of rows" << std::endl;
        return;
    }
    df_data[column_name] = column_data;
}

// Question 2
void
DataFrame::set_column (const key_type & column_name,
                        const mapped_type & column_data)
{
    if (! check_column_name(column_name))
    {
        std::cout << "The provided column does not exist" << std::endl;
        return;
    }

    // we rely on the auxiliary function
    set_column_data(column_name, column_data);
}


// Question 3
void
DataFrame::set_element_at (const key_type & column_name,
                            size_type index, double value)
{
    if (! check_column_name(column_name))
    {
        std::cout << "The provided column does not exist" << std::endl;
        return;
    }
    if (index >= df_data.at(column_name).size()) // if we are out of index we must return early.
    {
        std::cout << "The provided index does not exist" << std::endl;
        return;
    }
    df_data[column_name][index] = value;
}


// Question 2-bis
DataFrame::mapped_type
DataFrame::get_column (const key_type & column_name) const
{
    if (! check_column_name(column_name))
    {
        std::cout << "The provided column does not exist" << std::endl;
        return {};
    }

    return df_data.at(column_name);
}


// Question 3-bis
double
DataFrame::get_element_at (const key_type & column_name,
                           size_type index) const
{
    if (! check_column_name(column_name))
    {
        std::cout << "The provided column does not exist" << std::endl;
        return std::numeric_limits<double>::quiet_NaN();
    }
    if (index >= df_data.at(column_name).size())
    {
        std::cout << "The provided index does not exist" << std::endl;
        return std::numeric_limits<double>::quiet_NaN();
    }
    return df_data.at(column_name)[index];
}


// Question 4
double
DataFrame::get_mean (const key_type & column_name) const
{
    if (! check_column_name(column_name))
    {
        std::cout << "The provided column does not exist" << std::endl;
        return std::numeric_limits<double>::quiet_NaN();
    }

    const mapped_type & column = df_data.at(column_name); // we work on a reference to df_data(column_name) for readability
    if (column.empty())
    {
        return std::numeric_limits<double>::quiet_NaN();
    }

    double sum = 0.0;
    for (size_type idx = 0; idx < column.size(); ++idx)
    {
        sum += column[idx];
    }
    return sum / column.size();
}


// UTILITY for question 5
void
DataFrame::add_column (const key_type & column_name,
                        const mapped_type & column_data)
{
    if (check_column_name(column_name))
    {
        std::cout << "The provided column already exists" << std::endl;
        return;
    }
    set_column_data(column_name, column_data);
}


// Question 5
DataFrame
DataFrame::select_equal (const key_type & c_name,
                          double value) const
{
    // we create with the default constructor the df
    DataFrame df_new;

    // we check if the column exists
    if (! check_column_name(c_name))
    {
        std::cout << "The provided column does not exist" << std::endl;
        return df_new;
    }

    // we store the indices in an auxiliary vector
    std::vector<size_type> indices = {};
    const mapped_type & selected_column = df_data.at(c_name);
    for (size_type idx = 0; idx < selected_column.size(); ++idx)
    {
        if (selected_column[idx] == value)
        {
            indices.push_back(idx);
        }
    }

    for (const auto & column: df_data)
    {
        mapped_type filtered = {};
        for (const auto & idx : indices)
        {
            filtered.push_back(column.second[idx]);
        }
        df_new.add_column(column.first, filtered);
    }
    return df_new;
}