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
  /* Your code goes here */
}



// UTILITY for next questions
bool
DataFrame::check_column_name (const key_type & column_name) const
{
    /* Your code goes here */
}



// UTILITY for next questions
void
DataFrame::set_column_data (const key_type & column_name,
                            const mapped_type & column_data)
{
    /* Your code goes here */
}



// Question 2
void
DataFrame::set_column (const key_type & column_name,
                        const mapped_type & column_data)
{
    /* Your code goes here */
}



// Question 3
void
DataFrame::set_element_at (const key_type & column_name,
                            size_type index, double value)
{
    /* Your code goes here */
}



// Question 2-bis
DataFrame::mapped_type
DataFrame::get_column (const key_type & column_name) const
{
    /* Your code goes here */
}



// Question 3-bis
double
DataFrame::get_element_at (const key_type & column_name,
                           size_type index) const
{
    /* Your code goes here */
}



// Question 4
double
DataFrame::get_mean (const key_type & column_name) const
{
    /* Your code goes here */
}



// UTILITY for question 5
void
DataFrame::add_column (const key_type & column_name,
                        const mapped_type & column_data)
{
    /* Your code goes here */
}



// Question 5
DataFrame
DataFrame::select_equal (const key_type & c_name,
                          double value) const
{
    /* Your code goes here */
}
