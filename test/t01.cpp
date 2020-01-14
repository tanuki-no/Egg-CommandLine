#include <iostream>
#include <system_error>

#include "../include/egg/commandline/processor.hpp"

void
dump(
    egg::registry::value::const_iterator start,
    egg::registry::value::const_iterator end,
    int level)
{
  using std::cout;
  using std::endl;

  for (auto i  = start; i != end; ++i)
  {
    for (auto l = 0; l < level; ++l)
        cout << "  ";

    cout << "d[" << i->first.to_string() << "] = "
         << i->second.to_string() << endl;

    if (i->second.size())
      dump(
        (*i).second.begin(),
        (*i).second.end(),
        level + 1);
  }
}

void
test(
    egg::commandline::processor& cmd,
    const int         argc,
    const char*       argv[],
    egg::registry::value& v)
{
  try
  {
    cmd.parse(argc, argv, v);
  }
  catch (const std::exception& e)
  {
    std::cout << e.what() << std::endl;
  }
}

void
test(
  const int   argc,
  const char* argv[],
  egg::commandline::options& op,
  egg::registry::value& reg)
{
  egg::commandline::option _option;
  egg::variable _value;
  std::vector<std::string> vs;
  bool _options_met = false;

  if (reg.count("cmd"))
    reg["cmd"].clear();

  for (auto i = 1; i < argc; ++i)
  {
    std::cout << "Step " << i << ". ";
    const std::string arg(argv[i]);
    _value.reset();

    if (arg[0] == '-')
    {
      _options_met = true;
      std::string::size_type eq = arg.find('=');
      std::string key(arg.substr(1));

      std::cout << "Option: ";

      if (eq != std::string::npos)
      {
        key = arg.substr(1, eq - 1);
        _value = arg.substr(eq + 1);
      }

      if (key.size() == 1)
      {
        _option = op.get(key[0]);
        std::cout << key[0];
      }
      else if (arg.size() > 1 && key[0] == '-')
      {
	_option = op.get(key.substr(1));
        std::cout << key.substr(1);
      }
      else
      {
        std::string msg("Bad option \"");
	msg.append(arg);
	msg.push_back('\"');
	throw std::invalid_argument(msg);
      }

      // Hold arguments
      if (_option.has_argument())
      {
        if (_value.is_empty())
	{
	  ++i;
	  if (i < argc && argv[i][0] != '-')
	  {
	    _value = argv[i];
	  }
	  else
	  {
            std::string msg("Option \"");
	    msg.append(arg);
	    msg.append("\" expects the argument, separated by either space or '='");
	    throw std::invalid_argument(msg);
	  }
	}
    
        std::cout << ", value: " << _value;
      }

      // Preprocess the data
      const char _cK = _option.get_short();
      if (_cK)
        reg["cmd"][_cK] = _value;

      const std::string _sK(_option.get_long());
      if (_sK.size())
        reg["cmd"][_sK] = _value;

      if (_cK)
        op.assign(_cK, _value);
      else
        op.assign(_sK, _value);
    }
    else if (!_options_met)
    {
      vs.push_back(arg);
      std::cout << "Not an option: " << arg;
    }
    else
    {
      std::string msg("Bad option \"");
      msg.append(arg);
      msg.push_back('\"');
      throw std::invalid_argument(msg);
    }

    std::cout << std::endl;
  }

   reg["cmd"] = vs;
}

int
main(
  const int   argc,
  const char* argv[])
{
  using std::cout;
  using std::endl;
  using std::cerr;

  cout << "Checking various internals" << endl;
  cout << "---------------------------------------------------------" << endl;
  {
    if (argc > 1)
    {
      for (auto i = 0; i < argc; ++i)
        cout << ">> " << argv[i] << endl;
    }

    const std::string x("--version=\"Some string\"");
    auto eq = x.find('=');
    cout << '[' << x.substr(2, eq - 2) << "] ["
         << x.substr(eq + 1) << ']' << endl;

    const std::string y("--version=Some string");
    eq = x.find('=');
    cout << '[' << y.substr(2, eq - 2) << "] ["
         << y.substr(eq + 1) << ']' << endl;
  }
  cout  << "---------------------------------------------------------" << endl
        << "Done." << endl << endl;

  cout << "Checking command line processing" << endl;
  cout << "---------------------------------------------------------" << endl;
  {
    egg::commandline::description ds(
          "Sample name",
          "1.0.0-patch-0",
          "Some company, 2017",
"This is the typical description of the \"Sample name\" software produced by \"Some company\".\
And a lot of letters now: ajhfkajsd asdjklfh sadkljh asdfjkhsd aklsjfh sljksfh s jksdfh skljsdh\
sajdfhasjkdfh  askdjfh asdkljfh sdf jklh sadkljfh jklashdf kjhsdfkjljkl  lasdkl jh sdjkl jh asdjf",
          "This is the typical trailer.");

    egg::commandline::options op;

    std::string path("/etc/phoenix/controller.xml");

    std::int8_t   Int8 = 8;
    std::uint8_t  UInt8 = 8;
    std::int16_t  Int16 = 16;
    std::uint16_t UInt16 = 16;
    std::int32_t  Int32 = 32;
    std::uint32_t UInt32 = 32;
    std::int64_t  Int64 = 64;
    std::uint64_t UInt64 = 64;

    float         Float = 3.14;
    double        Double = 6.18;
    long double   LongDouble = 11.1111;

    op('h',
       "help",
       "Display help information on command line arguments")
      ('v',
       "version",
       "Display version")
      ('d',
       "daemon",
       "Run application as a daemon")
      ('t',
       "trace",
       "Enable tracing")
      ('c',
       "configuration",
       "Set configuration file to use",
       path)
      ('V',
       "validate",
       "Validate configuration file (don't run the service, only check configuration and reports the error found)")
      (0,
       "i8",
       "Test int 8",
       Int8)
      (0,
       "ui8",
       "Test unsigned int 8",
       UInt8)
      (0,
       "i16",
       "Test int 16",
       Int16)
      (0,
       "ui16",
       "Test unsigned int 16",
       UInt16)
      (0,
       "i32",
       "Test int 32",
       Int32)
      (0,
       "ui32",
       "Test unsigned int 32",
       UInt32)
      (0,
       "i64",
       "Test int 64",
       Int64)
      (0,
       "ui64",
       "Test unsigned int 64",
       UInt64)
      (0,
       "float",
       "Test float",
       Float)
      (0,
       "double",
       "Test double",
       Double)
      (0,
       "long-double",
       "Test long double",
       LongDouble)
    ;

    egg::registry::value _reg;

    try
    {
      const char* a[] = { "some prog name", "-v", "--version" };
      test(sizeof(a)/sizeof(const char *), a, op, _reg);
    }
    catch (const std::exception& e)
    {
      std::cerr << e.what() << endl;
    }

    cout << endl;
    dump(_reg.begin(), _reg.end(), 0);
    cout << endl;
    cout << op.to_string() << endl
         << "---------------------------------------------------------" << endl;

    try
    {
      const char* a[] = 
      { 
        "some prog name",
	"-h",
	"--help",
	"--configuration=/etc/config.xml",
	"-c=/etc/config.xml"
      };
      test(sizeof(a)/sizeof(const char *), a, op, _reg);
    }
    catch (const std::exception& e)
    {
      std::cerr << e.what() << endl;
    }

    cout << endl;
    dump(_reg.begin(), _reg.end(), 0);
    cout << endl;
    cout << op.to_string() << endl
         << "---------------------------------------------------------" << endl;

    try
    {
      const char* a[] = 
      { 
        "some prog name",
	"--configuration",
	"/etc/config.xml",
	"-c",
	"/etc/config.xml",
	"--long-double=3.14"
      };
      test(sizeof(a)/sizeof(const char *), a, op, _reg);
    }
    catch (const std::exception& e)
    {
      std::cerr << e.what() << endl;
    }

    cout << endl;
    dump(_reg.begin(), _reg.end(), 0);
    cout << endl;
    cout << op.to_string() << endl
         << "---------------------------------------------------------" << endl;

    try
    {
      const char* a[] = 
      { 
        "some prog name",
	"one",
	"two",
	"three",
	"--configuration",
	"/etc/config.xml",
	"-c",
	"/etc/config.xml",
	"--long-double=3.14"
      };
      test(sizeof(a)/sizeof(const char *), a, op, _reg);
    }
    catch (const std::exception& e)
    {
      std::cerr << e.what() << endl;
    }

    cout << endl;
    dump(_reg.begin(), _reg.end(), 0);
    cout << endl;
    cout << op.to_string() << endl
         << "---------------------------------------------------------" << endl;

    try
    {
      const char* a[] = 
      { 
        "some prog name",
	"one",
	"two",
	"three",
	"--configuration",
	"/etc/config.xml",
	"four",
	"-c",
	"/etc/config.xml",
	"--long-double=3.14"
      };
      test(sizeof(a)/sizeof(const char *), a, op, _reg);
    }
    catch (const std::exception& e)
    {
      std::cerr << e.what() << endl;
    }

    cout << endl;
    dump(_reg.begin(), _reg.end(), 0);
    cout << endl;
    cout << op.to_string() << endl
         << "---------------------------------------------------------" << endl;

    // Now check the command line
    egg::commandline::processor cmd(ds, op, false);
    std::cout << cmd.help();


    {
      const char* a[] =
      {
        "some prog name",
        "-v",
        "--version"
      };
      test(cmd, sizeof(a)/sizeof(const char *), a, _reg);
      cout << endl;
      dump(_reg.begin(), _reg.end(), 0);
      cout << endl;
    }

    {
      const char* a[] =
      {
        "some prog name",
        "--configuration",
        "/etc/config.xml",
        "-c",
        "/etc/config.xml",
        "--long-double=3.14"
      };
      test(cmd, sizeof(a)/sizeof(const char *), a, _reg);
      cout << endl;
      dump(_reg.begin(), _reg.end(), 0);
      cout << endl;
    }

    {
      const char* a[] =
      {
        "some prog name",
        "one",
        "two",
        "three",
        "--configuration",
        "/etc/config.xml",
        "-c",
        "/etc/config.xml",
        "--long-double=3.14"
      };
      test(cmd, sizeof(a)/sizeof(const char *), a, _reg);
      cout << endl;
      dump(_reg.begin(), _reg.end(), 0);
      cout << endl;
    }

    {
      const char* a[] =
      {
        argv[0],
        "one",
        "two",
        "three",
        "--configuration",
        "/etc/config.xml",
        "four",
        "-c",
        "/etc/config.xml",
        "--long-double=3.14"
      };
      test(cmd, sizeof(a)/sizeof(const char *), a, _reg);
      cout << endl;
      dump(_reg.begin(), _reg.end(), 0);
      cout << endl;
    }
  }
  cout  << "---------------------------------------------------------" << endl
        << "Done." << endl << endl;

  return 0;
}
