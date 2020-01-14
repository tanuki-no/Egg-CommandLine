/*!
 *	\file		processor.cpp
 *	\brief		Implements command line processing
 *	\author		Vladislav "Tanuki" Mikhailikov \<vmikhailikov\@gmail.com\>
 *	\copyright	GNU GPL v3
 *	\date		14/01/2020
 *	\version	1.0
 */

#include <sstream>

#include <egg/commandline/processor.hpp>
#include <egg/commandline/utility.hpp>


namespace egg
{
namespace commandline
{

processor::processor(
    const egg::commandline::description&	theDescription,
    const  egg::commandline::options&		theOptions,
    const bool					optionsFirst)
  : _description(theDescription),
    _options(theOptions),
    _optionsFirst(optionsFirst)
{}

processor::~processor() noexcept
{}

void
processor::parse(
      const int		argc,
      const char*	argv[],
      processor::value&	the_result)
{
  // Prepare repository
  if (the_result.count("cmd"))
     the_result["cmd"].clear();

  // Copy arguments as is and refine the program name
  {
    for (auto i = 0; i < argc; ++i)
      the_result["cmd"][' '][i] = argv[i];

    std::string n(argv[0]);
    std::string::size_type st = n.find_last_of('/');
    if (st == std::string::npos)
      st = 0;
    else
      ++st;
    the_result["cmd"][' ']["name"] = n.substr(st);
  }

  // Flush value list
  _valuelist.clear();

  // Local variables
  egg::commandline::option	the_option;
  egg::variable			the_value;
  bool				options_met = false;

  // Cycle
  unsigned j = 0;
  for (auto i = 1; i < argc; ++i)
  {
    const std::string arg(argv[i]);
    the_value.reset();

    if (arg[0] == '-')
    {
      options_met = true;
      std::string::size_type eq = arg.find('=');
      std::string key(arg.substr(1));

      if (eq != std::string::npos)
      {
        key = arg.substr(1, eq - 1);
        the_value = arg.substr(eq + 1);
      }

      if (key.size() == 1)
      {
        the_option = _options.get(key[0]);
      }
      else if (arg.size() > 1 && key[0] == '-')
      {
        the_option = _options.get(key.substr(1));
      }
      else
      {
        std::string msg("Bad option \"");
        msg.append(arg);
        msg.push_back('\"');
        throw std::invalid_argument(msg);
      }

      // Get short and long options
      const char _cK = the_option.get_short();
      const std::string _sK(the_option.get_long());

      if (!the_result["cmd"].count(_cK) &&
          !the_result["cmd"].count(_sK))
      {
        if (_cK)
          the_result["cmd"]['\t'][j]["short"] = _cK;

        if (_sK.size())
          the_result["cmd"]['\t'][j]["long"] = _sK;

        ++j;
      }

      // Hold arguments
      if (the_option.has_argument() &&
          the_value.is_empty())
      {
        ++i;
        if (i < argc && argv[i][0] != '-')
        {
          the_value = argv[i];
        }
        else
        {
          std::string msg("Option \"");
          msg.append(arg);
          msg.append("\" expects the argument, separated by either space or '='");
          throw std::invalid_argument(msg);
        }
      }

      // Preprocess the data
      if (_cK)
        the_result["cmd"][_cK] = the_value;

      if (_sK.size())
        the_result["cmd"][_sK] = the_value;

      if (_cK)
        _options.assign(_cK, the_value);
      else
        _options.assign(_sK, the_value);
    }
    else if (!options_met)
    {
      _valuelist.push_back(arg);
    }
    else
    {
      std::string msg("Bad option \"");
      msg.append(arg);
      msg.push_back('\"');
      throw std::invalid_argument(msg);
    }
  }

   the_result["cmd"] = _valuelist;
}

const processor::string_list&
processor::values() const noexcept
{
  return _valuelist;
}

const egg::commandline::options&
processor::options() const noexcept
{
  return _options;
}

const std::string
processor::help()
{
  using std::endl;

  std::string stroke(utility::width(), '-');

  std::ostringstream ost;

  ost << _description.name    << " "
      << _description.version << ", "
      << _description.copyright << endl
      << stroke << endl
      << utility::format(_description.header) << endl
      << stroke << endl
      << _options.to_string()
      << stroke << endl
      << _description.trailer << endl << endl;

  return ost.str();
}

const bool
processor::found(
    const char		the_key,
    processor::value&	the_value) const noexcept
{
  return (the_value.count("cmd") &&
          the_value["cmd"].count(the_key) ? true : false);
}

const bool
processor::found(
    const std::string&	the_key,
    processor::value&	the_value) const noexcept
{
  return (the_value.count("cmd") &&
          the_value["cmd"].count(the_key) ? true : false);
}

} // End of egg::commandline namespace
} // End of egg namespace

/* End of file */
